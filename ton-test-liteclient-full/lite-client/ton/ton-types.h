#pragma once

#include "crypto/common/bitstring.h"
#include "td/utils/int_types.h"
#include "td/utils/Slice.h"
#include "td/utils/buffer.h"
#include "td/utils/bits.h"

namespace ton {

using WorkchainId = td::int32;
constexpr WorkchainId workchainIdNotYet = (1U << 31);
using ShardId = td::uint64;  // prefix a of length l encoded as ((2 * a + 1) << (63 - l))
using AccountIdPrefix = td::uint64;
using BlockSeqno = td::uint32;      // usually >= 1; 0 used to indicate the initial state ("zerostate")
using Bits256 = td::BitArray<256>;  // was: td::UInt256
using BlockHash = Bits256;
using RootHash = Bits256;
using FileHash = Bits256;
using NodeIdShort = Bits256;    // compatible with AdnlNodeIdShort
using StdSmcAddress = Bits256;  // masterchain / base workchain smart-contract addresses
using UnixTime = td::uint32;
using LogicalTime = td::uint64;
using ValidatorWeight = td::uint64;  // was td::uint32 before
using CatchainSeqno = td::uint32;

using ValidatorSessionId = td::UInt256;

constexpr WorkchainId masterchainId = -1, basechainId = 0, workchainInvalid = 0x80000000;
constexpr ShardId shardIdAll = (1ULL << 63);

static inline int shard_pfx_len(ShardId shard) {
  return shard ? 63 - td::count_trailing_zeroes_non_zero64(shard) : 0;
}

struct ShardIdFull {
  WorkchainId workchain;
  ShardId shard;
  ShardIdFull() : workchain(workchainInvalid) {
  }
  explicit ShardIdFull(WorkchainId workchain) : workchain(workchain), shard(shardIdAll) {
  }
  ShardIdFull(WorkchainId workchain, ShardId shard) : workchain(workchain), shard(shard) {
  }
  bool operator==(const ShardIdFull& other) const {
    return workchain == other.workchain && shard == other.shard;
  }
  bool operator!=(const ShardIdFull& other) const {
    return workchain != other.workchain || shard != other.shard;
  }
  bool operator<(const ShardIdFull& other) const {
    return workchain < other.workchain || (workchain == other.workchain && shard < other.shard);
  }
  bool is_valid() const {
    return workchain != workchainInvalid;
  }
  bool is_valid_ext() const {
    return is_valid() && shard;
  }
  bool is_masterchain() const {
    return workchain == masterchainId;
  }
  bool is_split() const {
    return shard != shardIdAll;
  }
  bool is_masterchain_ext() const {
    return is_masterchain() && shard == shardIdAll;
  }
  int pfx_len() const {
    return shard_pfx_len(shard);
  }
  ShardIdFull operator+(int delta) const {
    return ShardIdFull{workchain, shard + delta};
  }
  ShardIdFull operator-(int delta) const {
    return ShardIdFull{workchain, shard - delta};
  }
  std::string to_str() const {
    char buffer[64];
    return std::string{buffer, (unsigned)snprintf(buffer, 63, "(%d,%016llx)", workchain, (unsigned long long)shard)};
  }
};

struct AccountIdPrefixFull {
  WorkchainId workchain;
  AccountIdPrefix account_id_prefix;
  AccountIdPrefixFull() : workchain(workchainInvalid) {
  }
  AccountIdPrefixFull(WorkchainId workchain, AccountIdPrefix prefix) : workchain(workchain), account_id_prefix(prefix) {
  }
  bool operator==(const AccountIdPrefixFull& other) const {
    return workchain == other.workchain && account_id_prefix == other.account_id_prefix;
  }
  bool operator!=(const AccountIdPrefixFull& other) const {
    return workchain != other.workchain || account_id_prefix != other.account_id_prefix;
  }
  bool operator<(const AccountIdPrefixFull& other) const {
    return workchain < other.workchain || (workchain == other.workchain && account_id_prefix < other.account_id_prefix);
  }
  bool is_valid() const {
    return workchain != workchainInvalid;
  }
  bool is_masterchain() const {
    return workchain == masterchainId;
  }
  ShardIdFull as_leaf_shard() const {
    return ShardIdFull{workchain, account_id_prefix | 1};
  }
  std::string to_str() const {
    char buffer[64];
    return std::string{
        buffer, (unsigned)snprintf(buffer, 63, "(%d,%016llx)", workchain, (unsigned long long)account_id_prefix)};
  }
};

struct BlockId {
  WorkchainId workchain;
  BlockSeqno seqno;
  ShardId shard;

  BlockId(WorkchainId workchain, ShardId shard, BlockSeqno seqno) : workchain(workchain), seqno(seqno), shard(shard) {
  }
  BlockId(ShardIdFull shard, BlockSeqno seqno) : workchain(shard.workchain), seqno(seqno), shard(shard.shard) {
  }
  BlockId() : workchain(workchainInvalid) {
  }
  explicit operator ShardIdFull() const {
    return ShardIdFull{workchain, shard};
  }
  bool is_valid() const {
    return workchain != workchainInvalid;
  }
  bool is_valid_ext() const {
    return is_valid() && shard;
  }
  bool is_masterchain() const {
    return workchain == masterchainId;
  }
  bool is_masterchain_ext() const {
    return is_masterchain() && shard == shardIdAll;
  }
  bool is_valid_full() const {
    return is_valid() && shard && !(shard & 7) && seqno <= 0x7fffffff && (!is_masterchain() || shard == shardIdAll);
  }
  void invalidate() {
    workchain = workchainInvalid;
  }
  void invalidate_clear() {
    invalidate();
    shard = 0;
    seqno = 0;
  }
  bool operator==(const BlockId& other) const {
    return workchain == other.workchain && seqno == other.seqno && shard == other.shard;
  }
  bool operator!=(const BlockId& other) const {
    return !(workchain == other.workchain && seqno == other.seqno && shard == other.shard);
  }
  bool operator<(const BlockId& other) const {
    return workchain < other.workchain ||
           (workchain == other.workchain && (seqno < other.seqno || (seqno == other.seqno && shard < other.shard)));
  }
  bool operator<(const ShardIdFull& other) const {
    return workchain < other.workchain || (workchain == other.workchain && shard < other.shard);
  }
  int pfx_len() const {
    return shard_pfx_len(shard);
  }
  std::string to_str() const {
    char buffer[64];
    return std::string{buffer,
                       (unsigned)snprintf(buffer, 63, "(%d,%016llx,%u)", workchain, (unsigned long long)shard, seqno)};
  }
};

inline bool operator<(const ShardIdFull& x, const BlockId& y) {
  return x.workchain < y.workchain || (x.workchain == y.workchain && x.shard < y.shard);
}

struct BlockIdExt {
  BlockId id;
  RootHash root_hash;
  FileHash file_hash;
  BlockIdExt(WorkchainId workchain, ShardId shard, BlockSeqno seqno, const RootHash& root_hash,
             const FileHash& file_hash)
      : id{workchain, shard, seqno}, root_hash(root_hash), file_hash(file_hash) {
  }
  BlockIdExt(BlockId id, const RootHash& root_hash, const FileHash& file_hash)
      : id(id), root_hash(root_hash), file_hash(file_hash) {
  }
  BlockIdExt(BlockId id, const FileHash& file_hash) : id(id), file_hash(file_hash) {
    root_hash.set_zero();
  }
  explicit BlockIdExt(BlockId id) : id(id) {
    root_hash.set_zero();
    file_hash.set_zero();
  }
  BlockIdExt() : id(workchainIdNotYet, 0, 0) {
  }
  void invalidate() {
    id.invalidate();
  }
  void invalidate_clear() {
    id.invalidate_clear();
    root_hash.set_zero();
    file_hash.set_zero();
  }
  bool operator==(const BlockIdExt& b) const {
    return id == b.id && root_hash == b.root_hash && file_hash == b.file_hash;
  }
  bool operator!=(const BlockIdExt& b) const {
    return !(id == b.id && root_hash == b.root_hash && file_hash == b.file_hash);
  }
  bool operator<(const BlockIdExt& b) const {
    return id < b.id || (id == b.id && file_hash < b.file_hash);
  }
  ShardIdFull shard_full() const {
    return ShardIdFull(id);
  }
  explicit operator ShardIdFull() const {
    return ShardIdFull(id);
  }
  bool is_valid() const {
    return id.is_valid();
  }
  bool is_valid_ext() const {
    return id.is_valid_ext();
  }
  bool is_valid_full() const {
    return id.is_valid_full() && !root_hash.is_zero() && !file_hash.is_zero();
  }
  bool is_masterchain() const {
    return id.is_masterchain();
  }
  std::string to_str() const {
    return id.to_str() + ':' + root_hash.to_hex() + ':' + file_hash.to_hex();
  }
};

struct ZeroStateIdExt {
  WorkchainId workchain{workchainInvalid};
  RootHash root_hash;
  FileHash file_hash;
  ZeroStateIdExt() = default;
  ZeroStateIdExt(WorkchainId wc, const RootHash& rhash, const FileHash& fhash)
      : workchain(wc), root_hash(rhash), file_hash(fhash) {
  }
  bool operator==(const ZeroStateIdExt& b) const {
    return workchain == b.workchain && root_hash == b.root_hash && file_hash == b.file_hash;
  }
  bool operator!=(const ZeroStateIdExt& b) const {
    return !(workchain == b.workchain && root_hash == b.root_hash && file_hash == b.file_hash);
  }
  bool operator<(const ZeroStateIdExt& b) const {
    return file_hash < b.file_hash;
  }
  bool is_valid() const {
    return workchain != workchainInvalid;
  }
  bool is_masterchain() const {
    return workchain == masterchainId;
  }
  bool is_valid_full() const {
    return is_valid() && !root_hash.is_zero() && !file_hash.is_zero();
  }
  std::string to_str() const {
    return PSTRING() << workchain << ':' << root_hash.to_hex() << ':' << file_hash.to_hex();
  }
};

//enum class BlockStatus { block_none, block_prevalidated, block_validated, block_applied };

struct BlockSignature {
  NodeIdShort node;
  td::BufferSlice signature;
};

struct ReceivedBlock {
  BlockIdExt id;
  td::BufferSlice data;
};

struct BlockBroadcast {
  BlockIdExt block_id;
  std::vector<BlockSignature> signatures;
  BlockIdExt masterchain_block_id;
  CatchainSeqno catchain_seqno;
  td::uint32 validator_set_hash;
  td::BufferSlice data;
  td::BufferSlice proof;
};

// represents (the contents of) a block
/*struct Block {
  BlockIdExt id;
  BlockStatus status;
  td::BufferSlice data;
  td::BufferSlice proof;
  std::vector<BlockSignature> signatures;
};*/

// represents (the complete final) state of a block
// if id.seqno == 0, represents the initial state ("zerostate") of a shardchain
struct BlockState {
  BlockId id;
  RootHash root_hash;
  FileHash file_hash;
  td::BufferSlice data;
};

struct BlockCandidate {
  BlockIdExt id;
  FileHash collated_file_hash;
  td::BufferSlice data;
  td::BufferSlice collated_data;

  BlockCandidate clone() const {
    return BlockCandidate{id, collated_file_hash, data.clone(), collated_data.clone()};
  }
};

inline td::UInt256 Bits256_2_UInt256(const Bits256& x) {
  td::UInt256 r;
  std::memcpy(r.raw, x.data(), 32);
  return r;
}

inline Bits256 UInt256_2_Bits256(const td::UInt256& x) {
  return Bits256(x.raw);
}

struct Ed25519_PrivateKey {
  Bits256 _privkey;
  explicit Ed25519_PrivateKey(const Bits256& x) : _privkey(x) {
  }
  explicit Ed25519_PrivateKey(const td::ConstBitPtr x) : _privkey(x) {
  }
  explicit Ed25519_PrivateKey(const td::UInt256& x) : _privkey(x.raw) {
  }
  Bits256 as_bits256() const {
    return _privkey;
  }
  operator Bits256() const {
    return _privkey;
  }
  td::UInt256 as_uint256() const {
    return Bits256_2_UInt256(_privkey);
  }
  operator td::UInt256() const {
    return Bits256_2_UInt256(_privkey);
  }
};

struct Ed25519_PublicKey {
  Bits256 _pubkey;
  explicit Ed25519_PublicKey(const Bits256& x) : _pubkey(x) {
  }
  explicit Ed25519_PublicKey(const td::ConstBitPtr x) : _pubkey(x) {
  }
  explicit Ed25519_PublicKey(const td::UInt256& x) : _pubkey(x.raw) {
  }
  Bits256 as_bits256() const {
    return _pubkey;
  }
  operator Bits256() const {
    return _pubkey;
  }
  td::UInt256 as_uint256() const {
    return Bits256_2_UInt256(_pubkey);
  }
  operator td::UInt256() const {
    return Bits256_2_UInt256(_pubkey);
  }
};

};  // namespace ton
