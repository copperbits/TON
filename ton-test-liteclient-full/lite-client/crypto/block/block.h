#pragma once
#include "common/refcnt.hpp"
#include "vm/cells.h"
#include "vm/cellslice.h"
#include "vm/dict.h"
#include <ostream>
#include "tl/tlblib.hpp"
#include "td/utils/bits.h"
#include "ton/ton-types.h"

namespace block {

using td::Ref;

struct StdAddress {
  ton::WorkchainId workchain{ton::workchainInvalid};
  ton::StdSmcAddress addr;
  bool bounceable;
  bool testnet;
  StdAddress() = default;
  StdAddress(ton::WorkchainId _wc, const ton::StdSmcAddress& _addr, bool _bounce = true, bool _testnet = false)
      : workchain(_wc), addr(_addr), bounceable(_bounce), testnet(_testnet) {
  }
  StdAddress(ton::WorkchainId _wc, td::ConstBitPtr _addr, bool _bounce = true, bool _testnet = false)
      : workchain(_wc), addr(_addr), bounceable(_bounce), testnet(_testnet) {
  }
  StdAddress(std::string serialized);
  StdAddress(td::Slice from);
  bool is_valid() const {
    return workchain != ton::workchainInvalid;
  }
  std::string rserialize(bool base64_url = false) const;
  bool rserialize_to(td::MutableSlice to, bool base64_url = false) const;
  bool rserialize_to(char to[48], bool base64_url = false) const;
  bool rdeserialize(td::Slice from);
  bool rdeserialize(std::string from);
  bool rdeserialize(const char from[48]);
  bool operator==(const StdAddress& other) const;
};

struct ShardId {
  ton::WorkchainId workchain_id;
  int shard_pfx_len;
  unsigned long long shard_pfx;
  ShardId(ton::WorkchainId wc_id = ton::workchainInvalid)
      : workchain_id(wc_id), shard_pfx_len(0), shard_pfx(1ULL << 63) {
  }
  ShardId(ton::WorkchainId wc_id, unsigned long long sh_pfx);
  ShardId(ton::ShardIdFull ton_shard);
  ShardId(ton::BlockId ton_block);
  ShardId(const ton::BlockIdExt& ton_block);
  ShardId(ton::WorkchainId wc_id, unsigned long long sh_pfx, int sh_pfx_len);
  ShardId(vm::CellSlice& cs) {
    deserialize(cs);
  }
  ShardId(Ref<vm::CellSlice> cs_ref) {
    vm::CellSlice cs{*cs_ref};
    deserialize(cs);
  }
  explicit operator ton::ShardIdFull() const {
    return ton::ShardIdFull{workchain_id, shard_pfx};
  }
  bool operator==(const ShardId& other) const {
    return workchain_id == other.workchain_id && shard_pfx == other.shard_pfx;
  }
  void invalidate() {
    workchain_id = ton::workchainInvalid;
    shard_pfx_len = 0;
  }
  bool is_valid() const {
    return workchain_id != ton::workchainInvalid;
  }
  void show(std::ostream& os) const;
  std::string to_str() const;
  bool serialize(vm::CellBuilder& cb) const;
  bool deserialize(vm::CellSlice& cs);

 private:
  void init();
};

struct MsgProcessedUpto {
  ton::ShardId shard;
  ton::BlockSeqno mc_seqno;
  ton::LogicalTime last_inmsg_lt;
  ton::Bits256 last_inmsg_hash;
  ton::LogicalTime our_end_lt;  // corresponds to end_lt of our block seen from mc_seqno
  MsgProcessedUpto() = default;
  MsgProcessedUpto(ton::ShardId _shard, ton::BlockSeqno _mcseqno, ton::LogicalTime _lt, td::ConstBitPtr _hash,
                   ton::LogicalTime _endlt = 0)
      : shard(_shard), mc_seqno(_mcseqno), last_inmsg_lt(_lt), last_inmsg_hash(_hash), our_end_lt(_endlt) {
  }
  bool operator<(const MsgProcessedUpto& other) const & {
    return shard < other.shard || (shard == other.shard && mc_seqno < other.mc_seqno);
  }
  bool contains(const MsgProcessedUpto& other) const &;
  bool contains(ton::ShardId other_shard, ton::LogicalTime other_lt, td::ConstBitPtr other_hash,
                ton::BlockSeqno other_mc_seqno) const &;
  // NB: this is for checking whether we have already imported an internal message
  bool already_processed(ton::ShardId msg_next_addr, ton::LogicalTime msg_lt, td::ConstBitPtr msg_hash) const;
};

struct MsgProcessedUptoCollection {
  ton::ShardIdFull owner;
  bool valid{false};
  std::vector<MsgProcessedUpto> list;
  MsgProcessedUptoCollection(ton::ShardIdFull _owner) : owner(_owner) {
  }
  MsgProcessedUptoCollection(ton::ShardIdFull _owner, Ref<vm::CellSlice> cs_ref);
  static std::unique_ptr<MsgProcessedUptoCollection> unpack(ton::ShardIdFull _owner, Ref<vm::CellSlice> cs_ref);
  bool insert(ton::LogicalTime last_proc_lt, td::ConstBitPtr last_proc_hash, ton::BlockSeqno mc_seqno);
  bool compactify();
  bool pack(vm::CellBuilder& cb);
};

namespace tlb {
using namespace ::tlb;

struct Anycast final : TLB {
  int get_size(const vm::CellSlice& cs) const override {
    return cs.have(5) ? 5 + (int)cs.prefetch_ulong(5) : -1;
  }
};

struct VarUInteger final : TLB_Complex {
  int n, ln;
  VarUInteger(int _n) : n(_n) {
    ln = 32 - td::count_leading_zeroes32(n - 1);
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  td::RefInt256 as_integer_skip(vm::CellSlice& cs) const override;
  unsigned long long as_uint(const vm::CellSlice& cs) const override;
  bool null_value(vm::CellBuilder& cb) const override {
    return cb.store_zeroes_bool(ln);
  }
  bool store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const override;
  unsigned precompute_integer_size(const td::BigInt256& value) const;
  unsigned precompute_integer_size(td::RefInt256 value) const;
};

extern const VarUInteger t_VarUInteger_3, t_VarUInteger_7, t_VarUInteger_16, t_VarUInteger_32;

struct VarUIntegerPos final : TLB_Complex {
  int n, ln;
  VarUIntegerPos(int _n) : n(_n) {
    ln = 32 - td::count_leading_zeroes32(n - 1);
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  td::RefInt256 as_integer_skip(vm::CellSlice& cs) const override;
  unsigned long long as_uint(const vm::CellSlice& cs) const override;
  bool store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const override;
};

extern const VarUIntegerPos t_VarUIntegerPos_16, t_VarUIntegerPos_32;

struct VarInteger final : TLB_Complex {
  int n, ln;
  VarInteger(int _n) : n(_n) {
    ln = 32 - td::count_leading_zeroes32(n - 1);
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  td::RefInt256 as_integer_skip(vm::CellSlice& cs) const override;
  long long as_int(const vm::CellSlice& cs) const override;
  bool null_value(vm::CellBuilder& cb) const override {
    return cb.store_zeroes_bool(ln);
  }
  bool store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const override;
};

struct VarIntegerNz final : TLB_Complex {
  int n, ln;
  VarIntegerNz(int _n) : n(_n) {
    ln = 32 - td::count_leading_zeroes32(n - 1);
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  td::RefInt256 as_integer_skip(vm::CellSlice& cs) const override;
  long long as_int(const vm::CellSlice& cs) const override;
  bool store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const override;
};

struct Unary final : TLB {
  int get_size(const vm::CellSlice& cs) const override {
    return cs.count_leading(1) + 1;
  }
  bool validate_skip(vm::CellSlice& cs, int& n) const {
    return cs.advance((n = cs.count_leading(1)) + 1);
  }
  bool skip(vm::CellSlice& cs, int& n) const {
    return validate_skip(cs, n);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(get_size(cs));
  }
  bool skip(vm::CellSlice& cs) const override {
    return validate_skip(cs);
  }
  bool validate(const vm::CellSlice& cs) const override {
    return cs.have(get_size(cs));
  }
};

extern const Unary t_Unary;

struct HmLabel final : TLB_Complex {
  enum { hml_short = 0, hml_long = 2, hml_same = 3 };
  int m;  // max size
  HmLabel(int _m) : m(_m) {
  }
  bool validate_skip(vm::CellSlice& cs, int& n) const;
  bool skip(vm::CellSlice& cs, int& n) const {
    return validate_skip(cs, n);
  }
  bool skip(vm::CellSlice& cs) const override {
    int n;
    return skip(cs, n);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    int n;
    return validate_skip(cs, n);
  }
  int get_tag(const vm::CellSlice& cs) const override;
};

struct Hashmap final : TLB_Complex {
  const TLB& value_type;
  int n;
  Hashmap(int _n, const TLB& _val_type) : value_type(_val_type), n(_n) {
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

struct HashmapNode final : TLB_Complex {
  enum { hmn_leaf = 0, hmn_fork = 1 };
  const TLB& value_type;
  int n;
  HashmapNode(int _n, const TLB& _val_type) : value_type(_val_type), n(_n) {
  }
  int get_size(const vm::CellSlice& cs) const override;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return n > 0 ? hmn_fork : n;
  }
};

struct HashmapE final : TLB {
  enum { hme_empty = 0, hme_root = 1 };
  Hashmap root_type;
  HashmapE(int _n, const TLB& _val_type) : root_type(_n, _val_type) {
  }
  int get_size(const vm::CellSlice& cs) const override;
  bool validate(const vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
  bool null_value(vm::CellBuilder& cb) const override {
    return cb.store_zeroes_bool(1);
  }
  bool add_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const override;
  int sub_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const override;
  bool add_values_ref(Ref<vm::Cell>& res, Ref<vm::Cell> arg1, Ref<vm::Cell> arg2) const;
  int sub_values_ref(Ref<vm::Cell>& res, Ref<vm::Cell> arg1, Ref<vm::Cell> arg2) const;
  bool store_ref(vm::CellBuilder& cb, Ref<vm::Cell> arg) const;
};

struct AugmentationCheckData : vm::dict::AugmentationData {
  const TLB& value_type;
  const TLB& extra_type;
  AugmentationCheckData(const TLB& val_type, const TLB& ex_type) : value_type(val_type), extra_type(ex_type) {
  }
  bool skip_extra(vm::CellSlice& cs) const override {
    return extra_type.skip(cs);
  }
  bool eval_fork(vm::CellBuilder& cb, vm::CellSlice& left_cs, vm::CellSlice& right_cs) const override {
    return extra_type.add_values(cb, left_cs, right_cs);
  }
  bool eval_empty(vm::CellBuilder& cb) const override {
    return extra_type.null_value(cb);
  }
};

struct HashmapAug final : TLB_Complex {
  const AugmentationCheckData& aug;
  int n;
  HashmapAug(int _n, const AugmentationCheckData& _aug) : aug(_aug), n(_n) {
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool extract_extra(vm::CellSlice& cs) const;
};

struct HashmapAugNode final : TLB_Complex {
  enum { ahmn_leaf = 0, ahmn_fork = 1 };
  const AugmentationCheckData& aug;
  int n;
  HashmapAugNode(int _n, const AugmentationCheckData& _aug) : aug(_aug), n(_n) {
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return n > 0 ? ahmn_fork : n;
  }
};

struct HashmapAugE final : TLB_Complex {
  enum { ahme_empty = 0, ahme_root = 1 };
  HashmapAug root_type;
  HashmapAugE(int _n, const AugmentationCheckData& _aug) : root_type(_n, std::move(_aug)) {
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool extract_extra(vm::CellSlice& cs) const;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

struct Grams final : TLB_Complex {
  bool validate_skip(vm::CellSlice& cs) const override;
  td::RefInt256 as_integer_skip(vm::CellSlice& cs) const override;
  bool null_value(vm::CellBuilder& cb) const override;
  bool store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const override;
  unsigned precompute_size(const td::BigInt256& value) const;
  unsigned precompute_size(td::RefInt256 value) const;
};

extern const Grams t_Grams;

struct MsgAddressInt final : TLB_Complex {
  enum { addr_std = 2, addr_var = 3 };
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(2);
  }
  ton::ShardIdFull get_shard(vm::CellSlice&& cs) const;
  ton::ShardIdFull get_shard(const vm::CellSlice& cs) const;
  ton::ShardIdFull get_shard(Ref<vm::CellSlice> cs_ref) const;
  bool extract_std_address(Ref<vm::CellSlice> cs_ref, ton::WorkchainId& workchain, ton::StdSmcAddress& addr,
                           bool rewrite = true) const;
  bool extract_std_address(vm::CellSlice& cs, ton::WorkchainId& workchain, ton::StdSmcAddress& addr,
                           bool rewrite = true) const;
};

extern const MsgAddressInt t_MsgAddressInt;

struct MsgAddressExt final : TLB {
  enum { addr_none = 0, addr_ext = 1 };
  int get_size(const vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(2);
  }
};

extern const MsgAddressExt t_MsgAddressExt;

struct MsgAddress final : TLB_Complex {
  enum { addr_none = 0, addr_ext = 1, addr_std = 2, addr_var = 3 };
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(2);
  }
};

extern const MsgAddress t_MsgAddress;

struct ExtraCurrencyCollection final : TLB {
  HashmapE dict_type;
  ExtraCurrencyCollection() : dict_type(32, t_VarUIntegerPos_32) {
  }
  int get_size(const vm::CellSlice& cs) const override {
    return dict_type.get_size(cs);
  }
  bool validate(const vm::CellSlice& cs) const override {
    return dict_type.validate(cs);
  }
  bool null_value(vm::CellBuilder& cb) const override {
    return cb.store_zeroes_bool(1);
  }
  bool add_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const override {
    return dict_type.add_values(cb, cs1, cs2);
  }
  int sub_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const override {
    return dict_type.sub_values(cb, cs1, cs2);
  }
  bool add_values_ref(Ref<vm::Cell>& res, Ref<vm::Cell> arg1, Ref<vm::Cell> arg2) const {
    return dict_type.add_values_ref(res, std::move(arg1), std::move(arg2));
  }
  int sub_values_ref(Ref<vm::Cell>& res, Ref<vm::Cell> arg1, Ref<vm::Cell> arg2) const {
    return dict_type.sub_values_ref(res, std::move(arg1), std::move(arg2));
  }
  bool store_ref(vm::CellBuilder& cb, Ref<vm::Cell> arg) const {
    return dict_type.store_ref(cb, std::move(arg));
  }
  unsigned precompute_size(Ref<vm::Cell> arg) const {
    return arg.is_null() ? 1 : 0x10001;
  }
};

extern const ExtraCurrencyCollection t_ExtraCurrencyCollection;

struct CurrencyCollection final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  td::RefInt256 as_integer_skip(vm::CellSlice& cs) const override;
  bool null_value(vm::CellBuilder& cb) const override {
    return cb.store_bits_same_bool(1 + 4, false);
  }
  bool add_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const override;
  bool unpack_special(vm::CellSlice& cs, td::RefInt256& balance, Ref<vm::Cell>& extra) const;
  bool pack_special(vm::CellBuilder& cb, td::RefInt256 balance, Ref<vm::Cell> extra) const;
  unsigned precompute_size(td::RefInt256 balance, Ref<vm::Cell> extra) const {
    return t_Grams.precompute_size(std::move(balance)) + t_ExtraCurrencyCollection.precompute_size(std::move(extra));
  }
};

extern const CurrencyCollection t_CurrencyCollection;

struct CommonMsgInfo final : TLB_Complex {
  enum { int_msg_info = 0, ext_in_msg_info = 2, ext_out_msg_info = 3 };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    int v = (int)cs.prefetch_ulong(2);
    return v == 1 ? int_msg_info : v;
  }
  struct Record_int_msg_info;
  bool unpack(vm::CellSlice& cs, Record_int_msg_info& data) const;
  bool get_created_lt(vm::CellSlice& cs, unsigned long long& created_lt) const;
  bool is_internal(const vm::CellSlice& cs) const {
    return get_tag(cs) == int_msg_info;
  }
};

struct CommonMsgInfo::Record_int_msg_info {
  bool ihr_disabled, bounce, bounced;
  Ref<vm::CellSlice> src, dest, value, ihr_fee, fwd_fee;
  unsigned long long created_lt;
  unsigned created_at;
};

extern const CommonMsgInfo t_CommonMsgInfo;

struct TickTock final : TLB {
  int get_size(const vm::CellSlice& cs) const override {
    return 2;
  }
};

extern const TickTock t_TickTock;

struct StateInit final : TLB_Complex {
  bool validate_skip(vm::CellSlice& cs) const override;
  bool get_ticktock(vm::CellSlice& cs, int& ticktock) const;
};

extern const StateInit t_StateInit;

struct Message final : TLB_Complex {
  bool validate_skip(vm::CellSlice& cs) const override;
  bool extract_info(vm::CellSlice& cs) const;
  bool get_created_lt(vm::CellSlice& cs, unsigned long long& created_lt) const;
  bool is_internal(const vm::CellSlice& cs) const {
    return t_CommonMsgInfo.is_internal(cs);
  }
  bool is_internal(Ref<vm::Cell> ref) const;
};

extern const Message t_Message;
extern const RefTo<Message> t_Ref_Message;

struct IntermediateAddress final : TLB_Complex {
  enum { interm_addr_regular = 0, interm_addr_simple = 2, interm_addr_ext = 3 };
  int get_size(const vm::CellSlice& cs) const override;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool fetch_regular(vm::CellSlice& cs, int& use_dst_bits) const {
    return cs.fetch_uint_to(8, use_dst_bits) && use_dst_bits <= 96;
  }
  int get_tag(const vm::CellSlice& cs) const override {
    int v = (int)cs.prefetch_ulong(2);
    return v == 1 ? interm_addr_regular : v;
  }
};

extern const IntermediateAddress t_IntermediateAddress;

struct MsgEnvelope final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool extract_fwd_fees_remaining(vm::CellSlice& cs) const;
  struct Record {
    typedef MsgEnvelope type_class;
    Ref<vm::CellSlice> cur_addr, next_addr, fwd_fee_remaining;
    Ref<vm::Cell> msg;
  };
  struct Record_std {
    typedef MsgEnvelope type_class;
    int cur_addr, next_addr;
    td::RefInt256 fwd_fee_remaining;
    Ref<vm::Cell> msg;
  };
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack(vm::CellSlice& cs, Record_std& data) const;
  bool unpack_std(vm::CellSlice& cs, int& cur_a, int& nhop_a, Ref<vm::Cell>& msg) const;
  bool get_created_lt(const vm::CellSlice& cs, unsigned long long& created_lt) const;
};

extern const MsgEnvelope t_MsgEnvelope;
extern const RefTo<MsgEnvelope> t_Ref_MsgEnvelope;

struct StorageUsed final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const StorageUsed t_StorageUsed;

struct StorageUsedShort final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const StorageUsedShort t_StorageUsedShort;

struct StorageInfo final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const StorageInfo t_StorageInfo;

struct AccountState final : TLB_Complex {
  enum { account_uninit = 0, account_frozen = 1, account_active = 2 };
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    int t = (int)cs.prefetch_ulong(2);
    return t == 3 ? account_active : t;
  }
  bool get_ticktock(vm::CellSlice& cs, int& ticktock) const;
};

extern const AccountState t_AccountState;

struct AccountStorage final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool skip_copy_balance(vm::CellBuilder& cb, vm::CellSlice& cs) const;
};

extern const AccountStorage t_AccountStorage;

struct Account final : TLB_Complex {
  enum { account_none = 0, account = 1 };
  bool allow_empty;
  Account(bool _allow_empty = false) : allow_empty(_allow_empty) {
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  // Ref<vm::CellSlice> get_balance(const vm::CellSlice& cs) const;
  bool skip_copy_balance(vm::CellBuilder& cb, vm::CellSlice& cs) const;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

extern const Account t_Account, t_AccountE;
extern const RefTo<Account> t_Ref_Account;

struct AccountStatus final : TLB {
  enum { acc_state_uninit, acc_state_frozen, acc_state_active, acc_state_nonexist };
  int get_size(const vm::CellSlice& cs) const override {
    return 2;
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(2);
  }
};

extern const AccountStatus t_AccountStatus;

struct ShardAccount final : TLB_Complex {
  int get_size(const vm::CellSlice& cs) const override {
    return 0x10140;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance_ext(0x140, 1);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(0x140) && t_Ref_Account.validate_skip(cs);
  }
};

extern const ShardAccount t_ShardAccount;

struct Aug_ShardAccounts final : AugmentationCheckData {
  Aug_ShardAccounts() : AugmentationCheckData(t_ShardAccount, t_CurrencyCollection) {
  }
  bool eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const override;
};

extern const Aug_ShardAccounts aug_ShardAccounts;

struct ShardAccounts final : TLB_Complex {
  HashmapAugE dict_type;
  ShardAccounts() : dict_type(256, aug_ShardAccounts){};
  bool skip(vm::CellSlice& cs) const override {
    return dict_type.skip(cs);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return dict_type.validate_skip(cs);
  }
};

extern const ShardAccounts t_ShardAccounts;

struct AccStatusChange final : TLB {
  enum { acst_unchanged = 0, acst_frozen = 2, acst_deleted = 3 };
  int get_size(const vm::CellSlice& cs) const override {
    return cs.prefetch_ulong(1) ? 2 : 1;
  }
  int get_tag(const vm::CellSlice& cs) const override {
    if (cs.size() == 1) {
      return (int)cs.prefetch_ulong(1) ? -1 : acst_unchanged;
    }
    int v = (int)cs.prefetch_ulong(2);
    return v == 1 ? acst_unchanged : v;
  }
};

extern const AccStatusChange t_AccStatusChange;

struct TrStoragePhase final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const TrStoragePhase t_TrStoragePhase;

struct TrCreditPhase final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const TrCreditPhase t_TrCreditPhase;

struct TrComputeInternal1 final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

struct ComputeSkipReason final : TLB {
  enum { cskip_no_state = 0, cskip_bad_state = 1, cskip_no_gas = 2 };
  int get_size(const vm::CellSlice& cs) const override {
    return 2;
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return get_tag(cs) >= 0 && cs.advance(2);
  }
  int get_tag(const vm::CellSlice& cs) const override {
    int t = (int)cs.prefetch_ulong(2);
    return t < 3 ? t : -1;
  }
};

extern const ComputeSkipReason t_ComputeSkipReason;

struct TrComputePhase final : TLB_Complex {
  enum { tr_phase_compute_skipped = 0, tr_phase_compute_vm = 1 };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

extern const TrComputePhase t_TrComputePhase;

struct TrActionPhase final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const TrActionPhase t_TrActionPhase;

struct TrBouncePhase final : TLB_Complex {
  enum { tr_phase_bounce_negfunds = 0, tr_phase_bounce_nofunds = 1, tr_phase_bounce_ok = 2 };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override;
};

extern const TrBouncePhase t_TrBouncePhase;

struct SplitMergeInfo final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const SplitMergeInfo t_SplitMergeInfo;

struct TransactionDescr final : TLB_Complex {
  enum {
    trans_ord = 0,
    trans_storage = 1,
    trans_tick_tock = 2,
    trans_split_prepare = 4,
    trans_split_install = 5,
    trans_merge_prepare = 6,
    trans_merge_install = 7
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override;
};

extern const TransactionDescr t_TransactionDescr;

struct Transaction final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool get_total_fees(vm::CellSlice&& cs, td::RefInt256& total_fees) const;
};

extern const Transaction t_Transaction;
extern const RefTo<Transaction> t_Ref_Transaction;

struct Aug_AccountTransactions final : AugmentationCheckData {
  Aug_AccountTransactions() : AugmentationCheckData(t_Ref_Transaction, t_Grams) {
  }
  bool eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const override;
};

extern const Aug_AccountTransactions aug_AccountTransactions;
extern const HashmapAug t_AccountTransactions;  // (HashmapAug 64 ^Transaction Grams)

struct HashUpdate final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(8 + 256 * 2);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.fetch_ulong(8) == 0x72 && cs.advance(256 * 2);
  }
};

extern const HashUpdate t_HashUpdate;
extern const RefTo<HashUpdate> t_Ref_HashUpdate;

struct AccountBlock final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool get_total_fees(vm::CellSlice&& cs, td::RefInt256& total_fees) const;
};

extern const AccountBlock t_AccountBlock;

struct Aug_ShardAccountBlocks final : AugmentationCheckData {
  Aug_ShardAccountBlocks() : AugmentationCheckData(t_AccountBlock, t_Grams) {
  }
  bool eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const override;
};

extern const Aug_ShardAccountBlocks aug_ShardAccountBlocks;
extern const HashmapAugE t_ShardAccountBlocks;  // (HashmapAugE 256 AccountBlock Grams)

struct ImportFees final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool null_value(vm::CellBuilder& cb) const override {
    return cb.store_bits_same_bool(4 + 4 + 1, false);
  }
  bool add_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const override;
};

extern const ImportFees t_ImportFees;

struct InMsg final : TLB_Complex {
  enum {
    msg_import_ext = 0,
    msg_import_ihr = 2,
    msg_import_imm = 3,
    msg_import_fin = 4,
    msg_import_tr = 5,
    msg_discard_fin = 6,
    msg_discard_tr = 7
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(3);
  }
  bool get_import_fees(vm::CellBuilder& cb, vm::CellSlice& cs) const;
};

extern const InMsg t_InMsg;

struct OutMsg final : TLB_Complex {
  enum {
    msg_export_ext = 0,
    msg_export_new = 1,
    msg_export_imm = 2,
    msg_export_tr = 3,
    msg_export_deq_imm = 4,
    msg_export_deq = 6,
    msg_export_tr_req = 7
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(3);
  }
  bool get_export_value(vm::CellBuilder& cb, vm::CellSlice& cs) const;
  bool get_created_lt(vm::CellSlice& cs, unsigned long long& created_lt) const;
};

extern const OutMsg t_OutMsg;

// next: InMsgDescr, OutMsgDescr, OutMsgQueue, and their augmentations

struct Aug_InMsgDescr final : AugmentationCheckData {
  Aug_InMsgDescr() : AugmentationCheckData(t_InMsg, t_ImportFees) {
  }
  bool eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const override {
    return t_InMsg.get_import_fees(cb, cs);
  }
};

extern const Aug_InMsgDescr aug_InMsgDescr;

struct InMsgDescr final : TLB_Complex {
  HashmapAugE dict_type;
  InMsgDescr() : dict_type(256, aug_InMsgDescr){};
  bool skip(vm::CellSlice& cs) const override {
    return dict_type.skip(cs);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return dict_type.validate_skip(cs);
  }
};

extern const InMsgDescr t_InMsgDescr;

struct Aug_OutMsgDescr final : AugmentationCheckData {
  Aug_OutMsgDescr() : AugmentationCheckData(t_OutMsg, t_CurrencyCollection) {
  }
  bool eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const override {
    return t_OutMsg.get_export_value(cb, cs);
  }
};

extern const Aug_OutMsgDescr aug_OutMsgDescr;

struct OutMsgDescr final : TLB_Complex {
  HashmapAugE dict_type;
  OutMsgDescr() : dict_type(256, aug_OutMsgDescr){};
  bool skip(vm::CellSlice& cs) const override {
    return dict_type.skip(cs);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return dict_type.validate_skip(cs);
  }
};

extern const OutMsgDescr t_OutMsgDescr;

struct EnqueuedMsg final : TLB_Complex {
  int get_size(const vm::CellSlice& cs) const override {
    return 0x10040;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance_ext(0x10040);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const EnqueuedMsg t_EnqueuedMsg;

struct Aug_OutMsgQueue final : AugmentationCheckData {
  Aug_OutMsgQueue() : AugmentationCheckData(t_EnqueuedMsg, t_uint64) {
  }
  bool eval_fork(vm::CellBuilder& cb, vm::CellSlice& left_cs, vm::CellSlice& right_cs) const override;
  bool eval_empty(vm::CellBuilder& cb) const override;
  bool eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const override;
};

extern const Aug_OutMsgQueue aug_OutMsgQueue;

struct OutMsgQueue final : TLB_Complex {
  HashmapAugE dict_type;
  OutMsgQueue() : dict_type(32 + 64 + 256, aug_OutMsgQueue){};
  bool skip(vm::CellSlice& cs) const override {
    return dict_type.skip(cs);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return dict_type.validate_skip(cs);
  }
};

extern const OutMsgQueue t_OutMsgQueue;

struct ProcessedUpto final : TLB {
  int get_size(const vm::CellSlice& cs) const override {
    return 64 + 256;
  }
};

extern const ProcessedUpto t_ProcessedUpto;
extern const HashmapE t_ProcessedInfo;
extern const HashmapE t_IhrPendingInfo;

struct OutMsgQueueInfo final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const OutMsgQueueInfo t_OutMsgQueueInfo;
extern const RefTo<OutMsgQueueInfo> t_Ref_OutMsgQueueInfo;

struct ExtBlkRef final : TLB {
  int get_size(const vm::CellSlice& cs) const override {
    return 64 + 32 + 256;
  }
};

extern const ExtBlkRef t_ExtBlkRef;

struct BlkMasterInfo final : TLB {
  int get_size(const vm::CellSlice& cs) const override {
    return t_ExtBlkRef.get_size(cs);
  }
};

extern const BlkMasterInfo t_BlkMasterInfo;

struct ShardIdent final : TLB_Complex {
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 2 + 6 + 32 + 64;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(get_size(cs));
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool unpack(vm::CellSlice& cs, ton::ShardIdFull& data) const;
  bool pack(vm::CellBuilder& cb, ton::ShardIdFull data) const;
  bool unpack(vm::CellSlice& cs, ton::WorkchainId& workchain, ton::ShardId& shard) const;
  bool pack(vm::CellBuilder& cb, ton::WorkchainId workchain, ton::ShardId shard) const;
};

struct ShardIdent::Record {
  int shard_pfx_bits;
  int workchain_id;
  unsigned long long shard_prefix;
  Record() : shard_pfx_bits(-1) {
  }
  Record(int _pfxlen, int _wcid, unsigned long long _pfx)
      : shard_pfx_bits(_pfxlen), workchain_id(_wcid), shard_prefix(_pfx) {
  }
  bool check() const;
  bool is_valid() const {
    return shard_pfx_bits >= 0;
  }
  void invalidate() {
    shard_pfx_bits = -1;
  }
};

extern const ShardIdent t_ShardIdent;

struct BlockIdExt final : TLB_Complex {
  int get_size(const vm::CellSlice& cs) const override {
    return 2 + 6 + 32 + 64 + 32 + 256 * 2;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(get_size(cs));
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, ton::BlockIdExt& data) const;
  bool pack(vm::CellBuilder& cb, const ton::BlockIdExt& data) const;
};

extern const BlockIdExt t_BlockIdExt;

struct ShardState final : TLB_Complex {
  enum { shard_state = (int)0x9023afde };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(32) == shard_state ? shard_state : -1;
  }
};

extern const ShardState t_ShardState;

struct ShardState_aux final : TLB_Complex {
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ShardState_aux t_ShardState_aux;

struct LibDescr final : TLB_Complex {
  enum { shared_lib_descr = 0 };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(2);
  }
};

extern const LibDescr t_LibDescr;

struct BlkPrevInfo final : TLB_Complex {
  bool merged;
  BlkPrevInfo(bool _merged) : merged(_merged) {
  }
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const BlkPrevInfo t_BlkPrevInfo_0;

struct McStateExtra final : TLB_Complex {
  enum { masterchain_state_extra = 0xcc1f };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
};

extern const McStateExtra t_McStateExtra;

}  // namespace tlb

std::ostream& operator<<(std::ostream& os, const ShardId& shard_id);

bool pack_std_smc_addr_to(char result[48], bool base64_url, ton::WorkchainId wc, const ton::StdSmcAddress& addr,
                          bool bounceable, bool testnet);
std::string pack_std_smc_addr(bool base64_url, ton::WorkchainId wc, const ton::StdSmcAddress& addr, bool bounceable,
                              bool testnet);
bool unpack_std_smc_addr(const char packed[48], ton::WorkchainId& wc, ton::StdSmcAddress& addr, bool& bounceable,
                         bool& testnet);
bool unpack_std_smc_addr(td::Slice packed, ton::WorkchainId& wc, ton::StdSmcAddress& addr, bool& bounceable,
                         bool& testnet);
bool unpack_std_smc_addr(std::string packed, ton::WorkchainId& wc, ton::StdSmcAddress& addr, bool& bounceable,
                         bool& testnet);

bool store_UInt7(vm::CellBuilder& cb, unsigned long long value);
bool store_UInt7(vm::CellBuilder& cb, unsigned long long value1, unsigned long long value2);
bool store_Maybe_Grams(vm::CellBuilder& cb, td::RefInt256 value);
bool store_Maybe_Grams_nz(vm::CellBuilder& cb, td::RefInt256 value);
bool store_CurrencyCollection(vm::CellBuilder& cb, td::RefInt256 value, Ref<vm::Cell> extra);
bool fetch_CurrencyCollection(vm::CellSlice& cs, td::RefInt256& value, Ref<vm::Cell>& extra);
bool unpack_CurrencyCollection(Ref<vm::CellSlice> csr, td::RefInt256& value, Ref<vm::Cell>& extra);

bool valid_library_collection(Ref<vm::Cell> cell, bool catch_errors = true);

bool valid_config_data(Ref<vm::Cell> cell, const td::BitArray<256>& addr, bool catch_errors = true,
                       bool relax_par0 = false);

bool add_extra_currency(Ref<vm::Cell> extra1, Ref<vm::Cell> extra2, Ref<vm::Cell>& res);
bool sub_extra_currency(Ref<vm::Cell> extra1, Ref<vm::Cell> extra2, Ref<vm::Cell>& res);

ton::ShardIdFull interpolate_addr(ton::ShardIdFull src, ton::ShardIdFull dest, int used_dest_bits);
// result: (transit_addr_dest_bits, nh_addr_dest_bits)
std::pair<int, int> perform_hypercube_routing(ton::ShardIdFull src, ton::ShardIdFull dest, ton::ShardIdFull cur,
                                              int used_dest_bits = 0);

bool unpack_block_prev_blk(Ref<vm::Cell> block_root, ton::BlockIdExt& id, std::vector<ton::BlockIdExt>& prev,
                           ton::BlockIdExt& mc_blkid, bool& after_split);
td::Status unpack_block_prev_blk_ext(Ref<vm::Cell> block_root, ton::BlockIdExt& id, std::vector<ton::BlockIdExt>& prev,
                                     ton::BlockIdExt& mc_blkid, bool& after_split);
td::Status unpack_block_prev_blk_try(Ref<vm::Cell> block_root, ton::BlockIdExt& id, std::vector<ton::BlockIdExt>& prev,
                                     ton::BlockIdExt& mc_blkid, bool& after_split);

std::unique_ptr<vm::Dictionary> get_prev_blocks_dict(Ref<vm::Cell> state_root);
bool get_old_mc_block_id(vm::Dictionary* prev_blocks_dict, ton::BlockSeqno seqno, ton::BlockIdExt& blkid,
                         ton::LogicalTime* end_lt = nullptr);
bool get_old_mc_block_id(vm::Dictionary& prev_blocks_dict, ton::BlockSeqno seqno, ton::BlockIdExt& blkid,
                         ton::LogicalTime* end_lt = nullptr);
bool check_old_mc_block_id(vm::Dictionary* prev_blocks_dict, const ton::BlockIdExt& blkid);
bool check_old_mc_block_id(vm::Dictionary& prev_blocks_dict, const ton::BlockIdExt& blkid);

}  // namespace block
