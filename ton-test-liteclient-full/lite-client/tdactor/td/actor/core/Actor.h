#pragma once
#include "td/actor/core/ActorInfo.h"

#include "td/utils/SharedObjectPool.h"

namespace td {
namespace actor {
namespace core {
class Actor {
 public:
  Actor() = default;
  Actor(const Actor &) = delete;
  Actor &operator=(const Actor &) = delete;
  Actor(Actor &&other) = delete;
  Actor &operator=(Actor &&other) = delete;
  virtual ~Actor() = default;

  void set_actor_info_ptr(ActorInfoPtr actor_info_ptr) {
    actor_info_ptr_ = std::move(actor_info_ptr);
  }
  const ActorInfoPtr &get_actor_info_ptr() const {
    return actor_info_ptr_;
  }

  td::Unit dummy() {
    return td::Unit();
  }

 protected:
  // Signal handlers
  virtual void start_up() {  // StartUp signal handler
    yield();
  }
  virtual void tear_down() {  // TearDown signal handler (or Kill)
    //noop
  }
  virtual void hangup() {  // HangUp signal handler
    stop();
  }
  virtual void hangup_shared() {  // HangUp signal handler
    loop();
  }
  virtual void wake_up() {  // WakeUp signal handler
    loop();
  }
  virtual void alarm() {  // Alarm signal handler
    loop();
  }

  virtual void loop() {  // default handler
    //noop
  }

  // Useful functions
  void yield() {  // send wakeup signal to itself
    ActorExecuteContext::get()->set_yield();
  }
  void stop() {  // send Kill signal to itself
    ActorExecuteContext::get()->set_stop();
  }
  Timestamp &alarm_timestamp() {
    return ActorExecuteContext::get()->alarm_timestamp();
  }
  Timestamp get_alarm_timestamp() {
    return ActorExecuteContext::get()->get_alarm_timestamp();
  }

  CSlice get_name() {
    return actor_info_ptr_->get_name();
  }
  uint64 get_link_token() {
    return ActorExecuteContext::get()->get_link_token();
  }

  //set context that will be inherited by all childrens
  //void set_context(std::shared_ptr<ActorContext> context);

  //void do_stop();  // process Kill signal immediately

 private:
  friend class ActorExecutor;
  friend class ActorMessageHangup;
  friend class ActorMessageHangupShared;

  ActorInfoPtr actor_info_ptr_;
};

}  // namespace core
}  // namespace actor
}  // namespace td
