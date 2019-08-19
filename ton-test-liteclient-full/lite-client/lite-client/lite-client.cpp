#include "lite-client.h"
#include "adnl/adnl-ext-client.h"
#include "tl-utils/lite-utils.hpp"
#include "auto/tl/ton_api_json.h"
#include "auto/tl/lite_api.h"
#include "td/utils/OptionsParser.h"
#include "td/utils/Time.h"
#include "td/utils/filesystem.h"
#include "td/utils/format.h"
#include "td/utils/Random.h"
#include "td/utils/crypto.h"
#include "td/utils/port/signals.h"
#include "td/utils/port/stacktrace.h"
#include "td/utils/port/StdStreams.h"
#include "td/utils/port/FileFd.h"
#include "terminal/terminal.h"
#include "ton/lite-tl.hpp"
#include "block/block-db.h"
#include "block/block.h"
#include "block/block-parse.h"
#include "block/block-auto.h"
#include "block/mc-config.h"
#include "block/check-proof.h"
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

using td::Ref;

int verbosity;

std::unique_ptr<ton::adnl::AdnlExtClient::Callback> TestNode::make_callback() {
  class Callback : public ton::adnl::AdnlExtClient::Callback {
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
  ton::ton_api::liteclient_config_global gc;
  ton::ton_api::from_json(gc, gc_j.get_object()).ensure();

  CHECK(gc.liteservers_.size() > 0);
  auto idx =
      liteserver_idx_ >= 0 ? liteserver_idx_ : td::Random::fast(0, static_cast<td::uint32>(gc.liteservers_.size() - 1));
  CHECK(idx >= 0 && static_cast<td::uint32>(idx) <= gc.liteservers_.size());
  auto& cli = gc.liteservers_[idx];
  td::IPAddress addr;
  addr.init_host_port(td::IPAddress::ipv4_to_str(cli->ip_), cli->port_).ensure();
  td::TerminalIO::out() << "using liteserver " << idx << " with addr " << addr << "\n";

  client_ =
      ton::adnl::AdnlExtClient::create(ton::adnl::AdnlNodeIdFull::create(cli->id_).move_as_ok(), addr, make_callback());
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
    auto F = ton::fetch_tl_object<ton::lite_api::liteServer_error>(data.clone(), true);
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
      ton::serialize_tl_object(ton::create_tl_object<ton::lite_api::liteServer_query>(std::move(query)), true);
  td::actor::send_closure(client_, &ton::adnl::AdnlExtClient::send_query, "query", std::move(b),
                          td::Timestamp::in(10.0), std::move(P));
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
  if (partial_blkid.is_masterchain() && partial_blkid.seqno == ~0U) {
    complete_blkid.id = ton::BlockId{ton::masterchainId, ton::shardIdAll, ~0U};
    complete_blkid.root_hash.set_zero();
    complete_blkid.file_hash.set_zero();
    return true;
  }
  return false;
}

bool TestNode::get_server_time() {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::lite_api::liteServer_getTime>(), true);
  return envelope_send_query(std::move(b), [&, Self = actor_id(this)](td::Result<td::BufferSlice> res) -> void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot get server time";
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::lite_api::liteServer_currentTime>(res.move_as_ok(), true);
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
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::lite_api::liteServer_getMasterchainInfo>(), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this)](td::Result<td::BufferSlice> res) -> void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot get masterchain info from server";
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::lite_api::liteServer_masterchainInfo>(res.move_as_ok(), true);
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
      ton::create_tl_object<ton::lite_api::liteServer_getBlock>(ton::create_tl_lite_block_id(blkid)), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this), blkid](td::Result<td::BufferSlice> res) -> void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot obtain block " << blkid.to_str() << " from server";
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::lite_api::liteServer_blockData>(res.move_as_ok(), true);
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
      ton::create_tl_object<ton::lite_api::liteServer_getState>(ton::create_tl_lite_block_id(blkid)), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this), blkid](td::Result<td::BufferSlice> res) -> void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot obtain state " << blkid.to_str() << " from server";
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::lite_api::liteServer_blockState>(res.move_as_ok(), true);
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
        td::actor::send_closure_later(Self, &TestNode::got_mc_state, blk_id, f->root_hash_, f->file_hash_,
                                      std::move(f->data_));
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

bool TestNode::convert_uint64(std::string word, td::uint64& val) {
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

bool TestNode::convert_int64(std::string word, td::int64& val) {
  val = (~0ULL << 63);
  if (word.empty()) {
    return false;
  }
  const char* ptr = word.c_str();
  char* end = nullptr;
  val = strtoll(ptr, &end, 10);
  if (end == ptr + word.size()) {
    return true;
  } else {
    val = (~0ULL << 63);
    return false;
  }
}

bool TestNode::convert_uint32(std::string word, td::uint32& val) {
  td::uint64 tmp;
  if (convert_uint64(word, tmp) && (td::uint32)tmp == tmp) {
    val = (td::uint32)tmp;
    return true;
  } else {
    return false;
  }
}

bool TestNode::convert_int32(std::string word, td::int32& val) {
  td::int64 tmp;
  if (convert_int64(word, tmp) && (td::int32)tmp == tmp) {
    val = (td::int32)tmp;
    return true;
  } else {
    return false;
  }
}

bool TestNode::parse_lt(ton::LogicalTime& lt) {
  return convert_uint64(get_word(), lt) || set_error("cannot parse logical time");
}

bool TestNode::parse_uint32(td::uint32& val) {
  return convert_uint32(get_word(), val) || set_error("cannot parse 32-bit unsigned integer");
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

bool TestNode::parse_hash(ton::Bits256& hash) {
  auto word = get_word();
  return (!word.empty() && parse_hash(word.c_str(), hash)) || set_error("cannot parse hash");
}

bool TestNode::convert_shard_id(std::string str, ton::ShardIdFull& shard) {
  shard.workchain = ton::workchainInvalid;
  shard.shard = 0;
  auto pos = str.find(':');
  if (pos == std::string::npos || pos > 10) {
    return false;
  }
  if (!convert_int32(str.substr(0, pos), shard.workchain)) {
    return false;
  }
  int t = 64;
  while (++pos < str.size()) {
    int z = parse_hex_digit(str[pos]);
    if (z < 0) {
      if (t == 64) {
        shard.shard = ton::shardIdAll;
      }
      return pos == str.size() - 1 && str[pos] == '_';
    }
    t -= 4;
    if (t >= 0) {
      shard.shard |= ((td::uint64)z << t);
    }
  }
  return true;
}

bool TestNode::parse_shard_id(ton::ShardIdFull& shard) {
  return convert_shard_id(get_word(), shard) || set_error("cannot parse full shard identifier or prefix");
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
         "lasttrans[dump] <account-id> <trans-lt> <trans-hash> [<count>]\tShows or dumps specified transaction and "
         "several preceding "
         "ones\n"
         "listblocktrans[rev] <block-id-ext> <count> [<start-account-id> <start-trans-lt>]\tLists block transactions, "
         "starting immediately after or before the specified one\n"
         "byseqno <workchain> <shard-prefix> <seqno>\tLooks up a block by workchain, shard and seqno, and shows its "
         "header\n"
         "bylt <workchain> <shard-prefix> <lt>\tLooks up a block by workchain, shard and logical time, and shows its "
         "header\n"
         "byutime <workchain> <shard-prefix> <utime>\tLooks up a block by workchain, shard and creation time, and "
         "shows its header\n"
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
  ton::Bits256 hash;
  ton::ShardIdFull shard;
  ton::BlockSeqno seqno;
  ton::UnixTime utime;
  unsigned count;
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
  } else if (word == "lasttrans" || word == "lasttransdump") {
    return parse_account_addr(workchain, addr) && parse_lt(lt) && parse_hash(hash) && seekeoln() &&
           get_last_transactions(workchain, addr, lt, hash, 10, word == "lasttransdump");
  } else if (word == "listblocktrans" || word == "listblocktransrev") {
    lt = 0;
    int mode = (word == "listblocktrans" ? 7 : 0x47);
    return parse_block_id_ext(blkid) && parse_uint32(count) &&
           (seekeoln() || (parse_hash(hash) && parse_lt(lt) && (mode |= 128) && seekeoln())) &&
           get_block_transactions(blkid, mode, count, hash, lt);
  } else if (word == "byseqno") {
    return parse_shard_id(shard) && parse_uint32(seqno) && seekeoln() && lookup_block(shard, 1, seqno);
  } else if (word == "byutime") {
    return parse_shard_id(shard) && parse_uint32(utime) && seekeoln() && lookup_block(shard, 4, utime);
  } else if (word == "bylt") {
    return parse_shard_id(shard) && parse_lt(lt) && seekeoln() && lookup_block(shard, 2, lt);
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

td::Result<std::pair<Ref<vm::Cell>, std::shared_ptr<vm::StaticBagOfCellsDb>>> lazy_boc_deserialize(
    td::BufferSlice data) {
  vm::StaticBagOfCellsDbLazy::Options options;
  options.check_crc32c = true;
  TRY_RESULT(boc, vm::StaticBagOfCellsDbLazy::create(vm::BufferSliceBlobView::create(std::move(data)), options));
  TRY_RESULT(rc, boc->get_root_count());
  if (rc != 1) {
    return td::Status::Error(-668, "bag-of-cells is not standard (exactly one root cell expected)");
  }
  TRY_RESULT(root, boc->get_root_cell(0));
  return std::make_pair(std::move(root), std::move(boc));
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
      auto F = ton::fetch_tl_object<ton::lite_api::liteServer_sendMsgStatus>(R.move_as_ok(), true);
      if (F.is_error()) {
        LOG(ERROR) << "cannot parse answer to liteServer.sendMessage";
      } else {
        int status = F.move_as_ok()->status_;
        LOG(INFO) << "external message status is " << status;
      }
    });
    auto b =
        ton::serialize_tl_object(ton::create_tl_object<ton::lite_api::liteServer_sendMessage>(F.move_as_ok()), true);
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
    auto b = ton::serialize_tl_object(ton::create_tl_object<ton::lite_api::liteServer_debug_setVerbosity>(
                                          ton::create_tl_object<ton::lite_api::liteServer_debug_verbosity>(value)),
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
  auto a = ton::create_tl_object<ton::lite_api::liteServer_accountId>(workchain, addr);
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::lite_api::liteServer_getAccountState>(
                                        ton::create_tl_lite_block_id(ref_blkid), std::move(a)),
                                    true);
  LOG(INFO) << "requesting account state for " << workchain << ":" << addr.to_hex() << " with respect to "
            << ref_blkid.to_str();
  return envelope_send_query(
      std::move(b), [Self = actor_id(this), workchain, addr, ref_blkid](td::Result<td::BufferSlice> R) -> void {
        if (R.is_error()) {
          return;
        }
        auto F = ton::fetch_tl_object<ton::lite_api::liteServer_accountState>(R.move_as_ok(), true);
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
  auto a = ton::create_tl_object<ton::lite_api::liteServer_accountId>(workchain, addr);
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::lite_api::liteServer_getOneTransaction>(
                                        ton::create_tl_lite_block_id(blkid), std::move(a), lt),
                                    true);
  LOG(INFO) << "requesting transaction " << lt << " of " << workchain << ":" << addr.to_hex() << " from block "
            << blkid.to_str();
  return envelope_send_query(
      std::move(b), [Self = actor_id(this), workchain, addr, lt, blkid, dump](td::Result<td::BufferSlice> R) -> void {
        if (R.is_error()) {
          return;
        }
        auto F = ton::fetch_tl_object<ton::lite_api::liteServer_transactionInfo>(R.move_as_ok(), true);
        if (F.is_error()) {
          LOG(ERROR) << "cannot parse answer to liteServer.getOneTransaction";
        } else {
          auto f = F.move_as_ok();
          td::actor::send_closure_later(Self, &TestNode::got_one_transaction, blkid, ton::create_block_id(f->id_),
                                        std::move(f->proof_), std::move(f->transaction_), workchain, addr, lt, dump);
        }
      });
}

bool TestNode::get_last_transactions(ton::WorkchainId workchain, ton::StdSmcAddress addr, ton::LogicalTime lt,
                                     ton::Bits256 hash, unsigned count, bool dump) {
  if (!(ready_ && !client_.empty())) {
    return set_error("server connection not ready");
  }
  auto a = ton::create_tl_object<ton::lite_api::liteServer_accountId>(workchain, addr);
  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::lite_api::liteServer_getTransactions>(count, std::move(a), lt, hash), true);
  LOG(INFO) << "requesting " << count << " last transactions from " << lt << ":" << hash.to_hex() << " of " << workchain
            << ":" << addr.to_hex();
  return envelope_send_query(
      std::move(b), [Self = actor_id(this), workchain, addr, lt, hash, count, dump](td::Result<td::BufferSlice> R) {
        if (R.is_error()) {
          return;
        }
        auto F = ton::fetch_tl_object<ton::lite_api::liteServer_transactionList>(R.move_as_ok(), true);
        if (F.is_error()) {
          LOG(ERROR) << "cannot parse answer to liteServer.getTransactions";
        } else {
          auto f = F.move_as_ok();
          std::vector<ton::BlockIdExt> blkids;
          for (auto& id : f->ids_) {
            blkids.push_back(ton::create_block_id(std::move(id)));
          }
          td::actor::send_closure_later(Self, &TestNode::got_last_transactions, std::move(blkids),
                                        std::move(f->transactions_), workchain, addr, lt, hash, count, dump);
        }
      });
}

void TestNode::got_account_state(ton::BlockIdExt ref_blk, ton::BlockIdExt blk, ton::BlockIdExt shard_blk,
                                 td::BufferSlice shard_proof, td::BufferSlice proof, td::BufferSlice state,
                                 ton::WorkchainId workchain, ton::StdSmcAddress addr) {
  LOG(INFO) << "got account state for " << workchain << ":" << addr.to_hex() << " with respect to blocks "
            << blk.to_str() << (shard_blk == blk ? "" : std::string{" and "} + shard_blk.to_str());
  block::AccountState account_state;
  account_state.blk = blk;
  account_state.shard_blk = shard_blk;
  account_state.shard_proof = std::move(shard_proof);
  account_state.proof = std::move(proof);
  account_state.state = std::move(state);
  auto r_info = account_state.validate(ref_blk, block::StdAddress(workchain, addr));
  if (r_info.is_error()) {
    LOG(ERROR) << r_info.error().message();
    return;
  }
  auto out = td::TerminalIO::out();
  auto info = r_info.move_as_ok();
  if (info.root.not_null()) {
    out << "account state is ";
    std::ostringstream outp;
    block::gen::t_Account.print_ref(outp, info.root);
    vm::load_cell_slice(info.root).print_rec(outp);
    out << outp.str();
    out << "last transaction lt = " << info.last_trans_lt << " hash = " << info.last_trans_hash.to_hex() << std::endl;
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
  auto P = vm::std_boc_deserialize(std::move(proof));
  if (P.is_error()) {
    LOG(ERROR) << "cannot deserialize block transaction proof";
    return;
  }
  auto proof_root = P.move_as_ok();
  try {
    auto block_root = vm::MerkleProof::virtualize(std::move(proof_root), 1);
    if (block_root.is_null()) {
      LOG(ERROR) << "transaction block proof is invalid";
      return;
    }
    auto res1 = block::check_block_header_proof(block_root, blkid);
    if (res1.is_error()) {
      LOG(ERROR) << "error in transaction block header proof : " << res1.move_as_error().to_string();
      return;
    }
    auto trans_root_res = block::get_block_transaction_try(std::move(block_root), workchain, addr, trans_lt);
    if (trans_root_res.is_error()) {
      LOG(ERROR) << trans_root_res.move_as_error().message();
      return;
    }
    auto trans_root = trans_root_res.move_as_ok();
    if (trans_root.is_null() && root.not_null()) {
      LOG(ERROR) << "error checking transaction proof: proof claims there is no such transaction, but we have got "
                    "transaction data with hash "
                 << root->get_hash().bits().to_hex(256);
      return;
    }
    if (trans_root.not_null() && root.is_null()) {
      LOG(ERROR) << "error checking transaction proof: proof claims there is such a transaction with hash "
                 << trans_root->get_hash().bits().to_hex(256)
                 << ", but we have got no "
                    "transaction data";
      return;
    }
    if (trans_root.not_null() && trans_root->get_hash().bits().compare(root->get_hash().bits(), 256)) {
      LOG(ERROR) << "transaction hash mismatch: Merkle proof expects " << trans_root->get_hash().bits().to_hex(256)
                 << " but received data has " << root->get_hash().bits().to_hex(256);
      return;
    }
  } catch (vm::VmError err) {
    LOG(ERROR) << "error while traversing block transaction proof : " << err.get_msg();
    return;
  } catch (vm::VmVirtError err) {
    LOG(ERROR) << "virtualization error while traversing block transaction proof : " << err.get_msg();
    return;
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

bool unpack_addr(std::ostream& os, Ref<vm::CellSlice> csr) {
  ton::WorkchainId wc;
  ton::StdSmcAddress addr;
  if (!block::tlb::t_MsgAddressInt.extract_std_address(std::move(csr), wc, addr)) {
    os << "<cannot unpack address>";
    return false;
  }
  os << wc << ":" << addr.to_hex();
  return true;
}

bool unpack_message(std::ostream& os, Ref<vm::Cell> msg, int mode) {
  if (msg.is_null()) {
    os << "<message not found>";
    return true;
  }
  vm::CellSlice cs{vm::NoVmOrd(), msg};
  block::gen::CommonMsgInfo info;
  Ref<vm::CellSlice> src, dest;
  switch (block::gen::t_CommonMsgInfo.get_tag(cs)) {
    case block::gen::CommonMsgInfo::ext_in_msg_info: {
      block::gen::CommonMsgInfo::Record_ext_in_msg_info info;
      if (!tlb::unpack(cs, info)) {
        LOG(DEBUG) << "cannot unpack inbound external message";
        return false;
      }
      os << "EXT-IN-MSG";
      if (!(mode & 2)) {
        os << " TO: ";
        if (!unpack_addr(os, std::move(info.dest))) {
          return false;
        }
      }
      return true;
    }
    case block::gen::CommonMsgInfo::ext_out_msg_info: {
      block::gen::CommonMsgInfo::Record_ext_out_msg_info info;
      if (!tlb::unpack(cs, info)) {
        LOG(DEBUG) << "cannot unpack outbound external message";
        return false;
      }
      os << "EXT-OUT-MSG";
      if (!(mode & 1)) {
        os << " FROM: ";
        if (!unpack_addr(os, std::move(info.src))) {
          return false;
        }
      }
      os << " LT:" << info.created_lt << " UTIME:" << info.created_at;
      return true;
    }
    case block::gen::CommonMsgInfo::int_msg_info: {
      block::gen::CommonMsgInfo::Record_int_msg_info info;
      if (!tlb::unpack(cs, info)) {
        LOG(DEBUG) << "cannot unpack internal message";
        return false;
      }
      os << "INT-MSG";
      if (!(mode & 1)) {
        os << " FROM: ";
        if (!unpack_addr(os, std::move(info.src))) {
          return false;
        }
      }
      if (!(mode & 2)) {
        os << " TO: ";
        if (!unpack_addr(os, std::move(info.dest))) {
          return false;
        }
      }
      os << " LT:" << info.created_lt << " UTIME:" << info.created_at;
      td::RefInt256 value;
      Ref<vm::Cell> extra;
      if (!block::unpack_CurrencyCollection(info.value, value, extra)) {
        LOG(ERROR) << "cannot unpack message value";
        return false;
      }
      os << " VALUE:" << value;
      if (extra.not_null()) {
        os << "+extra";
      }
      return true;
    }
    default:
      LOG(ERROR) << "cannot unpack message";
      return false;
  }
}

std::string message_info_str(Ref<vm::Cell> msg, int mode) {
  std::ostringstream os;
  if (!unpack_message(os, msg, mode)) {
    return "<cannot unpack message>";
  } else {
    return os.str();
  }
}

void TestNode::got_last_transactions(std::vector<ton::BlockIdExt> blkids, td::BufferSlice transactions_boc,
                                     ton::WorkchainId workchain, ton::StdSmcAddress addr, ton::LogicalTime lt,
                                     ton::Bits256 hash, unsigned count, bool dump) {
  LOG(INFO) << "got up to " << count << " transactions for " << workchain << ":" << addr.to_hex()
            << " from last transaction " << lt << ":" << hash.to_hex();
  block::TransactionList transaction_list;
  transaction_list.blkids = blkids;
  transaction_list.lt = lt;
  transaction_list.hash = hash;
  transaction_list.transactions_boc = std::move(transactions_boc);
  auto r_info = transaction_list.validate();
  if (r_info.is_error()) {
    LOG(ERROR) << "got_last_transactions: " << r_info.error();
    return;
  }
  auto info = r_info.move_as_ok();
  unsigned c = 0;
  auto out = td::TerminalIO::out();
  CHECK(!info.transactions.empty());
  for (auto& info : info.transactions) {
    const auto& blkid = info.blkid;
    out << "transaction #" << c << " from block " << blkid.to_str() << (dump ? " is " : "\n");
    if (dump) {
      std::ostringstream outp;
      block::gen::t_Transaction.print_ref(outp, info.transaction);
      vm::load_cell_slice(info.transaction).print_rec(outp);
      out << outp.str();
    }
    block::gen::Transaction::Record trans;
    if (!tlb::unpack_cell(info.transaction, trans)) {
      LOG(ERROR) << "cannot unpack transaction #" << c;
      return;
    }
    out << "  time=" << trans.now << " outmsg_cnt=" << trans.outmsg_cnt << std::endl;
    auto in_msg = trans.in_msg->prefetch_ref();
    if (in_msg.is_null()) {
      out << "  (no inbound message)" << std::endl;
    } else {
      out << "  inbound message: " << message_info_str(in_msg, 2 * 0) << std::endl;
      if (dump) {
        out << "    " << block::gen::t_Message_Any.as_string_ref(in_msg, 4);  // indentation = 4 spaces
      }
    }
    vm::Dictionary dict{trans.out_msgs, 15};
    for (int x = 0; x < trans.outmsg_cnt && x < 100; x++) {
      auto out_msg = dict.lookup_ref(td::BitArray<15>{x});
      out << "  outbound message #" << x << ": " << message_info_str(out_msg, 1 * 0) << std::endl;
      if (dump) {
        out << "    " << block::gen::t_Message_Any.as_string_ref(out_msg, 4);
      }
    }
    register_blkid(blkid);  // unsafe?
  }
  auto& last = info.transactions.back();
  if (last.prev_trans_lt > 0) {
    out << "previous transaction has lt " << last.prev_trans_lt << " hash " << last.prev_trans_hash.to_hex()
        << std::endl;
    if (info.transactions.size() < count) {
      LOG(WARNING) << "obtained less transactions than required";
    }
  } else {
    out << "no preceding transactions (list complete)" << std::endl;
  }
}

bool TestNode::get_block_transactions(ton::BlockIdExt blkid, int mode, unsigned count, ton::Bits256 acc_addr,
                                      ton::LogicalTime lt) {
  if (!(ready_ && !client_.empty())) {
    return set_error("server connection not ready");
  }
  auto a = ton::create_tl_object<ton::lite_api::liteServer_transactionId3>(acc_addr, lt);
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::lite_api::liteServer_listBlockTransactions>(
                                        ton::create_tl_lite_block_id(blkid), mode, count, std::move(a), false, false),
                                    true);
  LOG(INFO) << "requesting " << count << " transactions from block " << blkid.to_str() << " starting from account "
            << acc_addr.to_hex() << " lt " << lt;
  return envelope_send_query(std::move(b), [Self = actor_id(this), mode](td::Result<td::BufferSlice> R) {
    if (R.is_error()) {
      return;
    }
    auto F = ton::fetch_tl_object<ton::lite_api::liteServer_blockTransactions>(R.move_as_ok(), true);
    if (F.is_error()) {
      LOG(ERROR) << "cannot parse answer to liteServer.listBlockTransactions";
    } else {
      auto f = F.move_as_ok();
      std::vector<TransId> transactions;
      for (auto& id : f->ids_) {
        transactions.emplace_back(id->account_, id->lt_, id->hash_);
      }
      td::actor::send_closure_later(Self, &TestNode::got_block_transactions, ton::create_block_id(f->id_), mode,
                                    f->req_count_, f->incomplete_, std::move(transactions), std::move(f->proof_));
    }
  });
}

void TestNode::got_block_transactions(ton::BlockIdExt blkid, int mode, unsigned req_count, bool incomplete,
                                      std::vector<TestNode::TransId> trans, td::BufferSlice proof) {
  LOG(INFO) << "got up to " << req_count << " transactions from block " << blkid.to_str();
  auto out = td::TerminalIO::out();
  int count = 0;
  for (auto& t : trans) {
    out << "transaction #" << ++count << ": account " << t.acc_addr.to_hex() << " lt " << t.trans_lt << " hash "
        << t.trans_hash.to_hex() << std::endl;
  }
  out << (incomplete ? "(block transaction list incomplete)" : "(end of block transaction list)") << std::endl;
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
      ton::create_tl_object<ton::lite_api::liteServer_getAllShardsInfo>(ton::create_tl_lite_block_id(blkid)), true);
  LOG(INFO) << "requesting recent shard configuration";
  return envelope_send_query(std::move(b), [Self = actor_id(this)](td::Result<td::BufferSlice> R) -> void {
    if (R.is_error()) {
      return;
    }
    auto F = ton::fetch_tl_object<ton::lite_api::liteServer_allShardsInfo>(R.move_as_ok(), true);
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
      ton::create_tl_object<ton::lite_api::liteServer_getBlock>(ton::create_tl_lite_block_id(blkid)), true);
  return envelope_send_query(
      std::move(b), [Self = actor_id(this), blkid, dump](td::Result<td::BufferSlice> res) -> void {
        if (res.is_error()) {
          LOG(ERROR) << "cannot obtain block " << blkid.to_str()
                     << " from server : " << res.move_as_error().to_string();
          return;
        } else {
          auto F = ton::fetch_tl_object<ton::lite_api::liteServer_blockData>(res.move_as_ok(), true);
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
      ton::create_tl_object<ton::lite_api::liteServer_getState>(ton::create_tl_lite_block_id(blkid)), true);
  return envelope_send_query(
      std::move(b), [Self = actor_id(this), blkid, dump](td::Result<td::BufferSlice> res) -> void {
        if (res.is_error()) {
          LOG(ERROR) << "cannot obtain state " << blkid.to_str()
                     << " from server : " << res.move_as_error().to_string();
          return;
        } else {
          auto F = ton::fetch_tl_object<ton::lite_api::liteServer_blockState>(res.move_as_ok(), true);
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
            td::actor::send_closure_later(Self, &TestNode::got_state, blk_id, f->root_hash_, f->file_hash_,
                                          std::move(f->data_), dump);
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
      ton::create_tl_object<ton::lite_api::liteServer_getBlockHeader>(ton::create_tl_lite_block_id(blkid), mode), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this), blkid](td::Result<td::BufferSlice> res) -> void {
    if (res.is_error()) {
      LOG(ERROR) << "cannot obtain block header for " << blkid.to_str()
                 << " from server : " << res.move_as_error().to_string();
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::lite_api::liteServer_blockHeader>(res.move_as_ok(), true);
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

bool TestNode::lookup_block(ton::ShardIdFull shard, int mode, td::uint64 arg) {
  ton::BlockId id{shard, mode & 1 ? (td::uint32)arg : 0};
  LOG(INFO) << "got block lookup request for " << id.to_str() << " with mode " << mode << " and argument " << arg;
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::lite_api::liteServer_lookupBlock>(
                                        mode, ton::create_tl_lite_block_id_simple(id), arg, (td::uint32)arg),
                                    true);
  return envelope_send_query(
      std::move(b), [Self = actor_id(this), id, mode, arg](td::Result<td::BufferSlice> res) -> void {
        if (res.is_error()) {
          LOG(ERROR) << "cannot look up block header for " << id.to_str() << " with mode " << mode << " and argument "
                     << arg << " from server : " << res.move_as_error().to_string();
          return;
        } else {
          auto F = ton::fetch_tl_object<ton::lite_api::liteServer_blockHeader>(res.move_as_ok(), true);
          if (F.is_error()) {
            LOG(ERROR) << "cannot parse answer to liteServer.lookupBlock : " << res.move_as_error().to_string();
          } else {
            auto f = F.move_as_ok();
            auto blk_id = ton::create_block_id(f->id_);
            LOG(INFO) << "obtained block header for " << blk_id.to_str() << " from server";
            td::actor::send_closure_later(Self, &TestNode::got_block_header, blk_id, std::move(f->header_proof_),
                                          f->mode_);
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
  ton::BlockIdExt mc_blkid;
  bool after_split;
  auto res = block::unpack_block_prev_blk_ext(root, blkid, prev, mc_blkid, after_split);
  if (res.is_error()) {
    LOG(ERROR) << "cannot unpack header for block " << blkid.to_str() << " : " << res.to_string();
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
      << " catchain_seqno=" << info.gen_catchain_seqno << " min_ref_mc_seqno=" << info.min_ref_mc_seqno;
  if (!info.not_master) {
    out << " is_key_block=" << info.key_block << " prev_key_block_seqno=" << info.prev_key_block_seqno;
  }
  out << std::endl;
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

int main(int argc, char* argv[]) {
  SET_VERBOSITY_LEVEL(verbosity_INFO);
  td::set_default_failure_signal_handler();

  td::actor::ActorOwn<TestNode> x;

  td::OptionsParser p;
  p.set_description("Test Lite Client for TON Blockchain");
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
  p.add_option('d', "daemonize", "set SIGHUP", [&]() {
    td::set_signal_handler(td::SignalType::HangUp, [](int sig) {
#if TD_DARWIN || TD_LINUX
      close(0);
      setsid();
#endif
    }).ensure();
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
#endif

  td::actor::Scheduler scheduler({2});

  scheduler.run_in_context([&] { x = td::actor::create_actor<TestNode>("testnode"); });

  scheduler.run_in_context([&] { p.run(argc, argv).ensure(); });
  scheduler.run_in_context([&] {
    td::actor::send_closure(x, &TestNode::run);
    x.release();
  });
  scheduler.run();

  return 0;
}
