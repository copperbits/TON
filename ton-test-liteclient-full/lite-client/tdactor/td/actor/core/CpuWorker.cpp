#include "td/actor/core/CpuWorker.h"

#include "td/actor/core/ActorExecutor.h"
#include "td/actor/core/SchedulerContext.h"

namespace td {
namespace actor {
namespace core {
void CpuWorker::run() {
  auto thread_id = get_thread_id();
  auto &dispatcher = *SchedulerContext::get();

  int yields = 0;
  while (true) {
    SchedulerMessage message;
    if (queue_.try_pop(message, thread_id)) {
      if (!message) {
        return;
      }
      ActorExecutor executor(*message, dispatcher, ActorExecutor::Options().with_from_queue());
      yields = waiter_.stop_wait(yields, thread_id);
    } else {
      yields = waiter_.wait(yields, thread_id);
    }
  }
}
}  // namespace core
}  // namespace actor
}  // namespace td
