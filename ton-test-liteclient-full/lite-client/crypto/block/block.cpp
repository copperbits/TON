#include "td/utils/bits.h"
#include "block/block.h"
#include "block/block-auto.h"
#include "ton/ton-shard.h"
#include "common/util.h"
#include "td/utils/crypto.h"

namespace block {

using CombineError = vm::CombineError;

bool debug(const char* str) {
  std::cerr << str;
  return true;
}

bool debug(int x) {
  if (x < 100) {
    std::cerr << '[' << (char)(64 + x) << ']';
  } else {
    std::cerr << '[' << (char)(64 + x / 100) << x % 100 << ']';
  }
  return true;
}

#define DBG_START int dbg = 0;
#define DBG debug(++dbg)&&
#define DEB_START DBG_START
#define DEB DBG

bool pack_std_smc_addr_to(char result[48], bool base64_url, ton::WorkchainId wc, const ton::StdSmcAddress& addr,
                          bool bounceable, bool testnet) {
  if (wc < -128 || wc >= 128) {
    return false;
  }
  unsigned char buffer[36];
  buffer[0] = (unsigned char)(0x11 + bounceable * 0x40 + testnet * 0x80);
  buffer[1] = (unsigned char)wc;
  memcpy(buffer + 2, addr.data(), 32);
  unsigned crc = td::crc16(td::Slice{buffer, 34});
  buffer[34] = (unsigned char)(crc >> 8);
  buffer[35] = (unsigned char)(crc & 0xff);
  CHECK(buff_base64_encode(td::MutableSlice{result, 48}, td::Slice{buffer, 36}, base64_url) == 48);
  return true;
}

std::string pack_std_smc_addr(bool base64_url, ton::WorkchainId wc, const ton::StdSmcAddress& addr, bool bounceable,
                              bool testnet) {
  char result[48];
  if (pack_std_smc_addr_to(result, base64_url, wc, addr, bounceable, testnet)) {
    return std::string{result, 48};
  } else {
    return "";
  }
}

bool unpack_std_smc_addr(const char packed[48], ton::WorkchainId& wc, ton::StdSmcAddress& addr, bool& bounceable,
                         bool& testnet) {
  unsigned char buffer[36];
  wc = ton::workchainInvalid;
  if (!buff_base64_decode(td::MutableSlice{buffer, 36}, td::Slice{packed, 48}, true)) {
    return false;
  }
  unsigned crc = td::crc16(td::Slice{buffer, 34});
  if (buffer[34] != (unsigned char)(crc >> 8) || buffer[35] != (unsigned char)(crc & 0xff)) {
    return false;
  }
  if ((buffer[0] & 0x3f) != 0x11) {
    return false;
  }
  testnet = (buffer[0] & 0x80);
  bounceable = (buffer[0] & 0x40);
  wc = (char)buffer[1];
  memcpy(addr.data(), buffer + 2, 32);
  return true;
}

bool unpack_std_smc_addr(td::Slice packed, ton::WorkchainId& wc, ton::StdSmcAddress& addr, bool& bounceable,
                         bool& testnet) {
  return packed.size() == 48 && unpack_std_smc_addr(packed.data(), wc, addr, bounceable, testnet);
}

bool unpack_std_smc_addr(std::string packed, ton::WorkchainId& wc, ton::StdSmcAddress& addr, bool& bounceable,
                         bool& testnet) {
  return packed.size() == 48 && unpack_std_smc_addr(packed.data(), wc, addr, bounceable, testnet);
}

StdAddress::StdAddress(std::string serialized) {
  rdeserialize(std::move(serialized));
}

StdAddress::StdAddress(td::Slice from) {
  rdeserialize(std::move(from));
}

std::string StdAddress::rserialize(bool base64_url) const {
  char buffer[48];
  return rserialize_to(buffer, base64_url) ? std::string{buffer, 48} : "";
}

bool StdAddress::rserialize_to(td::MutableSlice to, bool base64_url) const {
  return to.size() == 48 && rserialize_to(to.data(), base64_url);
}

bool StdAddress::rserialize_to(char to[48], bool base64_url) const {
  return pack_std_smc_addr_to(to, base64_url, workchain, addr, bounceable, testnet);
}

bool StdAddress::rdeserialize(td::Slice from) {
  return from.size() == 48 && unpack_std_smc_addr(from.data(), workchain, addr, bounceable, testnet);
}

bool StdAddress::rdeserialize(std::string from) {
  return from.size() == 48 && unpack_std_smc_addr(from.data(), workchain, addr, bounceable, testnet);
}

bool StdAddress::rdeserialize(const char from[48]) {
  return unpack_std_smc_addr(from, workchain, addr, bounceable, testnet);
}

bool StdAddress::operator==(const StdAddress& other) const {
  return workchain == other.workchain && addr == other.addr && bounceable == other.bounceable &&
         testnet == other.testnet;
}

void ShardId::init() {
  if (!shard_pfx) {
    shard_pfx = (1ULL << 63);
    shard_pfx_len = 0;
  } else {
    shard_pfx_len = 63 - td::count_trailing_zeroes_non_zero64(shard_pfx);
  }
}

ShardId::ShardId(ton::WorkchainId wc_id, unsigned long long sh_pfx) : workchain_id(wc_id), shard_pfx(sh_pfx) {
  init();
}

ShardId::ShardId(ton::ShardIdFull ton_shard_id) : workchain_id(ton_shard_id.workchain), shard_pfx(ton_shard_id.shard) {
  init();
}

ShardId::ShardId(ton::BlockId ton_block_id) : workchain_id(ton_block_id.workchain), shard_pfx(ton_block_id.shard) {
  init();
}

ShardId::ShardId(const ton::BlockIdExt& ton_block_id)
    : workchain_id(ton_block_id.id.workchain), shard_pfx(ton_block_id.id.shard) {
  init();
}

ShardId::ShardId(ton::WorkchainId wc_id, unsigned long long sh_pfx, int sh_pfx_len)
    : workchain_id(wc_id), shard_pfx_len(sh_pfx_len) {
  if (sh_pfx_len < 0) {
    shard_pfx_len = 0;
    shard_pfx = (1ULL << 63);
  } else if (sh_pfx_len > 63) {
    shard_pfx_len = 63;
    shard_pfx = sh_pfx | 1;
  } else {
    unsigned long long pow = 1ULL << (63 - sh_pfx_len);
    shard_pfx = (sh_pfx | pow) & (pow - 1);
  }
}

std::ostream& operator<<(std::ostream& os, const ShardId& shard_id) {
  shard_id.show(os);
  return os;
}

void ShardId::show(std::ostream& os) const {
  if (workchain_id == ton::workchainInvalid) {
    os << '?';
    return;
  }
  os << workchain_id << ':' << shard_pfx_len << ',';
  unsigned long long t = shard_pfx;
  int cnt = 0;
  while ((t & ((1ULL << 63) - 1)) != 0) {
    static const char hex_digit[] = "0123456789ABCDEF";
    os << (char)hex_digit[t >> 60];
    t <<= 4;
    ++cnt;
  }
  if (!t || !cnt) {
    os << '_';
  }
}

std::string ShardId::to_str() const {
  std::ostringstream os;
  show(os);
  return os.str();
}

bool ShardId::serialize(vm::CellBuilder& cb) const {
  if (workchain_id == ton::workchainInvalid || cb.remaining_bits() < 104) {
    return false;
  }
  return cb.store_long_bool(0, 2) && cb.store_ulong_rchk_bool(shard_pfx_len, 6) &&
         cb.store_long_bool(workchain_id, 32) && cb.store_long_bool(shard_pfx & (shard_pfx - 1));
}

bool ShardId::deserialize(vm::CellSlice& cs) {
  if (cs.fetch_ulong(2) == 0 && cs.fetch_uint_to(6, shard_pfx_len) && cs.fetch_int_to(32, workchain_id) &&
      workchain_id != ton::workchainInvalid && cs.fetch_uint_to(64, shard_pfx)) {
    auto pow2 = (1ULL << (63 - shard_pfx_len));
    if (!(shard_pfx & (pow2 - 1))) {
      shard_pfx |= pow2;
      return true;
    }
  }

  invalidate();
  return false;
}

MsgProcessedUptoCollection::MsgProcessedUptoCollection(ton::ShardIdFull _owner, Ref<vm::CellSlice> cs_ref)
    : owner(_owner) {
  vm::Dictionary dict{std::move(cs_ref), 96};
  valid = dict.check_for_each([&](Ref<vm::CellSlice> value, td::ConstBitPtr key, int n) -> bool {
    if (value->size_ext() != 64 + 256) {
      return false;
    }
    list.emplace_back();
    MsgProcessedUpto& z = list.back();
    z.shard = key.get_uint(64);
    z.mc_seqno = (unsigned)((key + 64).get_uint(32));
    z.our_end_lt = 0;
    z.last_inmsg_lt = value.write().fetch_ulong(64);
    return value.write().fetch_bits_to(z.last_inmsg_hash) && z.shard && ton::shard_contains(owner.shard, z.shard);
  });
}

std::unique_ptr<MsgProcessedUptoCollection> MsgProcessedUptoCollection::unpack(ton::ShardIdFull _owner,
                                                                               Ref<vm::CellSlice> cs_ref) {
  auto v = std::make_unique<MsgProcessedUptoCollection>(_owner, std::move(cs_ref));
  return v && v->valid ? std::move(v) : std::unique_ptr<MsgProcessedUptoCollection>{};
}

bool MsgProcessedUpto::contains(const MsgProcessedUpto& other) const & {
  return ton::shard_is_ancestor(shard, other.shard) && mc_seqno >= other.mc_seqno &&
         (last_inmsg_lt > other.last_inmsg_lt ||
          (last_inmsg_lt == other.last_inmsg_lt && !(last_inmsg_hash < other.last_inmsg_hash)));
}

bool MsgProcessedUpto::contains(ton::ShardId other_shard, ton::LogicalTime other_lt, td::ConstBitPtr other_hash,
                                ton::BlockSeqno other_mc_seqno) const & {
  return ton::shard_is_ancestor(shard, other_shard) && mc_seqno >= other_mc_seqno &&
         (last_inmsg_lt > other_lt ||
          (last_inmsg_lt == other_lt && td::bitstring::bits_memcmp(last_inmsg_hash.bits(), other_hash, 256) > 0));
}

bool MsgProcessedUptoCollection::insert(ton::LogicalTime last_proc_lt, td::ConstBitPtr last_proc_hash,
                                        ton::BlockSeqno mc_seqno) {
  if (!last_proc_lt || last_proc_lt == std::numeric_limits<td::uint64>::max()) {
    return false;
  }
  for (const auto& z : list) {
    if (z.contains(owner.shard, last_proc_lt, last_proc_hash, mc_seqno)) {
      return true;
    }
  }
  list.emplace_back(owner.shard, mc_seqno, last_proc_lt, last_proc_hash);
  return true;
}

bool MsgProcessedUptoCollection::compactify() {
  std::sort(list.begin(), list.end());
  std::size_t i, j, k = 0, n = list.size();
  for (i = 0; i < n; i++) {
    bool f = true;
    for (j = 0; j < n; j++) {
      if (j != i && list[j].contains(list[i])) {
        f = false;
        break;
      }
    }
    if (f) {
      list[k++] = list[i];
    }
  }
  list.resize(k);
  return true;
}

bool MsgProcessedUptoCollection::pack(vm::CellBuilder& cb) {
  if (!compactify()) {
    return false;
  }
  vm::Dictionary dict{96};
  for (const auto& z : list) {
    td::BitArray<96> key;
    vm::CellBuilder cb2;
    key.bits().store_uint(z.shard, 64);
    (key.bits() + 64).store_uint(z.mc_seqno, 32);
    if (!(cb2.store_long_bool(z.last_inmsg_lt) && cb2.store_bits_bool(z.last_inmsg_hash) &&
          dict.set_builder(key, cb2, vm::Dictionary::SetMode::Add))) {
      return false;
    }
  }
  return std::move(dict).append_dict_to_bool(cb);
}

bool MsgProcessedUpto::already_processed(ton::ShardId msg_next_addr, ton::LogicalTime msg_lt,
                                         td::ConstBitPtr msg_hash) const {
  return false;  // TODO: implement this properly
}

namespace tlb {

using namespace ::tlb;

int MsgAddressExt::get_size(const vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case addr_none:  // 00, addr_none
      return 2;
    case addr_ext:  // 01, addr_ext
      if (cs.have(10)) {
        int len = cs.prefetch_long(10) & 0xff;
        return 2 + 8 + len;
      }
  }
  return -1;
}

const MsgAddressExt t_MsgAddressExt;

const Anycast t_Anycast;

const Maybe<Anycast> t_Maybe_Anycast;

bool MsgAddressInt::validate_skip(vm::CellSlice& cs) const {
  if (!cs.have(3)) {
    return false;
  }
  switch (get_tag(cs)) {
    case addr_std:
      return cs.advance(2) && t_Maybe_Anycast.skip(cs) && cs.advance(8 + 256);
    case addr_var:
      if (cs.advance(2) && t_Maybe_Anycast.skip(cs) && cs.have(9 + 32)) {
        int addr_len = (int)cs.fetch_ulong(9);
        int workchain_id = (int)cs.fetch_long(32);
        return cs.advance(addr_len) && (workchain_id < -0x80 || workchain_id > 0x7f || addr_len != 256) &&
               (workchain_id != 0 && workchain_id != -1);
      }
  }
  return false;
}

ton::ShardIdFull MsgAddressInt::get_shard(vm::CellSlice&& cs) const {
  if (!cs.have(3 + 8 + 64)) {
    return {};
  }
  ton::WorkchainId workchain;
  unsigned long long shard;
  int t = (int)cs.prefetch_ulong(2 + 1 + 5);
  switch (t >> 5) {
    case 4: {  // addr_std$10, anycast=nothing$0
      if (cs.advance(3) && cs.fetch_int_to(8, workchain) && cs.fetch_uint_to(64, shard)) {
        return {workchain, shard};
      }
      break;
    }
    case 5: {   // addr_std$10, anycast=just$1 (Anycast)
      t &= 31;  // depth:(## 5)
      unsigned long long rewrite;
      if (cs.advance(8) && cs.fetch_uint_to(t, rewrite)  // rewrite_pfx:(bits depth)
          && cs.fetch_int_to(8, workchain)               // workchain_id:int8
          && cs.fetch_uint_to(64, shard)) {              // address:bits256
        rewrite <<= 64 - t;
        return {workchain, (shard & (std::numeric_limits<td::uint64>::max() >> t)) | rewrite};
      }
      break;
    }
    case 6: {  // addr_var$11, anycast=nothing$0
      int len;
      if (cs.advance(3) && cs.fetch_uint_to(9, len)  // addr_len:(## 9)
          && len >= 64                               // { len >= 64 }
          && cs.fetch_int_to(32, workchain)          // workchain_id:int32
          && cs.fetch_uint_to(64, shard)) {          // address:(bits addr_len)
        return {workchain, shard};
      }
      break;
    }
    case 7: {   // addr_var$11, anycast=just$1 (Anycast)
      t &= 31;  // depth:(## 5)
      int len;
      unsigned long long rewrite;
      if (cs.advance(8) && cs.fetch_uint_to(t, rewrite)  // rewrite_pfx:(bits depth)
          && cs.fetch_uint_to(9, len)                    // addr_len:(## 9)
          && len >= 64                                   // { len >= 64 }
          && cs.fetch_int_to(32, workchain)              // workchain_id:int32
          && cs.fetch_uint_to(64, shard)) {              // address:bits256
        rewrite <<= 64 - t;
        return {workchain, (shard & (std::numeric_limits<td::uint64>::max() >> t)) | rewrite};
      }
      break;
    }
  }
  return {};
}

ton::ShardIdFull MsgAddressInt::get_shard(const vm::CellSlice& cs) const {
  vm::CellSlice cs2{cs};
  return get_shard(std::move(cs2));
}

ton::ShardIdFull MsgAddressInt::get_shard(Ref<vm::CellSlice> cs_ref) const {
  if (cs_ref->is_unique()) {
    return get_shard(std::move(cs_ref.unique_write()));
  } else {
    vm::CellSlice cs{*cs_ref};
    return get_shard(std::move(cs));
  }
}

bool MsgAddressInt::extract_std_address(Ref<vm::CellSlice> cs_ref, ton::WorkchainId& workchain,
                                        ton::StdSmcAddress& addr, bool rewrite) const {
  if (cs_ref.is_null()) {
    return false;
  } else if (cs_ref->is_unique()) {
    return extract_std_address(cs_ref.unique_write(), workchain, addr, rewrite);
  } else {
    vm::CellSlice cs{*cs_ref};
    return extract_std_address(cs, workchain, addr, rewrite);
  }
}

bool MsgAddressInt::extract_std_address(vm::CellSlice& cs, ton::WorkchainId& workchain, ton::StdSmcAddress& addr,
                                        bool do_rewrite) const {
  if (!cs.have(3 + 8 + 64)) {
    return {};
  }
  int t = (int)cs.prefetch_ulong(2 + 1 + 5);
  switch (t >> 5) {
    case 4: {  // addr_std$10, anycast=nothing$0
      return cs.advance(3) && cs.fetch_int_to(8, workchain) && cs.fetch_bits_to(addr);
    }
    case 5: {   // addr_std$10, anycast=just$1 (Anycast)
      t &= 31;  // depth:(## 5)
      unsigned long long rewrite;
      if (cs.advance(8) && cs.fetch_uint_to(t, rewrite)  // rewrite_pfx:(bits depth)
          && cs.fetch_int_to(8, workchain)               // workchain_id:int8
          && cs.fetch_bits_to(addr)) {                   // address:bits256
        if (do_rewrite) {
          addr.bits().store_uint(rewrite, t);
        }
        return true;
      }
      break;
    }
    case 6: {  // addr_var$11, anycast=nothing$0
      int len;
      return cs.advance(3) && cs.fetch_uint_to(9, len)  // addr_len:(## 9)
             && len == 256                              // only 256-bit addresses are standard
             && cs.fetch_int_to(32, workchain)          // workchain_id:int32
             && cs.fetch_bits_to(addr);                 // address:(bits addr_len)
    }
    case 7: {   // addr_var$11, anycast=just$1 (Anycast)
      t &= 31;  // depth:(## 5)
      int len;
      unsigned long long rewrite;
      if (cs.advance(8) && cs.fetch_uint_to(t, rewrite)  // rewrite_pfx:(bits depth)
          && cs.fetch_uint_to(9, len)                    // addr_len:(## 9)
          && len == 256                                  // only 256-bit addresses are standard
          && cs.fetch_int_to(32, workchain)              // workchain_id:int32
          && cs.fetch_bits_to(addr)) {                   // address:bits256
        if (do_rewrite) {
          addr.bits().store_uint(rewrite, t);
        }
        return true;
      }
      break;
    }
  }
  return false;
}

const MsgAddressInt t_MsgAddressInt;

bool MsgAddress::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case addr_none:
    case addr_ext:
      return t_MsgAddressExt.validate_skip(cs);
    case addr_std:
    case addr_var:
      return t_MsgAddressInt.validate_skip(cs);
  }
  return false;
}

const MsgAddress t_MsgAddress;

bool VarUInteger::skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return len >= 0 && len < n && cs.advance(len * 8);
}

bool VarUInteger::validate_skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return len >= 0 && len < n && (!len || cs.prefetch_ulong(8)) && cs.advance(len * 8);
}

td::RefInt256 VarUInteger::as_integer_skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return (len >= 0 && len < n && (!len || cs.prefetch_ulong(8))) ? cs.fetch_int256(len * 8, false) : td::RefInt256{};
}

unsigned long long VarUInteger::as_uint(const vm::CellSlice& cs) const {
  int len = (int)cs.prefetch_ulong(ln);
  return len >= 0 && len <= 8 && cs.have(ln + len * 8) ? td::bitstring::bits_load_ulong(cs.data_bits() + ln, len * 8)
                                                       : std::numeric_limits<td::uint64>::max();
}

bool VarUInteger::store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const {
  int k = value.bit_size(false);
  return k <= (n - 1) * 8 && cb.store_long_bool((k + 7) >> 3, ln) &&
         cb.store_bigint256_bool(value, (k + 7) & -8, false);
}

unsigned VarUInteger::precompute_integer_size(const td::BigInt256& value) const {
  int k = value.bit_size(false);
  return k <= (n - 1) * 8 ? ln + ((k + 7) & -8) : 0xfff;
}

unsigned VarUInteger::precompute_integer_size(td::RefInt256 value) const {
  if (value.is_null()) {
    return 0xfff;
  }
  int k = (*value)->bit_size(false);
  return k <= (n - 1) * 8 ? ln + ((k + 7) & -8) : 0xfff;
}

const VarUInteger t_VarUInteger_3{3}, t_VarUInteger_7{7}, t_VarUInteger_16{16}, t_VarUInteger_32{32};

bool VarUIntegerPos::skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return len > 0 && len < n && cs.advance(len * 8);
}

bool VarUIntegerPos::validate_skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return len > 0 && len < n && cs.prefetch_ulong(8) && cs.advance(len * 8);
}

td::RefInt256 VarUIntegerPos::as_integer_skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return (len > 0 && len < n && cs.prefetch_ulong(8)) ? cs.fetch_int256(len * 8, false) : td::RefInt256{};
}

unsigned long long VarUIntegerPos::as_uint(const vm::CellSlice& cs) const {
  int len = (int)cs.prefetch_ulong(ln);
  return len >= 0 && len <= 8 && cs.have(ln + len * 8) ? td::bitstring::bits_load_ulong(cs.data_bits() + ln, len * 8)
                                                       : std::numeric_limits<td::uint64>::max();
}

bool VarUIntegerPos::store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const {
  int k = value.bit_size(false);
  return k <= (n - 1) * 8 && value.sgn() > 0 && cb.store_long_bool((k + 7) >> 3, ln) &&
         cb.store_bigint256_bool(value, (k + 7) & -8, false);
}

const VarUIntegerPos t_VarUIntegerPos_16{16}, t_VarUIntegerPos_32{32};

static inline bool redundant_int(vm::CellSlice& cs) {
  int t = (int)cs.prefetch_long(9);
  return t == 0 || t == -1;
}

bool VarInteger::skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return len >= 0 && len < n && cs.advance(len * 8);
}

bool VarInteger::validate_skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return len >= 0 && len < n && (!len || !redundant_int(cs)) && cs.advance(len * 8);
}

td::RefInt256 VarInteger::as_integer_skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return (len >= 0 && len < n && (!len || !redundant_int(cs))) ? cs.fetch_int256(len * 8, true) : td::RefInt256{};
}

long long VarInteger::as_int(const vm::CellSlice& cs) const {
  int len = (int)cs.prefetch_ulong(ln);
  return len >= 0 && len <= 8 && cs.have(ln + len * 8) ? td::bitstring::bits_load_long(cs.data_bits() + ln, len * 8)
                                                       : (1ULL << 63);
}

bool VarInteger::store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const {
  int k = value.bit_size(true);
  return k <= (n - 1) * 8 && cb.store_long_bool((k + 7) >> 3, ln) && cb.store_bigint256_bool(value, (k + 7) & -8, true);
}

bool VarIntegerNz::skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return len > 0 && len < n && cs.advance(len * 8);
}

bool VarIntegerNz::validate_skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return len > 0 && len < n && !redundant_int(cs) && cs.advance(len * 8);
}

td::RefInt256 VarIntegerNz::as_integer_skip(vm::CellSlice& cs) const {
  int len = (int)cs.fetch_ulong(ln);
  return (len > 0 && len < n && !redundant_int(cs)) ? cs.fetch_int256(len * 8, true) : td::RefInt256{};
}

long long VarIntegerNz::as_int(const vm::CellSlice& cs) const {
  int len = (int)cs.prefetch_ulong(ln);
  return len >= 0 && len <= 8 && cs.have(ln + len * 8) ? td::bitstring::bits_load_long(cs.data_bits() + ln, len * 8)
                                                       : (1ULL << 63);
}

bool VarIntegerNz::store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const {
  int k = value.bit_size(true);
  return k <= (n - 1) * 8 && value.sgn() != 0 && cb.store_long_bool((k + 7) >> 3, ln) &&
         cb.store_bigint256_bool(value, (k + 7) & -8, true);
}

bool Grams::validate_skip(vm::CellSlice& cs) const {
  return t_VarUInteger_16.validate_skip(cs);
}

td::RefInt256 Grams::as_integer_skip(vm::CellSlice& cs) const {
  return t_VarUInteger_16.as_integer_skip(cs);
}

bool Grams::null_value(vm::CellBuilder& cb) const {
  return t_VarUInteger_16.null_value(cb);
}

bool Grams::store_integer_value(vm::CellBuilder& cb, const td::BigInt256& value) const {
  return t_VarUInteger_16.store_integer_value(cb, value);
}

unsigned Grams::precompute_size(const td::BigInt256& value) const {
  return t_VarUInteger_16.precompute_integer_size(value);
}

unsigned Grams::precompute_size(td::RefInt256 value) const {
  return t_VarUInteger_16.precompute_integer_size(std::move(value));
}

const Grams t_Grams;

const Unary t_Unary;

bool HmLabel::validate_skip(vm::CellSlice& cs, int& n) const {
  switch (get_tag(cs)) {
    case hml_short:
      return cs.advance(1) && (n = cs.count_leading(1)) <= m && cs.advance(2 * n + 1);
    case hml_long:
      return cs.advance(2) && cs.fetch_uint_leq(m, n) && cs.advance(n);
    case hml_same:
      return cs.advance(3) && cs.fetch_uint_leq(m, n);
  }
  return false;
}

int HmLabel::get_tag(const vm::CellSlice& cs) const {
  int tag = (int)cs.prefetch_ulong(2);
  return tag != 1 ? tag : hml_short;
}

int HashmapNode::get_size(const vm::CellSlice& cs) const {
  assert(n >= 0);
  return n ? 0x20000 : value_type.get_size(cs);
}

bool HashmapNode::skip(vm::CellSlice& cs) const {
  assert(n >= 0);
  return n ? cs.advance_refs(2) : value_type.skip(cs);
}

bool HashmapNode::validate_skip(vm::CellSlice& cs) const {
  assert(n >= 0);
  if (!n) {
    // hmn_leaf
    return value_type.validate_skip(cs);
  } else {
    // hmn_fork
    Hashmap branch_type{n - 1, value_type};
    return branch_type.validate_ref(cs.fetch_ref()) && branch_type.validate_ref(cs.fetch_ref());
  }
}

bool Hashmap::skip(vm::CellSlice& cs) const {
  int l;
  return HmLabel{n}.skip(cs, l) && HashmapNode{n - l, value_type}.skip(cs);
}

bool Hashmap::validate_skip(vm::CellSlice& cs) const {
  int l;
  return HmLabel{n}.skip(cs, l) && HashmapNode{n - l, value_type}.skip(cs);
}

int HashmapE::get_size(const vm::CellSlice& cs) const {
  int tag = get_tag(cs);
  return (tag >= 0 ? (tag > 0 ? 0x10001 : 1) : -1);
}

bool HashmapE::validate(const vm::CellSlice& cs) const {
  int tag = get_tag(cs);
  return tag <= 0 ? !tag : root_type.validate_ref(cs.prefetch_ref());
}

bool HashmapE::add_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const {
  try {
    int n = root_type.n;
    vm::Dictionary dict1{cs1, n, true, true}, dict2{cs2, n, true, true};
    const TLB& vt = root_type.value_type;
    vm::Dictionary::simple_combine_func_t combine = [vt](vm::CellBuilder& cb, Ref<vm::CellSlice> cs1_ref,
                                                         Ref<vm::CellSlice> cs2_ref) -> bool {
      if (!vt.add_values(cb, cs1_ref.write(), cs2_ref.write())) {
        throw CombineError{};
      }
      return true;
    };
    dict1.combine_with(dict2, combine);
    dict2.reset();
    return std::move(dict1).append_dict_to_bool(cb);
  } catch (CombineError&) {
    return false;
  }
}

bool HashmapE::add_values_ref(Ref<vm::Cell>& res, Ref<vm::Cell> arg1, Ref<vm::Cell> arg2) const {
  try {
    int n = root_type.n;
    vm::Dictionary dict1{std::move(arg1), n, true}, dict2{std::move(arg2), n, true};
    const TLB& vt = root_type.value_type;
    vm::Dictionary::simple_combine_func_t combine = [vt](vm::CellBuilder& cb, Ref<vm::CellSlice> cs1_ref,
                                                         Ref<vm::CellSlice> cs2_ref) -> bool {
      if (!vt.add_values(cb, cs1_ref.write(), cs2_ref.write())) {
        throw CombineError{};
      }
      return true;
    };
    dict1.combine_with(dict2, combine);
    dict2.reset();
    res = std::move(dict1).extract_root_cell();
    return true;
  } catch (CombineError&) {
    res = Ref<vm::Cell>{};
    return false;
  }
}

int HashmapE::sub_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const {
  try {
    int n = root_type.n;
    vm::Dictionary dict1{cs1, n, true, true}, dict2{cs2, n, true, true};
    const TLB& vt = root_type.value_type;
    vm::Dictionary::simple_combine_func_t combine = [vt](vm::CellBuilder& cb, Ref<vm::CellSlice> cs1_ref,
                                                         Ref<vm::CellSlice> cs2_ref) -> bool {
      int r = vt.sub_values(cb, cs1_ref.write(), cs2_ref.write());
      if (r < 0) {
        throw CombineError{};
      }
      return r;
    };
    dict1.combine_with(dict2, combine, 1);
    dict2.reset();
    bool not_empty = !dict1.is_empty();
    return std::move(dict1).append_dict_to_bool(cb) ? not_empty : -1;
  } catch (CombineError&) {
    return -1;
  }
}

int HashmapE::sub_values_ref(Ref<vm::Cell>& res, Ref<vm::Cell> arg1, Ref<vm::Cell> arg2) const {
  try {
    int n = root_type.n;
    vm::Dictionary dict1{std::move(arg1), n, true}, dict2{std::move(arg2), n, true};
    const TLB& vt = root_type.value_type;
    vm::Dictionary::simple_combine_func_t combine = [vt](vm::CellBuilder& cb, Ref<vm::CellSlice> cs1_ref,
                                                         Ref<vm::CellSlice> cs2_ref) -> bool {
      int r = vt.sub_values(cb, cs1_ref.write(), cs2_ref.write());
      if (r < 0) {
        throw CombineError{};
      }
      return r;
    };
    dict1.combine_with(dict2, combine, 1);
    dict2.reset();
    res = std::move(dict1).extract_root_cell();
    return res.not_null();
  } catch (CombineError&) {
    res = Ref<vm::Cell>{};
    return -1;
  }
}

bool HashmapE::store_ref(vm::CellBuilder& cb, Ref<vm::Cell> arg) const {
  if (arg.is_null()) {
    return cb.store_long_bool(0, 1);
  } else {
    return cb.store_long_bool(1, 1) && cb.store_ref_bool(std::move(arg));
  }
}

const ExtraCurrencyCollection t_ExtraCurrencyCollection;

bool CurrencyCollection::validate_skip(vm::CellSlice& cs) const {
  return t_Grams.validate_skip(cs) && t_ExtraCurrencyCollection.validate_skip(cs);
}

bool CurrencyCollection::skip(vm::CellSlice& cs) const {
  return t_Grams.skip(cs) && t_ExtraCurrencyCollection.skip(cs);
}

td::RefInt256 CurrencyCollection::as_integer_skip(vm::CellSlice& cs) const {
  auto res = t_Grams.as_integer_skip(cs);
  if (res.not_null() && t_ExtraCurrencyCollection.skip(cs)) {
    return res;
  } else {
    return {};
  }
}

bool CurrencyCollection::add_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const {
  return t_Grams.add_values(cb, cs1, cs2) && t_ExtraCurrencyCollection.add_values(cb, cs1, cs2);
}

bool CurrencyCollection::unpack_special(vm::CellSlice& cs, td::RefInt256& balance, Ref<vm::Cell>& extra) const {
  balance = t_Grams.as_integer_skip(cs);
  if (cs.fetch_ulong(1) == 1) {
    return balance.not_null() && cs.fetch_ref_to(extra) && cs.empty_ext();
  } else {
    extra.clear();
    return balance.not_null() && cs.empty_ext();
  }
}

bool CurrencyCollection::pack_special(vm::CellBuilder& cb, td::RefInt256 balance, Ref<vm::Cell> extra) const {
  return t_Grams.store_integer_ref(cb, std::move(balance)) && t_ExtraCurrencyCollection.store_ref(cb, std::move(extra));
}

const CurrencyCollection t_CurrencyCollection;

bool CommonMsgInfo::validate_skip(vm::CellSlice& cs) const {
  int tag = get_tag(cs);
  switch (tag) {
    case int_msg_info:
      return cs.advance(4)                              // int_msg_info$0 ihr_disabled:Bool bounce:Bool bounced:Bool
             && t_MsgAddressInt.validate_skip(cs)       // src
             && t_MsgAddressInt.validate_skip(cs)       // dest
             && t_CurrencyCollection.validate_skip(cs)  // value
             && t_Grams.validate_skip(cs)               // ihr_fee
             && t_Grams.validate_skip(cs)               // fwd_fee
             && cs.advance(64 + 32);                    // created_lt:uint64 created_at:uint32
    case ext_in_msg_info:
      return cs.advance(2) && t_MsgAddressExt.validate_skip(cs)  // src
             && t_MsgAddressInt.validate_skip(cs)                // dest
             && t_Grams.validate_skip(cs);                       // import_fee
    case ext_out_msg_info:
      return cs.advance(2) && t_MsgAddressInt.validate_skip(cs)  // src
             && t_MsgAddressExt.validate_skip(cs)                // dest
             && cs.advance(64 + 32);                             // created_lt:uint64 created_at:uint32
  }
  return false;
}

bool CommonMsgInfo::unpack(vm::CellSlice& cs, CommonMsgInfo::Record_int_msg_info& data) const {
  return get_tag(cs) == int_msg_info && cs.advance(1) && cs.fetch_bool_to(data.ihr_disabled) &&
         cs.fetch_bool_to(data.bounce) && cs.fetch_bool_to(data.bounced) && t_MsgAddressInt.fetch_to(cs, data.src) &&
         t_MsgAddressInt.fetch_to(cs, data.dest) && t_CurrencyCollection.fetch_to(cs, data.value) &&
         t_Grams.fetch_to(cs, data.ihr_fee) && t_Grams.fetch_to(cs, data.fwd_fee) &&
         cs.fetch_uint_to(64, data.created_lt) && cs.fetch_uint_to(32, data.created_at);
}

bool CommonMsgInfo::skip(vm::CellSlice& cs) const {
  int tag = get_tag(cs);
  switch (tag) {
    case int_msg_info:
      return cs.advance(4)                     // int_msg_info$0 ihr_disabled:Bool bounce:Bool bounced:Bool
             && t_MsgAddressInt.skip(cs)       // src
             && t_MsgAddressInt.skip(cs)       // dest
             && t_CurrencyCollection.skip(cs)  // value
             && t_Grams.skip(cs)               // ihr_fee
             && t_Grams.skip(cs)               // fwd_fee
             && cs.advance(64 + 32);           // created_lt:uint64 created_at:uint32
    case ext_in_msg_info:
      return cs.advance(2) && t_MsgAddressExt.skip(cs)  // src
             && t_MsgAddressInt.skip(cs)                // dest
             && t_Grams.skip(cs);                       // import_fee
    case ext_out_msg_info:
      return cs.advance(2) && t_MsgAddressInt.skip(cs)  // src
             && t_MsgAddressExt.skip(cs)                // dest
             && cs.advance(64 + 32);                    // created_lt:uint64 created_at:uint32
  }
  return false;
}

bool CommonMsgInfo::get_created_lt(vm::CellSlice& cs, unsigned long long& created_lt) const {
  switch (get_tag(cs)) {
    case int_msg_info:
      return cs.advance(4)                           // int_msg_info$0 ihr_disabled:Bool bounce:Bool bounced:Bool
             && t_MsgAddressInt.skip(cs)             // src
             && t_MsgAddressInt.skip(cs)             // dest
             && t_CurrencyCollection.skip(cs)        // value
             && t_Grams.skip(cs)                     // ihr_fee
             && t_Grams.skip(cs)                     // fwd_fee
             && cs.fetch_ulong_bool(64, created_lt)  // created_lt:uint64
             && cs.advance(32);                      // created_at:uint32
    case ext_in_msg_info:
      return false;
    case ext_out_msg_info:
      return cs.advance(2) && t_MsgAddressInt.skip(cs)  // src
             && t_MsgAddressExt.skip(cs)                // dest
             && cs.fetch_ulong_bool(64, created_lt)     // created_lt:uint64
             && cs.advance(32);                         // created_at:uint32
  }
  return false;
}

const CommonMsgInfo t_CommonMsgInfo;
const TickTock t_TickTock;
const RefAnything t_RefCell;

bool StateInit::validate_skip(vm::CellSlice& cs) const {
  return Maybe<UInt>{5}.validate_skip(cs)            // split_depth:(Maybe (## 5))
         && Maybe<TickTock>{}.validate_skip(cs)      // special:(Maybe TickTock)
         && Maybe<RefAnything>{}.validate_skip(cs)   // code:(Maybe ^Cell)
         && Maybe<RefAnything>{}.validate_skip(cs)   // data:(Maybe ^Cell)
         && Maybe<RefAnything>{}.validate_skip(cs);  // library:(Maybe ^Cell)
}

bool StateInit::get_ticktock(vm::CellSlice& cs, int& ticktock) const {
  bool have_tt;
  ticktock = 0;
  return Maybe<UInt>{5}.validate_skip(cs) && cs.fetch_bool_to(have_tt) && (!have_tt || cs.fetch_uint_to(2, ticktock));
}

const StateInit t_StateInit;

bool Message::validate_skip(vm::CellSlice& cs) const {
  static const Maybe<Either<StateInit, RefTo<StateInit>>> init_type;
  static const Either<Anything, RefAnything> body_type;
  return t_CommonMsgInfo.validate_skip(cs)  // info:CommonMsgInfo
         && init_type.validate_skip(cs)     // init:(Maybe (Either StateInit ^StateInit))
         && body_type.validate_skip(cs);    // body:(Either X ^X)
}

bool Message::extract_info(vm::CellSlice& cs) const {
  return t_CommonMsgInfo.extract(cs);
}

bool Message::get_created_lt(vm::CellSlice& cs, unsigned long long& created_lt) const {
  return t_CommonMsgInfo.get_created_lt(cs, created_lt);
}

bool Message::is_internal(Ref<vm::Cell> ref) const {
  return is_internal(load_cell_slice(std::move(ref)));
}

const Message t_Message;
const RefTo<Message> t_Ref_Message;

bool IntermediateAddress::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case interm_addr_regular:
      return cs.advance(1) && cs.fetch_ulong(7) <= 96U;
    case interm_addr_simple:
      return cs.advance(2 + 8 + 64);
    case interm_addr_ext:
      if (cs.have(2 + 32 + 64)) {
        cs.advance(2);
        int workchain_id = (int)cs.fetch_long(32);
        return (workchain_id < -128 || workchain_id >= 128) && cs.advance(64);
      }
      // no break
  }
  return false;
}

bool IntermediateAddress::skip(vm::CellSlice& cs) const {
  return cs.advance(get_size(cs));
}

int IntermediateAddress::get_size(const vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case interm_addr_regular:
      return 1 + 7;
    case interm_addr_simple:
      return 2 + 8 + 64;
    case interm_addr_ext:
      return 2 + 32 + 64;
  }
  return -1;
}

const IntermediateAddress t_IntermediateAddress;

bool MsgEnvelope::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 4                      // msg_envelope#4
         && t_IntermediateAddress.validate_skip(cs)  // cur_addr:IntermediateAddress
         && t_IntermediateAddress.validate_skip(cs)  // next_addr:IntermediateAddress
         && t_Grams.validate_skip(cs)                // fwd_fee_remaining:Grams
         && t_Ref_Message.validate_skip(cs);         // msg:^Message
}

bool MsgEnvelope::skip(vm::CellSlice& cs) const {
  return cs.advance(4)                      // msg_envelope#4
         && t_IntermediateAddress.skip(cs)  // cur_addr:IntermediateAddress
         && t_IntermediateAddress.skip(cs)  // next_addr:IntermediateAddress
         && t_Grams.skip(cs)                // fwd_fee_remaining:Grams
         && t_Ref_Message.skip(cs);         // msg:^Message
}

bool MsgEnvelope::extract_fwd_fees_remaining(vm::CellSlice& cs) const {
  return t_IntermediateAddress.skip(cs) && t_IntermediateAddress.skip(cs) && t_Grams.extract(cs);
}

bool MsgEnvelope::unpack(vm::CellSlice& cs, MsgEnvelope::Record& data) const {
  return cs.fetch_ulong(4) == 4                                 // msg_envelope#4
         && t_IntermediateAddress.fetch_to(cs, data.cur_addr)   // cur_addr:IntermediateAddress
         && t_IntermediateAddress.fetch_to(cs, data.next_addr)  // next_addr:IntermediateAddress
         && t_Grams.fetch_to(cs, data.fwd_fee_remaining)        // fwd_fee_remaining:Grams
         && cs.fetch_ref_to(data.msg);                          // msg:^Message
}

bool MsgEnvelope::unpack(vm::CellSlice& cs, MsgEnvelope::Record_std& data) const {
  return cs.fetch_ulong(4) == 4                                      // msg_envelope#4
         && t_IntermediateAddress.fetch_regular(cs, data.cur_addr)   // cur_addr:IntermediateAddress
         && t_IntermediateAddress.fetch_regular(cs, data.next_addr)  // next_addr:IntermediateAddress
         && t_Grams.as_integer_skip_to(cs, data.fwd_fee_remaining)   // fwd_fee_remaining:Grams
         && cs.fetch_ref_to(data.msg);                               // msg:^Message
}

bool MsgEnvelope::unpack_std(vm::CellSlice& cs, int& cur_a, int& nhop_a, Ref<vm::Cell>& msg) const {
  return cs.fetch_ulong(4) == 4                              // msg_envelope#4
         && t_IntermediateAddress.fetch_regular(cs, cur_a)   // cur_addr:IntermediateAddress
         && t_IntermediateAddress.fetch_regular(cs, nhop_a)  // next_addr:IntermediateAddress
         && cs.fetch_ref_to(msg);
}

bool MsgEnvelope::get_created_lt(const vm::CellSlice& cs, unsigned long long& created_lt) const {
  if (!cs.size_refs()) {
    return false;
  }
  auto msg_cs = load_cell_slice(cs.prefetch_ref());
  return t_Message.get_created_lt(msg_cs, created_lt);
}

const MsgEnvelope t_MsgEnvelope;
const RefTo<MsgEnvelope> t_Ref_MsgEnvelope;

bool StorageUsed::validate_skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.validate_skip(cs)      // cells:(VarUInteger 7)
         && t_VarUInteger_7.validate_skip(cs)   // bits:(VarUInteger 7)
         && t_VarUInteger_7.validate_skip(cs);  // public_cells:(VarUInteger 7)
}

bool StorageUsed::skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.skip(cs)      // cells:(VarUInteger 7)
         && t_VarUInteger_7.skip(cs)   // bits:(VarUInteger 7)
         && t_VarUInteger_7.skip(cs);  // public_cells:(VarUInteger 7)
}

const StorageUsed t_StorageUsed;

bool StorageUsedShort::validate_skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.validate_skip(cs)      // cells:(VarUInteger 7)
         && t_VarUInteger_7.validate_skip(cs);  // bits:(VarUInteger 7)
}

bool StorageUsedShort::skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.skip(cs)      // cells:(VarUInteger 7)
         && t_VarUInteger_7.skip(cs);  // bits:(VarUInteger 7)
}

const StorageUsedShort t_StorageUsedShort;

const Maybe<Grams> t_Maybe_Grams;

bool StorageInfo::skip(vm::CellSlice& cs) const {
  return t_StorageUsed.skip(cs)      // used:StorageUsed
         && cs.advance(32)           // last_paid:uint32
         && t_Maybe_Grams.skip(cs);  // due_payment:(Maybe Grams)
}

bool StorageInfo::validate_skip(vm::CellSlice& cs) const {
  return t_StorageUsed.validate_skip(cs)      // used:StorageUsed
         && cs.advance(32)                    // last_paid:uint32
         && t_Maybe_Grams.validate_skip(cs);  // due_payment:(Maybe Grams)
}

const StorageInfo t_StorageInfo;

bool AccountState::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case account_uninit:
      return cs.advance(2);
    case account_frozen:
      return cs.advance(2 + 256);
    case account_active:
      return cs.advance(1) && t_StateInit.validate_skip(cs);
  }
  return false;
}

bool AccountState::get_ticktock(vm::CellSlice& cs, int& ticktock) const {
  if (get_tag(cs) != account_active) {
    ticktock = 0;
    return true;
  }
  return cs.advance(1) && t_StateInit.get_ticktock(cs, ticktock);
}

const AccountState t_AccountState;

bool AccountStorage::skip(vm::CellSlice& cs) const {
  return cs.advance(64) && t_CurrencyCollection.skip(cs) && t_AccountState.skip(cs);
}

bool AccountStorage::skip_copy_balance(vm::CellBuilder& cb, vm::CellSlice& cs) const {
  return cs.advance(64) && t_CurrencyCollection.skip_copy(cb, cs) && t_AccountState.skip(cs);
}

bool AccountStorage::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(64) && t_CurrencyCollection.validate_skip(cs) && t_AccountState.validate_skip(cs);
}

const AccountStorage t_AccountStorage;

bool Account::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case account_none:
      return cs.advance(1);
    case account:
      return cs.advance(1)                  // account$1
             && t_MsgAddressInt.skip(cs)    // addr:MsgAddressInt
             && t_StorageInfo.skip(cs)      // storage_stat:StorageInfo
             && t_AccountStorage.skip(cs);  // storage:AccountStorage
  }
  return false;
}

bool Account::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case account_none:
      return allow_empty && cs.advance(1);
    case account:
      return cs.advance(1)                           // account$1
             && t_MsgAddressInt.validate_skip(cs)    // addr:MsgAddressInt
             && t_StorageInfo.validate_skip(cs)      // storage_stat:StorageInfo
             && t_AccountStorage.validate_skip(cs);  // storage:AccountStorage
  }
  return false;
}

bool Account::skip_copy_balance(vm::CellBuilder& cb, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case account_none:
      return allow_empty && cs.advance(1) && t_CurrencyCollection.null_value(cb);
    case account:
      return cs.advance(1)                                   // account$1
             && t_MsgAddressInt.skip(cs)                     // addr:MsgAddressInt
             && t_StorageInfo.skip(cs)                       // storage_stat:StorageInfo
             && t_AccountStorage.skip_copy_balance(cb, cs);  // storage:AccountStorage
  }
  return false;
}

const Account t_Account, t_AccountE{true};
const RefTo<Account> t_Ref_Account;
const ShardAccount t_ShardAccount;

const AccountStatus t_AccountStatus;

bool HashmapAugNode::skip(vm::CellSlice& cs) const {
  if (n < 0) {
    return false;
  } else if (!n) {
    // ahmn_leaf
    return aug.extra_type.skip(cs) && aug.value_type.skip(cs);
  } else {
    // ahmn_fork
    return cs.advance_refs(2) && aug.extra_type.skip(cs);
  }
}

bool HashmapAugNode::validate_skip(vm::CellSlice& cs) const {
  if (n < 0) {
    return false;
  }
  if (!n) {
    // ahmn_leaf
    vm::CellSlice cs_extra{cs};
    if (!aug.extra_type.validate_skip(cs)) {
      return false;
    }
    cs_extra.cut_tail(cs);
    vm::CellSlice cs_value{cs};
    if (!aug.value_type.validate_skip(cs)) {
      return false;
    }
    cs_value.cut_tail(cs);
    return aug.check_leaf(cs_extra, cs_value);
  }
  // ahmn_fork
  if (!cs.have_refs(2)) {
    return false;
  }
  HashmapAug branch_type{n - 1, aug};
  if (!branch_type.validate_ref(cs.prefetch_ref(0)) || !branch_type.validate_ref(cs.prefetch_ref(1))) {
    return false;
  }
  auto cs_left = load_cell_slice(cs.fetch_ref());
  auto cs_right = load_cell_slice(cs.fetch_ref());
  vm::CellSlice cs_extra{cs};
  if (!aug.extra_type.validate_skip(cs)) {
    return false;
  }
  cs_extra.cut_tail(cs);
  return branch_type.extract_extra(cs_left) && branch_type.extract_extra(cs_right) &&
         aug.check_fork(cs_extra, cs_left, cs_right);
}

bool HashmapAug::skip(vm::CellSlice& cs) const {
  int l;
  return HmLabel{n}.skip(cs, l) && HashmapAugNode{n - l, aug}.skip(cs);
}

bool HashmapAug::validate_skip(vm::CellSlice& cs) const {
  int l;
  return HmLabel{n}.validate_skip(cs, l) && HashmapAugNode{n - l, aug}.validate_skip(cs);
}

bool HashmapAug::extract_extra(vm::CellSlice& cs) const {
  int l;
  return HmLabel{n}.skip(cs, l) && (l == n || cs.advance_refs(2)) && aug.extra_type.extract(cs);
}

bool HashmapAugE::validate_skip(vm::CellSlice& cs) const {
  Ref<vm::CellSlice> extra;
  switch (get_tag(cs)) {
    case ahme_empty:
      return cs.advance(1) && (extra = root_type.aug.extra_type.validate_fetch(cs)).not_null() &&
             root_type.aug.check_empty(extra.unique_write());
    case ahme_root:
      if (cs.advance(1) && root_type.validate_ref(cs.prefetch_ref())) {
        auto cs_root = load_cell_slice(cs.fetch_ref());
        return (extra = root_type.aug.extra_type.validate_fetch(cs)).not_null() && root_type.extract_extra(cs_root) &&
               extra->contents_equal(cs_root);
      }
      break;
  }
  return false;
}

bool HashmapAugE::skip(vm::CellSlice& cs) const {
  int tag = (int)cs.fetch_ulong(1);
  return tag >= 0 && cs.advance_refs(tag) && root_type.aug.extra_type.skip(cs);
}

bool HashmapAugE::extract_extra(vm::CellSlice& cs) const {
  int tag = (int)cs.fetch_ulong(1);
  return tag >= 0 && cs.advance_refs(tag) && root_type.aug.extra_type.extract(cs);
}

bool Aug_ShardAccounts::eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const {
  if (cs.have_refs()) {
    auto cs2 = load_cell_slice(cs.prefetch_ref());
    return t_Account.skip_copy_balance(cb, cs2);
  } else {
    return false;
  }
}

const Aug_ShardAccounts aug_ShardAccounts;

const ShardAccounts t_ShardAccounts;

const AccStatusChange t_AccStatusChange;

bool TrStoragePhase::skip(vm::CellSlice& cs) const {
  return t_Grams.skip(cs)                // storage_fees_collected:Grams
         && t_Maybe_Grams.skip(cs)       // storage_fees_due:Grams
         && t_AccStatusChange.skip(cs);  // status_change:AccStatusChange
}

bool TrStoragePhase::validate_skip(vm::CellSlice& cs) const {
  return t_Grams.validate_skip(cs)                // storage_fees_collected:Grams
         && t_Maybe_Grams.validate_skip(cs)       // storage_fees_due:Grams
         && t_AccStatusChange.validate_skip(cs);  // status_change:AccStatusChange
}

const TrStoragePhase t_TrStoragePhase;

bool TrCreditPhase::skip(vm::CellSlice& cs) const {
  return t_Maybe_Grams.skip(cs)             // due_fees_collected:(Maybe Grams)
         && t_CurrencyCollection.skip(cs);  // credit:CurrencyCollection
}

bool TrCreditPhase::validate_skip(vm::CellSlice& cs) const {
  return t_Maybe_Grams.validate_skip(cs)             // due_fees_collected:(Maybe Grams)
         && t_CurrencyCollection.validate_skip(cs);  // credit:CurrencyCollection
}

const TrCreditPhase t_TrCreditPhase;

bool TrComputeInternal1::skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.skip(cs)           // gas_used:(VarUInteger 7)
         && t_VarUInteger_7.skip(cs)        // gas_limit:(VarUInteger 7)
         && Maybe<VarUInteger>{3}.skip(cs)  // gas_credit:(Maybe (VarUInteger 3))
         && cs.advance(8 + 32)              // mode:int8 exit_code:int32
         && Maybe<Int>{32}.skip(cs)         // exit_arg:(Maybe int32)
         && cs.advance(32 + 256 + 256);     // vm_steps:uint32
                                            // vm_init_state_hash:uint256
                                            // vm_final_state_hash:uint256
}

bool TrComputeInternal1::validate_skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.validate_skip(cs)           // gas_used:(VarUInteger 7)
         && t_VarUInteger_7.validate_skip(cs)        // gas_limit:(VarUInteger 7)
         && Maybe<VarUInteger>{3}.validate_skip(cs)  // gas_credit:(Maybe (VarUInteger 3))
         && cs.advance(8 + 32)                       // mode:int8 exit_code:int32
         && Maybe<Int>{32}.validate_skip(cs)         // exit_arg:(Maybe int32)
         && cs.advance(32 + 256 + 256);              // vm_steps:uint32
                                                     // vm_init_state_hash:uint256
                                                     // vm_final_state_hash:uint256
}

const TrComputeInternal1 t_TrComputeInternal1;
const RefTo<TrComputeInternal1> t_Ref_TrComputeInternal1;
const ComputeSkipReason t_ComputeSkipReason;

bool TrComputePhase::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case tr_phase_compute_skipped:
      return cs.advance(1) && t_ComputeSkipReason.skip(cs);
    case tr_phase_compute_vm:
      return cs.advance(1 + 3)    // tr_phase_compute_vm$1 success:Bool msg_state_used:Bool account_activated:Bool
             && t_Grams.skip(cs)  // gas_fees:Grams
             && t_Ref_TrComputeInternal1.skip(cs);  // ^[ gas_used:(..) .. ]
  }
  return false;
}

bool TrComputePhase::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case tr_phase_compute_skipped:
      return cs.advance(1) && t_ComputeSkipReason.validate_skip(cs);
    case tr_phase_compute_vm:
      return cs.advance(1 + 3)  // tr_phase_compute_vm$1 success:Bool msg_state_used:Bool account_activated:Bool
             && t_Grams.validate_skip(cs)                    // gas_fees:Grams
             && t_Ref_TrComputeInternal1.validate_skip(cs);  // ^[ gas_used:(..) .. ]
  }
  return false;
}

const TrComputePhase t_TrComputePhase;

bool TrActionPhase::skip(vm::CellSlice& cs) const {
  return cs.advance(3)                    // success:Bool valid:Bool no_funds:Bool
         && t_AccStatusChange.skip(cs)    // status_change:AccStatusChange
         && t_Maybe_Grams.skip(cs)        // total_fwd_fees:(Maybe Grams)
         && t_Maybe_Grams.skip(cs)        // total_action_fees:(Maybe Grams)
         && cs.advance(32)                // result_code:int32
         && Maybe<Int>{32}.skip(cs)       // result_arg:(Maybe int32)
         && cs.advance(16 * 4 + 256)      // tot_actions:uint16 spec_actions:uint16
                                          // skipped_actions:uint16 msgs_created:uint16
                                          // action_list_hash:uint256
         && t_StorageUsedShort.skip(cs);  // tot_msg_size:StorageUsedShort
}

bool TrActionPhase::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(3)                             // success:Bool valid:Bool no_funds:Bool
         && t_AccStatusChange.validate_skip(cs)    // status_change:AccStatusChange
         && t_Maybe_Grams.validate_skip(cs)        // total_fwd_fees:(Maybe Grams)
         && t_Maybe_Grams.validate_skip(cs)        // total_action_fees:(Maybe Grams)
         && cs.advance(32)                         // result_code:int32
         && Maybe<Int>{32}.validate_skip(cs)       // result_arg:(Maybe int32)
         && cs.advance(16 * 4 + 256)               // tot_actions:uint16 spec_actions:uint16
                                                   // skipped_actions:uint16 msgs_created:uint16
                                                   // action_list_hash:uint256
         && t_StorageUsedShort.validate_skip(cs);  // tot_msg_size:StorageUsed
}

const TrActionPhase t_TrActionPhase;

bool TrBouncePhase::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case tr_phase_bounce_negfunds:
      return cs.advance(2);  // tr_phase_bounce_negfunds$00
    case tr_phase_bounce_nofunds:
      return cs.advance(2)                   // tr_phase_bounce_nofunds$01
             && t_StorageUsedShort.skip(cs)  // msg_size:StorageUsedShort
             && t_Grams.skip(cs);            // req_fwd_fees:Grams
    case tr_phase_bounce_ok:
      return cs.advance(1)                   // tr_phase_bounce_ok$1
             && t_StorageUsedShort.skip(cs)  // msg_size:StorageUsedShort
             && t_Grams.skip(cs)             // msg_fees:Grams
             && t_Grams.skip(cs);            // fwd_fees:Grams
  }
  return false;
}

bool TrBouncePhase::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case tr_phase_bounce_negfunds:
      return cs.advance(2);  // tr_phase_bounce_negfunds$00
    case tr_phase_bounce_nofunds:
      return cs.advance(2)                            // tr_phase_bounce_nofunds$01
             && t_StorageUsedShort.validate_skip(cs)  // msg_size:StorageUsedShort
             && t_Grams.validate_skip(cs);            // req_fwd_fees:Grams
    case tr_phase_bounce_ok:
      return cs.advance(1)                            // tr_phase_bounce_ok$1
             && t_StorageUsedShort.validate_skip(cs)  // msg_size:StorageUsedShort
             && t_Grams.validate_skip(cs)             // msg_fees:Grams
             && t_Grams.validate_skip(cs);            // fwd_fees:Grams
  }
  return false;
}

int TrBouncePhase::get_tag(const vm::CellSlice& cs) const {
  if (cs.size() == 1) {
    return (int)cs.prefetch_ulong(1) == 1 ? tr_phase_bounce_ok : -1;
  }
  int v = (int)cs.prefetch_ulong(2);
  return v == 3 ? tr_phase_bounce_ok : v;
};

const TrBouncePhase t_TrBouncePhase;

bool SplitMergeInfo::skip(vm::CellSlice& cs) const {
  // cur_shard_pfx_len:(## 6) acc_split_depth:(##6) this_addr:uint256 sibling_addr:uint256
  return cs.advance(6 + 6 + 256 + 256);
}

bool SplitMergeInfo::validate_skip(vm::CellSlice& cs) const {
  if (!cs.have(6 + 6 + 256 + 256)) {
    return false;
  }
  int cur_pfx_len = (int)cs.fetch_ulong(6);
  int split_depth = (int)cs.fetch_ulong(6);
  unsigned char this_addr[32], sibling_addr[32];
  if (!cs.fetch_bytes(this_addr, 32) || !cs.fetch_bytes(sibling_addr, 32)) {
    return false;
  }
  // cur_pfx_len < split_depth, addresses match except in bit cur_pfx_len
  if (cur_pfx_len >= split_depth) {
    return false;
  }
  sibling_addr[cur_pfx_len >> 3] ^= (unsigned char)(0x80 >> (cur_pfx_len & 7));
  return !memcmp(this_addr, sibling_addr, 32);
}

const SplitMergeInfo t_SplitMergeInfo;

bool TransactionDescr::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case trans_ord:
      return cs.advance(4 + 1)                          // trans_ord$0000 storage_first:Bool
             && Maybe<TrStoragePhase>{}.skip(cs)        // storage_ph:(Maybe TrStoragePhase)
             && Maybe<TrCreditPhase>{}.skip(cs)         // credit_ph:(Maybe TrCreditPhase)
             && t_TrComputePhase.skip(cs)               // compute_ph:TrComputePhase
             && Maybe<RefTo<TrActionPhase>>{}.skip(cs)  // action:(Maybe ^TrActionPhase)
             && cs.advance(1)                           // aborted:Bool
             && Maybe<TrBouncePhase>{}.skip(cs)         // bounce:(Maybe TrBouncePhase)
             && cs.advance(1);                          // destroyed:Bool
    case trans_storage:
      return cs.advance(4)                  // trans_storage$0001
             && t_TrStoragePhase.skip(cs);  // storage_ph:TrStoragePhase
    case trans_tick_tock:
      return cs.advance(4)                              // trans_tick_tock$001 is_tock:Bool
             && t_TrStoragePhase.skip(cs)               // storage:TrStoragePhase
             && t_TrComputePhase.skip(cs)               // compute_ph:TrComputePhase
             && Maybe<RefTo<TrActionPhase>>{}.skip(cs)  // action:(Maybe ^TrActionPhase)
             && cs.advance(2);                          // aborted:Bool destroyed:Bool
    case trans_split_prepare:
      return cs.advance(4)                              // trans_split_prepare$0100
             && t_SplitMergeInfo.skip(cs)               // split_info:SplitMergeInfo
             && t_TrComputePhase.skip(cs)               // compute_ph:TrComputePhase
             && Maybe<RefTo<TrActionPhase>>{}.skip(cs)  // action:(Maybe ^TrActionPhase)
             && cs.advance(2);                          // aborted:Bool destroyed:Bool
    case trans_split_install:
      return cs.advance(4)                  // trans_split_install$0101
             && t_SplitMergeInfo.skip(cs)   // split_info:SplitMergeInfo
             && t_Ref_Transaction.skip(cs)  // prepare_transaction:^Transaction
             && cs.advance(1);              // installed:Bool
    case trans_merge_prepare:
      return cs.advance(4)                 // trans_merge_prepare$0110
             && t_SplitMergeInfo.skip(cs)  // split_info:SplitMergeInfo
             && t_TrStoragePhase.skip(cs)  // storage_ph:TrStoragePhase
             && cs.advance(1);             // aborted:Bool
    case trans_merge_install:
      return cs.advance(4)                              // trans_merge_install$0111
             && t_SplitMergeInfo.skip(cs)               // split_info:SplitMergeInfo
             && t_Ref_Transaction.skip(cs)              // prepare_transaction:^Transaction
             && Maybe<TrCreditPhase>{}.skip(cs)         // credit_ph:(Maybe TrCreditPhase)
             && Maybe<TrComputePhase>{}.skip(cs)        // compute_ph:TrComputePhase
             && Maybe<RefTo<TrActionPhase>>{}.skip(cs)  // action:(Maybe ^TrActionPhase)
             && cs.advance(2);                          // aborted:Bool destroyed:Bool
  }
  return false;
}

bool TransactionDescr::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case trans_ord:
      return cs.advance(4 + 1)                                   // trans_ord$0000 credit_first:Bool
             && Maybe<TrStoragePhase>{}.validate_skip(cs)        // storage_ph:(Maybe TrStoragePhase)
             && Maybe<TrCreditPhase>{}.validate_skip(cs)         // credit_ph:(Maybe TrCreditPhase)
             && t_TrComputePhase.validate_skip(cs)               // compute_ph:TrComputePhase
             && Maybe<RefTo<TrActionPhase>>{}.validate_skip(cs)  // action:(Maybe ^TrActionPhase)
             && cs.advance(1)                                    // aborted:Bool
             && Maybe<TrBouncePhase>{}.validate_skip(cs)         // bounce:(Maybe TrBouncePhase)
             && cs.advance(1);                                   // destroyed:Bool
    case trans_storage:
      return cs.advance(4)                           // trans_storage$0001
             && t_TrStoragePhase.validate_skip(cs);  // storage_ph:TrStoragePhase
    case trans_tick_tock:
      return cs.advance(4)                                       // trans_tick_tock$001 is_tock:Bool
             && t_TrStoragePhase.validate_skip(cs)               // storage:TrStoragePhase
             && t_TrComputePhase.validate_skip(cs)               // compute_ph:TrComputePhase
             && Maybe<RefTo<TrActionPhase>>{}.validate_skip(cs)  // action:(Maybe ^TrActionPhase)
             && cs.advance(2);                                   // aborted:Bool destroyed:Bool
    case trans_split_prepare:
      return cs.advance(4)                                       // trans_split_prepare$0100
             && t_SplitMergeInfo.validate_skip(cs)               // split_info:SplitMergeInfo
             && t_TrComputePhase.validate_skip(cs)               // compute_ph:TrComputePhase
             && Maybe<RefTo<TrActionPhase>>{}.validate_skip(cs)  // action:(Maybe ^TrActionPhase)
             && cs.advance(2);                                   // aborted:Bool destroyed:Bool
    case trans_split_install:
      return cs.advance(4)                           // trans_split_install$0101
             && t_SplitMergeInfo.validate_skip(cs)   // split_info:SplitMergeInfo
             && t_Ref_Transaction.validate_skip(cs)  // prepare_transaction:^Transaction
             && cs.advance(1);                       // installed:Bool
    case trans_merge_prepare:
      return cs.advance(4)                          // trans_merge_prepare$0110
             && t_SplitMergeInfo.validate_skip(cs)  // split_info:SplitMergeInfo
             && t_TrStoragePhase.validate_skip(cs)  // storage_ph:TrStoragePhase
             && cs.advance(1);                      // aborted:Bool
    case trans_merge_install:
      return cs.advance(4)                                       // trans_merge_install$0111
             && t_SplitMergeInfo.validate_skip(cs)               // split_info:SplitMergeInfo
             && t_Ref_Transaction.validate_skip(cs)              // prepare_transaction:^Transaction
             && Maybe<TrCreditPhase>{}.validate_skip(cs)         // credit_ph:(Maybe TrCreditPhase)
             && Maybe<TrComputePhase>{}.validate_skip(cs)        // compute_ph:TrComputePhase
             && Maybe<RefTo<TrActionPhase>>{}.validate_skip(cs)  // action:(Maybe ^TrActionPhase)
             && cs.advance(2);                                   // aborted:Bool destroyed:Bool
  }
  return false;
}

int TransactionDescr::get_tag(const vm::CellSlice& cs) const {
  int t = (int)cs.prefetch_ulong(4);
  return (t >= 0 && t <= 7) ? (t == 3 ? 2 : t) : -1;
}

const TransactionDescr t_TransactionDescr;

bool Transaction::skip(vm::CellSlice& cs) const {
  return cs.advance(
             4 + 256 + 64 + 256 + 64 + 32 +
             15)  // transaction$0110 account_addr:uint256 lt:uint64 prev_trans_hash:bits256 prev_trans_lt:uint64 now:uint32 outmsg_cnt:uint15
         && t_AccountStatus.skip(cs)              // orig_status:AccountStatus
         && t_AccountStatus.skip(cs)              // end_status:AccountStatus
         && Maybe<RefTo<Message>>{}.skip(cs)      // in_msg:(Maybe ^Message)
         && HashmapE{15, t_Ref_Message}.skip(cs)  // out_msgs:(HashmapE 15 ^Message)
         && t_Grams.skip(cs)                      // total_fees:Grams
         && t_RefCell.skip(cs)                    // state_update:^(MERKLE_UPDATE Account)
         && RefTo<TransactionDescr>{}.skip(cs);   // description:^TransactionDescr
}

bool Transaction::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 6  // transaction$0110
         &&
         cs.advance(
             256 + 64 + 256 + 64 + 32 +
             15)  // account_addr:uint256 lt:uint64 prev_trans_hash:bits256 prev_trans_lt:uint64 now:uint32 outmsg_cnt:uint15
         && t_AccountStatus.validate_skip(cs)              // orig_status:AccountStatus
         && t_AccountStatus.validate_skip(cs)              // end_status:AccountStatus
         && Maybe<RefTo<Message>>{}.validate_skip(cs)      // in_msg:(Maybe ^Message)
         && HashmapE{15, t_Ref_Message}.validate_skip(cs)  // out_msgs:(HashmapE 15 ^Message)
         && t_Grams.validate_skip(cs)                      // total_fees:Grams
         && t_RefCell.validate_skip(cs)                    // FIXME state_update:^(MERKLE_UPDATE Account)
         && RefTo<TransactionDescr>{}.validate_skip(cs);   // description:^TransactionDescr
}

bool Transaction::get_total_fees(vm::CellSlice&& cs, td::RefInt256& total_fees) const {
  return cs.fetch_ulong(4) == 6  // transaction$0110
         &&
         cs.advance(
             256 + 64 + 256 + 64 + 32 +
             15)  // account_addr:uint256 lt:uint64 prev_trans_hash:bits256 prev_trans_lt:uint64 now:uint32 outmsg_cnt:uint15
         && t_AccountStatus.skip(cs)                     // orig_status:AccountStatus
         && t_AccountStatus.skip(cs)                     // end_status:AccountStatus
         && Maybe<RefTo<Message>>{}.skip(cs)             // in_msg:(Maybe ^Message)
         && HashmapE{15, t_Ref_Message}.skip(cs)         // out_msgs:(HashmapE 15 ^Message)
         && t_Grams.as_integer_skip_to(cs, total_fees);  // total_fees:Grams
}

const Transaction t_Transaction;
const RefTo<Transaction> t_Ref_Transaction;

// leaf evaluation for (HashmapAug 64 ^Transaction Grams)
bool Aug_AccountTransactions::eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const {
  auto cell_ref = cs.prefetch_ref();
  td::RefInt256 total_fees;
  return cell_ref.not_null() && t_Transaction.get_total_fees(vm::load_cell_slice(std::move(cell_ref)), total_fees) &&
         t_Grams.store_integer_ref(cb, std::move(total_fees));
}

const Aug_AccountTransactions aug_AccountTransactions;
const HashmapAug t_AccountTransactions{64, aug_AccountTransactions};

const HashUpdate t_HashUpdate;
const RefTo<HashUpdate> t_Ref_HashUpdate;

bool AccountBlock::skip(vm::CellSlice& cs) const {
  return cs.advance(4 + 256)                // acc_trans#4 account_addr:bits256
         && t_AccountTransactions.skip(cs)  // transactions:(HashmapAug 64 ^Transaction Grams)
         && cs.advance_refs(1);             // state_update:^(HASH_UPDATE Account)
}

bool AccountBlock::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 4                      // acc_trans#4
         && cs.advance(256)                          // account_addr:bits256
         && t_AccountTransactions.validate_skip(cs)  // transactions:(HashmapAug 64 ^Transaction Grams)
         && t_Ref_HashUpdate.validate_skip(cs);      // state_update:^(HASH_UPDATE Account)
}

bool AccountBlock::get_total_fees(vm::CellSlice&& cs, td::RefInt256& total_fees) const {
  return cs.advance(4 + 256)                         // acc_trans#4 account_addr:bits256
         && t_AccountTransactions.extract_extra(cs)  // transactions:(HashmapAug 64 ^Transaction Grams)
         && t_Grams.as_integer_skip_to(cs, total_fees);
}

const AccountBlock t_AccountBlock;

bool Aug_ShardAccountBlocks::eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const {
  td::RefInt256 total_fees;
  return t_AccountBlock.get_total_fees(std::move(cs), total_fees) &&
         t_Grams.store_integer_ref(cb, std::move(total_fees));
}

const Aug_ShardAccountBlocks aug_ShardAccountBlocks;
const HashmapAugE t_ShardAccountBlocks{256, aug_ShardAccountBlocks};  // (HashmapAugE 256 AccountBlock Grams)

bool ImportFees::validate_skip(vm::CellSlice& cs) const {
  return t_Grams.validate_skip(cs) && t_CurrencyCollection.validate_skip(cs);
}

bool ImportFees::skip(vm::CellSlice& cs) const {
  return t_Grams.skip(cs) && t_CurrencyCollection.skip(cs);
}

bool ImportFees::add_values(vm::CellBuilder& cb, vm::CellSlice& cs1, vm::CellSlice& cs2) const {
  return t_Grams.add_values(cb, cs1, cs2) && t_CurrencyCollection.add_values(cb, cs1, cs2);
}

const ImportFees t_ImportFees;

bool InMsg::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case msg_import_ext:
      return cs.advance(3)                   // msg_import_ext$000
             && t_Ref_Message.skip(cs)       // msg:^Message
             && t_Ref_Transaction.skip(cs);  // transaction:^Transaction
    case msg_import_ihr:
      return cs.advance(3)                  // msg_import_ihr$010
             && t_Ref_Message.skip(cs)      // msg:^Message
             && t_Ref_Transaction.skip(cs)  // transaction:^Transaction
             && t_Grams.skip(cs)            // ihr_fee:Grams
             && t_RefCell.skip(cs);         // proof_created:^Cell
    case msg_import_imm:
      return cs.advance(3)                  // msg_import_imm$011
             && t_Ref_MsgEnvelope.skip(cs)  // in_msg:^MsgEnvelope
             && t_Ref_Transaction.skip(cs)  // transaction:^Transaction
             && t_Grams.skip(cs);           // fwd_fee:Grams
    case msg_import_fin:
      return cs.advance(3)                  // msg_import_fin$100
             && t_Ref_MsgEnvelope.skip(cs)  // in_msg:^MsgEnvelope
             && t_Ref_Transaction.skip(cs)  // transaction:^Transaction
             && t_Grams.skip(cs);           // fwd_fee:Grams
    case msg_import_tr:
      return cs.advance(3)                  // msg_import_tr$101
             && t_Ref_MsgEnvelope.skip(cs)  // in_msg:^MsgEnvelope
             && t_Ref_MsgEnvelope.skip(cs)  // out_msg:^MsgEnvelope
             && t_Grams.skip(cs);           // transit_fee:Grams
    case msg_discard_fin:
      return cs.advance(3)                  // msg_discard_fin$110
             && t_Ref_MsgEnvelope.skip(cs)  // in_msg:^MsgEnvelope
             && cs.advance(64)              // transaction_id:uint64
             && t_Grams.skip(cs);           // fwd_fee:Grams
    case msg_discard_tr:
      return cs.advance(3)                  // msg_discard_tr$111
             && t_Ref_MsgEnvelope.skip(cs)  // in_msg:^MsgEnvelope
             && cs.advance(64)              // transaction_id:uint64
             && t_Grams.skip(cs)            // fwd_fee:Grams
             && t_RefCell.skip(cs);         // proof_delivered:^Cell
  }
  return false;
}

bool InMsg::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case msg_import_ext:
      return cs.advance(3)                            // msg_import_ext$000
             && t_Ref_Message.validate_skip(cs)       // msg:^Message
             && t_Ref_Transaction.validate_skip(cs);  // transaction:^Transaction
    case msg_import_ihr:
      return cs.advance(3)                           // msg_import_ihr$010
             && t_Ref_Message.validate_skip(cs)      // msg:^Message
             && t_Ref_Transaction.validate_skip(cs)  // transaction:^Transaction
             && t_Grams.validate_skip(cs)            // ihr_fee:Grams
             && t_RefCell.validate_skip(cs);         // proof_created:^Cell
    case msg_import_imm:
      return cs.advance(3)                           // msg_import_imm$011
             && t_Ref_MsgEnvelope.validate_skip(cs)  // in_msg:^MsgEnvelope
             && t_Ref_Transaction.validate_skip(cs)  // transaction:^Transaction
             && t_Grams.validate_skip(cs);           // fwd_fee:Grams
    case msg_import_fin:
      return cs.advance(3)                           // msg_import_fin$100
             && t_Ref_MsgEnvelope.validate_skip(cs)  // in_msg:^MsgEnvelope
             && t_Ref_Transaction.validate_skip(cs)  // transaction:^Transaction
             && t_Grams.validate_skip(cs);           // fwd_fee:Grams
    case msg_import_tr:
      return cs.advance(3)                           // msg_import_tr$101
             && t_Ref_MsgEnvelope.validate_skip(cs)  // in_msg:^MsgEnvelope
             && t_Ref_MsgEnvelope.validate_skip(cs)  // out_msg:^MsgEnvelope
             && t_Grams.validate_skip(cs);           // transit_fee:Grams
    case msg_discard_fin:
      return cs.advance(3)                           // msg_discard_fin$110
             && t_Ref_MsgEnvelope.validate_skip(cs)  // in_msg:^MsgEnvelope
             && cs.advance(64)                       // transaction_id:uint64
             && t_Grams.validate_skip(cs);           // fwd_fee:Grams
    case msg_discard_tr:
      return cs.advance(3)                           // msg_discard_tr$111
             && t_Ref_MsgEnvelope.validate_skip(cs)  // in_msg:^MsgEnvelope
             && cs.advance(64)                       // transaction_id:uint64
             && t_Grams.validate_skip(cs)            // fwd_fee:Grams
             && t_RefCell.validate_skip(cs);         // proof_delivered:^Cell
  }
  return false;
}

bool InMsg::get_import_fees(vm::CellBuilder& cb, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case msg_import_ext:                   // inbound external message
      return t_ImportFees.null_value(cb);  // external messages have no value and no import fees
    case msg_import_ihr:                   // IHR-forwarded internal message to its final destination
      if (cs.advance(3) && cs.size_refs() >= 3) {
        auto msg_cs = load_cell_slice(cs.fetch_ref());
        CommonMsgInfo::Record_int_msg_info msg_info;
        td::RefInt256 ihr_fee;
        vm::CellBuilder aux;
        // sort of Prolog-style in C++
        return t_Message.extract_info(msg_cs) && t_CommonMsgInfo.unpack(msg_cs, msg_info) &&
               cs.fetch_ref().not_null() && (ihr_fee = t_Grams.as_integer_skip(cs)).not_null() &&
               cs.fetch_ref().not_null() && !cmp(ihr_fee, t_Grams.as_integer(*msg_info.ihr_fee)) &&
               cb.append_cellslice_bool(msg_info.ihr_fee)  // fees_collected := ihr_fee
               && aux.append_cellslice_bool(msg_info.ihr_fee) && t_ExtraCurrencyCollection.null_value(aux) &&
               t_CurrencyCollection.add_values(cb, aux.as_cellslice_ref().write(),
                                               msg_info.value.write());  // value_imported := ihr_fee + value
      }
      return false;
    case msg_import_imm:  // internal message re-imported from this very block
      if (cs.advance(3) && cs.size_refs() >= 2) {
        return cs.fetch_ref().not_null() && cs.fetch_ref().not_null() &&
               cb.append_cellslice_bool(t_Grams.fetch(cs))  // fees_collected := fwd_fees
               && t_CurrencyCollection.null_value(cb);      // value_imported := 0
      }
      return false;
    case msg_import_fin:  // internal message delivered to its final destination in this block
      if (cs.advance(3) && cs.size_refs() >= 2) {
        auto msg_env_cs = load_cell_slice(cs.fetch_ref());
        MsgEnvelope::Record in_msg;
        td::RefInt256 fwd_fee, fwd_fee_remaining, value_grams, ihr_fee;
        if (!(t_MsgEnvelope.unpack(msg_env_cs, in_msg) && cs.fetch_ref().not_null() &&
              t_Grams.as_integer_skip_to(cs, fwd_fee) &&
              (fwd_fee_remaining = t_Grams.as_integer(in_msg.fwd_fee_remaining)).not_null() &&
              !(cmp(fwd_fee, fwd_fee_remaining)))) {
          return false;
        }
        auto msg_cs = load_cell_slice(std::move(in_msg.msg));
        CommonMsgInfo::Record_int_msg_info msg_info;
        return t_Message.extract_info(msg_cs) && t_CommonMsgInfo.unpack(msg_cs, msg_info) &&
               cb.append_cellslice_bool(in_msg.fwd_fee_remaining)  // fees_collected := fwd_fee_remaining
               && t_Grams.as_integer_skip_to(msg_info.value.write(), value_grams) &&
               (ihr_fee = t_Grams.as_integer(std::move(msg_info.ihr_fee))).not_null() &&
               t_Grams.store_integer_ref(cb, value_grams + ihr_fee + fwd_fee_remaining) &&
               cb.append_cellslice_bool(
                   msg_info.value.write());  // value_imported = msg.value + msg.ihr_fee + fwd_fee_remaining
      }
      return false;
    case msg_import_tr:  // transit internal message
      if (cs.advance(3) && cs.size_refs() >= 2) {
        auto msg_env_cs = load_cell_slice(cs.fetch_ref());
        MsgEnvelope::Record in_msg;
        td::RefInt256 transit_fee, fwd_fee_remaining, value_grams, ihr_fee;
        if (!(t_MsgEnvelope.unpack(msg_env_cs, in_msg) && cs.fetch_ref().not_null() &&
              t_Grams.as_integer_skip_to(cs, transit_fee) &&
              (fwd_fee_remaining = t_Grams.as_integer(in_msg.fwd_fee_remaining)).not_null() &&
              cmp(transit_fee, fwd_fee_remaining) <= 0)) {
          return false;
        }
        auto msg_cs = load_cell_slice(in_msg.msg);
        CommonMsgInfo::Record_int_msg_info msg_info;
        return t_Message.extract_info(msg_cs) && t_CommonMsgInfo.unpack(msg_cs, msg_info) &&
               t_Grams.store_integer_ref(cb, std::move(transit_fee))  // fees_collected := transit_fees
               && t_Grams.as_integer_skip_to(msg_info.value.write(), value_grams) &&
               (ihr_fee = t_Grams.as_integer(std::move(msg_info.ihr_fee))).not_null() &&
               t_Grams.store_integer_ref(cb, value_grams + ihr_fee + fwd_fee_remaining) &&
               cb.append_cellslice_bool(
                   msg_info.value.write());  // value_imported = msg.value + msg.ihr_fee + fwd_fee_remaining
      }
      return false;
    case msg_discard_fin:  // internal message discarded at its final destination because of previous IHR delivery
      if (cs.advance(3) && cs.size_refs() >= 1) {
        Ref<vm::CellSlice> fwd_fee;
        return cs.fetch_ref().not_null() && cs.advance(64) && (fwd_fee = t_Grams.fetch(cs)).not_null() &&
               cb.append_cellslice_bool(fwd_fee)  // fees_collected := fwd_fee
               && cb.append_cellslice_bool(std::move(fwd_fee)) &&
               t_ExtraCurrencyCollection.null_value(cb);  // value_imported := fwd_fee
      }
      return false;
    case msg_discard_tr:  // internal message discarded at an intermediate destination
      if (cs.advance(3) && cs.size_refs() >= 2) {
        Ref<vm::CellSlice> fwd_fee;
        return cs.fetch_ref().not_null() && cs.advance(64) && (fwd_fee = t_Grams.fetch(cs)).not_null() &&
               cs.fetch_ref().not_null() && cb.append_cellslice_bool(fwd_fee)  // fees_collected := fwd_fee
               && cb.append_cellslice_bool(std::move(fwd_fee)) &&
               t_ExtraCurrencyCollection.null_value(cb);  // value_imported := fwd_fee
      }
      return false;
  }
  return false;
}

const InMsg t_InMsg;

const Aug_InMsgDescr aug_InMsgDescr;
const InMsgDescr t_InMsgDescr;

bool OutMsg::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case msg_export_ext:
      return cs.advance(3)                   // msg_export_ext$000
             && t_Ref_Message.skip(cs)       // msg:^Message
             && t_Ref_Transaction.skip(cs);  // transaction:^Transaction
    case msg_export_imm:
      return cs.advance(3)                  // msg_export_imm$010
             && t_Ref_MsgEnvelope.skip(cs)  // out_msg:^MsgEnvelope
             && t_Ref_Transaction.skip(cs)  // transaction:^Transaction
             && RefTo<InMsg>{}.skip(cs);    // reimport:^InMsg
    case msg_export_new:
      return cs.advance(3)                   // msg_export_new$001
             && t_Ref_MsgEnvelope.skip(cs)   // out_msg:^MsgEnvelope
             && t_Ref_Transaction.skip(cs);  // transaction:^Transaction
    case msg_export_tr:
      return cs.advance(3)                  // msg_export_tr$011
             && t_Ref_MsgEnvelope.skip(cs)  // out_msg:^MsgEnvelope
             && RefTo<InMsg>{}.skip(cs);    // imported:^InMsg
    case msg_export_deq_imm:
      return cs.advance(3)                  // msg_export_deq_imm$100
             && t_Ref_MsgEnvelope.skip(cs)  // out_msg:^MsgEnvelope
             && RefTo<InMsg>{}.skip(cs);    // reimport:^InMsg
    case msg_export_deq:
      return cs.advance(3)                  // msg_export_deq$110
             && t_Ref_MsgEnvelope.skip(cs)  // out_msg:^MsgEnvelope
             && cs.advance(64);             // import_block_lt:uint64
    case msg_export_tr_req:
      return cs.advance(3)                  // msg_export_tr_req$111
             && t_Ref_MsgEnvelope.skip(cs)  // out_msg:^MsgEnvelope
             && RefTo<InMsg>{}.skip(cs);    // imported:^InMsg
  }
  return false;
}

bool OutMsg::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case msg_export_ext:
      return cs.advance(3)                            // msg_export_ext$000
             && t_Ref_Message.validate_skip(cs)       // msg:^Message
             && t_Ref_Transaction.validate_skip(cs);  // transaction:^Transaction
    case msg_export_imm:
      return cs.advance(3)                           // msg_export_imm$010
             && t_Ref_MsgEnvelope.validate_skip(cs)  // out_msg:^MsgEnvelope
             && t_Ref_Transaction.validate_skip(cs)  // transaction:^Transaction
             && RefTo<InMsg>{}.validate_skip(cs);    // reimport:^InMsg
    case msg_export_new:
      return cs.advance(3)                            // msg_export_new$001
             && t_Ref_MsgEnvelope.validate_skip(cs)   // out_msg:^MsgEnvelope
             && t_Ref_Transaction.validate_skip(cs);  // transaction:^Transaction
    case msg_export_tr:
      return cs.advance(3)                           // msg_export_tr$011
             && t_Ref_MsgEnvelope.validate_skip(cs)  // out_msg:^MsgEnvelope
             && RefTo<InMsg>{}.validate_skip(cs);    // imported:^InMsg
    case msg_export_deq_imm:
      return cs.advance(3)                           // msg_export_deq_imm$100
             && t_Ref_MsgEnvelope.validate_skip(cs)  // out_msg:^MsgEnvelope
             && RefTo<InMsg>{}.validate_skip(cs);    // reimport:^InMsg
    case msg_export_deq:
      return cs.advance(3)                           // msg_export_deq$110
             && t_Ref_MsgEnvelope.validate_skip(cs)  // out_msg:^MsgEnvelope
             && cs.advance(64);                      // import_block_lt:uint64
    case msg_export_tr_req:
      return cs.advance(3)                           // msg_export_tr_req$111
             && t_Ref_MsgEnvelope.validate_skip(cs)  // out_msg:^MsgEnvelope
             && RefTo<InMsg>{}.validate_skip(cs);    // imported:^InMsg
  }
  return false;
}

bool OutMsg::get_export_value(vm::CellBuilder& cb, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
    case msg_export_ext:  // external outbound message carries no value
      if (cs.have(3, 2)) {
        return t_CurrencyCollection.null_value(cb);
      }
      return false;
    case msg_export_imm:  // outbound internal message delivered in this very block, no value exported
      return cs.have(3, 3) && t_CurrencyCollection.null_value(cb);
    case msg_export_deq_imm:  // dequeuing record for outbound message delivered in this very block, no value exported
      return cs.have(3, 2) && t_CurrencyCollection.null_value(cb);
    case msg_export_deq:  // dequeueing record for outbound message, no exported value
      return cs.have(3, 1) && t_CurrencyCollection.null_value(cb);
    case msg_export_new:     // newly-generated outbound internal message, queued
    case msg_export_tr:      // transit internal message, queued
    case msg_export_tr_req:  // transit internal message, re-queued from this shardchain
      if (cs.advance(3) && cs.size_refs() >= 2) {
        auto msg_env_cs = load_cell_slice(cs.fetch_ref());
        MsgEnvelope::Record out_msg;
        if (!(cs.fetch_ref().not_null() && t_MsgEnvelope.unpack(msg_env_cs, out_msg))) {
          return false;
        }
        auto msg_cs = load_cell_slice(std::move(out_msg.msg));
        CommonMsgInfo::Record_int_msg_info msg_info;
        td::RefInt256 value_grams, ihr_fee, fwd_fee_remaining;
        return t_Message.extract_info(msg_cs) && t_CommonMsgInfo.unpack(msg_cs, msg_info) &&
               (value_grams = t_Grams.as_integer_skip(msg_info.value.write())).not_null() &&
               (ihr_fee = t_Grams.as_integer(std::move(msg_info.ihr_fee))).not_null() &&
               (fwd_fee_remaining = t_Grams.as_integer(out_msg.fwd_fee_remaining)).not_null() &&
               t_Grams.store_integer_ref(cb, value_grams + ihr_fee + fwd_fee_remaining) &&
               cb.append_cellslice_bool(std::move(msg_info.value));
        // exported value = msg.value + msg.ihr_fee + fwd_fee_remaining
      }
      return false;
  }
  return false;
}

bool OutMsg::get_created_lt(vm::CellSlice& cs, unsigned long long& created_lt) const {
  switch (get_tag(cs)) {
    case msg_export_ext:
      if (cs.have(3, 1)) {
        auto msg_cs = load_cell_slice(cs.prefetch_ref());
        return t_Message.get_created_lt(msg_cs, created_lt);
      } else {
        return false;
      }
    case msg_export_imm:
    case msg_export_new:
    case msg_export_tr:
    case msg_export_deq:
    case msg_export_deq_imm:
    case msg_export_tr_req:
      if (cs.have(3, 1)) {
        auto out_msg_cs = load_cell_slice(cs.prefetch_ref());
        return t_MsgEnvelope.get_created_lt(out_msg_cs, created_lt);
      } else {
        return false;
      }
  }
  return false;
}

const OutMsg t_OutMsg;

const Aug_OutMsgDescr aug_OutMsgDescr;
const OutMsgDescr t_OutMsgDescr;

bool EnqueuedMsg::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(64) && t_Ref_MsgEnvelope.validate_skip(cs);
}

const EnqueuedMsg t_EnqueuedMsg;

bool Aug_OutMsgQueue::eval_fork(vm::CellBuilder& cb, vm::CellSlice& left_cs, vm::CellSlice& right_cs) const {
  unsigned long long x, y;
  return left_cs.fetch_ulong_bool(64, x) && right_cs.fetch_ulong_bool(64, y) &&
         cb.store_ulong_rchk_bool(std::min(x, y), 64);
}

bool Aug_OutMsgQueue::eval_empty(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 64);
}

bool Aug_OutMsgQueue::eval_leaf(vm::CellBuilder& cb, vm::CellSlice& cs) const {
  Ref<vm::Cell> msg_env;
  unsigned long long created_lt;
  return cs.fetch_ref_to(msg_env) && t_MsgEnvelope.get_created_lt(load_cell_slice(std::move(msg_env)), created_lt) &&
         cb.store_ulong_rchk_bool(created_lt, 64);
}

const Aug_OutMsgQueue aug_OutMsgQueue;
const OutMsgQueue t_OutMsgQueue;

const ProcessedUpto t_ProcessedUpto;
const HashmapE t_ProcessedInfo{96, t_ProcessedUpto};
const HashmapE t_IhrPendingInfo{256, t_uint128};

// _ out_queue:OutMsgQueue proc_info:ProcessedInfo = OutMsgQueueInfo;
bool OutMsgQueueInfo::skip(vm::CellSlice& cs) const {
  return t_OutMsgQueue.skip(cs) && t_ProcessedInfo.skip(cs) && t_IhrPendingInfo.skip(cs);
}

bool OutMsgQueueInfo::validate_skip(vm::CellSlice& cs) const {
  return t_OutMsgQueue.validate_skip(cs) && t_ProcessedInfo.validate_skip(cs) && t_IhrPendingInfo.validate_skip(cs);
}

const OutMsgQueueInfo t_OutMsgQueueInfo;
const RefTo<OutMsgQueueInfo> t_Ref_OutMsgQueueInfo;

const ExtBlkRef t_ExtBlkRef;
const BlkMasterInfo t_BlkMasterInfo;

bool ShardIdent::validate_skip(vm::CellSlice& cs) const {
  int shard_pfx_len, workchain_id;
  unsigned long long shard_pfx;
  if (cs.fetch_ulong(2) == 0 && cs.fetch_uint_to(6, shard_pfx_len) && cs.fetch_int_to(32, workchain_id) &&
      workchain_id != ton::workchainInvalid && cs.fetch_uint_to(64, shard_pfx)) {
    auto pow2 = (1ULL << (63 - shard_pfx_len));
    if (!(shard_pfx & (pow2 - 1))) {
      return true;
    }
  }
  return false;
}

bool ShardIdent::Record::check() const {
  return workchain_id != ton::workchainInvalid && !(shard_prefix & ((1ULL << (63 - shard_pfx_bits)) - 1));
}

bool ShardIdent::unpack(vm::CellSlice& cs, ShardIdent::Record& data) const {
  if (cs.fetch_ulong(2) == 0 && cs.fetch_uint_to(6, data.shard_pfx_bits) && cs.fetch_int_to(32, data.workchain_id) &&
      cs.fetch_uint_to(64, data.shard_prefix) && data.check()) {
    return true;
  } else {
    data.invalidate();
    return false;
  }
}

bool ShardIdent::pack(vm::CellBuilder& cb, const Record& data) const {
  return data.check() && cb.store_ulong_rchk_bool(0, 2) && cb.store_ulong_rchk_bool(data.shard_pfx_bits, 6) &&
         cb.store_long_rchk_bool(data.workchain_id, 32) && cb.store_ulong_rchk_bool(data.shard_prefix, 64);
}

bool ShardIdent::unpack(vm::CellSlice& cs, ton::WorkchainId& workchain, ton::ShardId& shard) const {
  int bits;
  unsigned long long pow2;
  auto assign = [](auto& a, auto b) { return a = b; };
  auto assign_or = [](auto& a, auto b) { return a |= b; };
  return cs.fetch_ulong(2) == 0                  // shard_ident$00
         && cs.fetch_uint_leq(60, bits)          // shard_pfx_bits:(#<= 60)
         && assign(pow2, (1ULL << (63 - bits)))  // (power)
         && cs.fetch_int_to(32, workchain)       // workchain_id:int32
         && cs.fetch_uint_to(64, shard)          // shard_prefix:uint64
         && workchain != ton::workchainInvalid && !(shard & (2 * pow2 - 1)) && assign_or(shard, pow2);
}

bool ShardIdent::unpack(vm::CellSlice& cs, ton::ShardIdFull& data) const {
  return unpack(cs, data.workchain, data.shard);
}

bool ShardIdent::pack(vm::CellBuilder& cb, ton::WorkchainId workchain, ton::ShardId shard) const {
  int bits = ton::shard_prefix_length(shard);
  return workchain != ton::workchainInvalid               // check workchain
         && shard                                         // check shard
         && cb.store_long_bool(0, 2)                      // shard_ident$00
         && cb.store_uint_leq(60, bits)                   // shard_pfx_bits:(#<= 60)
         && cb.store_long_bool(workchain, 32)             // workchain_id:int32
         && cb.store_long_bool(shard & (shard - 1), 64);  // shard_prefix:uint64
}

bool ShardIdent::pack(vm::CellBuilder& cb, ton::ShardIdFull data) const {
  return pack(cb, data.workchain, data.shard);
}

const ShardIdent t_ShardIdent;

bool BlockIdExt::validate_skip(vm::CellSlice& cs) const {
  return t_ShardIdent.validate_skip(cs) && cs.advance(32 + 256 * 2);
}

bool BlockIdExt::unpack(vm::CellSlice& cs, ton::BlockIdExt& data) const {
  return t_ShardIdent.unpack(cs, data.id.workchain, data.id.shard)  // block_id_ext$_ shard_id:ShardIdent
         && cs.fetch_uint_to(32, data.id.seqno)                     // seq_no:uint32
         && cs.fetch_bits_to(data.root_hash)                        // root_hash:bits256
         && cs.fetch_bits_to(data.file_hash);                       // file_hash:bits256
}

bool BlockIdExt::pack(vm::CellBuilder& cb, const ton::BlockIdExt& data) const {
  return t_ShardIdent.pack(cb, data.id.workchain, data.id.shard)  // block_id_ext$_ shard_id:ShardIdent
         && cb.store_long_bool(data.id.seqno, 32)                 // seq_no:uint32
         && cb.store_bits_bool(data.root_hash)                    // root_hash:bits256
         && cb.store_bits_bool(data.file_hash);                   // file_hash:bits256
}

const BlockIdExt t_BlockIdExt;

bool ShardState::skip(vm::CellSlice& cs) const {
  return get_tag(cs) == shard_state && cs.advance(64)  // shard_state#9023afde blockchain_id:int32
         && t_ShardIdent.skip(cs)                      // shard_id:ShardIdent
         && cs.advance(32 + 32 + 32 + 64 +
                       32)  // seq_no:int32 vert_seq_no:# gen_utime:uint32 gen_lt:uint64 min_ref_mc_seqno:uint32
         && t_Ref_OutMsgQueueInfo.skip(cs)  // out_msg_queue_info:^OutMsgQueueInfo
         && cs.advance(1)                   // before_split:Bool
         && t_ShardAccounts.skip(cs)        // accounts:ShardAccounts
         &&
         cs.advance_refs(
             1)  // ^[ total_balance:CurrencyCollection total_validator_fees:CurrencyCollection libraries:(HashmapE 256 LibDescr) ]
         && Maybe<BlkMasterInfo>{}.skip(cs)         // master_ref:(Maybe BlkMasterInfo)
         && Maybe<RefTo<McStateExtra>>{}.skip(cs);  // custom:(Maybe ^McStateExtra)
}

bool ShardState::validate_skip(vm::CellSlice& cs) const {
  int seq_no;
  return get_tag(cs) == shard_state && cs.advance(64)  // shard_state#9023afde blockchain_id:int32
         && t_ShardIdent.validate_skip(cs)             // shard_id:ShardIdent
         && cs.fetch_int_to(32, seq_no)                // seq_no:int32
         && seq_no >= -1                               // { seq_no >= -1 }
         && cs.advance(32 + 32 + 64 + 32)  // vert_seq_no:# gen_utime:uint32 gen_lt:uint64 min_ref_mc_seqno:uint32
         && t_Ref_OutMsgQueueInfo.validate_skip(cs)  // out_msg_queue_info:^OutMsgQueueInfo
         && cs.advance(1)                            // before_split:Bool
         && t_ShardAccounts.validate_skip(cs)        // accounts:ShardAccounts
         &&
         t_ShardState_aux.validate_skip_ref(
             cs)  // ^[ total_balance:CurrencyCollection total_validator_fees:CurrencyCollection libraries:(HashmapE 256 LibDescr) ]
         && Maybe<BlkMasterInfo>{}.validate_skip(cs)         // master_ref:(Maybe BlkMasterInfo)
         && Maybe<RefTo<McStateExtra>>{}.validate_skip(cs);  // custom:(Maybe ^McStateExtra)
}

const ShardState t_ShardState;

bool ShardState_aux::skip(vm::CellSlice& cs) const {
  return cs.advance(128)                         // overload_history:uint64 underload_history:uint64
         && t_CurrencyCollection.skip(cs)        // total_balance:CurrencyCollection
         && t_CurrencyCollection.skip(cs)        // total_validator_fees:CurrencyCollection
         && HashmapE{256, t_LibDescr}.skip(cs);  // libraries:(HashmapE 256 LibDescr)
}

bool ShardState_aux::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(128)                                  // overload_history:uint64 underload_history:uint64
         && t_CurrencyCollection.validate_skip(cs)        // total_balance:CurrencyCollection
         && t_CurrencyCollection.validate_skip(cs)        // total_validator_fees:CurrencyCollection
         && HashmapE{256, t_LibDescr}.validate_skip(cs);  // libraries:(HashmapE 256 LibDescr)
}

const ShardState_aux t_ShardState_aux;

bool LibDescr::skip(vm::CellSlice& cs) const {
  return cs.advance(2)                      // shared_lib_descr$00
         && cs.fetch_ref().not_null()       // lib:^Cell
         && Hashmap{256, t_True}.skip(cs);  // publishers:(Hashmap 256 False)
}

bool LibDescr::validate_skip(vm::CellSlice& cs) const {
  return get_tag(cs) == shared_lib_descr && cs.advance(2)  // shared_lib_descr$00
         && cs.fetch_ref().not_null()                      // lib:^Cell
         && Hashmap{256, t_True}.validate_skip(cs);        // publishers:(Hashmap 256 False)
}

const LibDescr t_LibDescr;

bool BlkPrevInfo::skip(vm::CellSlice& cs) const {
  return t_ExtBlkRef.skip(cs)                   // prev_blk_info$_ {merged:#} prev:ExtBlkRef
         && (!merged || t_ExtBlkRef.skip(cs));  // prev_alt:merged?ExtBlkRef
}

bool BlkPrevInfo::validate_skip(vm::CellSlice& cs) const {
  return t_ExtBlkRef.validate_skip(cs)                   // prev_blk_info$_ {merged:#} prev:ExtBlkRef
         && (!merged || t_ExtBlkRef.validate_skip(cs));  // prev_alt:merged?ExtBlkRef
}

const BlkPrevInfo t_BlkPrevInfo_0{0};

bool McStateExtra::skip(vm::CellSlice& cs) const {
  return block::gen::t_McStateExtra.skip(cs);
}

bool McStateExtra::validate_skip(vm::CellSlice& cs) const {
  return block::gen::t_McStateExtra.validate_skip(cs);  // FIXME
}

const McStateExtra t_McStateExtra;

}  // namespace tlb

/*
 * 
 *    Other block-related functions
 * 
 */

bool store_UInt7(vm::CellBuilder& cb, unsigned long long value) {
  return block::tlb::t_VarUInteger_7.store_long(cb, (long long)value);
}

bool store_UInt7(vm::CellBuilder& cb, unsigned long long value1, unsigned long long value2) {
  return store_UInt7(cb, value1) && store_UInt7(cb, value2);
}

bool store_Maybe_Grams(vm::CellBuilder& cb, td::RefInt256 value) {
  if (value.is_null()) {
    return cb.store_long_bool(0, 1);
  } else {
    return cb.store_long_bool(1, 1) && block::tlb::t_Grams.store_integer_ref(cb, std::move(value));
  }
}

bool store_Maybe_Grams_nz(vm::CellBuilder& cb, td::RefInt256 value) {
  if (value.is_null() || !(*value)->sgn()) {
    return cb.store_long_bool(0, 1);
  } else {
    return cb.store_long_bool(1, 1) && block::tlb::t_Grams.store_integer_ref(cb, std::move(value));
  }
}

bool store_CurrencyCollection(vm::CellBuilder& cb, td::RefInt256 value, Ref<vm::Cell> extra) {
  return block::tlb::t_CurrencyCollection.pack_special(cb, std::move(value), std::move(extra));
}

bool fetch_CurrencyCollection(vm::CellSlice& cs, td::RefInt256& value, Ref<vm::Cell>& extra) {
  return block::tlb::t_CurrencyCollection.unpack_special(cs, value, extra);
}

bool unpack_CurrencyCollection(Ref<vm::CellSlice> csr, td::RefInt256& value, Ref<vm::Cell>& extra) {
  if (csr.is_null()) {
    return false;
  } else if (csr->is_unique()) {
    return block::tlb::t_CurrencyCollection.unpack_special(csr.write(), value, extra);
  } else {
    vm::CellSlice cs{*csr};
    return block::tlb::t_CurrencyCollection.unpack_special(cs, value, extra);
  }
}

bool check_one_library(Ref<vm::CellSlice> cs_ref, td::ConstBitPtr key, int n) {
  assert(n == 256);
  if (cs_ref->size_ext() != 0x10001) {
    return false;
  }
  Ref<vm::Cell> cell = cs_ref->prefetch_ref();
  const auto& cell_hash = cell->get_hash();
  return !td::bitstring::bits_memcmp(cell_hash.bits(), key, n);
}

bool valid_library_collection(Ref<vm::Cell> cell, bool catch_errors) {
  if (cell.is_null()) {
    return true;
  }
  if (!catch_errors) {
    vm::Dictionary dict{std::move(cell), 256};
    return dict.check_for_each(check_one_library);
  }
  try {
    vm::Dictionary dict{std::move(cell), 256};
    return dict.check_for_each(check_one_library);
  } catch (vm::VmError&) {
    return false;
  }
}

bool check_one_config_param(Ref<vm::CellSlice> cs_ref, td::ConstBitPtr key, td::ConstBitPtr addr, bool relax_par0) {
  if (cs_ref->size_ext() != 0x10000) {
    return false;
  }
  Ref<vm::Cell> cell = cs_ref->prefetch_ref();
  int idx = (int)key.get_int(32);
  if (!idx) {
    auto cs = load_cell_slice(std::move(cell));
    return (cs.size_ext() == 256 &&
            (relax_par0 || !td::bitstring::bits_memcmp(addr, cs.fetch_bits(256).get_bitptr(), 256)));
  } else if (idx < 0) {
    return true;
  }
  bool ok = block::gen::ConfigParam{idx}.validate_ref(std::move(cell));
  if (!ok) {
    LOG(ERROR) << "configuration parameter #" << idx << " is invalid";
  }
  return ok;
}

const int mandatory_config_params[] = {18, 34};

bool valid_config_data(Ref<vm::Cell> cell, const td::BitArray<256>& addr, bool catch_errors, bool relax_par0) {
  using namespace std::placeholders;
  if (cell.is_null()) {
    return false;
  }
  if (!catch_errors) {
    vm::Dictionary dict{std::move(cell), 32};
    for (int x : mandatory_config_params) {
      if (!dict.int_key_exists(x)) {
        LOG(ERROR) << "mandatory configuration parameter #" << x << " is missing";
        return false;
      }
    }
    return dict.check_for_each(std::bind(check_one_config_param, _1, _2, addr.cbits(), relax_par0));
  }
  try {
    vm::Dictionary dict{std::move(cell), 32};
    for (int x : mandatory_config_params) {
      if (!dict.int_key_exists(x)) {
        LOG(ERROR) << "mandatory configuration parameter #" << x << " is missing";
        return false;
      }
    }
    return dict.check_for_each(std::bind(check_one_config_param, _1, _2, addr.cbits(), relax_par0));
  } catch (vm::VmError&) {
    return false;
  }
}

bool add_extra_currency(Ref<vm::Cell> extra1, Ref<vm::Cell> extra2, Ref<vm::Cell>& res) {
  if (extra2.is_null()) {
    res = extra1;
    return true;
  } else if (extra1.is_null()) {
    res = extra2;
    return true;
  } else {
    return block::tlb::t_ExtraCurrencyCollection.add_values_ref(res, std::move(extra1), std::move(extra2));
  }
}

bool sub_extra_currency(Ref<vm::Cell> extra1, Ref<vm::Cell> extra2, Ref<vm::Cell>& res) {
  if (extra2.is_null()) {
    res = extra1;
    return true;
  } else if (extra1.is_null()) {
    res.clear();
    return false;
  } else {
    return block::tlb::t_ExtraCurrencyCollection.sub_values_ref(res, std::move(extra1), std::move(extra2));
  }
}

// combine d bits from dest, remaining 64 - d bits from src
ton::ShardIdFull interpolate_addr(ton::ShardIdFull src, ton::ShardIdFull dest, int d) {
  if (d <= 0) {
    return src;
  } else if (d >= 96) {
    return dest;
  } else if (d >= 32) {
    unsigned long long mask = (std::numeric_limits<td::uint64>::max() >> (d - 32));
    return ton::ShardIdFull{dest.workchain, (dest.shard & ~mask) | (src.shard & mask)};
  } else {
    int mask = (-1 >> d);
    return ton::ShardIdFull{(dest.workchain & ~mask) | (src.workchain & mask), src.shard};
  }
}

// result: (transit_addr_dest_bits, nh_addr_dest_bits)
std::pair<int, int> perform_hypercube_routing(ton::ShardIdFull src, ton::ShardIdFull dest, ton::ShardIdFull cur,
                                              int used_dest_bits) {
  ton::ShardIdFull transit = interpolate_addr(src, dest, used_dest_bits);
  if (!ton::shard_contains(cur, transit)) {
    return {-1, -1};
  }
  if (transit.workchain != dest.workchain) {
    return {used_dest_bits, 32};
  }
  if (transit.shard == dest.shard || ton::shard_contains(cur, dest)) {
    return {96, 96};
  }
  unsigned long long x = cur.shard & (cur.shard - 1), y = cur.shard | (cur.shard - 1);
  unsigned long long t = transit.shard, q = dest.shard ^ t;
  int i = (td::count_leading_zeroes64(q) & -4);  // top i bits match, next 4 bits differ
  unsigned long long m = (std::numeric_limits<td::uint64>::max() >> i), h;
  do {
    m >>= 4;
    h = t ^ (q & ~m);
    i += 4;
  } while (h >= x && h <= y);
  return {28 + i, 32 + i};
}

bool unpack_block_prev_blk(Ref<vm::Cell> block_root, ton::BlockIdExt& id, std::vector<ton::BlockIdExt>& prev,
                           ton::BlockIdExt& mc_blkid, bool& after_split) {
  return unpack_block_prev_blk_ext(std::move(block_root), id, prev, mc_blkid, after_split).is_ok();
}

td::Status unpack_block_prev_blk_try(Ref<vm::Cell> block_root, ton::BlockIdExt& id, std::vector<ton::BlockIdExt>& prev,
                                     ton::BlockIdExt& mc_blkid, bool& after_split) {
  try {
    return unpack_block_prev_blk_ext(std::move(block_root), id, prev, mc_blkid, after_split);
  } catch (vm::VmError err) {
    return td::Status::Error(std::string{"error while processing Merkle proof: "} + err.get_msg());
  } catch (vm::VmVirtError err) {
    return td::Status::Error(std::string{"error while processing Merkle proof: "} + err.get_msg());
  }
}

td::Status unpack_block_prev_blk_ext(Ref<vm::Cell> block_root, ton::BlockIdExt& id, std::vector<ton::BlockIdExt>& prev,
                                     ton::BlockIdExt& mc_blkid, bool& after_split) {
  block::gen::Block::Record blk;
  block::gen::BlockInfo::Record info;
  block::gen::BlkPrevInfo::Record prevref;
  block::gen::ExtBlkRef::Record mcref;  // _ ExtBlkRef = BlkMasterInfo;
  ton::ShardIdFull shard;
  if (!(tlb::unpack_cell(block_root, blk) && tlb::unpack_cell(blk.info, info) && !info.version &&
        block::tlb::t_ShardIdent.unpack(info.shard.write(), shard) && !info.vert_seq_no &&
        tlb::type_unpack_cell(info.prev_ref, block::gen::BlkPrevInfo{info.after_merge}, prevref) &&
        (!info.not_master || tlb::unpack_cell(info.master_ref, mcref)))) {
    return td::Status::Error("cannot unpack block header");
  }
  id.id = ton::BlockId{shard, (unsigned)info.seq_no};
  id.root_hash = block_root->get_hash().bits();
  id.file_hash.clear();
  if (info.not_master != !shard.is_masterchain()) {
    return td::Status::Error("block has invalid not_master flag in its (Merkelized) header");
  }
  after_split = info.after_split;
  block::gen::ExtBlkRef::Record prev1, prev2;
  if (!(tlb::csr_unpack(prevref.prev, prev1) && (!info.after_merge || tlb::csr_unpack(prevref.prev_alt, prev2)))) {
    return td::Status::Error("cannot unpack previous block references from block header");
  }
  prev.clear();
  ton::BlockSeqno prev_seqno = prev1.seq_no;
  if (!info.after_merge) {
    prev.emplace_back(shard.workchain, info.after_split ? ton::shard_parent(shard.shard) : shard.shard, prev1.seq_no,
                      prev1.root_hash, prev1.file_hash);
    if (info.after_split && !prev1.seq_no) {
      return td::Status::Error("shardchains cannot be split immediately after initial state");
    }
  } else {
    if (info.after_split) {
      return td::Status::Error("shardchains cannot be simultaneously split and merged at the same block");
    }
    prev.emplace_back(shard.workchain, ton::shard_child(shard.shard, true), prev1.seq_no, prev1.root_hash,
                      prev1.file_hash);
    prev.emplace_back(shard.workchain, ton::shard_child(shard.shard, false), prev2.seq_no, prev2.root_hash,
                      prev2.file_hash);
    prev_seqno = std::max<unsigned>(prev1.seq_no, prev2.seq_no);
    if (!prev1.seq_no || !prev2.seq_no) {
      return td::Status::Error("shardchains cannot be merged immediately after initial state");
    }
  }
  if (id.id.seqno != prev_seqno + 1) {
    return td::Status::Error("new block has invalid seqno (not equal to one plus maximum of seqnos of its ancestors)");
  }
  if (shard.is_masterchain()) {
    mc_blkid = prev.at(0);
  } else {
    mc_blkid = ton::BlockIdExt{ton::masterchainId, ton::shardIdAll, mcref.seq_no, mcref.root_hash, mcref.file_hash};
  }
  return td::Status::OK();
}

std::unique_ptr<vm::Dictionary> get_prev_blocks_dict(Ref<vm::Cell> state_root) {
  block::gen::ShardStateUnsplit::Record info;
  block::gen::McStateExtra::Record extra_info;
  if (!(::tlb::unpack_cell(std::move(state_root), info) && info.custom->size_refs() &&
        ::tlb::unpack_cell(info.custom->prefetch_ref(), extra_info))) {
    return {};
  }
  return std::make_unique<vm::Dictionary>(extra_info.r1.prev_blocks, 32);
}

bool get_old_mc_block_id(vm::Dictionary* prev_blocks_dict, ton::BlockSeqno seqno, ton::BlockIdExt& blkid,
                         ton::LogicalTime* end_lt) {
  return prev_blocks_dict && get_old_mc_block_id(*prev_blocks_dict, seqno, blkid, end_lt);
}

bool get_old_mc_block_id(vm::Dictionary& prev_blocks_dict, ton::BlockSeqno seqno, ton::BlockIdExt& blkid,
                         ton::LogicalTime* end_lt) {
  auto val = prev_blocks_dict.lookup(td::BitArray<32>{seqno});
  block::gen::ExtBlkRef::Record data;
  if (!(val.not_null() && ::tlb::csr_unpack(std::move(val), data) && data.seq_no == seqno)) {
    return false;
  }
  blkid.id = ton::BlockId{ton::masterchainId, ton::shardIdAll, seqno};
  blkid.root_hash = data.root_hash;
  blkid.file_hash = data.file_hash;
  if (end_lt) {
    *end_lt = data.end_lt;
  }
  return true;
}

bool check_old_mc_block_id(vm::Dictionary* prev_blocks_dict, const ton::BlockIdExt& blkid) {
  return prev_blocks_dict && check_old_mc_block_id(*prev_blocks_dict, blkid);
}

bool check_old_mc_block_id(vm::Dictionary& prev_blocks_dict, const ton::BlockIdExt& blkid) {
  if (!blkid.id.is_masterchain_ext()) {
    return false;
  }
  auto val = prev_blocks_dict.lookup(td::BitArray<32>{blkid.id.seqno});
  block::gen::ExtBlkRef::Record data;
  if (!(val.not_null() && ::tlb::csr_unpack(std::move(val), data) && data.seq_no == blkid.id.seqno)) {
    return false;
  }
  return blkid.root_hash == data.root_hash && blkid.file_hash == data.file_hash;
}

}  // namespace block
