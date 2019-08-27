#pragma once
#include "adnl/adnl-ext-client.h"
#include "tl-utils/tl-utils.hpp"
#include "ton/ton-types.h"
#include "terminal/terminal.h"
#include "vm/cells.h"
#include "web_server/server_http.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using td::Ref;

class TestNode : public td::actor::Actor {
 private:
  std::string local_config_ = "ton-local.config";
  std::string global_config_ = "ton-global.config";
  std::string load_files_dir_ ="./";

  td::actor::ActorOwn<ton::adnl::AdnlExtClient> client_;
  td::actor::ActorOwn<td::TerminalIO> io_;

  bool readline_enabled_ = true;
  td::int32 liteserver_idx_ = -1;

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

  std::vector<ton::BlockIdExt> known_blk_ids_;
  std::size_t shown_blk_ids_ = 0;

  std::unique_ptr<ton::adnl::AdnlExtClient::Callback> make_callback();

  struct TransId {
    ton::Bits256 acc_addr;
    ton::LogicalTime trans_lt;
    ton::Bits256 trans_hash;
    TransId(const ton::Bits256& addr_, ton::LogicalTime lt_, const ton::Bits256& hash_)
        : acc_addr(addr_), trans_lt(lt_), trans_hash(hash_) {
    }
  };

  void run_init_queries();
  bool get_server_time();
  //bool get_server_mc_block_id(bool silent = false); Moved to public methods
  void got_server_mc_block_id(ton::BlockIdExt blkid, ton::ZeroStateIdExt zstateid, bool silent);
  bool request_block(ton::BlockIdExt blkid);
  bool request_state(ton::BlockIdExt blkid);
  void got_mc_block(ton::BlockIdExt blkid, td::BufferSlice data);
  void got_mc_state(ton::BlockIdExt blkid, ton::RootHash root_hash, ton::FileHash file_hash, td::BufferSlice data);
  td::Status send_set_verbosity(std::string verbosity);
  td::Status send_ext_msg_from_filename(std::string filename);
  td::Status save_db_file(ton::FileHash file_hash, td::BufferSlice data);
  bool get_account_state(ton::WorkchainId workchain, ton::StdSmcAddress addr, ton::BlockIdExt ref_blkid);
  void got_account_state(ton::BlockIdExt ref_blk, ton::BlockIdExt blk, ton::BlockIdExt shard_blk,
                         td::BufferSlice shard_proof, td::BufferSlice proof, td::BufferSlice state,
                         ton::WorkchainId workchain, ton::StdSmcAddress addr);
  void got_account_state_web(ton::BlockIdExt ref_blk, ton::BlockIdExt blk, ton::BlockIdExt shard_blk,
                             td::BufferSlice shard_proof, td::BufferSlice proof, td::BufferSlice state,
                             ton::WorkchainId workchain, ton::StdSmcAddress addr,
                             std::shared_ptr<HttpServer::Response> response);
  bool get_all_shards(bool use_last = true, ton::BlockIdExt blkid = {});
  void got_all_shards(ton::BlockIdExt blk, td::BufferSlice proof, td::BufferSlice data);
  void got_all_shards_web(ton::BlockIdExt blk, td::BufferSlice proof, td::BufferSlice data,
                          std::shared_ptr<HttpServer::Response> response);
  bool get_block(ton::BlockIdExt blk, bool dump = false);
  void got_block(ton::BlockIdExt blkid, td::BufferSlice data, bool dump);
  void got_block_web(ton::BlockIdExt blkid, td::BufferSlice data, bool dump,
                     std::shared_ptr<HttpServer::Response> response);
  bool get_state(ton::BlockIdExt blk, bool dump = false);
  void got_state(ton::BlockIdExt blkid, ton::RootHash root_hash, ton::FileHash file_hash, td::BufferSlice data,
                 bool dump);
  bool get_block_header(ton::BlockIdExt blk, int mode);
  bool lookup_block(ton::ShardIdFull shard, int mode, td::uint64 arg);
  void got_block_header(ton::BlockIdExt blkid, td::BufferSlice data, int mode);
  bool show_block_header(ton::BlockIdExt blkid, Ref<vm::Cell> root, int mode);
  bool give_block_header_description(std::ostringstream& out, ton::BlockIdExt blkid, Ref<vm::Cell> root, int mode);
  bool show_state_header(ton::BlockIdExt blkid, Ref<vm::Cell> root, int mode);
  bool get_one_transaction(ton::BlockIdExt blkid, ton::WorkchainId workchain, ton::StdSmcAddress addr,
                           ton::LogicalTime lt, bool dump = false);
  void got_one_transaction(ton::BlockIdExt req_blkid, ton::BlockIdExt blkid, td::BufferSlice proof,
                           td::BufferSlice transaction, ton::WorkchainId workchain, ton::StdSmcAddress addr,
                           ton::LogicalTime trans_lt, bool dump);
  void got_one_transaction_web(ton::BlockIdExt req_blkid, ton::BlockIdExt blkid, td::BufferSlice proof,
                               td::BufferSlice transaction, ton::WorkchainId workchain, ton::StdSmcAddress addr,
                               ton::LogicalTime trans_lt, bool dump, std::shared_ptr<HttpServer::Response> response);
  bool get_last_transactions(ton::WorkchainId workchain, ton::StdSmcAddress addr, ton::LogicalTime lt,
                             ton::Bits256 hash, unsigned count, bool dump);
  void got_last_transactions(std::vector<ton::BlockIdExt> blkids, td::BufferSlice transactions_boc,
                             ton::WorkchainId workchain, ton::StdSmcAddress addr, ton::LogicalTime lt,
                             ton::Bits256 hash, unsigned count, bool dump);
  bool get_block_transactions(ton::BlockIdExt blkid, int mode, unsigned count, ton::Bits256 acc_addr,
                              ton::LogicalTime lt);
  void got_block_transactions(ton::BlockIdExt blkid, int mode, unsigned req_count, bool incomplete,
                              std::vector<TransId> trans, td::BufferSlice proof);
  void got_block_transactions_web(ton::BlockIdExt blkid, int mode, unsigned req_count, bool incomplete,
                                  std::vector<TransId> trans, td::BufferSlice proof,
                                  std::shared_ptr<HttpServer::Response> response);
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
  static int parse_hex_digit(int c);
  static bool parse_hash(const char* str, ton::Bits256& hash);
  static bool convert_uint64(std::string word, td::uint64& val);
  static bool convert_int64(std::string word, td::int64& val);
  static bool convert_uint32(std::string word, td::uint32& val);
  static bool convert_int32(std::string word, td::int32& val);
  static bool convert_shard_id(std::string str, ton::ShardIdFull& shard);
  bool parse_hash(ton::Bits256& hash);
  bool parse_lt(ton::LogicalTime& lt);
  bool parse_uint32(td::uint32& val);
  bool parse_shard_id(ton::ShardIdFull& shard);
  bool parse_block_id_ext(ton::BlockIdExt& blkid, bool allow_incomplete = false);
  bool parse_block_id_ext(std::string blk_id_string, ton::BlockIdExt& blkid, bool allow_incomplete = false) const;
  bool register_blkid(const ton::BlockIdExt& blkid);
  bool show_new_blkids(bool all = false);
  bool complete_blkid(ton::BlockId partial_blkid, ton::BlockIdExt& complete_blkid) const;

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

  void set_load_files_dir(std::string str) {
    load_files_dir_ = str;
  }
  void start_up() override {
  }
  void tear_down() override {
    // FIXME: do not work in windows
    //td::actor::SchedulerContext::get()->stop();
  }

  bool envelope_send_query(td::BufferSlice query, td::Promise<td::BufferSlice> promise);
  void parse_line(td::BufferSlice data);

  bool get_server_mc_block_id(bool silent = false);

  // web server methods
  bool envelope_send_web(td::BufferSlice query, td::Promise<td::BufferSlice> promise, std::shared_ptr<HttpServer::Response> response);
  void get_server_time_web(std::shared_ptr<HttpServer::Response> response);
  void get_account_state_web(std::string address, std::string ref_blkid_str, std::shared_ptr<HttpServer::Response> response);
  void get_block_web(std::string blkid_str, std::shared_ptr<HttpServer::Response> response, bool dump = true);
  void get_block_transactions_web(std::string ref_blkid_str, int mode, unsigned count, std::shared_ptr<HttpServer::Response> response);
  void get_one_transaction_web(ton::BlockIdExt blkid, ton::WorkchainId workchain, ton::StdSmcAddress addr,
                               ton::LogicalTime lt, std::shared_ptr<HttpServer::Response> response,
                               bool dump = false);
  void get_server_mc_block_id_web(std::shared_ptr<HttpServer::Response> response);
  void get_all_shards_web(std::shared_ptr<HttpServer::Response> response, bool use_last = true, std::string blkid_str = "");
  void send_ext_msg_from_filename_web(std::string filename, std::shared_ptr<HttpServer::Response> response);


  TestNode() {
  }

  void run();
  void silent_update(){
    get_server_mc_block_id(true);
  }
};
