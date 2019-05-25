#pragma once

#include "td/utils/common.h"

namespace td {
namespace detail {
class ThreadIdGuard {
 public:
  ThreadIdGuard();
  ~ThreadIdGuard();
  ThreadIdGuard(const ThreadIdGuard &) = delete;
  ThreadIdGuard &operator=(const ThreadIdGuard &) = delete;
  ThreadIdGuard(ThreadIdGuard &&) = delete;
  ThreadIdGuard &operator=(ThreadIdGuard &&) = delete;

 private:
  int32 thread_id_;
};
}  // namespace detail
}  // namespace td
