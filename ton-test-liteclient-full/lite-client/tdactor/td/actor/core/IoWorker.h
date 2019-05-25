#pragma once

#include "td/actor/core/SchedulerContext.h"
#include "td/actor/core/SchedulerMessage.h"
#include "td/utils/MpscPollableQueue.h"

namespace td {
namespace actor {
namespace core {
class IoWorker {
 public:
  explicit IoWorker(MpscPollableQueue<SchedulerMessage> &queue) : queue_(queue) {
  }

  void start_up();
  void tear_down();

  bool run_once(double timeout);

 private:
  MpscPollableQueue<SchedulerMessage> &queue_;
};
}  // namespace core
}  // namespace actor
}  // namespace td
