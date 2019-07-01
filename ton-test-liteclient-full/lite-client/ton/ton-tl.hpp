#pragma once

#include "ton-types.h"
#include "auto/tl/ton_api.h"

namespace ton {

static inline tl_object_ptr<ton_api::tonNode_blockIdExt> create_tl_block_id(const BlockIdExt &block_id) {
  return create_tl_object<ton_api::tonNode_blockIdExt>(block_id.id.workchain, block_id.id.shard, block_id.id.seqno,
                                                       block_id.root_hash, block_id.file_hash);
}

static inline BlockIdExt create_block_id(const tl_object_ptr<ton_api::tonNode_blockIdExt> &B) {
  return BlockIdExt{B->workchain_, static_cast<td::uint64>(B->shard_), static_cast<BlockSeqno>(B->seqno_),
                    B->root_hash_, B->file_hash_};
}

static inline tl_object_ptr<ton_api::tonNode_blockId> create_tl_block_id_simple(const BlockId &block_id) {
  return create_tl_object<ton_api::tonNode_blockId>(block_id.workchain, block_id.shard, block_id.seqno);
}

static inline BlockId create_block_id_simple(const tl_object_ptr<ton_api::tonNode_blockId> &B) {
  return BlockId{B->workchain_, static_cast<td::uint64>(B->shard_), static_cast<BlockSeqno>(B->seqno_)};
}

static inline BlockIdExt empty_block_id() {
  return BlockIdExt{workchainIdNotYet, 0, 0, RootHash::zero(), FileHash::zero()};
}

static inline tl_object_ptr<ton_api::tonNode_zeroStateIdExt> create_tl_zero_state_id(const ZeroStateIdExt &id) {
  return create_tl_object<ton_api::tonNode_zeroStateIdExt>(id.workchain, id.root_hash, id.file_hash);
}

static inline ZeroStateIdExt create_zero_state_id(tl_object_ptr<ton_api::tonNode_zeroStateIdExt> &B) {
  return ZeroStateIdExt{B->workchain_, B->root_hash_, B->file_hash_};
}

}  // namespace ton
