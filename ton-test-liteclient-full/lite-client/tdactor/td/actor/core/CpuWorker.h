#pragma once

#include "td/actor/core/SchedulerMessage.h"

#include "td/utils/MpmcQueue.h"
#include "td/utils/MpmcWaiter.h"

namespace td {
namespace actor {
namespace core {
class CpuWorker {
 public:
  CpuWorker(MpmcQueue<SchedulerMessage> &queue, MpmcWaiter &waiter) : queue_(queue), waiter_(waiter) {
  }
  void run();

 private:
  MpmcQueue<SchedulerMessage> &queue_;
  MpmcWaiter &waiter_;
};
}  // namespace core
}  // namespace actor
}  // namespace td
