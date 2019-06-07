#include "mc-config.h"
#include "block/block.h"
#include "block/block-auto.h"
#include "common/bitstring.h"
#include "vm/dict.h"
#include "td/utils/bits.h"
#include "ton/ton-types.h"
#include "ton/ton-shard.h"
#include "crypto/openssl/digest.h"
#include <absl/numeric/int128.h>
#include <stack>
#include <algorithm>

namespace block {
using td::Ref;

td::Result<std::unique_ptr<Config>> Config::extract_config(std::shared_ptr<vm::StaticBagOfCellsDb> static_boc,
                                                           int mode) {
  auto rc = static_boc->get_root_count();
  if (rc.is_error()) {
    return rc.move_as_error();
  }
  if (rc.move_as_ok() != 1) {
    return td::Status::Error(-668, "Masterchain state BoC is invalid");
  }
  auto root = static_boc->get_root_cell(0);
  if (root.is_error()) {
    return root.move_as_error();
  }
  return extract_config(root.move_as_ok(), mode);
}

td::Result<std::unique_ptr<Config>> Config::extract_config(Ref<vm::Cell> mc_state_root, int mode) {
  if (mc_state_root.is_null()) {
    return td::Status::Error("configuration state root cell is null");
  }
  auto config = std::unique_ptr<Config>{new Config(std::move(mc_state_root), mode)};
  auto res = config->unpack_wrapped();
  if (res.is_ok()) {
    return std::move(config);
  } else {
    return res;
  }
}

Config::Config(Ref<vm::Cell> mc_state_root, int _mode) : mode(_mode), state_root(std::move(mc_state_root)) {
  config_addr.set_zero();
  block_id.root_hash.set_zero();
  block_id.file_hash.set_zero();
}

td::Status Config::unpack_wrapped() {
  try {
    return unpack();
  } catch (vm::VmError err) {
    return td::Status::Error(PSLICE() << err.get_msg());
  }
}

std::unique_ptr<vm::AugmentedDictionary> Config::create_accounts_dict() const {
  if (mode & needAccountsRoot) {
    return std::make_unique<vm::AugmentedDictionary>(accounts_root, 256, block::tlb::aug_ShardAccounts);
  } else {
    return nullptr;
  }
}

const vm::AugmentedDictionary& Config::get_accounts_dict() const {
  return *accounts_dict;
}

td::Status Config::unpack() {
  gen::ShardStateUnsplit::Record root_info;
  if (!tlb::unpack_cell(state_root, root_info) || !root_info.global_id) {
    return td::Status::Error("configuration state root cannot be deserialized");
  }
  global_id_ = root_info.global_id;
  block::ShardId shard_id{root_info.shard_id};
  block_id.id = ton::BlockId{ton::ShardIdFull(shard_id), (unsigned)root_info.seq_no};
  block_id.root_hash.set_zero();
  block_id.file_hash.set_zero();
  vert_seqno = root_info.vert_seq_no;
  utime = root_info.gen_utime;
  lt = root_info.gen_lt;
  min_ref_mc_seqno_ = root_info.min_ref_mc_seqno;
  if (!root_info.custom->size_refs()) {
    return td::Status::Error("state does not have a `custom` field with masterchain configuration");
  }
  if ((mode & needLibraries) && root_info.r1.libraries->size_refs()) {
    lib_root = root_info.r1.libraries->prefetch_ref();
  }
  if (mode & needAccountsRoot) {
    accounts_root = root_info.accounts;
    LOG(DEBUG) << "requested accounts dictionary";
    accounts_dict = std::make_unique<vm::AugmentedDictionary>(accounts_root, 256, block::tlb::aug_ShardAccounts);
    LOG(DEBUG) << "accounts dictionary created";
  }
  state_extra_root = root_info.custom->prefetch_ref();
  if (!is_masterchain()) {
    if (mode & (needShardHashes | needValidatorSet | needSpecialSmc | needPrevBlocks | needWorkchainInfo)) {
      return td::Status::Error("cannot extract masterchain-specific configuration data from a non-masterchain state");
    }
    cleanup();
    return td::Status::OK();
  }
  gen::McStateExtra::Record extra_info;
  if (!tlb::unpack_cell(state_extra_root, extra_info)) {
    vm::load_cell_slice(state_extra_root).print_rec(std::cerr);
    block::gen::t_McStateExtra.print_ref(std::cerr, state_extra_root);
    return td::Status::Error("state extra information is invalid");
  }
  gen::ValidatorInfo::Record validator_info;
  if (!tlb::csr_unpack(extra_info.r1.validator_info, validator_info)) {
    return td::Status::Error("validator_info in state extra information is invalid");
  }
  cc_seqno_ = validator_info.catchain_seqno;
  nx_cc_updated = validator_info.nx_cc_updated;
  if ((mode & needShardHashes) && !ShardConfig::unpack(extra_info.shard_hashes)) {
    return td::Status::Error("cannot unpack Shard configuration");
  }
  gen::ConfigParams::Record config_params;
  if (!tlb::csr_unpack(extra_info.config, config_params)) {
    return td::Status::Error("cannot unpack ConfigParams");
  }
  config_addr = config_params.config_addr;
  config_root = std::move(config_params.config);
  config_dict = std::make_unique<vm::Dictionary>(config_root, 32);
  if (mode & needValidatorSet) {
    auto vset_res = unpack_validator_set(get_config_param(34));
    if (vset_res.is_error()) {
      return vset_res.move_as_error();
    }
    cur_validators = vset_res.move_as_ok();
  }
  if (mode & needSpecialSmc) {
    LOG(DEBUG) << "needSpecialSmc flag set";
    auto param = get_config_param(31);
    if (param.is_null()) {
      special_smc_dict = std::make_unique<vm::Dictionary>(256);
    } else {
      special_smc_dict = std::make_unique<vm::Dictionary>(vm::load_cell_slice_ref(std::move(param)), 256);
      LOG(DEBUG) << "smc dictionary created";
    }
  }
  std::unique_ptr<vm::Dictionary> prev_blocks_dict = std::make_unique<vm::Dictionary>(extra_info.r1.prev_blocks, 32);
  if (block_id.id.seqno) {
    block::gen::ExtBlkRef::Record extref = {};
    if (!(tlb::csr_unpack_safe(prev_blocks_dict->lookup(td::BitArray<32>{1 - 1}), extref) && !extref.seq_no)) {
      return td::Status::Error("OldMcBlocks in masterchain state does not contain a valid zero state reference");
    }
    zerostate_id_.root_hash = extref.root_hash;
    zerostate_id_.file_hash = extref.file_hash;
  } else {
    zerostate_id_.root_hash.set_zero();
    zerostate_id_.file_hash.set_zero();
  }
  zerostate_id_.workchain = ton::masterchainId;
  if (mode & needPrevBlocks) {
    prev_blocks_dict_ = std::move(prev_blocks_dict);
  }
  if (mode & needWorkchainInfo) {
    TRY_RESULT(pair, unpack_workchain_list_ext(get_config_param(12)));
    workchains_ = std::move(pair.first);
    workchains_dict_ = std::move(pair.second);
  }
  // ...
  cleanup();
  return td::Status::OK();
}

std::unique_ptr<vm::Dictionary> Config::extract_shard_hashes_dict(Ref<vm::Cell> mc_state_root) {
  gen::ShardStateUnsplit::Record root_info;
  gen::McStateExtra::Record extra_info;
  if (mc_state_root.not_null()                       //
      && tlb::unpack_cell(mc_state_root, root_info)  //
      && tlb::unpack_cell(root_info.custom->prefetch_ref(), extra_info)) {
    return std::make_unique<vm::Dictionary>(std::move(extra_info.shard_hashes), 32);
  } else {
    return {};
  }
}

td::Result<std::pair<WorkchainSet, std::unique_ptr<vm::Dictionary>>> Config::unpack_workchain_list_ext(
    Ref<vm::Cell> root) {
  if (root.is_null()) {
    LOG(DEBUG) << "workchain description dictionary is empty (no configuration parameter #12)";
    return std::make_pair(WorkchainSet{}, std::make_unique<vm::Dictionary>(32));
  } else {
    auto wc_dict = std::make_unique<vm::Dictionary>(vm::load_cell_slice_ref(std::move(root)), 32);
    WorkchainSet wc_list;
    LOG(DEBUG) << "workchain description dictionary created";
    if (!(wc_dict->check_for_each([&wc_list](Ref<vm::CellSlice> cs_ref, td::ConstBitPtr key, int n) -> bool {
          ton::WorkchainId wc = ton::WorkchainId(key.get_int(32));
          Ref<WorkchainInfo> wc_info{true};
          return wc_info.unique_write().unpack(wc, cs_ref.write()) && wc_list.emplace(wc, std::move(wc_info)).second;
        }))) {
      return td::Status::Error("cannot unpack WorkchainDescr from masterchain configuration");
    }
    return std::make_pair(std::move(wc_list), std::move(wc_dict));
  }
}

td::Result<WorkchainSet> Config::unpack_workchain_list(Ref<vm::Cell> root) {
  TRY_RESULT(pair, unpack_workchain_list_ext(std::move(root)));
  return std::move(pair.first);
}

td::Result<std::unique_ptr<ValidatorSet>> Config::unpack_validator_set(Ref<vm::Cell> vset_root) {
  if (vset_root.is_null()) {
    return td::Status::Error("validator set is absent");
  }
  gen::ValidatorSet::Record rec;
  if (!tlb::unpack_cell(std::move(vset_root), rec)) {
    return td::Status::Error("validator set is invalid");
  }
  vm::Dictionary dict{vm::Dictionary::construct_root_from(*rec.list), 16};
  td::BitArray<16> key_buffer;
  auto last = dict.get_minmax_key(key_buffer.bits(), 16, true);
  if (last.is_null() || (int)key_buffer.to_ulong() != rec.total - 1) {
    return td::Status::Error(
        "maximal index in a validator set dictionary must be one less than the total number of validators");
  }
  auto ptr = std::make_unique<ValidatorSet>(rec.utime_since, rec.utime_until, rec.total, rec.main);
  for (int i = 0; i < rec.total; i++) {
    key_buffer.store_ulong(i);
    auto descr_cs = dict.lookup(key_buffer.bits(), 16);
    if (descr_cs.is_null()) {
      return td::Status::Error("indices in a validator set dictionary must be integers 0..total-1");
    }
    gen::ValidatorDescr::Record descr;
    if (!tlb::csr_unpack(std::move(descr_cs), descr)) {
      return td::Status::Error(PSLICE() << "validator #" << i << " is absent in a validator set dictionary");
    }
    gen::SigPubKey::Record sig_pubkey;
    if (!tlb::csr_unpack(std::move(descr.public_key), sig_pubkey)) {
      return td::Status::Error(PSLICE() << "validator #" << i
                                        << " has no public key or its public key is in unsupported format");
    }
    if (!descr.weight) {
      return td::Status::Error(PSLICE() << "validator #" << i << " has zero weight");
    }
    if (descr.weight > ~(ptr->total_weight)) {
      return td::Status::Error("total weight of all validators in validator set exceeds 2^64");
    }
    ptr->list.emplace_back(sig_pubkey.pubkey, descr.weight, ptr->total_weight);
    ptr->total_weight += descr.weight;
  }
  return std::move(ptr);
}

bool Config::set_block_id_ext(const ton::BlockIdExt& block_id_ext) {
  if (block_id.id == block_id_ext.id) {
    block_id = block_id_ext;
    if (!block_id.id.seqno) {
      zerostate_id_.workchain = ton::masterchainId;
      zerostate_id_.root_hash = block_id_ext.root_hash;
      zerostate_id_.file_hash = block_id_ext.file_hash;
    }
    reset_mc_hash();
    return true;
  } else {
    return false;
  }
}

void Config::cleanup() {
  if (!(mode & needStateRoot)) {
    state_root.clear();
  }
  if (!(mode & needStateExtraRoot)) {
    state_extra_root.clear();
  }
}

Ref<vm::Cell> Config::get_config_param(int idx) const {
  if (!config_dict) {
    return {};
  }
  return config_dict->lookup_ref(td::BitArray<32>{idx});
}

td::Result<std::vector<StoragePrices>> Config::get_storage_prices() const {
  auto cell = get_config_param(18);
  std::vector<StoragePrices> res;
  if (cell.is_null()) {
    return td::Status::Error("configuration parameter 18 with storage prices dictionary is absent");
  }
  vm::Dictionary dict{std::move(cell), 32};
  if (!dict.check_for_each([&res](Ref<vm::CellSlice> cs_ref, td::ConstBitPtr key, int n) -> bool {
        block::gen::StoragePrices::Record data;
        if (!tlb::csr_unpack(std::move(cs_ref), data) || data.utime_since != key.get_uint(n)) {
          return false;
        }
        res.emplace_back(data.utime_since, data.bit_price_ps, data.cell_price_ps, data.mc_bit_price_ps,
                         data.mc_cell_price_ps);
        return true;
      })) {
    return td::Status::Error("invalid storage prices dictionary in configuration parameter 18");
  }
  return std::move(res);
}

CatchainValidatorsConfig Config::unpack_catchain_validators_config(Ref<vm::Cell> cell) {
  block::gen::CatchainConfig::Record cfg;
  if (cell.is_null() || !tlb::unpack_cell(std::move(cell), cfg)) {
    return {default_mc_catchain_lifetime, default_shard_catchain_lifetime, default_shard_validators_lifetime,
            default_shard_validators_num};
  } else {
    return {cfg.mc_catchain_lifetime, cfg.shard_catchain_lifetime, cfg.shard_validators_lifetime,
            cfg.shard_validators_num};
  }
}

CatchainValidatorsConfig Config::get_catchain_validators_config() const {
  return unpack_catchain_validators_config(get_config_param(28));
}

void McShardHash::set_fsm(FsmState fsm, ton::UnixTime fsm_utime, ton::UnixTime fsm_interval) {
  fsm_ = fsm;
  fsm_utime_ = fsm_utime;
  fsm_interval_ = fsm_interval;
}

Ref<McShardHash> McShardHash::unpack(vm::CellSlice& cs, ton::ShardIdFull id) {
  gen::ShardDescr::Record descr;
  if (!tlb::unpack_exact(cs, descr)) {
    return {};  // throw ?
  }
  auto res = Ref<McShardHash>(true, ton::BlockId{id, (unsigned)descr.seq_no}, descr.start_lt, descr.end_lt,
                              descr.gen_utime, descr.root_hash, descr.file_hash, descr.min_ref_mc_seqno,
                              descr.next_catchain_seqno, descr.next_validator_shard, descr.nx_cc_updated,
                              descr.before_split, descr.before_merge, descr.want_split, descr.want_merge);
  McShardHash& sh = res.unique_write();
  switch (gen::t_FutureSplitMerge.get_tag(*(descr.split_merge_at))) {
    case gen::FutureSplitMerge::fsm_none:
      return res;
    case gen::FutureSplitMerge::fsm_split:
      if (gen::t_FutureSplitMerge.unpack_fsm_split(descr.split_merge_at.write(), sh.fsm_utime_, sh.fsm_interval_)) {
        sh.fsm_ = FsmState::fsm_split;
        return res;
      }
      break;
    case gen::FutureSplitMerge::fsm_merge:
      if (!gen::t_FutureSplitMerge.unpack_fsm_merge(descr.split_merge_at.write(), sh.fsm_utime_, sh.fsm_interval_)) {
        sh.fsm_ = FsmState::fsm_merge;
        return res;
      }
      break;
    default:
      break;
  }
  return {};
}

bool McShardHash::pack(vm::CellBuilder& cb) const {
  if (!(is_valid()                                        // (validate)
        && cb.store_long_bool(blk_.id.seqno, 32)          // shard_descr$_ seq_no:uint32
        && cb.store_long_bool(start_lt_, 64)              // start_lt:uint64
        && cb.store_long_bool(end_lt_, 64)                // end_lt:uint64
        && cb.store_bits_bool(blk_.root_hash)             // root_hash:bits256
        && cb.store_bits_bool(blk_.file_hash)             // file_hash:bits256
        && cb.store_bool_bool(before_split_)              // before_split:Bool
        && cb.store_bool_bool(before_merge_)              // before_merge:Bool
        && cb.store_bool_bool(want_split_)                // want_split:Bool
        && cb.store_bool_bool(want_merge_)                // want_merge:Bool
        && cb.store_bool_bool(nx_cc_updated_)             // nx_cc_updated:Bool
        && cb.store_long_bool(0, 3)                       // flags:(## 3) { flags = 0 }
        && cb.store_long_bool(next_catchain_seqno_, 32)   // next_catchain_seqno:uint32
        && cb.store_long_bool(next_validator_shard_, 64)  // next_validator_shard:uint64
        && cb.store_long_bool(min_ref_mc_seqno_, 32)      // min_ref_mc_seqno:uint32
        && cb.store_long_bool(gen_utime_, 32)             // gen_utime:uint32
        )) {
    return false;
  }
  switch (fsm_) {  // split_merge_at:FutureSplitMerge = ShardDescr;
    case FsmState::fsm_none:
      return gen::t_FutureSplitMerge.pack_fsm_none(cb);
    case FsmState::fsm_split:
      return gen::t_FutureSplitMerge.pack_fsm_split(cb, fsm_utime_, fsm_interval_);
    case FsmState::fsm_merge:
      return gen::t_FutureSplitMerge.pack_fsm_merge(cb, fsm_utime_, fsm_interval_);
    default:
      return false;
  }
}

Ref<McShardHash> McShardHash::from_block(Ref<vm::Cell> block_root, const ton::FileHash& fhash) {
  if (block_root.is_null()) {
    return {};
  }
  block::gen::Block::Record rec;
  block::gen::BlockInfo::Record info;
  block::ShardId shard;
  if (!(tlb::unpack_cell(block_root, rec) && tlb::unpack_cell(rec.info, info) &&
        shard.deserialize(info.shard.write()))) {
    return {};
  }
  ton::RootHash rhash = block_root->get_hash().bits();
  return Ref<McShardHash>(true, ton::BlockId{ton::ShardIdFull(shard), (unsigned)info.seq_no}, info.start_lt,
                          info.end_lt, info.gen_utime, rhash, fhash, info.min_ref_mc_seqno, info.gen_catchain_seqno,
                          shard.shard_pfx, false, info.before_split, false, info.want_split, info.want_merge);
}

Ref<McShardDescr> McShardDescr::from_block(Ref<vm::Cell> block_root, Ref<vm::Cell> state_root,
                                           const ton::FileHash& fhash) {
  if (block_root.is_null()) {
    return {};
  }
  block::gen::Block::Record rec;
  block::gen::BlockInfo::Record info;
  block::ShardId shard;
  if (!(tlb::unpack_cell(block_root, rec) && tlb::unpack_cell(rec.info, info) &&
        shard.deserialize(info.shard.write()))) {
    return {};
  }
  // TODO: use a suitable vm::MerkleUpdate method here
  vm::CellSlice cs(vm::NoVm(), rec.state_update);
  if (cs.special_type() != vm::Cell::SpecialType::MerkleUpdate) {
    LOG(ERROR) << "state update in a block is not a Merkle update";
    return {};
  }
  if (cs.size_refs() != 2 || cs.prefetch_ref(1)->get_hash(0) != state_root->get_hash()) {
    LOG(ERROR) << "invalid Merkle update for block state : resulting state hash mismatch";
    return {};
  }
  ton::RootHash rhash = block_root->get_hash().bits();
  auto res =
      Ref<McShardDescr>(true, ton::BlockId{ton::ShardIdFull(shard), (unsigned)info.seq_no}, info.start_lt, info.end_lt,
                        info.gen_utime, rhash, fhash, info.min_ref_mc_seqno, info.gen_catchain_seqno, shard.shard_pfx,
                        false, info.before_split, false, info.want_split, info.want_merge);
  res.unique_write().block_root = std::move(block_root);
  res.unique_write().state_root = std::move(state_root);
  return res;
}

void Config::reset_mc_hash() {
  if (block_id.is_masterchain() && !block_id.root_hash.is_zero()) {
    // TODO: use block_start_lt instead of lt if available
    set_mc_hash(Ref<McShardHash>(true, block_id.id, lt, lt, utime, block_id.root_hash, block_id.file_hash));
  } else {
    set_mc_hash(Ref<McShardHash>{});
  }
}

Ref<vm::CellSlice> ShardConfig::get_root_csr() const {
  if (!shard_hashes_dict_) {
    return {};
  }
  return shard_hashes_dict_->get_root();
}

bool ShardConfig::unpack(Ref<vm::Cell> shard_hashes, Ref<McShardHash> mc_shard_hash) {
  shard_hashes_ = std::move(shard_hashes);
  mc_shard_hash_ = std::move(mc_shard_hash);
  return init();
}

bool ShardConfig::unpack(Ref<vm::CellSlice> shard_hashes, Ref<McShardHash> mc_shard_hash) {
  shard_hashes_ = shard_hashes->prefetch_ref();
  mc_shard_hash_ = std::move(mc_shard_hash);
  return init();
}

bool ShardConfig::init() {
  shard_hashes_dict_ = std::make_unique<vm::Dictionary>(shard_hashes_, 32);
  valid_ = true;
  return true;
}

ShardConfig::ShardConfig(const ShardConfig& other)
    : shard_hashes_(other.shard_hashes_), mc_shard_hash_(other.mc_shard_hash_) {
  init();
}

bool ShardConfig::get_shard_hash_raw_from(vm::Dictionary& dict, vm::CellSlice& cs, ton::ShardIdFull id,
                                          ton::ShardIdFull& true_id, bool exact, Ref<vm::Cell>* leaf) {
  if (id.is_masterchain() || !id.is_valid()) {
    return false;
  }
  auto root = dict.lookup_ref(td::BitArray<32>{id.workchain});
  if (root.is_null()) {
    return false;
  }
  unsigned long long z = id.shard, m = -1LL;
  int len = id.pfx_len();
  while (true) {
    cs.load(vm::NoVmOrd{}, leaf ? root : std::move(root));
    int t = (int)cs.fetch_ulong(1);
    if (t < 0) {
      return false;  // throw DictError ?
    } else if (!t) {
      if (len && exact) {
        return false;
      }
      true_id = ton::ShardIdFull{id.workchain, (id.shard | m) - (m >> 1)};
      if (leaf) {
        *leaf = std::move(root);
      }
      return true;
    }
    if (!len || cs.size_ext() != 0x20000) {
      return false;  // throw DictError in the second case?
    }
    root = cs.prefetch_ref((unsigned)(z >> 63));
    z <<= 1;
    --len;
    m >>= 1;
  }
}

bool ShardConfig::get_shard_hash_raw(vm::CellSlice& cs, ton::ShardIdFull id, ton::ShardIdFull& true_id,
                                     bool exact) const {
  return shard_hashes_dict_ && get_shard_hash_raw_from(*shard_hashes_dict_, cs, id, true_id, exact);
}

Ref<McShardHash> ShardConfig::get_shard_hash(ton::ShardIdFull id, bool exact) const {
  if (id.is_masterchain()) {
    return (!exact || id.shard == ton::shardIdAll) ? get_mc_hash() : Ref<McShardHash>{};
  }
  ton::ShardIdFull true_id;
  vm::CellSlice cs;
  if (get_shard_hash_raw(cs, id, true_id, exact)) {
    return McShardHash::unpack(cs, true_id);
  } else {
    return {};
  }
}

ton::CatchainSeqno ShardConfig::get_shard_cc_seqno(ton::ShardIdFull shard) const {
  if (shard.is_masterchain() || !shard.is_valid()) {
    return -1U;
  }
  ton::ShardIdFull true_id;
  gen::ShardDescr::Record info;
  vm::CellSlice cs;
  if (!(get_shard_hash_raw(cs, shard - 1, true_id, false) &&
        (ton::shard_is_ancestor(true_id, shard) || ton::shard_is_parent(shard, true_id)) &&
        tlb::unpack_exact(cs, info))) {
    return -1U;
  }
  ton::CatchainSeqno cc_seqno = info.next_catchain_seqno;
  if (ton::shard_is_ancestor(true_id, shard)) {
    return cc_seqno;
  }
  if (!(get_shard_hash_raw(cs, shard + 1, true_id, false) && ton::shard_is_parent(shard, true_id) &&
        tlb::unpack_exact(cs, info))) {
    return -1U;
  }
  return std::max(cc_seqno, info.next_catchain_seqno) + 1;
}

ton::LogicalTime ShardConfig::get_shard_end_lt_ext(ton::AccountIdPrefixFull acc, ton::ShardIdFull& actual_shard) const {
  if (!acc.is_valid()) {
    actual_shard.workchain = ton::workchainInvalid;
    return 0;
  }
  if (acc.is_masterchain()) {
    actual_shard = ton::ShardIdFull(ton::masterchainId);
    CHECK(mc_shard_hash_.not_null());
    return mc_shard_hash_->end_lt_;
  }
  vm::CellSlice cs;
  unsigned long long end_lt;
  return get_shard_hash_raw(cs, acc.as_leaf_shard(), actual_shard, false)  // lookup ShardDescr containing acc
                 && cs.advance(96)                   // shard_descr$_ seq_no:uint32 start_lt:uint64
                 && cs.fetch_ulong_bool(64, end_lt)  // end_lt:uint64
             ? end_lt
             : 0;
}

ton::LogicalTime ShardConfig::get_shard_end_lt(ton::AccountIdPrefixFull acc) const {
  ton::ShardIdFull tmp;
  return get_shard_end_lt_ext(acc, tmp);
}

bool ShardConfig::contains(ton::BlockIdExt blkid) const {
  auto entry = get_shard_hash(blkid.shard_full());
  return entry.not_null() && entry->blk_ == blkid;
}

static int process_workchain_shard_hashes(Ref<vm::Cell>& branch, ton::ShardIdFull shard,
                                          std::function<int(McShardHash&)>& func) {
  auto cs = vm::load_cell_slice(branch);
  int f = (int)cs.fetch_ulong(1);
  if (f == 1) {
    if ((shard.shard & 1) || cs.size_ext() != 0x20000) {
      return false;
    }
    auto left = cs.prefetch_ref(0), right = cs.prefetch_ref(1);
    int r = process_workchain_shard_hashes(left, ton::shard_child(shard, true), func);
    if (r < 0) {
      return r;
    }
    r |= process_workchain_shard_hashes(right, ton::shard_child(shard, false), func);
    if (r <= 0) {
      return r;
    }
    vm::CellBuilder cb;
    return cb.store_bool_bool(true) && cb.store_ref_bool(std::move(left)) && cb.store_ref_bool(std::move(right)) &&
                   cb.finalize_to(branch)
               ? r
               : -1;
  } else if (!f) {
    auto shard_info = McShardHash::unpack(cs, shard);
    if (shard_info.is_null()) {
      return -1;
    }
    int r = func(shard_info.write());
    if (r <= 0) {
      return r;
    }
    vm::CellBuilder cb;
    return cb.store_bool_bool(false) && shard_info->pack(cb) && cb.finalize_to(branch) ? r : -1;
  } else {
    return -1;
  }
}

bool ShardConfig::process_shard_hashes(std::function<int(McShardHash&)> func) {
  if (!shard_hashes_dict_) {
    return false;
  }
  bool ok = true;
  shard_hashes_dict_->map(
      [&ok, &func](vm::CellBuilder& cb, Ref<vm::CellSlice> csr, td::ConstBitPtr key, int n) -> bool {
        Ref<vm::Cell> root;
        ok = ok && (n == 32) && csr->size_ext() == 0x10000 && std::move(csr)->prefetch_ref_to(root) &&
             process_workchain_shard_hashes(root, ton::ShardIdFull{(int)key.get_int(32)}, func) >= 0 &&
             cb.store_ref_bool(std::move(root));
        return true;
      });
  return ok;
}

static int process_workchain_sibling_shard_hashes(Ref<vm::Cell>& branch, Ref<vm::Cell> sibling, ton::ShardIdFull shard,
                                                  std::function<int(McShardHash&, const McShardHash*)>& func) {
  auto cs = vm::load_cell_slice(branch);
  int f = (int)cs.fetch_ulong(1);
  if (f == 1) {
    if ((shard.shard & 1) || cs.size_ext() != 0x20000) {
      return false;
    }
    auto left = cs.prefetch_ref(0), right = cs.prefetch_ref(1);
    auto orig_left = left;
    int r = process_workchain_sibling_shard_hashes(left, right, ton::shard_child(shard, true), func);
    if (r < 0) {
      return r;
    }
    r |= process_workchain_sibling_shard_hashes(right, std::move(orig_left), ton::shard_child(shard, false), func);
    if (r <= 0) {
      return r;
    }
    vm::CellBuilder cb;
    return cb.store_bool_bool(true) && cb.store_ref_bool(std::move(left)) && cb.store_ref_bool(std::move(right)) &&
                   cb.finalize_to(branch)
               ? r
               : -1;
  } else if (!f) {
    auto shard_info = McShardHash::unpack(cs, shard);
    if (shard_info.is_null()) {
      return -1;
    }
    Ref<McShardHash> sibling_info;
    if (sibling.not_null()) {
      auto cs2 = vm::load_cell_slice(sibling);
      if (!cs2.fetch_ulong(1)) {
        sibling_info = McShardHash::unpack(cs2, ton::shard_sibling(shard));
        if (sibling_info.is_null()) {
          return -1;
        }
      }
    }
    int r = func(shard_info.write(), sibling_info.get());
    if (r <= 0) {
      return r;
    }
    vm::CellBuilder cb;
    return cb.store_bool_bool(false) && shard_info->pack(cb) && cb.finalize_to(branch) ? r : -1;
  } else {
    return -1;
  }
}

bool ShardConfig::process_sibling_shard_hashes(std::function<int(McShardHash&, const McShardHash*)> func) {
  if (!shard_hashes_dict_) {
    return false;
  }
  bool ok = true;
  shard_hashes_dict_->map([&ok, &func](vm::CellBuilder& cb, Ref<vm::CellSlice> csr, td::ConstBitPtr key,
                                       int n) -> bool {
    Ref<vm::Cell> root;
    ok = ok && (n == 32) && csr->size_ext() == 0x10000 && std::move(csr)->prefetch_ref_to(root) &&
         process_workchain_sibling_shard_hashes(root, Ref<vm::Cell>{}, ton::ShardIdFull{(int)key.get_int(32)}, func) >=
             0 &&
         cb.store_ref_bool(std::move(root));
    return true;
  });
  return ok;
}

std::vector<ton::BlockId> ShardConfig::get_shard_hash_ids(
    const std::function<bool(ton::ShardIdFull, bool)>& filter) const {
  if (!shard_hashes_dict_) {
    return {};
  }
  std::vector<ton::BlockId> res;
  bool mcout = mc_shard_hash_.is_null() || !mc_shard_hash_->seqno();  // include masterchain as a shard if seqno > 0
  bool ok = shard_hashes_dict_->check_for_each(
      [&res, &mcout, mc_shard_hash_ = mc_shard_hash_, &filter ](Ref<vm::CellSlice> cs_ref, td::ConstBitPtr key, int n)
          ->bool {
            int workchain = (int)key.get_int(n);
            if (workchain >= 0 && !mcout) {
              if (filter(ton::ShardIdFull{ton::masterchainId}, true)) {
                res.emplace_back(mc_shard_hash_->blk_.id);
              }
              mcout = true;
            }
            if (!cs_ref->have_refs()) {
              return false;
            }
            std::stack<std::pair<Ref<vm::Cell>, unsigned long long>> stack;
            stack.emplace(cs_ref->prefetch_ref(), ton::shardIdAll);
            while (!stack.empty()) {
              vm::CellSlice cs{vm::NoVm{}, std::move(stack.top().first)};
              unsigned long long shard = stack.top().second;
              stack.pop();
              int t = (int)cs.fetch_ulong(1);
              if (t < 0) {
                return false;
              }
              if (!filter(ton::ShardIdFull{workchain, shard}, !t)) {
                continue;
              }
              if (!t) {
                res.emplace_back(workchain, shard, (int)cs.prefetch_ulong(32));
                continue;
              }
              unsigned long long delta = (td::lower_bit64(shard) >> 1);
              if (!delta || cs.size_ext() != 0x20000) {
                return false;
              }
              stack.emplace(cs.prefetch_ref(1), shard + delta);
              stack.emplace(cs.prefetch_ref(0), shard - delta);
            }
            return true;
          },
      true);
  if (!ok) {
    return {};
  }
  if (!mcout && filter(ton::ShardIdFull{ton::masterchainId}, true)) {
    res.emplace_back(mc_shard_hash_->blk_.id);
  }
  return res;
}

std::vector<ton::BlockId> ShardConfig::get_shard_hash_ids(bool skip_mc) const {
  return get_shard_hash_ids(
      [skip_mc](ton::ShardIdFull shard, bool) -> bool { return !(skip_mc && shard.is_masterchain()); });
}

std::vector<ton::BlockId> ShardConfig::get_intersecting_shard_hash_ids(ton::ShardIdFull myself) const {
  return get_shard_hash_ids(
      [myself](ton::ShardIdFull shard, bool) -> bool { return ton::shard_intersects(myself, shard); });
}

std::vector<ton::BlockId> ShardConfig::get_neighbor_shard_hash_ids(ton::ShardIdFull myself) const {
  return get_shard_hash_ids([myself](ton::ShardIdFull shard, bool) -> bool { return is_neighbor(myself, shard); });
}

std::vector<ton::BlockId> ShardConfig::get_proper_neighbor_shard_hash_ids(ton::ShardIdFull myself) const {
  return get_shard_hash_ids([myself](ton::ShardIdFull shard, bool leaf) -> bool {
    return is_neighbor(myself, shard) && !(leaf && ton::shard_intersects(myself, shard));
  });
}

bool ShardConfig::is_neighbor(ton::ShardIdFull x, ton::ShardIdFull y) {
  if (x.is_masterchain() || y.is_masterchain()) {
    return true;
  }
  unsigned long long xs = x.shard, ys = y.shard;
  unsigned long long xl = td::lower_bit64(xs), yl = td::lower_bit64(ys);
  unsigned long long z = (xs ^ ys) & td::bits_negate64(std::max(xl, yl) << 1);
  if (!z) {
    return true;
  }
  if (x.workchain != y.workchain) {
    return false;
  }
  int c1 = (td::count_leading_zeroes_non_zero64(z) >> 2);
  int c2 = (td::count_trailing_zeroes_non_zero64(z) >> 2);
  return c1 + c2 == 15;
}

bool ShardConfig::has_workchain(ton::WorkchainId workchain) const {
  return shard_hashes_dict_ && shard_hashes_dict_->key_exists(td::BitArray<32>{workchain});
}

bool ShardConfig::new_workchain(ton::WorkchainId workchain, const ton::RootHash& zerostate_root_hash,
                                const ton::FileHash& zerostate_file_hash) {
  if (!shard_hashes_dict_ || has_workchain(workchain)) {
    return false;
  }
  vm::CellBuilder cb;
  Ref<vm::Cell> cell;
  return cb.store_zeroes_bool(1 + 32 + 64 * 2)  // bt_leaf$0 ; shard_descr$_ seq_no:uint32 start_lt:uint64 end_lt:uint64
         && cb.store_bits_bool(zerostate_root_hash)  // root_hash:bits256
         && cb.store_bits_bool(zerostate_file_hash)  // file_hash:bits256
         && cb.store_long_bool(8, 8)                 // ... nx_cc_updated:Bool ...
         && cb.store_long_bool(0, 32)                // next_catchain_seqno:uint32
         && cb.store_long_bool(1ULL << 63, 64)       // next_validator_shard:uint64
         && cb.store_long_bool(~0U, 32)              // min_ref_mc_seqno:uint32
         && cb.store_long_bool(0, 32)                // gen_utime:uint32
         && cb.store_zeroes_bool(1)                  // split_merge_at:FutureSplitMerge
         && cb.finalize_to(cell) && block::gen::t_BinTree_ShardDescr.validate_ref(cell) &&
         shard_hashes_dict_->set_ref(td::BitArray<32>{workchain}, std::move(cell), vm::Dictionary::SetMode::Add);
}

td::Result<bool> ShardConfig::may_update_shard_block_info(Ref<McShardHash> new_info,
                                                          const std::vector<ton::BlockIdExt>& old_blkids,
                                                          ton::LogicalTime lt_limit, Ref<McShardHash>* ancestor) const {
  if (!shard_hashes_dict_) {
    return td::Status::Error(-666, "no shard top block dictionary present");
  }
  if (new_info.is_null()) {
    return td::Status::Error(-666, "suggested new top shard block info is empty");
  }
  if (!new_info->is_valid()) {
    return td::Status::Error(-666, "new top shard block description is invalid");
  }
  auto wc = new_info->shard().workchain;
  if (wc == ton::workchainInvalid || wc == ton::masterchainId) {
    return td::Status::Error(-666, "new top shard block description belongs to an invalid workchain");
  }
  if (!has_workchain(wc)) {
    return td::Status::Error(-666, "new top shard block belongs to an unknown or disabled workchain");
  }
  if (old_blkids.size() != 1 && old_blkids.size() != 2) {
    return td::Status::Error(-666, "must have either one or two start blocks in a top shard block update");
  }
  bool before_split = ton::shard_is_parent(old_blkids[0].shard_full(), new_info->shard());
  bool before_merge = (old_blkids.size() == 2);
  if (before_merge) {
    if (!ton::shard_is_sibling(old_blkids[0].shard_full(), old_blkids[1].shard_full())) {
      return td::Status::Error(-666, "the two start blocks of a top shard block update must be siblings");
    }
    if (!ton::shard_is_parent(new_info->shard(), old_blkids[0].shard_full())) {
      return td::Status::Error(
          -666,
          std::string{"the two start blocks of a top shard block update do not merge into expected final shard "} +
              old_blkids[0].shard_full().to_str());
    }
  } else if (new_info->shard() != old_blkids[0].shard_full() && !before_split) {
    return td::Status::Error(
        -666, "the start block of a top shard block update must either coincide with the final shard or be its parent");
  }
  if (ancestor) {
    ancestor->clear();
  }
  ton::CatchainSeqno old_cc_seqno = 0;
  for (const auto& ob : old_blkids) {
    auto odef = get_shard_hash(ob.shard_full());
    if (odef.is_null() || odef->blk_ != ob) {
      return td::Status::Error(-666,
                               std::string{"the start block "} + ob.to_str() +
                                   " of a top shard block update is not contained in the previous shard configuration");
    }
    old_cc_seqno = std::max(old_cc_seqno, odef->next_catchain_seqno_);
    if (shards_updated_.find(ob.shard_full()) != shards_updated_.end()) {
      return td::Status::Error(
          -666, std::string{"the shard of the start block "} + ob.to_str() +
                    " of a top shard block update has been already updated in the current shard configuration");
    }
    if (odef->before_split_ != before_split) {
      return td::Status::Error(
          -666, PSTRING() << "the shard of the start block " << ob.to_str()
                          << " had before_split=" << odef->before_split_
                          << " but the top shard block update is valid only if before_split=" << before_split);
    }
    if (odef->before_merge_ != before_merge) {
      return td::Status::Error(
          -666, PSTRING() << "the shard of the start block " << ob.to_str()
                          << " had before_merge=" << odef->before_merge_
                          << " but the top shard block update is valid only if before_merge=" << before_merge);
    }
    if (new_info->before_split_) {
      if (before_merge || before_split) {
        return td::Status::Error(
            -666, PSTRING() << "cannot register a before-split block " << new_info->top_block_id().to_str()
                            << " at the end of a chain that itself starts with a split/merge event");
      }
      if (odef->fsm_state() != block::McShardHash::FsmState::fsm_split) {
        return td::Status::Error(-666, PSTRING() << "cannot register a before-split block "
                                                 << new_info->top_block_id().to_str()
                                                 << " because fsm_split state was not set for this shard beforehand");
      }
      if (new_info->gen_utime_ < odef->fsm_utime_ || new_info->gen_utime_ >= odef->fsm_utime_ + odef->fsm_interval_) {
        return td::Status::Error(-666, PSTRING() << "cannot register a before-split block "
                                                 << new_info->top_block_id().to_str()
                                                 << " because fsm_split state was enabled for unixtime "
                                                 << odef->fsm_utime_ << " .. " << odef->fsm_utime_ + odef->fsm_interval_
                                                 << " but the block is generated at " << new_info->gen_utime_);
      }
    }
    if (before_merge) {
      if (odef->fsm_state() != block::McShardHash::FsmState::fsm_merge) {
        return td::Status::Error(-666, PSTRING() << "cannot register merged block " << new_info->top_block_id().to_str()
                                                 << " because fsm_merge state was not set for shard "
                                                 << odef->top_block_id().shard_full().to_str() << " beforehand");
      }
      if (new_info->gen_utime_ < odef->fsm_utime_ || new_info->gen_utime_ >= odef->fsm_utime_ + odef->fsm_interval_) {
        return td::Status::Error(-666, PSTRING() << "cannot register merged block " << new_info->top_block_id().to_str()
                                                 << " because fsm_merge state was enabled for shard "
                                                 << odef->top_block_id().shard_full().to_str() << " for unixtime "
                                                 << odef->fsm_utime_ << " .. " << odef->fsm_utime_ + odef->fsm_interval_
                                                 << " but the block is generated at " << new_info->gen_utime_);
      }
    }
    if (ancestor && !before_merge && !before_split) {
      *ancestor = odef;
    }
  }
  if (old_cc_seqno + before_merge != new_info->next_catchain_seqno_) {
    return td::Status::Error(-666, PSTRING()
                                       << "the top shard block update is generated with catchain_seqno="
                                       << new_info->next_catchain_seqno_ << " but previous shard configuration expects "
                                       << old_cc_seqno + before_merge);
  }
  if (new_info->end_lt_ > lt_limit) {
    return td::Status::Error(-666, PSTRING() << "the top shard block update has end_lt " << new_info->end_lt_
                                             << " which is larger than the current limit " << lt_limit);
  }
  return !before_split;
}

td::Result<bool> ShardConfig::update_shard_block_info(Ref<McShardHash> new_info,
                                                      const std::vector<ton::BlockIdExt>& old_blkids) {
  Ref<McShardHash> ancestor;
  auto res = may_update_shard_block_info(new_info, old_blkids, ~0ULL, &ancestor);
  if (res.is_error()) {
    return res;
  }
  if (!res.move_as_ok()) {
    return td::Status::Error(-666, std::string{"cannot apply the after-split update for "} + new_info->blk_.to_str() +
                                       " without a corresponding sibling update");
  }
  if (ancestor.not_null() && ancestor->fsm_ != McShardHash::FsmState::fsm_none) {
    new_info.write().set_fsm(ancestor->fsm_, ancestor->fsm_utime_, ancestor->fsm_interval_);
  }
  bool ok = do_update_shard_info(std::move(new_info));
  if (!ok) {
    return td::Status::Error(
        -666,
        std::string{
            "unknown serialization error for (BinTree ShardDescr) while updating shard configuration to include "} +
            new_info->blk_.to_str());
  } else {
    return true;
  }
}

td::Result<bool> ShardConfig::update_shard_block_info2(Ref<McShardHash> new_info1, Ref<McShardHash> new_info2,
                                                       const std::vector<ton::BlockIdExt>& old_blkids) {
  auto res1 = may_update_shard_block_info(new_info1, old_blkids);
  if (res1.is_error()) {
    return res1;
  }
  auto res2 = may_update_shard_block_info(new_info2, old_blkids);
  if (res2.is_error()) {
    return res2;
  }
  if (res1.move_as_ok() || res2.move_as_ok()) {
    return td::Status::Error(-666, "the two updates in update_shard_block_info2 must follow a shard split event");
  }
  if (new_info1->blk_.id.shard > new_info2->blk_.id.shard) {
    std::swap(new_info1, new_info2);
  }
  bool ok = do_update_shard_info2(std::move(new_info1), std::move(new_info2));
  if (!ok) {
    return td::Status::Error(
        -666,
        std::string{
            "unknown serialization error for (BinTree ShardDescr) while updating shard configuration to include "} +
            new_info1->blk_.to_str() + " and " + new_info2->blk_.to_str());
  } else {
    return true;
  }
}

bool ShardConfig::do_update_shard_info(Ref<McShardHash> new_info) {
  vm::CellBuilder cb;
  Ref<vm::Cell> ref;
  return new_info.not_null() && cb.store_bool_bool(false)  // bt_leaf$0
         && new_info->pack(cb)                             // leaf:ShardDescr
         && cb.finalize_to(ref) && set_shard_info(new_info->shard(), std::move(ref));
}

bool ShardConfig::do_update_shard_info2(Ref<McShardHash> new_info1, Ref<McShardHash> new_info2) {
  if (new_info1.is_null() || new_info2.is_null() || !ton::shard_is_sibling(new_info1->shard(), new_info2->shard())) {
    return false;
  }
  if (new_info1->blk_.id.shard > new_info2->blk_.id.shard) {
    std::swap(new_info1, new_info2);
  }
  vm::CellBuilder cb, cb1;
  Ref<vm::Cell> ref;
  return cb.store_bool_bool(true)              // bt_node$1
         && cb1.store_bool_bool(false)         // ( bt_leaf$0
         && new_info1->pack(cb1)               //   leaf:ShardDescr
         && cb1.finalize_to(ref)               // ) -> ref
         && cb.store_ref_bool(std::move(ref))  // left:^(BinTree ShardDescr)
         && cb1.store_bool_bool(false)         // ( bt_leaf$0
         && new_info2->pack(cb1)               //   leaf:ShardDescr
         && cb1.finalize_to(ref)               // ) -> ref
         && cb.store_ref_bool(std::move(ref))  // right:^(BinTree ShardDescr)
         && cb.finalize_to(ref) && set_shard_info(ton::shard_parent(new_info1->shard()), std::move(ref));
}

static bool btree_set(Ref<vm::Cell>& root, ton::ShardId shard, Ref<vm::Cell> value) {
  if (!shard) {
    return false;
  }
  if (shard == ton::shardIdAll) {
    root = value;
    return true;
  }
  auto cs = vm::load_cell_slice(std::move(root));
  if (cs.size_ext() != 0x20001 || cs.prefetch_ulong(1)) {
    return false;  // branch does not exist
  }
  Ref<vm::Cell> left = cs.prefetch_ref(0), right = cs.prefetch_ref(1);
  if (!(btree_set(shard & (1ULL << 63) ? right : left, shard << 1, std::move(value)))) {
    return false;
  }
  vm::CellBuilder cb;
  return cb.store_bool_bool(true)                // bt_node$1
         && cb.store_ref_bool(std::move(left))   // left:^(BinTree ShardDescr)
         && cb.store_ref_bool(std::move(right))  // right:^(BinTree ShardDescr)
         && cb.finalize_to(root);                // = BinTree ShardDescr
}

bool ShardConfig::set_shard_info(ton::ShardIdFull shard, Ref<vm::Cell> value) {
  if (!gen::t_BinTree_ShardDescr.validate_ref(value)) {
    LOG(ERROR) << "attempting to store an invalid (BinTree ShardDescr) at shard configuration position "
               << shard.to_str();
    gen::t_BinTree_ShardDescr.print_ref(std::cerr, value);
    vm::load_cell_slice(value).print_rec(std::cerr);
    return false;
  }
  auto root = shard_hashes_dict_->lookup_ref(td::BitArray<32>{shard.workchain});
  if (root.is_null()) {
    LOG(ERROR) << "attempting to store a new ShardDescr for shard " << shard.to_str() << " in an undefined workchain";
    return false;
  }
  if (!btree_set(root, shard.shard, value)) {
    LOG(ERROR) << "error while storing a new ShardDescr for shard " << shard.to_str() << " into shard configuration";
    return false;
  }
  if (!shard_hashes_dict_->set_ref(td::BitArray<32>{shard.workchain}, std::move(root),
                                   vm::Dictionary::SetMode::Replace)) {
    return false;
  }
  auto ins = shards_updated_.insert(shard);
  CHECK(ins.second);
  return true;
}

bool Config::is_special_smartcontract(const ton::StdSmcAddress& addr) const {
  CHECK(special_smc_dict);
  return special_smc_dict->lookup(addr).not_null();
}

td::Result<std::vector<ton::StdSmcAddress>> Config::get_special_smartcontracts() const {
  if (!special_smc_dict) {
    return td::Status::Error(-666, "configuration loaded without fundamental smart contract list");
  }
  std::vector<ton::StdSmcAddress> res;
  if (!special_smc_dict->check_for_each([&res](Ref<vm::CellSlice> cs_ref, td::ConstBitPtr key, int n) -> bool {
        if (cs_ref->size_ext() || n != 256) {
          return false;
        }
        res.emplace_back(key);
        return true;
      })) {
    return td::Status::Error(-666, "invalid fundamental smart contract set in configuration parameter 31");
  }
  return std::move(res);
}

td::Result<std::vector<std::pair<ton::StdSmcAddress, int>>> Config::get_special_ticktock_smartcontracts(
    int tick_tock) const {
  if (!special_smc_dict) {
    return td::Status::Error(-666, "configuration loaded without fundamental smart contract list");
  }
  if (!accounts_dict) {
    return td::Status::Error(-666, "state loaded without accounts information");
  }
  std::vector<std::pair<ton::StdSmcAddress, int>> res;
  if (!special_smc_dict->check_for_each(
          [this, &res, tick_tock](Ref<vm::CellSlice> cs_ref, td::ConstBitPtr key, int n) -> bool {
            if (cs_ref->size_ext() || n != 256) {
              return false;
            }
            int tt = get_smc_tick_tock(key);
            if (tt < -1) {
              return false;
            }
            if (tt >= 0 && (tt & tick_tock) != 0) {
              res.emplace_back(key, tt);
            }
            return true;
          })) {
    return td::Status::Error(-666,
                             "invalid fundamental smart contract set in configuration parameter 31, or unable to "
                             "recover tick-tock value from one of them");
  }
  return std::move(res);
}

int Config::get_smc_tick_tock(td::ConstBitPtr smc_addr) const {
  if (!accounts_dict) {
    return -2;
  }
  auto acc_csr = accounts_dict->lookup(smc_addr, 256);
  Ref<vm::Cell> acc_cell;
  if (acc_csr.is_null() || !acc_csr->prefetch_ref_to(acc_cell)) {
    return -1;
  }
  auto acc_cs = vm::load_cell_slice(std::move(acc_cell));
  if (block::gen::t_Account.get_tag(acc_cs) == block::gen::Account::account_none) {
    return 0;
  }
  block::gen::Account::Record_account acc;
  block::gen::AccountStorage::Record storage;
  int ticktock;
  return (tlb::unpack_exact(acc_cs, acc) && tlb::csr_unpack(acc.storage, storage) &&
          block::tlb::t_AccountState.get_ticktock(storage.state.write(), ticktock))
             ? ticktock
             : -2;
}

ton::CatchainSeqno Config::get_shard_cc_seqno(ton::ShardIdFull shard) const {
  return shard.is_masterchain() ? cc_seqno_ : ShardConfig::get_shard_cc_seqno(shard);
}

std::vector<std::pair<ton::validator::ValidatorFullId, ton::ValidatorWeight>> Config::compute_validator_set(
    ton::ShardIdFull shard, const block::ValidatorSet& vset, ton::UnixTime time,
    ton::CatchainSeqno& cc_seqno_delta) const {
  if (cc_seqno_delta & -2) {
    return {};
  }
  ton::CatchainSeqno cc_seqno = get_shard_cc_seqno(shard);
  if (cc_seqno == -1U) {
    return {};
  }
  cc_seqno_delta += cc_seqno;
  return do_compute_validator_set(get_catchain_validators_config(), shard, vset, time, cc_seqno_delta);
}

void validator_set_descr::incr_seed() {
  for (int i = 31; i >= 0 && !++(seed[i]); --i) {
  }
}

void validator_set_descr::hash_to(unsigned char hash_buffer[64]) const {
  digest::hash_str<digest::SHA512>(hash_buffer, (const void*)this, sizeof(*this));
}

td::uint64 ValidatorSetPRNG::next_ulong() {
  if (pos < limit) {
    return td::bswap64(hash_longs[pos++]);
  }
  data.hash_to(hash);
  data.incr_seed();
  pos = 1;
  limit = 8;
  return td::bswap64(hash_longs[0]);
}

td::uint64 ValidatorSetPRNG::next_ranged(td::uint64 range) {
  td::uint64 y = next_ulong();
#if defined(ABSL_HAVE_INTRINSIC_INT128)
  __int128 t = __int128(range) * y;
#else
  absl::uint128 t = absl::uint128(range) * y;
#endif
  return (td::uint64)(t >> 64);
}

inline bool operator<(td::uint64 pos, const ValidatorDescr& descr) {
  return pos < descr.cum_weight;
}

const ValidatorDescr& ValidatorSet::at_weight(td::uint64 weight_pos) const {
  CHECK(weight_pos < total_weight);
  auto it = std::upper_bound(list.begin(), list.end(), weight_pos);
  CHECK(it != list.begin());
  return *--it;
}

std::vector<std::pair<ton::validator::ValidatorFullId, ton::ValidatorWeight>> Config::do_compute_validator_set(
    const block::CatchainValidatorsConfig& ccv_conf, ton::ShardIdFull shard, const block::ValidatorSet& vset,
    ton::UnixTime time, ton::CatchainSeqno cc_seqno) {
  LOG(DEBUG) << "in Config::do_compute_validator_set() for " << shard.to_str() << " ; cc_seqno=" << cc_seqno;
  std::vector<std::pair<ton::validator::ValidatorFullId, ton::ValidatorWeight>> nodes;
  bool is_mc = shard.is_masterchain();
  unsigned count = std::min<unsigned>(is_mc ? vset.main : ccv_conf.shard_val_num, vset.total);
  CHECK((unsigned)vset.total == vset.list.size());
  if (!count) {
    return {};  // no validators?
  }
  nodes.reserve(count);
  if (is_mc) {
    // simply take needed number of validators from the head of the list
    // TODO: write a more clever validator list selection algorithm
    // (if we really need one for the masterchain)
    for (unsigned i = 0; i < count; i++) {
      nodes.emplace_back(vset.list[i].pubkey, vset.list[i].weight);
    }
    return nodes;
  }
  // this is the "true" algorithm for generating shardchain validator subgroups
  ValidatorSetPRNG gen{shard, cc_seqno};  // use zero seed (might use a non-trivial seed from ccv_conf in the future)
  std::vector<std::pair<td::uint64, td::uint64>> holes;
  holes.reserve(count);
  td::uint64 total_wt = vset.total_weight;
  for (unsigned i = 0; i < count; i++) {
    CHECK(total_wt > 0);
    auto p = gen.next_ranged(total_wt);  // generate a pseudo-random number 0 .. total_wt-1
    // auto op = p;
    for (auto& hole : holes) {
      if (p < hole.first) {
        break;
      }
      p += hole.second;
    }
    auto& entry = vset.at_weight(p);
    // LOG(DEBUG) << "vset entry #" << i << ": rem_wt=" << total_wt << ", total_wt=" << vset.total_weight << ", op=" << op << ", p=" << p << "; entry.cum_wt=" << entry.cum_weight << ", entry.wt=" << entry.weight << " " << entry.cum_weight / entry.weight;
    nodes.emplace_back(entry.pubkey, 1);  // NB: shardchain validator lists have all weights = 1
    CHECK(total_wt >= entry.weight);
    total_wt -= entry.weight;
    std::pair<td::uint64, td::uint64> new_hole{entry.cum_weight, entry.weight};
    auto it = std::upper_bound(holes.begin(), holes.end(), new_hole);
    CHECK(it == holes.begin() || *(it - 1) < new_hole);
    holes.insert(it, new_hole);
  }
  return nodes;
}

bool Config::rotated_all_shards() const {
  return nx_cc_updated;
}

bool WorkchainInfo::unpack(ton::WorkchainId wc, vm::CellSlice& cs) {
  workchain = ton::workchainInvalid;
  if (wc == ton::workchainInvalid) {
    return false;
  }
  block::gen::WorkchainDescr::Record info;
  if (!tlb::unpack(cs, info)) {
    return false;
  }
  enabled_since = info.enabled_since;
  actual_min_split = info.actual_min_split;
  min_split = info.min_split;
  max_split = info.max_split;
  basic = info.basic;
  active = info.active;
  accept_msgs = info.accept_msgs;
  flags = info.flags;
  zerostate_root_hash = info.zerostate_root_hash;
  zerostate_file_hash = info.zerostate_file_hash;
  version = info.version;
  if (basic) {
    min_addr_len = max_addr_len = addr_len_step = 256;
  } else {
    block::gen::WorkchainFormat::Record_wfmt_ext ext;
    if (!tlb::type_unpack(cs, block::gen::WorkchainFormat{basic}, ext)) {
      return false;
    }
    min_addr_len = ext.min_addr_len;
    max_addr_len = ext.max_addr_len;
    addr_len_step = ext.addr_len_step;
  }
  workchain = wc;
  LOG(DEBUG) << "unpacked info for workchain " << wc << ": basic=" << basic << ", active=" << active
             << ", accept_msgs=" << accept_msgs << ", min_split=" << min_split << ", max_split=" << max_split;
  return true;
}

Ref<WorkchainInfo> Config::get_workchain_info(ton::WorkchainId workchain_id) const {
  if (!workchains_dict_) {
    return {};
  }
  auto it = workchains_.find(workchain_id);
  if (it == workchains_.end()) {
    return {};
  } else {
    return it->second;
  }
}

bool Config::get_old_mc_block_id(ton::BlockSeqno seqno, ton::BlockIdExt& blkid, ton::LogicalTime* end_lt) const {
  if (block_id.is_valid() && seqno == block_id.id.seqno) {
    blkid = block_id;
    return true;
  } else {
    return block::get_old_mc_block_id(prev_blocks_dict_.get(), seqno, blkid, end_lt);
  }
}

bool Config::check_old_mc_block_id(const ton::BlockIdExt& blkid, bool strict) const {
  return (!strict && block_id.is_valid() && blkid.id.seqno == block_id.id.seqno)
             ? blkid == block_id
             : block::check_old_mc_block_id(prev_blocks_dict_.get(), blkid);
}

}  // namespace block
