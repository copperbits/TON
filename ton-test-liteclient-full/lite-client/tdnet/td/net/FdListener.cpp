#include "td/net/FdListener.h"

namespace td {
void FdListener::start_up() {
  fd_.add_flags(PollFlags::ReadWrite());
  td::actor::SchedulerContext::get()->get_poll().subscribe(std::move(fd_), PollFlags::ReadWrite());
}

void FdListener::tear_down() {
  td::actor::SchedulerContext::get()->get_poll().unsubscribe(fd_ref_);
}
}  // namespace td
