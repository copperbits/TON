#pragma once
#include "adnl/adnl-ext-client.h"
#include "tl-utils/tl-utils.hpp"
#include "ton/ton-types.h"
#include "terminal/terminal.h"
#include "vm/cells.h"

using td::Ref;

class TestNode : public td::actor::Actor {
 private:
  std::string local_config_ = "ton-local.config";
  std::string global_config_ = "ton-global.config";

  td::actor::ActorOwn<ton::AdnlExtClient> client_;
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

  std::unique_ptr<ton::AdnlExtClient::Callback> make_callback();

  void run_init_queries();
  bool get_server_time();
  bool get_server_mc_block_id();
  void got_server_mc_block_id(ton::BlockIdExt blkid, ton::ZeroStateIdExt zstateid);
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
  bool get_all_shards(bool use_last = true, ton::BlockIdExt blkid = {});
  void got_all_shards(ton::BlockIdExt blk, td::BufferSlice proof, td::BufferSlice data);
  bool get_block(ton::BlockIdExt blk, bool dump = false);
  void got_block(ton::BlockIdExt blkid, td::BufferSlice data, bool dump);
  bool get_state(ton::BlockIdExt blk, bool dump = false);
  void got_state(ton::BlockIdExt blkid, ton::RootHash root_hash, ton::FileHash file_hash, td::BufferSlice data,
                 bool dump);
  bool get_block_header(ton::BlockIdExt blk, int mode);
  void got_block_header(ton::BlockIdExt blkid, td::BufferSlice data, int mode);
  bool show_block_header(ton::BlockIdExt blkid, Ref<vm::Cell> root, int mode);
  bool show_state_header(ton::BlockIdExt blkid, Ref<vm::Cell> root, int mode);
  bool get_one_transaction(ton::BlockIdExt blkid, ton::WorkchainId workchain, ton::StdSmcAddress addr,
                           ton::LogicalTime lt, bool dump = false);
  void got_one_transaction(ton::BlockIdExt req_blkid, ton::BlockIdExt blkid, td::BufferSlice proof,
                           td::BufferSlice transaction, ton::WorkchainId workchain, ton::StdSmcAddress addr,
                           ton::LogicalTime trans_lt, bool dump);
  bool get_last_transactions(ton::WorkchainId workchain, ton::StdSmcAddress addr, ton::LogicalTime lt,
                             ton::Bits256 hash, unsigned count, bool dump);
  void got_last_transactions(std::vector<ton::BlockIdExt> blkids, td::BufferSlice transactions_boc,
                             ton::WorkchainId workchain, ton::StdSmcAddress addr, ton::LogicalTime lt,
                             ton::Bits256 hash, unsigned count, bool dump);

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
  static bool parse_uint64(std::string word, td::uint64& val);
  bool parse_hash(ton::Bits256& hash);
  bool parse_lt(ton::LogicalTime& lt);
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

  void start_up() override {
  }
  void tear_down() override {
    // FIXME: do not work in windows
    //td::actor::SchedulerContext::get()->stop();
  }

  bool envelope_send_query(td::BufferSlice query, td::Promise<td::BufferSlice> promise);
  void parse_line(td::BufferSlice data);

  TestNode() {
  }

  void run();
};
