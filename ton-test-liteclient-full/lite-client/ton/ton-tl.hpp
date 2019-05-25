#pragma once

#include "ton-types.h"
#include "auto/tl/ton_api.h"

namespace ton {

static inline tl_object_ptr<ton_api::tonNode_blockIdExt> create_tl_block_id(const BlockIdExt &block_id) {
  return create_tl_object<ton_api::tonNode_blockIdExt>(block_id.id.workchain, block_id.id.shard, block_id.id.seqno,
                                                       Bits256_2_UInt256(block_id.root_hash),
                                                       Bits256_2_UInt256(block_id.file_hash));
}

static inline BlockIdExt create_block_id(const tl_object_ptr<ton_api::tonNode_blockIdExt> &B) {
  return BlockIdExt{B->workchain_, static_cast<td::uint64>(B->shard_), static_cast<BlockSeqno>(B->seqno_),
                    UInt256_2_Bits256(B->root_hash_), UInt256_2_Bits256(B->file_hash_)};
}
static inline BlockIdExt empty_block_id() {
  return BlockIdExt{workchainIdNotYet, 0, 0, UInt256_2_Bits256(td::UInt256::zero()),
                    UInt256_2_Bits256(td::UInt256::zero())};
}

static inline tl_object_ptr<ton_api::tonNode_zeroStateIdExt> create_tl_zero_state_id(const ZeroStateIdExt &id) {
  return create_tl_object<ton_api::tonNode_zeroStateIdExt>(id.workchain, Bits256_2_UInt256(id.root_hash),
                                                           Bits256_2_UInt256(id.file_hash));
}

static inline ZeroStateIdExt create_zero_state_id(tl_object_ptr<ton_api::tonNode_zeroStateIdExt> &B) {
  return ZeroStateIdExt{B->workchain_, UInt256_2_Bits256(B->root_hash_), UInt256_2_Bits256(B->file_hash_)};
}

}  // namespace ton
