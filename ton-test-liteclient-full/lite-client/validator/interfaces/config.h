#pragma once

#include "ton/ton-types.h"
#include "crypto/common/refcnt.hpp"

namespace ton {

namespace validator {

class McShardHash : public td::CntObject {
 public:
  enum class FsmState { fsm_none, fsm_split, fsm_merge };
  virtual BlockIdExt top_block_id() const = 0;
  virtual LogicalTime start_lt() const = 0;
  virtual LogicalTime end_lt() const = 0;
  virtual UnixTime fsm_utime() const = 0;
  virtual FsmState fsm_state() const = 0;
  virtual ShardIdFull shard() const = 0;
  virtual bool before_split() const = 0;
  virtual bool before_merge() const = 0;
};

}  // namespace validator

}  // namespace ton
