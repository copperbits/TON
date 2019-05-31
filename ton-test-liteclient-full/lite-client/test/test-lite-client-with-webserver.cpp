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
#include "vm/boc.h"
#include "vm/cellops.h"
#include "web_server/server_http.hpp"

#if TD_DARWIN || TD_LINUX
#include <unistd.h>
#include <fcntl.h>
#endif
#include <iostream>
#include <string>
#include <sstream>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int verbosity;

template <std::size_t size>
std::ostream& operator<<(std::ostream& stream, const td::UInt<size>& x) {
  for (size_t i = 0; i < size / 8; i++) {
    stream << td::format::hex_digit((x.raw[i] >> 4) & 15) << td::format::hex_digit(x.raw[i] & 15);
  }

  return stream;
}

class TestNode : public td::actor::Actor {
 private:
  std::string local_config_ = "ton-local.config";
  std::string global_config_ = "ton-global.config";

  td::actor::ActorOwn<ton::AdnlExtClient> client_;
  td::actor::ActorOwn<td::TerminalIO> io_;

  bool readline_enabled_ = true;
  td::int32 liteserver_idx_ = -1;

  std::unique_ptr<ton::AdnlExtClient::Callback> make_callback() {
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

  bool ready_ = false;
  bool inited_ = false;
  std::string db_root_;

  int server_time_ = 0;
  int server_time_got_at_ = 0;

  ton::ZeroStateIdExt zstate_id_;
  ton::BlockIdExt mc_last_id_;

  ton::BlockIdExt last_block_id_, last_state_id_;
  td::BufferSlice last_block_data_, last_state_data_;

  std::string line_;
  const char *parse_ptr_, *parse_end_;
  td::Status error_;

  void run_init_queries();
  bool get_server_time();
  bool get_server_mc_block_id();
  bool get_server_mc_block_id_silent();
  void got_server_mc_block_id(ton::BlockIdExt blkid, ton::ZeroStateIdExt zstateid);
  void got_server_mc_block_id_silent(ton::BlockIdExt blkid, ton::ZeroStateIdExt zstateid);
  bool request_block(ton::BlockIdExt blkid);
  bool request_state(ton::BlockIdExt blkid);
  void got_block(ton::BlockIdExt blkid, td::BufferSlice data);
  void got_state(ton::BlockIdExt blkid, ton::RootHash root_hash, ton::FileHash file_hash, td::BufferSlice data);
  td::Status send_set_verbosity(std::string verbosity);
  td::Status send_ext_msg_from_filename(std::string filename);
  td::Status save_db_file(ton::FileHash file_hash, td::BufferSlice data);
  bool get_account_state(ton::WorkchainId workchain, ton::StdSmcAddress addr);
  void got_account_state(ton::BlockIdExt blk, ton::BlockIdExt shard_blk, td::BufferSlice shard_proof,
                         td::BufferSlice proof, td::BufferSlice state, ton::WorkchainId workchain,
                         ton::StdSmcAddress addr);
  void got_account_state_web(ton::BlockIdExt blk, ton::BlockIdExt shard_blk, td::BufferSlice shard_proof,
                             td::BufferSlice proof, td::BufferSlice state, ton::WorkchainId workchain,
                             ton::StdSmcAddress addr, std::shared_ptr<HttpServer::Response> response);

  bool do_parse_line();
  bool show_help(std::string command);
  std::string get_word(char delim = ' ');
  int skipspc();
  std::string get_line_tail(bool remove_spaces = true) const;
  bool eoln() const;
  bool seekeoln();
  bool set_error(td::Status error);
  bool set_error(std::string err_msg);
  void show_context() const;
  bool parse_account_addr(ton::WorkchainId& wc, ton::StdSmcAddress& addr);
  static bool parse_account_addr(std::string acc_string, ton::WorkchainId& wc, ton::StdSmcAddress& addr);

 public:
  void conn_ready() {
    LOG(ERROR) << "conn ready";
    ready_ = true;
    if (!inited_) {
      run_init_queries();
    }
  }
  void conn_closed() {
    ready_ = false;
  }
  void set_local_config(std::string str) {
    local_config_ = str;
  }
  void set_global_config(std::string str) {
    global_config_ = str;
  }
  void set_db_root(std::string db_root) {
    db_root_ = db_root;
  }
  void set_readline_enabled(bool value) {
    readline_enabled_ = value;
  }
  void set_liteserver_idx(td::int32 idx) {
    liteserver_idx_ = idx;
  }

  void start_up() override {
  }
  void tear_down() override {
    // FIXME: do not work in windows
    //td::actor::SchedulerContext::get()->stop();
  }

  bool envelope_send_query(td::BufferSlice query, td::Promise<td::BufferSlice> promise);
  bool envelope_send_web(td::BufferSlice query, td::Promise<td::BufferSlice> promise, std::shared_ptr<HttpServer::Response> response);
  void parse_line(td::BufferSlice data);

  // web server methods
  void get_server_time_web(std::shared_ptr<HttpServer::Response> response);
  void get_account_state_web(std::string address, std::shared_ptr<HttpServer::Response> response);

  TestNode() {
  }

  void run() {
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
    auto idx = liteserver_idx_ >= 0 ? liteserver_idx_
                                     : td::Random::fast(0, static_cast<td::uint32>(gc.liteclients_.size() - 1));
    CHECK(idx >= 0 && static_cast<td::uint32>(idx) <= gc.liteclients_.size());
    auto& cli = gc.liteclients_[idx];
    td::IPAddress addr;
    addr.init_host_port(td::IPAddress::ipv4_to_str(cli->ip_), cli->port_).ensure();
    td::TerminalIO::out() << "using liteserver " << idx << " with addr " << addr << "\n";

    client_ = ton::AdnlExtClient::create(ton::AdnlNodeIdFull{cli->id_}, addr, make_callback());
  }

  void web_last(){
    get_server_mc_block_id_silent();
  }
};

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

bool TestNode::envelope_send_web(td::BufferSlice query,
                                 td::Promise<td::BufferSlice> promise,
                                 std::shared_ptr<HttpServer::Response> response) {
  if (!ready_ || client_.empty()) {
    response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                      "failed to send query to server: not ready");
    return false;
  }
  auto P = td::PromiseCreator::lambda([promise = std::move(promise), response](td::Result<td::BufferSlice> R) mutable {
    if (R.is_error()) {
      auto err = R.move_as_error();
      response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                        "failed query");
      promise.set_error(std::move(err));
      return;
    }
    auto data = R.move_as_ok();
    auto F = ton::fetch_tl_object<ton::ton_api::liteServer_error>(data.clone(), true);
    if (F.is_ok()) {
      auto f = F.move_as_ok();
      auto err = td::Status::Error(f->code_, f->message_);
      response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                        "received error");
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

bool TestNode::get_server_time() {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getTime>(), true);
  return envelope_send_query(std::move(b), [&, Self = actor_id(this)](td::Result<td::BufferSlice> res) -> void {
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

void TestNode::get_server_time_web(std::shared_ptr<HttpServer::Response> response) {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getTime>(), true);

  envelope_send_web(std::move(b), [&, Self = actor_id(this), response](td::Result<td::BufferSlice> res) -> void {
    if (res.is_error()) {
      response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                        "cannot get server time");
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_currentTime>(res.move_as_ok(), true);
      if (F.is_error()) {
        response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                          "cannot parse answer to liteServer.getTime");
      } else {
        server_time_ = F.move_as_ok()->now_;
        server_time_got_at_ = static_cast<td::uint32>(td::Clocks::system());
        response -> write(std::to_string(server_time_));
      }
    }
  }, response);
}

bool TestNode::get_server_mc_block_id() {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getMasterchainInfo>(), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this)](td::Result<td::BufferSlice> res) -> void {
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
  if (!mc_last_id_.is_valid()) {
    mc_last_id_ = blkid;
    request_block(blkid);
    // request_state(blkid);
  } else if (mc_last_id_.id.seqno < blkid.id.seqno) {
    mc_last_id_ = blkid;
  }
}

bool TestNode::get_server_mc_block_id_silent() {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getMasterchainInfo>(), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this)](td::Result<td::BufferSlice> res) -> void {
    if (res.is_error()) {
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_masterchainInfo>(res.move_as_ok(), true);
      if (F.is_error()) {
      } else {
        auto f = F.move_as_ok();
        auto blk_id = create_block_id(f->last_);
        auto zstate_id = create_zero_state_id(f->init_);
        td::actor::send_closure_later(Self, &TestNode::got_server_mc_block_id_silent, blk_id, zstate_id);
      }
    }
  });
}

void TestNode::got_server_mc_block_id_silent(ton::BlockIdExt blkid, ton::ZeroStateIdExt zstateid) {
  if (!zstate_id_.is_valid()) {
    zstate_id_ = zstateid;
  } else if (zstate_id_ != zstateid) {
    stop();
    return;
  }
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
  return envelope_send_query(std::move(b), [Self = actor_id(this), blkid](td::Result<td::BufferSlice> res) -> void {
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
        td::actor::send_closure_later(Self, &TestNode::got_block, blk_id, std::move(f->data_));
      }
    }
  });
}

bool TestNode::request_state(ton::BlockIdExt blkid) {
  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::ton_api::liteServer_getState>(ton::create_tl_block_id(blkid)), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this), blkid](td::Result<td::BufferSlice> res) -> void {
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
        td::actor::send_closure_later(Self, &TestNode::got_state, blk_id, ton::UInt256_2_Bits256(f->root_hash_),
                                      ton::UInt256_2_Bits256(f->file_hash_), std::move(f->data_));
      }
    }
  });
}

void TestNode::got_block(ton::BlockIdExt blkid, td::BufferSlice data) {
  LOG(INFO) << "obtained " << data.size() << " data bytes for block " << blkid.to_str();
  ton::FileHash fhash;
  td::sha256(data.as_slice(), fhash.as_slice());
  if (fhash != blkid.file_hash) {
    LOG(ERROR) << "file hash mismatch for block " << blkid.to_str() << ": expected " << blkid.file_hash.to_hex()
               << ", computed " << fhash.to_hex();
    return;
  }
  last_block_id_ = blkid;
  last_block_data_ = data.clone();
  if (!db_root_.empty()) {
    auto res = save_db_file(fhash, std::move(data));
    if (res.is_error()) {
      LOG(ERROR) << "error saving block file: " << res.to_string();
    }
  }
}

void TestNode::got_state(ton::BlockIdExt blkid, ton::RootHash root_hash, ton::FileHash file_hash,
                         td::BufferSlice data) {
  LOG(INFO) << "obtained " << data.size() << " state bytes for block " << blkid.to_str();
  ton::FileHash fhash;
  td::sha256(data.as_slice(), fhash.as_slice());
  if (fhash != file_hash) {
    LOG(ERROR) << "file hash mismatch for state " << blkid.to_str() << ": expected " << file_hash.to_hex()
               << ", computed " << fhash.to_hex();
    return;
  }
  last_state_id_ = blkid;
  last_state_data_ = data.clone();
  if (!db_root_.empty()) {
    auto res = save_db_file(fhash, std::move(data));
    if (res.is_error()) {
      LOG(ERROR) << "error saving state file: " << res.to_string();
    }
  }
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

bool TestNode::parse_account_addr(std::string acc_string, ton::WorkchainId& wc, ton::StdSmcAddress& addr) {
  block::StdAddress a{acc_string};
  if (a.is_valid()) {
    wc = a.workchain;
    addr = a.addr;
    return true;
  }
  auto pos = acc_string.find(':');
  if (pos != std::string::npos) {
    std::string tmp{acc_string, 0, pos};
    char* end = 0;
    wc = static_cast<ton::WorkchainId>(strtoll(tmp.c_str(), &end, 10));
    if (end != tmp.c_str() + pos) {
      return false;
    }
    if (wc != 0 && wc != -1) {
      return false;
    }
    acc_string.erase(0, pos + 1);
  }
  LOG(DEBUG) << "parsing " << acc_string << " address";
  if (acc_string.size() == 64) {
    int i = 0;
    for (int c : acc_string) {
      int x = -1, m = 15;
      c |= 0x20;
      if (c >= '0' && c <= '9') {
        x = c - '0';
      } else if (c >= 'a' && c <= 'f') {
        x = c - 'a' + 10;
      } else {
        i = -1;
        break;
      }
      if (!(i & 1)) {
        x <<= 4;
        m <<= 4;
      }
      addr.data()[i >> 1] = (unsigned char)((addr.data()[i >> 1] & ~m) | x);
      i++;
    }
    if (i >= 0) {
      return wc != ton::workchainInvalid;
    }
  }
  return false;
}

bool TestNode::parse_account_addr(ton::WorkchainId& wc, ton::StdSmcAddress& addr) {
  return parse_account_addr(get_word(), wc, addr) || set_error("cannot parse account address");
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
  td::TerminalIO::out() << "list of available commands:\n"
                           "time\tGet server time\n"
                           "last\tGet last block and state info from server\n"
                           "sendfile <filename>\tLoad a serialized message from <filename> and send it to server\n"
                           "status\tShow connection and local database status\n"
                           "getaccount <addr>\tLoads the most recent state of specified account; <addr> is in "
                           "[<workchain>:]<hex-or-base64-addr> format\n"
                           "privkey <filename>\tLoads a private key from file\n"
                           "help [<command>]\tThis help\n"
                           "quit\tExit\n";
  return true;
}

bool TestNode::do_parse_line() {
  ton::WorkchainId workchain = ton::masterchainId;  // change to basechain later
  ton::StdSmcAddress addr;
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
    return parse_account_addr(workchain, addr) && seekeoln() && get_account_state(workchain, addr);
  } else if (word == "quit" && eoln()) {
    LOG(INFO) << "Exiting";
    stop();
    exit(0);
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

bool TestNode::get_account_state(ton::WorkchainId workchain, ton::StdSmcAddress addr) {
  if (!mc_last_id_.is_valid()) {
    return set_error("must obtain last block information before making other queries");
  }
  if (!(ready_ && !client_.empty())) {
    return set_error("server connection not ready");
  }
  auto a = ton::create_tl_object<ton::ton_api::liteServer_accountId>(workchain, ton::Bits256_2_UInt256(addr));
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getAccountState>(
                                        ton::create_tl_block_id(mc_last_id_), std::move(a)),
                                    true);
  LOG(INFO) << "requesting account state for " << workchain << ":" << addr.to_hex();
  return envelope_send_query(
      std::move(b), [Self = actor_id(this), workchain, addr](td::Result<td::BufferSlice> R) -> void {
        if (R.is_error()) {
          return;
        }
        auto F = ton::fetch_tl_object<ton::ton_api::liteServer_accountState>(R.move_as_ok(), true);
        if (F.is_error()) {
          LOG(ERROR) << "cannot parse answer to liteServer.getAccountState";
        } else {
          auto f = F.move_as_ok();
          td::actor::send_closure_later(Self, &TestNode::got_account_state, ton::create_block_id(f->id_),
                                        ton::create_block_id(f->shardblk_), std::move(f->shard_proof_),
                                        std::move(f->proof_), std::move(f->state_), workchain, addr);
        }
      });
}

void TestNode::get_account_state_web(std::string address, std::shared_ptr<HttpServer::Response> response) {
  ton::WorkchainId workchain = ton::masterchainId;  // change to basechain later
  ton::StdSmcAddress addr;
  if (!TestNode::parse_account_addr(address, workchain, addr)){
    response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                      "parse_account_addr fail");
    return;
  }

  if (!mc_last_id_.is_valid()) {
    response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                      "must obtain last block information before making other queries");
    return;
  }
  if (!(ready_ && !client_.empty())) {
    response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                      "server connection not ready");
    return;
  }

  auto a = ton::create_tl_object<ton::ton_api::liteServer_accountId>(workchain, ton::Bits256_2_UInt256(addr));
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getAccountState>(
                                        ton::create_tl_block_id(mc_last_id_), std::move(a)),
                                    true);

  envelope_send_web(
    std::move(b), [Self = actor_id(this), workchain, addr, response](td::Result<td::BufferSlice> R) -> void {
      if (R.is_error()) {
        response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                          "Unknown Error");
        return;
      }
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_accountState>(R.move_as_ok(), true);
      if (F.is_error()) {
        response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                          "cannot parse answer to liteServer.getAccountState");
      } else {
        auto f = F.move_as_ok();
        td::actor::send_closure_later(Self, &TestNode::got_account_state_web, ton::create_block_id(f->id_),
                                      ton::create_block_id(f->shardblk_), std::move(f->shard_proof_),
                                      std::move(f->proof_), std::move(f->state_), workchain, addr, response);
      }
    }, response);
}

void TestNode::got_account_state(ton::BlockIdExt blk, ton::BlockIdExt shard_blk, td::BufferSlice shard_proof,
                                 td::BufferSlice proof, td::BufferSlice state, ton::WorkchainId workchain,
                                 ton::StdSmcAddress addr) {
  LOG(INFO) << "got account state for " << workchain << ":" << addr.to_hex() << " with respect to blocks "
            << blk.to_str() << " and " << shard_blk.to_str();
  if (state.empty()) {
    td::TerminalIO::out() << "account state is empty" << '\n';
  } else {
    auto R = vm::std_boc_deserialize(state.clone());
    if (R.is_error()) {
      LOG(ERROR) << "cannot deserialize account state";
      return;
    }
    auto root = R.move_as_ok();
    auto out = td::TerminalIO::out();
    out << "account state is ";
    std::ostringstream outp;
    block::gen::t_Account.print_ref(outp, root);
    vm::load_cell_slice(root).print_rec(outp);
    out << outp.str();
  }
}

void TestNode::got_account_state_web(ton::BlockIdExt blk, ton::BlockIdExt shard_blk, td::BufferSlice shard_proof,
                                     td::BufferSlice proof, td::BufferSlice state, ton::WorkchainId workchain,
                                     ton::StdSmcAddress addr, std::shared_ptr<HttpServer::Response> response) {
  if (state.empty()) {
    response -> write("account state is empty");
  } else {
    auto R = vm::std_boc_deserialize(state.clone());
    if (R.is_error()) {
      response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                        "cannot deserialize account state");
      return;
    }
    auto root = R.move_as_ok();
    std::ostringstream outp;
    block::gen::t_Account.print_ref(outp, root);
    vm::load_cell_slice(root).print_rec(outp);
    response -> write(outp.str());
  }
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


void run_web_server(td::actor::Scheduler* scheduler, td::actor::ActorOwn<TestNode>* x){
  HttpServer server;
  server.config.port = 8000;

  // get a time
  server.resource["^/time$"]["GET"] = [scheduler, x](std::shared_ptr<HttpServer::Response> response,
                                                     std::shared_ptr<HttpServer::Request> request) {

    std::thread work_thread([response, scheduler, x] {
      scheduler -> run_in_context([&] {
        td::actor::send_closure(x -> get(), &TestNode::get_server_time_web, response);
      });
    });
    work_thread.detach();
  };
  //

  // get a balance
  server.resource["^/getaccount/(.+)$"]["GET"] = [scheduler, x](std::shared_ptr<HttpServer::Response> response,
                                                                          std::shared_ptr<HttpServer::Request> request) {
    std::string address = request -> path_match[1].str();

    std::thread work_thread([response, scheduler, x, address] {
      scheduler -> run_in_context([&] {
        td::actor::send_closure(x -> get(), &TestNode::get_account_state_web, address, response);
      });
    });
    work_thread.detach();
  };
  //

  server.start();
}


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
  std::thread webserver = std::thread(run_web_server, &scheduler, &x);
  // updater thread called 'last' command
  std::thread updater = std::thread(run_updater, &scheduler, &x);

  scheduler.run();

  return 0;
}
