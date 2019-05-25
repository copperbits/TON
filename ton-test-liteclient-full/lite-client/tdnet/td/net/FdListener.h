#pragma once

#include "td/actor/actor.h"

#include "td/utils/Observer.h"
#include "td/utils/port/detail/PollableFd.h"

namespace td {
class FdListener : public td::actor::Actor {
 public:
  FdListener(td::PollableFd fd, std::unique_ptr<td::Destructor> guard)
      : fd_(std::move(fd)), fd_ref_(fd_.ref()), guard_(std::move(guard)) {
  }

 private:
  PollableFd fd_;
  PollableFdRef fd_ref_;
  std::unique_ptr<Destructor> guard_;

  void start_up() override;

  void tear_down() override;
};
}  // namespace td
