#pragma once
#include "td/actor/common.h"
#include "td/actor/ActorId.h"

namespace td {
namespace actor {
template <class ActorType>
class ActorOwn {
 public:
  using ActorT = ActorType;
  ActorOwn() = default;
  explicit ActorOwn(ActorId<ActorType> id) : id_(std::move(id)) {
  }
  template <class OtherActorType>
  explicit ActorOwn(ActorId<OtherActorType> id) : id_(std::move(id)) {
  }
  template <class OtherActorType>
  ActorOwn(ActorOwn<OtherActorType> &&other) : id_(other.release()) {
  }
  template <class OtherActorType>
  ActorOwn &operator=(ActorOwn<OtherActorType> &&other) {
    reset(other.release());
    return *this;
  }
  ActorOwn(ActorOwn &&other) : id_(other.release()) {
  }
  ActorOwn &operator=(ActorOwn &&other) {
    reset(other.release());
    return *this;
  }
  ActorOwn(const ActorOwn &) = delete;
  ActorOwn &operator=(const ActorOwn &) = delete;
  ~ActorOwn() {
    reset();
  }

  bool empty() const {
    return id_.empty();
  }
  bool is_alive() const {
    return id_.is_alive();
  }
  ActorId<ActorType> get() const {
    return id_;
  }
  ActorType &get_actor_unsafe() const {
    return (*this)->get_actor_unsafe();
  }
  ActorId<ActorType> release() {
    return std::move(id_);
  }
  void reset(ActorId<ActorType> other = ActorId<ActorType>()) {
    static_assert(sizeof(ActorType) > 0, "Can't use ActorOwn with incomplete type");
    hangup();
    id_ = std::move(other);
  }
  const ActorId<ActorType> *operator->() const {
    return &id_;
  }

  detail::ActorRef as_actor_ref() const {
    CHECK(!empty());
    return detail::ActorRef(*id_.actor_info_ptr(), 0);
  }

 private:
  ActorId<ActorType> id_;
  void hangup() const {
    if (empty()) {
      return;
    }
    detail::send_message(as_actor_ref(), detail::ActorMessageCreator::hangup());
  }
};

template <class ToActorType, class FromActorType>
ActorOwn<ToActorType> actor_dynamic_cast(ActorOwn<FromActorType> from) {
  return ActorOwn<ToActorType>(td::actor::actor_dynamic_cast<ToActorType>(from.release()));
}

}  // namespace actor
}  // namespace td
