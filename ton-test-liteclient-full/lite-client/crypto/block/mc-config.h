#pragma once
#include "common/refcnt.hpp"
#include "vm/db/StaticBagOfCellsDb.h"
#include "vm/dict.h"
#include "ton/ton-types.h"
#include "validator/interfaces/config.h"
#include "validator/interfaces/validator-full-id.h"
#include "common/bitstring.h"
#include "block.h"
#include <vector>
#include <map>
#include <set>
#include <cstring>

namespace block {
using td::Ref;

struct ValidatorDescr {
  ton::Ed25519_PublicKey pubkey;
  td::uint64 weight;
  td::uint64 cum_weight;
  ValidatorDescr() = default;
  ValidatorDescr(const td::BitArray<256>& _pubkey, td::uint64 _weight, td::uint64 _cum_weight)
      : pubkey(_pubkey), weight(_weight), cum_weight(_cum_weight) {
  }
  ValidatorDescr(const ton::Ed25519_PublicKey& _pubkey, td::uint64 _weight, td::uint64 _cum_weight)
      : pubkey(_pubkey), weight(_weight), cum_weight(_cum_weight) {
  }
  bool operator<(td::uint64 wt_pos) const & {
    return cum_weight < wt_pos;
  }
};

struct ValidatorSet {
  unsigned utime_since;
  unsigned utime_until;
  int total;
  int main;
  td::uint64 total_weight;
  std::vector<ValidatorDescr> list;
  ValidatorSet() = default;
  ValidatorSet(unsigned _since, unsigned _until, int _total, int _main = 0)
      : utime_since(_since), utime_until(_until), total(_total), main(_main > 0 ? _main : _total), total_weight(0) {
  }
  const ValidatorDescr& operator[](unsigned i) const {
    return list[i];
  }
  const ValidatorDescr& at_weight(td::uint64 weight_pos) const;
};

#pragma pack(push, 1)
// this structure is hashed with SHA512 to produce pseudo-random bit stream in do_compute_validator_set()
// NB: all integers (including 256-bit seed) are actually big-endian
struct validator_set_descr {
  unsigned char seed[32];  // seed for validator set computation, set to zero if none
  td::uint64 shard;
  td::int32 workchain;
  td::uint32 cc_seqno;
  validator_set_descr() = default;
  validator_set_descr(ton::ShardIdFull shard_id, ton::CatchainSeqno cc_seqno_, bool flag)
      : shard(td::bswap64(shard_id.shard))
      , workchain(td::bswap32(shard_id.workchain))
      , cc_seqno(td::bswap32(cc_seqno_)) {
  }
  validator_set_descr(ton::ShardIdFull shard_id, ton::CatchainSeqno cc_seqno_)
      : validator_set_descr(shard_id, cc_seqno_, false) {
    memset(seed, 0, 32);
  }
  validator_set_descr(ton::ShardIdFull shard_id, ton::CatchainSeqno cc_seqno_, const unsigned char seed_[32])
      : validator_set_descr(shard_id, cc_seqno_, false) {
    memcpy(seed, seed_, 32);
  }
  validator_set_descr(ton::ShardIdFull shard_id, ton::CatchainSeqno cc_seqno_, td::ConstBitPtr seed_)
      : validator_set_descr(shard_id, cc_seqno_, false) {
    td::BitPtr{seed}.copy_from(seed_, 256);
  }
  validator_set_descr(ton::ShardIdFull shard_id, ton::CatchainSeqno cc_seqno_, const td::Bits256& seed_)
      : validator_set_descr(shard_id, cc_seqno_, false) {
    td::BitPtr{seed}.copy_from(seed_.cbits(), 256);
  }
  void incr_seed();
  void hash_to(unsigned char hash_buffer[64]) const;
};
#pragma pack(pop)

class ValidatorSetPRNG {
  validator_set_descr data;
  union {
    unsigned char hash[64];
    td::uint64 hash_longs[8];
  };
  int pos{0}, limit{0};

 public:
  ValidatorSetPRNG() = default;
  ValidatorSetPRNG(ton::ShardIdFull shard_id, ton::CatchainSeqno cc_seqno_) : data(shard_id, cc_seqno_) {
  }
  ValidatorSetPRNG(ton::ShardIdFull shard_id, ton::CatchainSeqno cc_seqno_, const unsigned char seed_[32])
      : data(shard_id, cc_seqno_, seed_) {
  }
  ValidatorSetPRNG(ton::ShardIdFull shard_id, ton::CatchainSeqno cc_seqno_, td::ConstBitPtr seed_)
      : data(shard_id, cc_seqno_, std::move(seed_)) {
  }
  ValidatorSetPRNG(ton::ShardIdFull shard_id, ton::CatchainSeqno cc_seqno_, const td::Bits256& seed_)
      : data(shard_id, cc_seqno_, seed_) {
  }
  td::uint64 next_ulong();
  td::uint64 next_ranged(td::uint64 range);  // integer in 0 .. range-1
  ValidatorSetPRNG& operator>>(td::uint64& x) {
    x = next_ulong();
    return *this;
  }
};

struct McShardHash : public ton::validator::McShardHash {
  ton::BlockIdExt blk_;
  ton::LogicalTime start_lt_, end_lt_;
  ton::UnixTime gen_utime_{0};
  ton::UnixTime fsm_utime_{0};
  ton::UnixTime fsm_interval_{0};
  ton::BlockSeqno min_ref_mc_seqno_{-1U};
  FsmState fsm_{FsmState::fsm_none};
  bool before_split_{false}, before_merge_{false}, want_split_{false}, want_merge_{false};
  bool nx_cc_updated_{false};
  ton::CatchainSeqno next_catchain_seqno_{-1U};
  ton::ShardId next_validator_shard_{ton::shardIdAll};
  McShardHash(const ton::BlockId& id, ton::LogicalTime start_lt, ton::LogicalTime end_lt, ton::UnixTime gen_utime,
              const ton::BlockHash& root_hash, const ton::FileHash& file_hash, ton::BlockSeqno min_ref_mc_seqno = -1u,
              ton::CatchainSeqno cc_seqno = -1u, ton::ShardId val_shard = 0, bool nx_cc_updated = false,
              bool before_split = false, bool before_merge = false, bool want_split = false, bool want_merge = false)
      : blk_(id, root_hash, file_hash)
      , start_lt_(start_lt)
      , end_lt_(end_lt)
      , gen_utime_(gen_utime)
      , min_ref_mc_seqno_(min_ref_mc_seqno)
      , before_split_(before_split)
      , before_merge_(before_merge)
      , want_split_(want_split)
      , want_merge_(want_merge)
      , nx_cc_updated_(nx_cc_updated)
      , next_catchain_seqno_(cc_seqno)
      , next_validator_shard_(val_shard ? val_shard : id.shard) {
  }
  McShardHash(const ton::BlockIdExt& blk, ton::LogicalTime start_lt, ton::LogicalTime end_lt)
      : blk_(blk), start_lt_(start_lt), end_lt_(end_lt) {
  }
  McShardHash(const McShardHash&) = default;
  bool is_valid() const {
    return blk_.is_valid();
  }
  ton::BlockIdExt top_block_id() const override final {
    return blk_;
  }
  //  ZeroStateIdExt zero_state() const override;
  ton::LogicalTime start_lt() const override final {
    return start_lt_;
  }
  ton::LogicalTime end_lt() const override final {
    return end_lt_;
  }
  ton::UnixTime fsm_utime() const override final {
    return fsm_utime_;
  }
  ton::UnixTime fsm_utime_end() const {
    return fsm_utime_ + fsm_interval_;
  }
  ton::UnixTime created_at() const {
    return gen_utime_;
  }
  FsmState fsm_state() const override final {
    return fsm_;
  }
  bool is_fsm_none() const {
    return fsm_ == FsmState::fsm_none;
  }
  bool is_fsm_split() const {
    return fsm_ == FsmState::fsm_split;
  }
  bool is_fsm_merge() const {
    return fsm_ == FsmState::fsm_merge;
  }
  ton::ShardIdFull shard() const override final {
    return ton::ShardIdFull(blk_);
  }
  ton::WorkchainId workchain() const {
    return blk_.id.workchain;
  }
  bool before_split() const override final {
    return before_split_;
  }
  bool before_merge() const override final {
    return before_merge_;
  }
  ton::BlockSeqno seqno() const {
    return blk_.id.seqno;
  }
  void clear_fsm() {
    fsm_ = FsmState::fsm_none;
  }
  void set_fsm(FsmState fsm, ton::UnixTime fsm_utime, ton::UnixTime fsm_interval);
  void set_fsm_split(ton::UnixTime fsm_utime, ton::UnixTime fsm_interval) {
    set_fsm(FsmState::fsm_split, fsm_utime, fsm_interval);
  }
  void set_fsm_merge(ton::UnixTime fsm_utime, ton::UnixTime fsm_interval) {
    set_fsm(FsmState::fsm_merge, fsm_utime, fsm_interval);
  }
  bool pack(vm::CellBuilder& cb) const;
  static Ref<McShardHash> unpack(vm::CellSlice& cs, ton::ShardIdFull id);
  static Ref<McShardHash> from_block(Ref<vm::Cell> block_root, const ton::FileHash& _fhash);
  McShardHash* make_copy() const override {
    return new McShardHash(*this);
  }
};

struct McShardDescr final : public McShardHash {
  Ref<vm::Cell> block_root;
  Ref<vm::Cell> state_root;
  Ref<vm::Cell> outmsg_root;
  std::shared_ptr<block::MsgProcessedUptoCollection> processed_upto;
  McShardDescr(const ton::BlockId& id, ton::LogicalTime start_lt, ton::LogicalTime end_lt, ton::UnixTime gen_utime,
               const ton::BlockHash& root_hash, const ton::FileHash& file_hash, ton::BlockSeqno min_ref_mc_seqno = -1u,
               ton::CatchainSeqno cc_seqno = -1u, ton::ShardId val_shard = ton::shardIdAll, bool nx_cc_updated = false,
               bool before_split = false, bool before_merge = false, bool want_split = false, bool want_merge = false)
      : McShardHash(id, start_lt, end_lt, gen_utime, root_hash, file_hash, min_ref_mc_seqno, cc_seqno, val_shard,
                    nx_cc_updated, before_split, before_merge, want_split, want_merge) {
  }
  McShardDescr(const ton::BlockIdExt& blk, ton::LogicalTime start_lt, ton::LogicalTime end_lt)
      : McShardHash(blk, start_lt, end_lt) {
  }
  McShardDescr(const McShardHash& shard_hash) : McShardHash(shard_hash) {
  }
  McShardDescr(const McShardDescr&) = default;
  static Ref<McShardDescr> from_block(Ref<vm::Cell> block_root, Ref<vm::Cell> state_root, const ton::FileHash& _fhash);
};

struct StoragePrices {
  ton::UnixTime valid_since{0};
  td::uint64 bit_price{0};
  td::uint64 cell_price{0};
  td::uint64 mc_bit_price{0};
  td::uint64 mc_cell_price{0};
  StoragePrices();
  StoragePrices(ton::UnixTime _valid_since, td::uint64 _bprice, td::uint64 _cprice, td::uint64 _mc_bprice,
                td::uint64 _mc_cprice)
      : valid_since(_valid_since)
      , bit_price(_bprice)
      , cell_price(_cprice)
      , mc_bit_price(_mc_bprice)
      , mc_cell_price(_mc_cprice) {
  }
};

struct CatchainValidatorsConfig {
  td::uint32 mc_cc_lifetime, shard_cc_lifetime, shard_val_lifetime, shard_val_num;
  CatchainValidatorsConfig(td::uint32 mc_cc_lt_, td::uint32 sh_cc_lt_, td::uint32 sh_val_lt_, td::uint32 sh_val_num_)
      : mc_cc_lifetime(mc_cc_lt_)
      , shard_cc_lifetime(sh_cc_lt_)
      , shard_val_lifetime(sh_val_lt_)
      , shard_val_num(sh_val_num_) {
  }
};

struct WorkchainInfo : public td::CntObject {
  ton::WorkchainId workchain{ton::workchainInvalid};
  ton::UnixTime enabled_since;
  td::uint32 actual_min_split;
  td::uint32 min_split, max_split;
  bool basic;
  bool active;
  bool accept_msgs;
  int flags;
  td::uint32 version;
  ton::RootHash zerostate_root_hash;
  ton::FileHash zerostate_file_hash;
  int min_addr_len, max_addr_len, addr_len_step;
  bool is_valid() const {
    return workchain != ton::workchainInvalid;
  }
  bool unpack(ton::WorkchainId wc, vm::CellSlice& cs);
};

using WorkchainSet = std::map<td::int32, Ref<WorkchainInfo>>;

class ShardConfig {
  Ref<vm::Cell> shard_hashes_;
  Ref<McShardHash> mc_shard_hash_;
  std::unique_ptr<vm::Dictionary> shard_hashes_dict_;
  std::set<ton::ShardIdFull> shards_updated_;
  bool valid_{false};

 public:
  ShardConfig() = default;
  ShardConfig(const ShardConfig& other);
  ShardConfig(ShardConfig&& other) = default;
  ShardConfig(Ref<vm::Cell> shard_hashes, Ref<McShardHash> mc_shard_hash = {})
      : shard_hashes_(std::move(shard_hashes)), mc_shard_hash_(std::move(mc_shard_hash)) {
    init();
  }
  bool is_valid() const {
    return valid_;
  }
  bool unpack(Ref<vm::Cell> shard_hashes, Ref<McShardHash> mc_shard_hash = {});
  bool unpack(Ref<vm::CellSlice> shard_hashes, Ref<McShardHash> mc_shard_hash = {});
  Ref<vm::CellSlice> get_root_csr() const;
  bool has_workchain(ton::WorkchainId workchain) const;
  Ref<McShardHash> get_shard_hash(ton::ShardIdFull id, bool exact = true) const;
  bool contains(ton::BlockIdExt blkid) const;
  bool get_shard_hash_raw(vm::CellSlice& cs, ton::ShardIdFull id, ton::ShardIdFull& true_id, bool exact = true) const;
  ton::LogicalTime get_shard_end_lt(ton::AccountIdPrefixFull acc) const;
  ton::LogicalTime get_shard_end_lt_ext(ton::AccountIdPrefixFull acc, ton::ShardIdFull& actual_shard) const;
  static bool get_shard_hash_raw_from(vm::Dictionary& shard_hashes_dict, vm::CellSlice& cs, ton::ShardIdFull id,
                                      ton::ShardIdFull& true_id, bool exact = true, Ref<vm::Cell>* leaf = nullptr);
  std::vector<ton::BlockId> get_shard_hash_ids(bool skip_mc = false) const;
  std::vector<ton::BlockId> get_shard_hash_ids(const std::function<bool(ton::ShardIdFull, bool)>& filter) const;
  std::vector<ton::BlockId> get_intersecting_shard_hash_ids(ton::ShardIdFull myself) const;
  std::vector<ton::BlockId> get_neighbor_shard_hash_ids(ton::ShardIdFull myself) const;
  std::vector<ton::BlockId> get_proper_neighbor_shard_hash_ids(ton::ShardIdFull myself) const;
  bool process_shard_hashes(std::function<int(McShardHash&)> func);
  bool process_sibling_shard_hashes(std::function<int(McShardHash&, const McShardHash*)> func);
  // may become non-static const in the future
  static bool is_neighbor(ton::ShardIdFull x, ton::ShardIdFull y);
  Ref<McShardHash> get_mc_hash() const {
    return mc_shard_hash_;
  }
  void set_mc_hash(Ref<McShardHash> mc_shard_hash) {
    mc_shard_hash_ = std::move(mc_shard_hash);
  }
  ton::CatchainSeqno get_shard_cc_seqno(ton::ShardIdFull shard) const;
  block::compute_shard_end_lt_func_t get_compute_shard_end_lt_func() const {
    return std::bind(&ShardConfig::get_shard_end_lt, *this, std::placeholders::_1);
  }
  bool new_workchain(ton::WorkchainId workchain, const ton::RootHash& zerostate_root_hash,
                     const ton::FileHash& zerostate_file_hash);
  td::Result<bool> update_shard_block_info(Ref<McShardHash> new_info, const std::vector<ton::BlockIdExt>& old_blkids);
  td::Result<bool> update_shard_block_info2(Ref<McShardHash> new_info1, Ref<McShardHash> new_info2,
                                            const std::vector<ton::BlockIdExt>& old_blkids);
  td::Result<bool> may_update_shard_block_info(Ref<McShardHash> new_info,
                                               const std::vector<ton::BlockIdExt>& old_blkids,
                                               ton::LogicalTime lt_limit = ~0ULL,
                                               Ref<McShardHash>* ancestor = nullptr) const;

 private:
  bool init();
  bool do_update_shard_info(Ref<McShardHash> new_info);
  bool do_update_shard_info2(Ref<McShardHash> new_info1, Ref<McShardHash> new_info2);
  bool set_shard_info(ton::ShardIdFull shard, Ref<vm::Cell> value);
};

class Config : public ShardConfig {
  enum {
    default_mc_catchain_lifetime = 200,
    default_shard_catchain_lifetime = 200,
    default_shard_validators_lifetime = 3000,
    default_shard_validators_num = 7
  };

 public:
  enum {
    needStateRoot = 1,
    needLibraries = 2,
    needStateExtraRoot = 4,
    needShardHashes = 8,
    needValidatorSet = 16,
    needSpecialSmc = 32,
    needAccountsRoot = 64,
    needPrevBlocks = 128,
    needWorkchainInfo = 256
  };
  int mode{0};
  ton::BlockIdExt block_id;
  int vert_seqno{-1};
  int global_id_{0};
  ton::UnixTime utime{0};
  ton::LogicalTime lt{0};
  ton::BlockSeqno min_ref_mc_seqno_{~0U};
  ton::CatchainSeqno cc_seqno_{std::numeric_limits<td::uint32>::max()};
  int shard_cc_updated{-1};
  bool nx_cc_updated;

 private:
  Ref<vm::Cell> state_root;
  Ref<vm::Cell> lib_root;
  Ref<vm::Cell> state_extra_root;
  Ref<vm::CellSlice> accounts_root;
  Ref<vm::Cell> shard_hashes;
  td::BitArray<256> config_addr;
  Ref<vm::Cell> config_root;
  ton::ZeroStateIdExt zerostate_id_;
  std::unique_ptr<vm::Dictionary> config_dict;
  std::unique_ptr<ValidatorSet> cur_validators;
  std::unique_ptr<vm::Dictionary> shard_hashes_dict;
  std::unique_ptr<vm::Dictionary> special_smc_dict;
  std::unique_ptr<vm::AugmentedDictionary> accounts_dict;
  std::unique_ptr<vm::Dictionary> prev_blocks_dict_;
  std::unique_ptr<vm::Dictionary> workchains_dict_;
  WorkchainSet workchains_;

 public:
  Ref<vm::Cell> get_config_param(int idx) const;
  Ref<vm::Cell> operator[](int idx) const {
    return get_config_param(idx);
  }
  bool is_masterchain() const {
    return block_id.is_masterchain();
  }
  static constexpr ton::LogicalTime lt_align = 1000000, max_lt_growth = 10 * lt_align - 1;
  td::Result<std::vector<ton::StdSmcAddress>> get_special_smartcontracts() const;
  td::Result<std::vector<std::pair<ton::StdSmcAddress, int>>> get_special_ticktock_smartcontracts(
      int tick_tock = 3) const;
  bool is_special_smartcontract(const ton::StdSmcAddress& addr) const;
  int get_smc_tick_tock(td::ConstBitPtr smc_addr) const;
  std::unique_ptr<vm::AugmentedDictionary> create_accounts_dict() const;
  const vm::AugmentedDictionary& get_accounts_dict() const;
  static td::Result<std::unique_ptr<Config>> extract_config(std::shared_ptr<vm::StaticBagOfCellsDb> static_boc,
                                                            int mode = 0);
  static td::Result<std::unique_ptr<Config>> extract_config(Ref<vm::Cell> mc_state_root, int mode = 0);
  static td::Result<std::unique_ptr<ValidatorSet>> unpack_validator_set(Ref<vm::Cell> valset_root);
  td::Result<std::vector<StoragePrices>> get_storage_prices() const;
  static CatchainValidatorsConfig unpack_catchain_validators_config(Ref<vm::Cell> cell);
  CatchainValidatorsConfig get_catchain_validators_config() const;
  static std::unique_ptr<vm::Dictionary> extract_shard_hashes_dict(Ref<vm::Cell> mc_state_root);
  bool set_block_id_ext(const ton::BlockIdExt& block_id_ext);
  ton::ZeroStateIdExt get_zerostate_id() const {
    return zerostate_id_;
  }
  static td::Result<std::pair<WorkchainSet, std::unique_ptr<vm::Dictionary>>> unpack_workchain_list_ext(
      Ref<vm::Cell> cell);
  static td::Result<WorkchainSet> unpack_workchain_list(Ref<vm::Cell> cell);
  const WorkchainSet& get_workchain_list() const {
    return workchains_;
  }
  Ref<WorkchainInfo> get_workchain_info(ton::WorkchainId workchain_id) const;
  bool rotated_all_shards() const;
  int get_global_blockchain_id() const {
    return global_id_;
  }
  bool get_old_mc_block_id(ton::BlockSeqno seqno, ton::BlockIdExt& blkid, ton::LogicalTime* end_lt = nullptr) const;
  bool check_old_mc_block_id(const ton::BlockIdExt& blkid, bool strict = false) const;
  ton::CatchainSeqno get_shard_cc_seqno(ton::ShardIdFull shard) const;
  std::vector<std::pair<ton::validator::ValidatorFullId, ton::ValidatorWeight>> compute_validator_set(
      ton::ShardIdFull shard, const block::ValidatorSet& vset, ton::UnixTime time,
      ton::CatchainSeqno& cc_seqno_delta) const;
  static std::vector<std::pair<ton::validator::ValidatorFullId, ton::ValidatorWeight>> do_compute_validator_set(
      const block::CatchainValidatorsConfig& ccv_conf, ton::ShardIdFull shard, const block::ValidatorSet& vset,
      ton::UnixTime time, ton::CatchainSeqno cc_seqno);

 private:
  Config(Ref<vm::Cell> mc_state_root, int _mode = 0);
  td::Status unpack_wrapped();
  td::Status unpack();
  void reset_mc_hash();
  void cleanup();
};

}  // namespace block
