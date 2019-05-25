#pragma once

#include "td/utils/common.h"
#include "td/utils/logging.h"

namespace td {
namespace actor {
namespace core {
class SchedulerId {
 public:
  SchedulerId() : id_(-1) {
  }
  explicit SchedulerId(uint8 id) : id_(id) {
  }
  bool is_valid() const {
    return id_ >= 0;
  }
  uint8 value() const {
    CHECK(is_valid());
    return static_cast<uint8>(id_);
  }
  bool operator==(SchedulerId scheduler_id) const {
    return id_ == scheduler_id.id_;
  }

 private:
  int32 id_{0};
};
}  // namespace core
}  // namespace actor
}  // namespace td
