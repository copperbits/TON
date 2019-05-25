#pragma once

#include "ton/ton-types.h"
#include "td/actor/PromiseFuture.h"
#include "td/actor/actor.h"

namespace ton {

class ValidatorManager;

struct BlockHandleImpl {
 public:
  virtual BlockIdExt id() const = 0;
  virtual bool received() const = 0;
  virtual bool inited_next_left() const = 0;
  virtual bool inited_next_right() const = 0;
  virtual bool inited_next() const = 0;
  virtual bool inited_prev_left() const = 0;
  virtual bool inited_prev_right() const = 0;
  virtual bool inited_prev() const = 0;
  virtual bool inited_logical_time() const = 0;
  virtual bool inited_proof() const = 0;
  virtual bool inited_proof_link() const = 0;
  virtual bool inited_signatures() const = 0;
  virtual bool inited_split_after() const = 0;
  virtual bool inited_merge_before() const = 0;
  virtual bool split_after() const = 0;
  virtual bool merge_before() const = 0;
  virtual bool inited_state_root_hash() const = 0;
  virtual bool received_state() const = 0;
  virtual bool inited_state_file() const = 0;
  virtual bool inited_state_boc() const = 0;
  virtual bool need_flush() const = 0;
  virtual bool is_zero() const = 0;
  virtual bool is_archived() const = 0;
  virtual std::vector<BlockIdExt> prev() const = 0;
  virtual BlockIdExt one_prev(bool left) const = 0;
  virtual std::vector<BlockIdExt> next() const = 0;
  virtual BlockIdExt one_next(bool left) const = 0;
  virtual RootHash state() const = 0;
  virtual td::uint32 version() const = 0;

  virtual bool processed() const = 0;
  virtual void set_processed() = 0;

  virtual void flush(td::actor::ActorId<ton::ValidatorManager> manager, std::shared_ptr<BlockHandleImpl> self,
                     td::Promise<td::Unit> promise) = 0;
  virtual void flushed_upto(td::uint32 version) = 0;
  virtual void set_logical_time(LogicalTime lt) = 0;
  virtual LogicalTime logical_time() const = 0;
  virtual void set_proof() = 0;
  virtual void set_proof_link() = 0;
  virtual void set_signatures() = 0;
  virtual void set_next(BlockIdExt next) = 0;
  virtual void set_prev(BlockIdExt prev) = 0;
  virtual void set_received() = 0;
  virtual void set_split(bool value) = 0;
  virtual void set_merge(bool value) = 0;
  virtual void set_state_root_hash(RootHash hash) = 0;
  virtual void set_state_file() = 0;
  virtual void set_state_boc() = 0;
  virtual void archive() = 0;

  virtual td::BufferSlice serialize() const = 0;

  virtual ~BlockHandleImpl() = default;
};

using BlockHandle = std::shared_ptr<BlockHandleImpl>;

}  // namespace ton
