#include "td/actor/actor.h"

namespace ton {

template <typename T>
class DelayedAction : public td::actor::Actor {
 public:
  DelayedAction(T promise) : promise_(std::move(promise)) {
  }
  void set_timer(td::Timestamp t) {
    alarm_timestamp() = t;
  }
  void alarm() override {
    promise_();
    stop();
  }

  static void create(T promise, td::Timestamp t) {
    auto A = td::actor::create_actor<DelayedAction>("delayed", std::move(promise));
    td::actor::send_closure(A, &DelayedAction::set_timer, t);
    A.release();
  }

 private:
  T promise_;
};

template <typename T>
void delay_action(T promise, td::Timestamp timeout) {
  DelayedAction<T>::create(std::move(promise), timeout);
}
}  // namespace ton
