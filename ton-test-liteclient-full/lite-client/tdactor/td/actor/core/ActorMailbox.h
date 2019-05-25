#pragma once

#include "td/actor/core/ActorMessage.h"
#include "td/utils/MpscLinkQueue.h"

namespace td {
namespace actor {
namespace core {
class ActorMailbox {
 public:
  ActorMailbox() = default;
  ActorMailbox(const ActorMailbox &) = delete;
  ActorMailbox &operator=(const ActorMailbox &) = delete;
  ActorMailbox(ActorMailbox &&other) = delete;
  ActorMailbox &operator=(ActorMailbox &&other) = delete;
  ~ActorMailbox() {
    clear();
  }
  void push(ActorMessage message) {
    queue_.push(std::move(message));
  }
  void push_unsafe(ActorMessage message) {
    queue_.push_unsafe(std::move(message));
  }

  td::MpscLinkQueue<ActorMessage>::Reader &reader() {
    return reader_;
  }

  void pop_all() {
    queue_.pop_all(reader_);
  }
  void pop_all_unsafe() {
    queue_.pop_all_unsafe(reader_);
  }

  void clear() {
    pop_all();
    while (reader_.read()) {
      // skip
    }
  }

 private:
  td::MpscLinkQueue<ActorMessage> queue_;
  td::MpscLinkQueue<ActorMessage>::Reader reader_;
};
}  // namespace core
}  // namespace actor
}  // namespace td
