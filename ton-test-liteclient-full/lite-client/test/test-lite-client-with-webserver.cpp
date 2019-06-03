#include "adnl/adnl-ext-client.h"
#include "adnl/tl-utils.hpp"
#include "auto/tl/ton_api_json.h"
#include "td/utils/OptionsParser.h"
#include "td/utils/Time.h"
#include "td/utils/filesystem.h"
#include "td/utils/format.h"
#include "td/utils/Random.h"
#include "td/utils/crypto.h"
#include "td/utils/port/signals.h"
#include "td/utils/port/FileFd.h"
#include "terminal/terminal.h"
#include "ton/ton-tl.hpp"
#include "block/block-db.h"
#include "block/block.h"
#include "block/block-auto.h"
#include "block/mc-config.h"
#include "vm/boc.h"
#include "vm/cellops.h"
#include "vm/cells/MerkleProof.h"
#include "ton/ton-shard.h"

#if TD_DARWIN || TD_LINUX
#include <unistd.h>
#include <fcntl.h>
#endif
#include <iostream>
#include <sstream>

#include "web_server/server_http.hpp"
#include "web_server/lite-client-test-node.cpp"
#include "web_server/lite-client-test-node-helpers.cpp"
#include "web_server/lite-client-web-server.cpp"
#include "web_server/include/method-time.cpp"
#include "web_server/include/method-getaccount.cpp"
#include "web_server/include/method-getblock.cpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using td::Ref;

int verbosity;

template <std::size_t size>
std::ostream& operator<<(std::ostream& stream, const td::UInt<size>& x) {
  for (size_t i = 0; i < size / 8; i++) {
    stream << td::format::hex_digit((x.raw[i] >> 4) & 15) << td::format::hex_digit(x.raw[i] & 15);
  }

  return stream;
}

std::unique_ptr<ton::AdnlExtClient::Callback> TestNode::make_callback() {
  class Callback : public ton::AdnlExtClient::Callback {
   public:
    void on_ready() override {
      td::actor::send_closure(id_, &TestNode::conn_ready);
    }
    void on_stop_ready() override {
      td::actor::send_closure(id_, &TestNode::conn_closed);
    }
    Callback(td::actor::ActorId<TestNode> id) : id_(std::move(id)) {
    }

   private:
    td::actor::ActorId<TestNode> id_;
  };
  return std::make_unique<Callback>(actor_id(this));
}

void TestNode::run() {
  class Cb : public td::TerminalIO::Callback {
   public:
    void line_cb(td::BufferSlice line) override {
      td::actor::send_closure(id_, &TestNode::parse_line, std::move(line));
    }
    Cb(td::actor::ActorId<TestNode> id) : id_(id) {
    }

   private:
    td::actor::ActorId<TestNode> id_;
  };
  io_ = td::TerminalIO::create("> ", readline_enabled_, std::make_unique<Cb>(actor_id(this)));
  td::actor::send_closure(io_, &td::TerminalIO::set_log_interface);

  auto G = td::read_file(global_config_).move_as_ok();
  auto gc_j = td::json_decode(G.as_slice()).move_as_ok();
  ton::ton_api::config_global gc;
  ton::ton_api::from_json(gc, gc_j.get_object()).ensure();

  CHECK(gc.liteclients_.size() > 0);
  auto idx =
      liteserver_idx_ >= 0 ? liteserver_idx_ : td::Random::fast(0, static_cast<td::uint32>(gc.liteclients_.size() - 1));
  CHECK(idx >= 0 && static_cast<td::uint32>(idx) <= gc.liteclients_.size());
  auto& cli = gc.liteclients_[idx];
  td::IPAddress addr;
  addr.init_host_port(td::IPAddress::ipv4_to_str(cli->ip_), cli->port_).ensure();
  td::TerminalIO::out() << "using liteserver " << idx << " with addr " << addr << "\n";

  client_ = ton::AdnlExtClient::create(ton::AdnlNodeIdFull{cli->id_}, addr, make_callback());
}

bool TestNode::envelope_send_query(td::BufferSlice query, td::Promise<td::BufferSlice> promise) {
  if (!ready_ || client_.empty()) {
    LOG(ERROR) << "failed to send query to server: not ready";
    return false;
  }
  auto P = td::PromiseCreator::lambda([promise = std::move(promise)](td::Result<td::BufferSlice> R) mutable {
    if (R.is_error()) {
      auto err = R.move_as_error();
      LOG(ERROR) << "failed query: " << err;
      promise.set_error(std::move(err));
      return;
    }
    auto data = R.move_as_ok();
    auto F = ton::fetch_tl_object<ton::ton_api::liteServer_error>(data.clone(), true);
    if (F.is_ok()) {
      auto f = F.move_as_ok();
      auto err = td::Status::Error(f->code_, f->message_);
      LOG(ERROR) << "received error: " << err;
      promise.set_error(std::move(err));
      return;
    }
    promise.set_result(std::move(data));
  });
  td::BufferSlice b =
      ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_query>(std::move(query)), true);
  td::actor::send_closure(client_, &ton::AdnlExtClient::send_query, "query", std::move(b), td::Timestamp::in(10.0),
                          std::move(P));
  return true;
}

bool TestNode::register_blkid(const ton::BlockIdExt& blkid) {
  for (const auto& id : known_blk_ids_) {
    if (id == blkid) {
      return false;
    }
  }
  known_blk_ids_.push_back(blkid);
  return true;
}

bool TestNode::show_new_blkids(bool all) {
  if (all) {
    shown_blk_ids_ = 0;
  }
  int cnt = 0;
  while (shown_blk_ids_ < known_blk_ids_.size()) {
    td::TerminalIO::out() << "BLK#" << shown_blk_ids_ + 1 << " = " << known_blk_ids_[shown_blk_ids_].to_str()
                          << std::endl;
    ++shown_blk_ids_;
    ++cnt;
  }
  return cnt;
}

bool TestNode::complete_blkid(ton::BlockId partial_blkid, ton::BlockIdExt& complete_blkid) const {
  auto n = known_blk_ids_.size();
  while (n) {
    --n;
    if (known_blk_ids_[n].id == partial_blkid) {
      complete_blkid = known_blk_ids_[n];
      return true;
    }
  }
  return false;
}

bool TestNode::get_server_time() {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getTime>(), true);
  return envelope_send_query(std::move(b), [&, Self = actor_id(this) ](td::Result<td::BufferSlice> res)->void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot get server time";
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_currentTime>(res.move_as_ok(), true);
      if (F.is_error()) {
        LOG(ERROR) << "cannot parse answer to liteServer.getTime";
      } else {
        server_time_ = F.move_as_ok()->now_;
        server_time_got_at_ = static_cast<td::uint32>(td::Clocks::system());
        LOG(INFO) << "server time is " << server_time_;
      }
    }
  });
}

bool TestNode::get_server_mc_block_id() {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getMasterchainInfo>(), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this)](td::Result<td::BufferSlice> res)->void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot get masterchain info from server";
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_masterchainInfo>(res.move_as_ok(), true);
      if (F.is_error()) {
        LOG(ERROR) << "cannot parse answer to liteServer.getMasterchainInfo";
      } else {
        auto f = F.move_as_ok();
        auto blk_id = create_block_id(f->last_);
        auto zstate_id = create_zero_state_id(f->init_);
        LOG(INFO) << "last masterchain block is " << blk_id.to_str();
        td::actor::send_closure_later(Self, &TestNode::got_server_mc_block_id, blk_id, zstate_id);
      }
    }
  });
}

void TestNode::got_server_mc_block_id(ton::BlockIdExt blkid, ton::ZeroStateIdExt zstateid) {
  if (!zstate_id_.is_valid()) {
    zstate_id_ = zstateid;
    LOG(INFO) << "zerostate id set to " << zstate_id_.to_str();
  } else if (zstate_id_ != zstateid) {
    LOG(ERROR) << "fatal: masterchain zero state id suddenly changed: expected " << zstate_id_.to_str() << ", found "
               << zstateid.to_str();
    stop();
    return;
  }
  register_blkid(blkid);
  //register_blkid(zstateid);
  if (!mc_last_id_.is_valid()) {
    mc_last_id_ = blkid;
    request_block(blkid);
    // request_state(blkid);
  } else if (mc_last_id_.id.seqno < blkid.id.seqno) {
    mc_last_id_ = blkid;
  }
}

bool TestNode::request_block(ton::BlockIdExt blkid) {
  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::ton_api::liteServer_getBlock>(ton::create_tl_block_id(blkid)), true);
  return envelope_send_query(std::move(b), [ Self = actor_id(this), blkid ](td::Result<td::BufferSlice> res)->void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot obtain block " << blkid.to_str() << " from server";
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_blockData>(res.move_as_ok(), true);
      if (F.is_error()) {
        LOG(ERROR) << "cannot parse answer to liteServer.getBlock";
      } else {
        auto f = F.move_as_ok();
        auto blk_id = ton::create_block_id(f->id_);
        LOG(INFO) << "obtained block " << blk_id.to_str() << " from server";
        if (blk_id != blkid) {
          LOG(ERROR) << "block id mismatch: expected data for block " << blkid.to_str() << ", obtained for "
                     << blk_id.to_str();
        }
        td::actor::send_closure_later(Self, &TestNode::got_mc_block, blk_id, std::move(f->data_));
      }
    }
  });
}

bool TestNode::request_state(ton::BlockIdExt blkid) {
  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::ton_api::liteServer_getState>(ton::create_tl_block_id(blkid)), true);
  return envelope_send_query(std::move(b), [ Self = actor_id(this), blkid ](td::Result<td::BufferSlice> res)->void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot obtain state " << blkid.to_str() << " from server";
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_blockState>(res.move_as_ok(), true);
      if (F.is_error()) {
        LOG(ERROR) << "cannot parse answer to liteServer.getState";
      } else {
        auto f = F.move_as_ok();
        auto blk_id = ton::create_block_id(f->id_);
        LOG(INFO) << "obtained state " << blk_id.to_str() << " from server";
        if (blk_id != blkid) {
          LOG(ERROR) << "block id mismatch: expected state for block " << blkid.to_str() << ", obtained for "
                     << blk_id.to_str();
        }
        td::actor::send_closure_later(Self, &TestNode::got_mc_state, blk_id, ton::UInt256_2_Bits256(f->root_hash_),
                                      ton::UInt256_2_Bits256(f->file_hash_), std::move(f->data_));
      }
    }
  });
}

void TestNode::got_mc_block(ton::BlockIdExt blkid, td::BufferSlice data) {
  LOG(INFO) << "obtained " << data.size() << " data bytes for block " << blkid.to_str();
  ton::FileHash fhash;
  td::sha256(data.as_slice(), fhash.as_slice());
  if (fhash != blkid.file_hash) {
    LOG(ERROR) << "file hash mismatch for block " << blkid.to_str() << ": expected " << blkid.file_hash.to_hex()
               << ", computed " << fhash.to_hex();
    return;
  }
  register_blkid(blkid);
  last_block_id_ = blkid;
  last_block_data_ = data.clone();
  if (!db_root_.empty()) {
    auto res = save_db_file(fhash, std::move(data));
    if (res.is_error()) {
      LOG(ERROR) << "error saving block file: " << res.to_string();
    }
  }
  show_new_blkids();
}

void TestNode::got_mc_state(ton::BlockIdExt blkid, ton::RootHash root_hash, ton::FileHash file_hash,
                            td::BufferSlice data) {
  LOG(INFO) << "obtained " << data.size() << " state bytes for block " << blkid.to_str();
  ton::FileHash fhash;
  td::sha256(data.as_slice(), fhash.as_slice());
  if (fhash != file_hash) {
    LOG(ERROR) << "file hash mismatch for state " << blkid.to_str() << ": expected " << file_hash.to_hex()
               << ", computed " << fhash.to_hex();
    return;
  }
  register_blkid(blkid);
  last_state_id_ = blkid;
  last_state_data_ = data.clone();
  if (!db_root_.empty()) {
    auto res = save_db_file(fhash, std::move(data));
    if (res.is_error()) {
      LOG(ERROR) << "error saving state file: " << res.to_string();
    }
  }
  show_new_blkids();
}

td::Status TestNode::save_db_file(ton::FileHash file_hash, td::BufferSlice data) {
  std::string fname = block::compute_db_filename(db_root_ + '/', file_hash);
  for (int i = 0; i < 10; i++) {
    std::string tmp_fname = block::compute_db_tmp_filename(db_root_ + '/', file_hash, i);
    auto res = block::save_binary_file(tmp_fname, data);
    if (res.is_ok()) {
      if (rename(tmp_fname.c_str(), fname.c_str()) < 0) {
        int err = errno;
        LOG(ERROR) << "cannot rename " << tmp_fname << " to " << fname << " : " << strerror(err);
        return td::Status::Error(std::string{"cannot rename file: "} + strerror(err));
      } else {
        LOG(INFO) << data.size() << " bytes saved into file " << fname;
        return td::Status::OK();
      }
    } else if (i == 9) {
      return res;
    }
  }
  return td::Status::Error("cannot save data file");
}

void TestNode::run_init_queries() {
  get_server_time();
  get_server_mc_block_id();
}

std::string TestNode::get_word(char delim) {
  if (delim == ' ' || !delim) {
    skipspc();
  }
  const char* ptr = parse_ptr_;
  while (ptr < parse_end_ && *ptr != delim && (*ptr != '\t' || delim != ' ')) {
    ptr++;
  }
  std::swap(ptr, parse_ptr_);
  return std::string{ptr, parse_ptr_};
}

int TestNode::skipspc() {
  int i = 0;
  while (parse_ptr_ < parse_end_ && (*parse_ptr_ == ' ' || *parse_ptr_ == '\t')) {
    i++;
    parse_ptr_++;
  }
  return i;
}

std::string TestNode::get_line_tail(bool remove_spaces) const {
  const char *ptr = parse_ptr_, *end = parse_end_;
  if (remove_spaces) {
    while (ptr < end && (*ptr == ' ' || *ptr == '\t')) {
      ptr++;
    }
    while (ptr < end && (end[-1] == ' ' || end[-1] == '\t')) {
      --end;
    }
  }
  return std::string{ptr, end};
}

bool TestNode::eoln() const {
  return parse_ptr_ == parse_end_;
}

bool TestNode::seekeoln() {
  skipspc();
  return eoln();
}

bool TestNode::parse_account_addr(ton::WorkchainId& wc, ton::StdSmcAddress& addr) {
  return block::parse_std_account_addr(get_word(), wc, addr) || set_error("cannot parse account address");
}

bool TestNode::parse_uint64(std::string word, td::uint64& val) {
  val = ~0ULL;
  if (word.empty()) {
    return false;
  }
  const char* ptr = word.c_str();
  char* end = nullptr;
  val = strtoull(ptr, &end, 10);
  if (end == ptr + word.size()) {
    return true;
  } else {
    val = ~0ULL;
    return false;
  }
}

bool TestNode::parse_lt(ton::LogicalTime& lt) {
  return parse_uint64(get_word(), lt) || set_error("cannot parse logical time");
}

bool TestNode::set_error(td::Status error) {
  if (error.is_ok()) {
    return true;
  }
  LOG(ERROR) << "error: " << error.to_string();
  if (error_.is_ok()) {
    error_ = std::move(error);
  }
  return false;
}

int TestNode::parse_hex_digit(int c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  c |= 0x20;
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 10;
  }
  return -1;
}

bool TestNode::parse_hash(const char* str, ton::Bits256& hash) {
  unsigned char* data = hash.data();
  for (int i = 0; i < 32; i++) {
    int a = parse_hex_digit(str[2 * i]);
    if (a < 0) {
      return false;
    }
    int b = parse_hex_digit(str[2 * i + 1]);
    if (b < 0) {
      return false;
    }
    data[i] = (unsigned char)((a << 4) + b);
  }
  return true;
}

bool TestNode::parse_block_id_ext(std::string blkid_str, ton::BlockIdExt& blkid, bool allow_incomplete) const {
  if (blkid_str.empty()) {
    return false;
  }
  auto fc = blkid_str[0];
  if (fc == 'B' || fc == '#') {
    unsigned n = 0;
    if (sscanf(blkid_str.c_str(), fc == 'B' ? "BLK#%u" : "#%u", &n) != 1 || !n || n > known_blk_ids_.size()) {
      return false;
    }
    blkid = known_blk_ids_.at(n - 1);
    return true;
  }
  if (blkid_str[0] != '(') {
    return false;
  }
  auto pos = blkid_str.find(')');
  if (pos == std::string::npos || pos >= 38) {
    return false;
  }
  char buffer[40];
  memcpy(buffer, blkid_str.c_str(), pos + 1);
  buffer[pos + 1] = 0;
  unsigned long long shard;
  if (sscanf(buffer, "(%d,%016llx,%u)", &blkid.id.workchain, &shard, &blkid.id.seqno) != 3) {
    return false;
  }
  blkid.id.shard = shard;
  if (!blkid.id.is_valid_full()) {
    return false;
  }
  pos++;
  if (pos == blkid_str.size()) {
    blkid.root_hash.set_zero();
    blkid.file_hash.set_zero();
    return complete_blkid(blkid.id, blkid) || allow_incomplete;
  }
  return pos + 2 * 65 == blkid_str.size() && blkid_str[pos] == ':' && blkid_str[pos + 65] == ':' &&
         parse_hash(blkid_str.c_str() + pos + 1, blkid.root_hash) &&
         parse_hash(blkid_str.c_str() + pos + 66, blkid.file_hash) && blkid.is_valid_full();
}

bool TestNode::parse_block_id_ext(ton::BlockIdExt& blk, bool allow_incomplete) {
  return parse_block_id_ext(get_word(), blk, allow_incomplete) || set_error("cannot parse BlockIdExt");
}

bool TestNode::set_error(std::string err_msg) {
  return set_error(td::Status::Error(-1, err_msg));
}

void TestNode::parse_line(td::BufferSlice data) {
  line_ = data.as_slice().str();
  parse_ptr_ = line_.c_str();
  parse_end_ = parse_ptr_ + line_.size();
  error_ = td::Status::OK();
  if (seekeoln()) {
    return;
  }
  if (!do_parse_line() || error_.is_error()) {
    show_context();
    LOG(ERROR) << (error_.is_ok() ? "Syntax error" : error_.to_string());
    error_ = td::Status::OK();
  }
  show_new_blkids();
}

void TestNode::show_context() const {
  const char* ptr = line_.c_str();
  CHECK(parse_ptr_ >= ptr && parse_ptr_ <= parse_end_);
  auto out = td::TerminalIO::out();
  for (; ptr < parse_ptr_; ptr++) {
    out << (char)(*ptr == '\t' ? *ptr : ' ');
  }
  out << "^" << '\n';
}

bool TestNode::show_help(std::string command) {
  td::TerminalIO::out()
      << "list of available commands:\n"
         "time\tGet server time\n"
         "last\tGet last block and state info from server\n"
         "sendfile <filename>\tLoad a serialized message from <filename> and send it to server\n"
         "status\tShow connection and local database status\n"
         "getaccount <addr> [<block-id-ext>]\tLoads the most recent state of specified account; <addr> is in "
         "[<workchain>:]<hex-or-base64-addr> format\n"
         "allshards [<block-id-ext>]\tShows shard configuration from the most recent masterchain "
         "state or from masterchain state corresponding to <block-id-ext>\n"
         "gethead <block-id-ext>\tShows block header for <block-id-ext>\n"
         "getblock <block-id-ext>\tDownloads block\n"
         "dumpblock <block-id-ext>\tDownloads and dumps specified block\n"
         "getstate <block-id-ext>\tDownloads state corresponding to specified block\n"
         "dumpstate <block-id-ext>\tDownloads and dumps state corresponding to specified block\n"
         "dumptrans <block-id-ext> <account-id> <trans-lt>\tDumps one transaction of specified account\n"
         "known\tShows the list of all known block ids\n"
         "privkey <filename>\tLoads a private key from file\n"
         "help [<command>]\tThis help\n"
         "quit\tExit\n";
  return true;
}

bool TestNode::do_parse_line() {
  ton::WorkchainId workchain = ton::masterchainId;  // change to basechain later
  ton::StdSmcAddress addr;
  ton::BlockIdExt blkid;
  ton::LogicalTime lt;
  std::string word = get_word();
  skipspc();
  if (word == "time") {
    return eoln() && get_server_time();
  } else if (word == "setverbosity") {
    return !eoln() && set_error(send_set_verbosity(get_word())) && eoln();
  } else if (word == "last") {
    return eoln() && get_server_mc_block_id();
  } else if (word == "sendfile") {
    return !eoln() && set_error(send_ext_msg_from_filename(get_line_tail()));
  } else if (word == "getaccount") {
    return parse_account_addr(workchain, addr) &&
           (seekeoln() ? get_account_state(workchain, addr, mc_last_id_)
                       : parse_block_id_ext(blkid) && seekeoln() && get_account_state(workchain, addr, blkid));
  } else if (word == "allshards") {
    return eoln() ? get_all_shards() : (parse_block_id_ext(blkid) && seekeoln() && get_all_shards(false, blkid));
  } else if (word == "getblock") {
    return parse_block_id_ext(blkid) && seekeoln() && get_block(blkid, false);
  } else if (word == "dumpblock") {
    return parse_block_id_ext(blkid) && seekeoln() && get_block(blkid, true);
  } else if (word == "getstate") {
    return parse_block_id_ext(blkid) && seekeoln() && get_state(blkid, false);
  } else if (word == "dumpstate") {
    return parse_block_id_ext(blkid) && seekeoln() && get_state(blkid, true);
  } else if (word == "gethead") {
    return parse_block_id_ext(blkid) && seekeoln() && get_block_header(blkid, 0xffff);
  } else if (word == "dumptrans") {
    return parse_block_id_ext(blkid) && parse_account_addr(workchain, addr) && parse_lt(lt) && seekeoln() &&
           get_one_transaction(blkid, workchain, addr, lt, true);
  } else if (word == "known") {
    return eoln() && show_new_blkids(true);
  } else if (word == "quit" && eoln()) {
    LOG(INFO) << "Exiting";
    stop();
    // exit(0);
    return true;
  } else if (word == "help") {
    return show_help(get_line_tail());
  } else {
    td::TerminalIO::out() << "unknown command: " << word << " ; type `help` to get help" << '\n';
    return false;
  }
}

td::Status TestNode::send_ext_msg_from_filename(std::string filename) {
  auto F = td::read_file(filename);
  if (F.is_error()) {
    auto err = F.move_as_error();
    LOG(ERROR) << "failed to read file `" << filename << "`: " << err.to_string();
    return err;
  }
  if (ready_ && !client_.empty()) {
    LOG(ERROR) << "sending query from file " << filename;
    auto P = td::PromiseCreator::lambda([](td::Result<td::BufferSlice> R) {
      if (R.is_error()) {
        return;
      }
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_sendMsgStatus>(R.move_as_ok(), true);
      if (F.is_error()) {
        LOG(ERROR) << "cannot parse answer to liteServer.sendMessage";
      } else {
        int status = F.move_as_ok()->status_;
        LOG(INFO) << "external message status is " << status;
      }
    });
    auto b =
        ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_sendMessage>(F.move_as_ok()), true);
    return envelope_send_query(std::move(b), std::move(P)) ? td::Status::OK()
                                                           : td::Status::Error("cannot send query to server");
  } else {
    return td::Status::Error("server connection not ready");
  }
}

td::Status TestNode::send_set_verbosity(std::string verbosity_str) {
  auto value = std::stoi(verbosity_str);
  if (ready_ && !client_.empty()) {
    LOG(ERROR) << "sending set verbosity " << value << " query";
    auto P = td::PromiseCreator::lambda([](td::Result<td::BufferSlice> R) {
      if (R.is_error()) {
        LOG(INFO) << "failed to set verbosity: " << R.move_as_error();
        return;
      }
      LOG(INFO) << "success set verbosity";
    });
    auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_debug_setVerbosity>(
                                          ton::create_tl_object<ton::ton_api::liteServer_debug_verbosity>(value)),
                                      true);
    return envelope_send_query(std::move(b), std::move(P)) ? td::Status::OK()
                                                           : td::Status::Error("cannot send query to server");
  } else {
    return td::Status::Error("server connection not ready");
  }
}

bool TestNode::get_account_state(ton::WorkchainId workchain, ton::StdSmcAddress addr, ton::BlockIdExt ref_blkid) {
  if (!ref_blkid.is_valid()) {
    return set_error("must obtain last block information before making other queries");
  }
  if (!(ready_ && !client_.empty())) {
    return set_error("server connection not ready");
  }
  auto a = ton::create_tl_object<ton::ton_api::liteServer_accountId>(workchain, ton::Bits256_2_UInt256(addr));
  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::ton_api::liteServer_getAccountState>(ton::create_tl_block_id(ref_blkid), std::move(a)),
      true);
  LOG(INFO) << "requesting account state for " << workchain << ":" << addr.to_hex() << " with respect to "
            << ref_blkid.to_str();
  return envelope_send_query(
      std::move(b), [ Self = actor_id(this), workchain, addr, ref_blkid ](td::Result<td::BufferSlice> R)->void {
        if (R.is_error()) {
          return;
        }
        auto F = ton::fetch_tl_object<ton::ton_api::liteServer_accountState>(R.move_as_ok(), true);
        if (F.is_error()) {
          LOG(ERROR) << "cannot parse answer to liteServer.getAccountState";
        } else {
          auto f = F.move_as_ok();
          td::actor::send_closure_later(Self, &TestNode::got_account_state, ref_blkid, ton::create_block_id(f->id_),
                                        ton::create_block_id(f->shardblk_), std::move(f->shard_proof_),
                                        std::move(f->proof_), std::move(f->state_), workchain, addr);
        }
      });
}

bool TestNode::get_one_transaction(ton::BlockIdExt blkid, ton::WorkchainId workchain, ton::StdSmcAddress addr,
                                   ton::LogicalTime lt, bool dump) {
  if (!blkid.is_valid_full()) {
    return set_error("invalid block id");
  }
  if (!ton::shard_contains(blkid.shard_full(), ton::extract_addr_prefix(workchain, addr))) {
    return set_error("the shard of this block cannot contain this account");
  }
  if (!(ready_ && !client_.empty())) {
    return set_error("server connection not ready");
  }
  auto a = ton::create_tl_object<ton::ton_api::liteServer_accountId>(workchain, ton::Bits256_2_UInt256(addr));
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getOneTransaction>(
                                        ton::create_tl_block_id(blkid), std::move(a), lt),
                                    true);
  LOG(INFO) << "requesting transaction " << lt << " of " << workchain << ":" << addr.to_hex() << " from block "
            << blkid.to_str();
  return envelope_send_query(
      std::move(b), [ Self = actor_id(this), workchain, addr, lt, blkid, dump ](td::Result<td::BufferSlice> R)->void {
        if (R.is_error()) {
          return;
        }
        auto F = ton::fetch_tl_object<ton::ton_api::liteServer_transactionInfo>(R.move_as_ok(), true);
        if (F.is_error()) {
          LOG(ERROR) << "cannot parse answer to liteServer.getOneTransaction";
        } else {
          auto f = F.move_as_ok();
          td::actor::send_closure_later(Self, &TestNode::got_one_transaction, blkid, ton::create_block_id(f->id_),
                                        std::move(f->proof_), std::move(f->transaction_), workchain, addr, lt, dump);
        }
      });
}

td::Status check_block_header_proof(Ref<vm::Cell> root, ton::BlockIdExt blkid,
                                    ton::Bits256* store_shard_hash_to = nullptr, bool check_state_hash = false) {
  ton::RootHash vhash{root->get_hash().bits()};
  if (vhash != blkid.root_hash) {
    return td::Status::Error(PSTRING() << " block header for block " << blkid.to_str() << " has incorrect root hash "
                                       << vhash.to_hex() << " instead of " << blkid.root_hash.to_hex());
  }
  std::vector<ton::BlockIdExt> prev;
  ton::BlockIdExt mc_blkid, blkid_u = blkid;
  bool after_split;
  auto res = block::unpack_block_prev_blk_ext(root, blkid_u, prev, mc_blkid, after_split);
  if (res.is_error()) {
    return res;
  }
  if (blkid_u.id != blkid.id || blkid_u.root_hash != blkid.root_hash) {
    return td::Status::Error(PSTRING() << "block header claims it is for block " << blkid_u.to_str() << " not "
                                       << blkid.to_str());
  }
  block::gen::Block::Record blk;
  block::gen::BlockInfo::Record info;
  if (!(tlb::unpack_cell(root, blk) && tlb::unpack_cell(blk.info, info))) {
    return td::Status::Error(std::string{"cannot unpack header for block "} + blkid.to_str());
  }
  if (store_shard_hash_to) {
    vm::CellSlice upd_cs{vm::NoVmSpec(), blk.state_update};
    if (!(upd_cs.is_special() && upd_cs.prefetch_long(8) == 4  // merkle update
          && upd_cs.size_ext() == 0x20228)) {
      return td::Status::Error("invalid Merkle update in block header");
    }
    auto upd_hash = upd_cs.prefetch_ref(1)->get_hash(0);
    if (!check_state_hash) {
      *store_shard_hash_to = upd_hash.bits();
    } else if (store_shard_hash_to->compare(upd_hash.bits())) {
      return td::Status::Error(PSTRING() << "state hash mismatch in block header of " << blkid.to_str()
                                         << " : header declares " << upd_hash.bits().to_hex(256) << " expected "
                                         << store_shard_hash_to->to_hex());
    }
  }
  return td::Status::OK();
}

void TestNode::got_account_state(ton::BlockIdExt ref_blk, ton::BlockIdExt blk, ton::BlockIdExt shard_blk,
                                 td::BufferSlice shard_proof, td::BufferSlice proof, td::BufferSlice state,
                                 ton::WorkchainId workchain, ton::StdSmcAddress addr) {
  LOG(INFO) << "got account state for " << workchain << ":" << addr.to_hex() << " with respect to blocks "
            << blk.to_str() << (shard_blk == blk ? "" : std::string{" and "} + shard_blk.to_str());
  Ref<vm::Cell> root;
  if (!state.empty()) {
    auto R = vm::std_boc_deserialize(state.clone());
    if (R.is_error()) {
      LOG(ERROR) << "cannot deserialize account state";
      return;
    }
    root = R.move_as_ok();
    CHECK(root.not_null());
  }
  if (blk != ref_blk) {
    LOG(ERROR) << "obtained getAccountState() for a different reference block " << blk.to_str()
               << " instead of requested " << ref_blk.to_str();
    return;
  }
  if (!shard_blk.is_valid_full()) {
    LOG(ERROR) << "shard block id " << shard_blk.to_str() << " in answer is invalid";
    return;
  }
  if (!ton::shard_contains(shard_blk.shard_full(), ton::extract_addr_prefix(workchain, addr))) {
    LOG(ERROR) << "received data from shard block " << shard_blk.to_str() << " that cannot contain requested account "
               << workchain << ":" << addr.to_hex();
    return;
  }
  if (blk != shard_blk) {
    if (!blk.is_masterchain() || !blk.is_valid_full()) {
      LOG(ERROR) << "reference block " << blk.to_str() << " for a getAccountState query must belong to the masterchain";
      return;
    }
    auto P = vm::std_boc_deserialize_multi(std::move(shard_proof));
    if (P.is_error()) {
      LOG(ERROR) << "cannot deserialize shard configuration proof";
      return;
    }
    auto P_roots = P.move_as_ok();
    if (P_roots.size() != 2) {
      LOG(ERROR) << "shard configuration proof must have exactly two roots";
      return;
    }
    try {
      auto mc_state_root = vm::MerkleProof::virtualize(std::move(P_roots[1]), 1);
      if (mc_state_root.is_null()) {
        LOG(ERROR) << "shard configuration proof is invalid";
        return;
      }
      ton::Bits256 mc_state_hash = mc_state_root->get_hash().bits();
      auto res1 =
          check_block_header_proof(vm::MerkleProof::virtualize(std::move(P_roots[0]), 1), blk, &mc_state_hash, true);
      if (res1.is_error()) {
        LOG(ERROR) << "error in shard configuration block header proof : " << res1.move_as_error().to_string();
        return;
      }
      block::gen::ShardStateUnsplit::Record sstate;
      if (!(tlb::unpack_cell(mc_state_root, sstate))) {
        LOG(ERROR) << "cannot unpack masterchain state header";
        return;
      }
      auto shards_dict = block::Config::extract_shard_hashes_dict(std::move(mc_state_root));
      if (!shards_dict) {
        LOG(ERROR) << "cannot extract shard configuration dictionary from proof";
        return;
      }
      vm::CellSlice cs;
      ton::ShardIdFull true_shard;
      if (!block::ShardConfig::get_shard_hash_raw_from(*shards_dict, cs, shard_blk.shard_full(), true_shard)) {
        LOG(ERROR) << "masterchain state contains no information for shard " << shard_blk.shard_full().to_str();
        return;
      }
      auto shard_info = block::McShardHash::unpack(cs, true_shard);
      if (shard_info.is_null()) {
        LOG(ERROR) << "cannot unpack information for shard " << shard_blk.shard_full().to_str()
                   << " from masterchain state";
        return;
      }
      if (shard_info->top_block_id() != shard_blk) {
        LOG(ERROR) << "shard configuration mismatch: expected to find block " << shard_blk.to_str() << " , found "
                   << shard_info->top_block_id().to_str();
        return;
      }
    } catch (vm::VmError err) {
      LOG(ERROR) << "error while traversing shard configuration proof : " << err.get_msg();
      return;
    } catch (vm::VmVirtError err) {
      LOG(ERROR) << "virtualization error while traversing shard configuration proof : " << err.get_msg();
      return;
    }
  }
  auto Q = vm::std_boc_deserialize_multi(std::move(proof));
  if (Q.is_error()) {
    LOG(ERROR) << "cannot deserialize account proof";
    return;
  }
  auto Q_roots = Q.move_as_ok();
  if (Q_roots.size() != 2) {
    LOG(ERROR) << "account state proof must have exactly two roots";
    return;
  }
  ton::LogicalTime last_trans_lt = 0;
  ton::Bits256 last_trans_hash;
  last_trans_hash.set_zero();
  try {
    auto state_root = vm::MerkleProof::virtualize(std::move(Q_roots[1]), 1);
    if (state_root.is_null()) {
      LOG(ERROR) << "account state proof is invalid";
      return;
    }
    ton::Bits256 state_hash = state_root->get_hash().bits();
    auto res1 =
        check_block_header_proof(vm::MerkleProof::virtualize(std::move(Q_roots[0]), 1), shard_blk, &state_hash, true);
    if (res1.is_error()) {
      LOG(ERROR) << "error in account shard block header proof : " << res1.move_as_error().to_string();
      return;
    }
    block::gen::ShardStateUnsplit::Record sstate;
    if (!(tlb::unpack_cell(std::move(state_root), sstate))) {
      LOG(ERROR) << "cannot unpack state header";
      return;
    }
    vm::AugmentedDictionary accounts_dict{sstate.accounts->prefetch_ref(), 256, block::tlb::aug_ShardAccounts};
    auto acc_csr = accounts_dict.lookup(addr);
    if (acc_csr.not_null()) {
      if (root.is_null()) {
        LOG(ERROR) << "account state proof shows that account state for " << workchain << ":" << addr.to_hex()
                   << " must be non-empty, but it actually is empty";
        return;
      }
      block::gen::ShardAccount::Record acc_info;
      if (!tlb::csr_unpack(std::move(acc_csr), acc_info)) {
        LOG(ERROR) << "cannot unpack ShardAccount from proof";
        return;
      }
      if (acc_info.account->get_hash().bits().compare(root->get_hash().bits(), 256)) {
        LOG(ERROR) << "account state hash mismatch: Merkle proof expects "
                   << acc_info.account->get_hash().bits().to_hex(256) << " but received data has "
                   << root->get_hash().bits().to_hex(256);
        return;
      }
      last_trans_hash = acc_info.last_trans_hash;
      last_trans_lt = acc_info.last_trans_lt;
    } else if (root.not_null()) {
      LOG(ERROR) << "account state proof shows that account state for " << workchain << ":" << addr.to_hex()
                 << " must be empty, but it is not";
      return;
    }
  } catch (vm::VmError err) {
    LOG(ERROR) << "error while traversing account proof : " << err.get_msg();
    return;
  } catch (vm::VmVirtError err) {
    LOG(ERROR) << "virtualization error while traversing account proof : " << err.get_msg();
    return;
  }
  auto out = td::TerminalIO::out();
  if (root.not_null()) {
    out << "account state is ";
    std::ostringstream outp;
    block::gen::t_Account.print_ref(outp, root);
    vm::load_cell_slice(root).print_rec(outp);
    out << outp.str();
    out << "last transaction lt = " << last_trans_lt << " hash = " << last_trans_hash.to_hex() << std::endl;
  } else {
    out << "account state is empty" << std::endl;
  }
}

void TestNode::got_one_transaction(ton::BlockIdExt req_blkid, ton::BlockIdExt blkid, td::BufferSlice proof,
                                   td::BufferSlice transaction, ton::WorkchainId workchain, ton::StdSmcAddress addr,
                                   ton::LogicalTime trans_lt, bool dump) {
  LOG(INFO) << "got transaction " << trans_lt << " for " << workchain << ":" << addr.to_hex()
            << " with respect to block " << blkid.to_str();
  if (blkid != req_blkid) {
    LOG(ERROR) << "obtained TransactionInfo for a different block " << blkid.to_str() << " instead of requested "
               << req_blkid.to_str();
    return;
  }
  if (!ton::shard_contains(blkid.shard_full(), ton::extract_addr_prefix(workchain, addr))) {
    LOG(ERROR) << "received data from block " << blkid.to_str() << " that cannot contain requested account "
               << workchain << ":" << addr.to_hex();
    return;
  }
  Ref<vm::Cell> root;
  if (!transaction.empty()) {
    auto R = vm::std_boc_deserialize(std::move(transaction));
    if (R.is_error()) {
      LOG(ERROR) << "cannot deserialize transaction";
      return;
    }
    root = R.move_as_ok();
    CHECK(root.not_null());
  }
  auto out = td::TerminalIO::out();
  if (root.is_null()) {
    out << "transaction not found" << std::endl;
  } else {
    out << "transaction is ";
    std::ostringstream outp;
    block::gen::t_Transaction.print_ref(outp, root);
    vm::load_cell_slice(root).print_rec(outp);
    out << outp.str();
  }
}

bool TestNode::get_all_shards(bool use_last, ton::BlockIdExt blkid) {
  if (use_last) {
    blkid = mc_last_id_;
  }
  if (!blkid.is_valid_full()) {
    return set_error(use_last ? "must obtain last block information before making other queries"
                              : "invalid masterchain block id");
  }
  if (!blkid.is_masterchain()) {
    return set_error("only masterchain blocks contain shard configuration");
  }
  if (!(ready_ && !client_.empty())) {
    return set_error("server connection not ready");
  }
  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::ton_api::liteServer_getAllShardsInfo>(ton::create_tl_block_id(blkid)), true);
  LOG(INFO) << "requesting recent shard configuration";
  return envelope_send_query(std::move(b), [Self = actor_id(this)](td::Result<td::BufferSlice> R)->void {
    if (R.is_error()) {
      return;
    }
    auto F = ton::fetch_tl_object<ton::ton_api::liteServer_allShardsInfo>(R.move_as_ok(), true);
    if (F.is_error()) {
      LOG(ERROR) << "cannot parse answer to liteServer.getAllShardsInfo";
    } else {
      auto f = F.move_as_ok();
      td::actor::send_closure_later(Self, &TestNode::got_all_shards, ton::create_block_id(f->id_), std::move(f->proof_),
                                    std::move(f->data_));
    }
  });
}

void TestNode::got_all_shards(ton::BlockIdExt blk, td::BufferSlice proof, td::BufferSlice data) {
  LOG(INFO) << "got shard configuration with respect to block " << blk.to_str();
  if (data.empty()) {
    td::TerminalIO::out() << "shard configuration is empty" << '\n';
  } else {
    auto R = vm::std_boc_deserialize(data.clone());
    if (R.is_error()) {
      LOG(ERROR) << "cannot deserialize shard configuration";
      return;
    }
    auto root = R.move_as_ok();
    auto out = td::TerminalIO::out();
    out << "shard configuration is ";
    std::ostringstream outp;
    block::gen::t_ShardHashes.print_ref(outp, root);
    vm::load_cell_slice(root).print_rec(outp);
    out << outp.str();
    block::ShardConfig sh_conf;
    if (!sh_conf.unpack(vm::load_cell_slice_ref(root))) {
      out << "cannot extract shard block list from shard configuration\n";
    } else {
      auto ids = sh_conf.get_shard_hash_ids(true);
      int cnt = 0;
      for (auto id : ids) {
        auto ref = sh_conf.get_shard_hash(ton::ShardIdFull(id));
        if (ref.not_null()) {
          register_blkid(ref->top_block_id());
          out << "shard #" << ++cnt << " : " << ref->top_block_id().to_str() << " @ " << ref->created_at() << " lt "
              << ref->start_lt() << " .. " << ref->end_lt() << std::endl;
        } else {
          out << "shard #" << ++cnt << " : " << id.to_str() << " (cannot unpack)\n";
        }
      }
    }
  }
  show_new_blkids();
}

bool TestNode::get_block(ton::BlockIdExt blkid, bool dump) {
  LOG(INFO) << "got block download request for " << blkid.to_str();
  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::ton_api::liteServer_getBlock>(ton::create_tl_block_id(blkid)), true);
  return envelope_send_query(
      std::move(b), [ Self = actor_id(this), blkid, dump ](td::Result<td::BufferSlice> res)->void {
        if (res.is_error()) {
          LOG(ERROR) << "cannot obtain block " << blkid.to_str()
                     << " from server : " << res.move_as_error().to_string();
          return;
        } else {
          auto F = ton::fetch_tl_object<ton::ton_api::liteServer_blockData>(res.move_as_ok(), true);
          if (F.is_error()) {
            LOG(ERROR) << "cannot parse answer to liteServer.getBlock : " << res.move_as_error().to_string();
          } else {
            auto f = F.move_as_ok();
            auto blk_id = ton::create_block_id(f->id_);
            LOG(INFO) << "obtained block " << blk_id.to_str() << " from server";
            if (blk_id != blkid) {
              LOG(ERROR) << "block id mismatch: expected data for block " << blkid.to_str() << ", obtained for "
                         << blk_id.to_str();
              return;
            }
            td::actor::send_closure_later(Self, &TestNode::got_block, blk_id, std::move(f->data_), dump);
          }
        }
      });
}

bool TestNode::get_state(ton::BlockIdExt blkid, bool dump) {
  LOG(INFO) << "got state download request for " << blkid.to_str();
  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::ton_api::liteServer_getState>(ton::create_tl_block_id(blkid)), true);
  return envelope_send_query(
      std::move(b), [ Self = actor_id(this), blkid, dump ](td::Result<td::BufferSlice> res)->void {
        if (res.is_error()) {
          LOG(ERROR) << "cannot obtain state " << blkid.to_str()
                     << " from server : " << res.move_as_error().to_string();
          return;
        } else {
          auto F = ton::fetch_tl_object<ton::ton_api::liteServer_blockState>(res.move_as_ok(), true);
          if (F.is_error()) {
            LOG(ERROR) << "cannot parse answer to liteServer.getState";
          } else {
            auto f = F.move_as_ok();
            auto blk_id = ton::create_block_id(f->id_);
            LOG(INFO) << "obtained state " << blk_id.to_str() << " from server";
            if (blk_id != blkid) {
              LOG(ERROR) << "block id mismatch: expected state for block " << blkid.to_str() << ", obtained for "
                         << blk_id.to_str();
              return;
            }
            td::actor::send_closure_later(Self, &TestNode::got_state, blk_id, ton::UInt256_2_Bits256(f->root_hash_),
                                          ton::UInt256_2_Bits256(f->file_hash_), std::move(f->data_), dump);
          }
        }
      });
}

void TestNode::got_block(ton::BlockIdExt blkid, td::BufferSlice data, bool dump) {
  LOG(INFO) << "obtained " << data.size() << " data bytes for block " << blkid.to_str();
  ton::FileHash fhash;
  td::sha256(data.as_slice(), fhash.as_slice());
  if (fhash != blkid.file_hash) {
    LOG(ERROR) << "file hash mismatch for block " << blkid.to_str() << ": expected " << blkid.file_hash.to_hex()
               << ", computed " << fhash.to_hex();
    return;
  }
  register_blkid(blkid);
  if (!db_root_.empty()) {
    auto res = save_db_file(fhash, data.clone());
    if (res.is_error()) {
      LOG(ERROR) << "error saving block file: " << res.to_string();
    }
  }
  if (dump) {
    auto res = vm::std_boc_deserialize(data.clone());
    if (res.is_error()) {
      LOG(ERROR) << "cannot deserialize block data : " << res.move_as_error().to_string();
      return;
    }
    auto root = res.move_as_ok();
    ton::RootHash rhash{root->get_hash().bits()};
    if (rhash != blkid.root_hash) {
      LOG(ERROR) << "block root hash mismatch: data has " << rhash.to_hex() << " , expected "
                 << blkid.root_hash.to_hex();
      return;
    }
    auto out = td::TerminalIO::out();
    out << "block contents is ";
    std::ostringstream outp;
    block::gen::t_Block.print_ref(outp, root);
    vm::load_cell_slice(root).print_rec(outp);
    out << outp.str();
    show_block_header(blkid, std::move(root), 0xffff);
  } else {
    auto res = lazy_boc_deserialize(data.clone());
    if (res.is_error()) {
      LOG(ERROR) << "cannot lazily deserialize block data : " << res.move_as_error().to_string();
      return;
    }
    auto pair = res.move_as_ok();
    auto root = std::move(pair.first);
    ton::RootHash rhash{root->get_hash().bits()};
    if (rhash != blkid.root_hash) {
      LOG(ERROR) << "block root hash mismatch: data has " << rhash.to_hex() << " , expected "
                 << blkid.root_hash.to_hex();
      return;
    }
    show_block_header(blkid, std::move(root), 0xffff);
  }
  show_new_blkids();
}

void TestNode::got_state(ton::BlockIdExt blkid, ton::RootHash root_hash, ton::FileHash file_hash, td::BufferSlice data,
                         bool dump) {
  LOG(INFO) << "obtained " << data.size() << " state bytes for block " << blkid.to_str();
  ton::FileHash fhash;
  td::sha256(data.as_slice(), fhash.as_slice());
  if (fhash != file_hash) {
    LOG(ERROR) << "file hash mismatch for state " << blkid.to_str() << ": expected " << file_hash.to_hex()
               << ", computed " << fhash.to_hex();
    return;
  }
  register_blkid(blkid);
  if (!db_root_.empty()) {
    auto res = save_db_file(fhash, std::move(data));
    if (res.is_error()) {
      LOG(ERROR) << "error saving state file: " << res.to_string();
    }
  }
  if (dump) {
    auto res = vm::std_boc_deserialize(data.clone());
    if (res.is_error()) {
      LOG(ERROR) << "cannot deserialize block data : " << res.move_as_error().to_string();
      return;
    }
    auto root = res.move_as_ok();
    ton::RootHash rhash{root->get_hash().bits()};
    if (rhash != root_hash) {
      LOG(ERROR) << "block state root hash mismatch: data has " << rhash.to_hex() << " , expected "
                 << root_hash.to_hex();
      return;
    }
    auto out = td::TerminalIO::out();
    out << "shard state contents is ";
    std::ostringstream outp;
    block::gen::t_ShardState.print_ref(outp, root);
    vm::load_cell_slice(root).print_rec(outp);
    out << outp.str();
    show_state_header(blkid, std::move(root), 0xffff);
  } else {
    auto res = lazy_boc_deserialize(data.clone());
    if (res.is_error()) {
      LOG(ERROR) << "cannot lazily deserialize block data : " << res.move_as_error().to_string();
      return;
    }
    auto pair = res.move_as_ok();
    auto root = std::move(pair.first);
    ton::RootHash rhash{root->get_hash().bits()};
    if (rhash != root_hash) {
      LOG(ERROR) << "block state root hash mismatch: data has " << rhash.to_hex() << " , expected "
                 << root_hash.to_hex();
      return;
    }
    show_state_header(blkid, std::move(root), 0xffff);
  }
  show_new_blkids();
}

bool TestNode::get_block_header(ton::BlockIdExt blkid, int mode) {
  LOG(INFO) << "got block header request for " << blkid.to_str() << " with mode " << mode;
  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::ton_api::liteServer_getBlockHeader>(ton::create_tl_block_id(blkid), mode), true);
  return envelope_send_query(std::move(b), [ Self = actor_id(this), blkid ](td::Result<td::BufferSlice> res)->void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot obtain block header for " << blkid.to_str()
                 << " from server : " << res.move_as_error().to_string();
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_blockHeader>(res.move_as_ok(), true);
      if (F.is_error()) {
        LOG(ERROR) << "cannot parse answer to liteServer.getBlockHeader : " << res.move_as_error().to_string();
      } else {
        auto f = F.move_as_ok();
        auto blk_id = ton::create_block_id(f->id_);
        LOG(INFO) << "obtained block header for " << blk_id.to_str() << " from server";
        if (blk_id != blkid) {
          LOG(ERROR) << "block id mismatch: expected data for block " << blkid.to_str() << ", obtained for "
                     << blk_id.to_str();
        }
        td::actor::send_closure_later(Self, &TestNode::got_block_header, blk_id, std::move(f->header_proof_), f->mode_);
      }
    }
  });
  return false;
}

bool TestNode::show_block_header(ton::BlockIdExt blkid, Ref<vm::Cell> root, int mode) {
  ton::RootHash vhash{root->get_hash().bits()};
  if (vhash != blkid.root_hash) {
    LOG(ERROR) << " block header for block " << blkid.to_str() << " has incorrect root hash " << vhash.to_hex()
               << " instead of " << blkid.root_hash.to_hex();
    return false;
  }
  std::vector<ton::BlockIdExt> prev;
  ton::BlockIdExt mc_blkid, blkid_u = blkid;
  bool after_split;
  auto res = block::unpack_block_prev_blk_ext(root, blkid_u, prev, mc_blkid, after_split);
  if (res.is_error()) {
    LOG(ERROR) << "cannot unpack header for block " << blkid.to_str() << " : " << res.to_string();
    return false;
  }
  if (blkid_u.id != blkid.id || blkid_u.root_hash != blkid.root_hash) {
    LOG(ERROR) << "block header claims it is for block " << blkid_u.to_str() << " not " << blkid.to_str();
    return false;
  }
  block::gen::Block::Record blk;
  block::gen::BlockInfo::Record info;
  if (!(tlb::unpack_cell(root, blk) && tlb::unpack_cell(blk.info, info))) {
    LOG(ERROR) << "cannot unpack header for block " << blkid.to_str();
    return false;
  }
  auto out = td::TerminalIO::out();
  out << "block header of " << blkid.to_str() << " @ " << info.gen_utime << " lt " << info.start_lt << " .. "
      << info.end_lt << std::endl;
  out << "global_id=" << blk.global_id << " version=" << info.version << " not_master=" << info.not_master
      << " after_merge=" << info.after_merge << " after_split=" << info.after_split
      << " before_split=" << info.before_split << " want_merge=" << info.want_merge << " want_split=" << info.want_split
      << " validator_list_hash_short=" << info.gen_validator_list_hash_short
      << " catchain_seqno=" << info.gen_catchain_seqno << " min_ref_mc_seqno=" << info.min_ref_mc_seqno << std::endl;
  register_blkid(blkid);
  int cnt = 0;
  for (auto id : prev) {
    out << "previous block #" << ++cnt << " : " << id.to_str() << std::endl;
    register_blkid(id);
  }
  out << "reference masterchain block : " << mc_blkid.to_str() << std::endl;
  register_blkid(mc_blkid);
  return true;
}

bool TestNode::show_state_header(ton::BlockIdExt blkid, Ref<vm::Cell> root, int mode) {
  return true;
}

void TestNode::got_block_header(ton::BlockIdExt blkid, td::BufferSlice data, int mode) {
  LOG(INFO) << "obtained " << data.size() << " data bytes as block header for " << blkid.to_str();
  auto res = vm::std_boc_deserialize(data.clone());
  if (res.is_error()) {
    LOG(ERROR) << "cannot deserialize block header data : " << res.move_as_error().to_string();
    return;
  }
  auto root = res.move_as_ok();
  std::ostringstream outp;
  vm::CellSlice cs{vm::NoVm{}, root};
  cs.print_rec(outp);
  td::TerminalIO::out() << outp.str();
  try {
    auto virt_root = vm::MerkleProof::virtualize(root, 1);
    if (virt_root.is_null()) {
      LOG(ERROR) << " block header proof for block " << blkid.to_str() << " is not a valid Merkle proof";
      return;
    }
    show_block_header(blkid, std::move(virt_root), mode);
  } catch (vm::VmError err) {
    LOG(ERROR) << "error processing header for " << blkid.to_str() << " : " << err.get_msg();
  } catch (vm::VmVirtError err) {
    LOG(ERROR) << "error processing header for " << blkid.to_str() << " : " << err.get_msg();
  }
  show_new_blkids();
}

td::Result<td::UInt256> get_uint256(std::string str) {
  if (str.size() != 64) {
    return td::Status::Error("uint256 must have 64 bytes");
  }
  td::UInt256 res;
  for (size_t i = 0; i < 32; i++) {
    res.raw[i] = static_cast<td::uint8>(td::hex_to_int(str[2 * i]) * 16 + td::hex_to_int(str[2 * i + 1]));
  }
  return res;
}

#if TD_DARWIN || TD_LINUX
#include <execinfo.h>
void unblock_stdin() {
  int flags = fcntl(0, F_GETFL, 0);
  if (flags >= 0) {
    fcntl(0, F_SETFL, flags & ~O_NONBLOCK);
    std::cerr << "stdin unblocked ok: " << flags << " -> " << (flags & ~O_NONBLOCK) << std::endl;
  }
}

void print_backtrace(int sig) {
  const int max_frames = 128;
  void* frames[max_frames];
  int nframes = backtrace(frames, max_frames);
  backtrace_symbols_fd(frames, nframes, 2);
  unblock_stdin();
  exit(EXIT_FAILURE);
}
#endif

void run_updater(td::actor::Scheduler* scheduler, td::actor::ActorOwn<TestNode>* x){
  unsigned int microseconds = 2000000;
  while(true){
    usleep(microseconds);
    scheduler -> run_in_context([&] {
      td::actor::send_closure(x -> get(), &TestNode::web_last);
    });
  }
}

int main(int argc, char* argv[]) {
#if TD_DARWIN || TD_LINUX
  atexit(&unblock_stdin);
#endif
  SET_VERBOSITY_LEVEL(verbosity_INFO);

  td::actor::ActorOwn<TestNode> x;
  int autoupdate = 0;

  td::OptionsParser p;
  p.set_description("test basic adnl functionality");
  p.add_option('h', "help", "prints_help", [&]() {
    char b[10240];
    td::StringBuilder sb(td::MutableSlice{b, 10000});
    sb << p;
    std::cout << sb.as_cslice().c_str();
    std::exit(2);
    return td::Status::OK();
  });
  p.add_option('C', "global-config", "file to read global config", [&](td::Slice fname) {
    td::actor::send_closure(x, &TestNode::set_global_config, fname.str());
    return td::Status::OK();
  });
  p.add_option('c', "local-config", "file to read local config", [&](td::Slice fname) {
    td::actor::send_closure(x, &TestNode::set_local_config, fname.str());
    return td::Status::OK();
  });
  p.add_option('r', "disable-readline", "", [&]() {
    td::actor::send_closure(x, &TestNode::set_readline_enabled, false);
    return td::Status::OK();
  });
  p.add_option('R', "enable-readline", "", [&]() {
    td::actor::send_closure(x, &TestNode::set_readline_enabled, true);
    return td::Status::OK();
  });
  p.add_option('D', "db", "root for dbs", [&](td::Slice fname) {
    td::actor::send_closure(x, &TestNode::set_db_root, fname.str());
    return td::Status::OK();
  });
  p.add_option('v', "verbosity", "set verbosity level", [&](td::Slice arg) {
    verbosity = td::to_integer<int>(arg);
    SET_VERBOSITY_LEVEL(VERBOSITY_NAME(FATAL) + verbosity);
    return (verbosity >= 0 && verbosity <= 9) ? td::Status::OK() : td::Status::Error("verbosity must be 0..9");
  });
  p.add_option('i', "idx", "set liteserver idx", [&](td::Slice arg) {
    auto idx = td::to_integer<int>(arg);
    td::actor::send_closure(x, &TestNode::set_liteserver_idx, idx);
    return td::Status::OK();
  });
  p.add_option('a', "autoupdate", "start autoupdate loop", [&](td::Slice arg) {
    autoupdate = td::to_integer<int>(arg);
    return td::Status::OK();
  });
  p.add_option('u', "update-on-demand", "update state before each call", [&]() {
    td::actor::send_closure(x, &TestNode::set_update_on_demand, true);
    return td::Status::OK();
  });
  p.add_option('d', "daemonize", "set SIGHUP", [&]() {
    td::set_signal_handler(td::SignalType::HangUp,
                           [](int sig) {
#if TD_DARWIN || TD_LINUX
                             close(0);
                             setsid();
#endif
                           })
        .ensure();
    return td::Status::OK();
  });
#if TD_DARWIN || TD_LINUX
  p.add_option('l', "logname", "log to file", [&](td::Slice fname) {
    auto FileLog = td::FileFd::open(td::CSlice(fname.str().c_str()),
                                    td::FileFd::Flags::Create | td::FileFd::Flags::Append | td::FileFd::Flags::Write)
                       .move_as_ok();

    dup2(FileLog.get_native_fd().fd(), 1);
    dup2(FileLog.get_native_fd().fd(), 2);
    return td::Status::OK();
  });
  td::set_signal_handler(td::SignalType::Abort, print_backtrace).ensure();
  td::set_signal_handler(td::SignalType::Error, print_backtrace).ensure();
#endif

  td::actor::Scheduler scheduler({2});

  scheduler.run_in_context([&] { x = td::actor::create_actor<TestNode>("testnode"); });

  scheduler.run_in_context([&] { p.run(argc, argv).ensure(); });
  scheduler.run_in_context([&] {
    td::actor::send_closure(x, &TestNode::run);
    // TMP disable release due to having an ability to call obj in another threads
    // TODO: do requests directly w/o using actors
    // x.release();
  });

  // web server thread
  std::thread webserver = std::thread(TestNode::run_web_server, &scheduler, &x);

  // updater thread called 'last' command
  if(autoupdate) {
    std::thread updater = std::thread(run_updater, &scheduler, &x);
  }

  scheduler.run();

  return 0;
}
