#pragma once
#include "td/actor/PromiseFuture.h"

namespace td {
namespace detail {
class MultiPromiseImpl;
}

class MultiPromise {
  using Impl = detail::MultiPromiseImpl;

 public:
  struct Options {
    Options() {
    }
    bool ignore_errors{false};
  };
  explicit MultiPromise(Options options = Options{}) : options_(options) {
  }

  struct InitGuard {
   public:
    InitGuard() = default;
    InitGuard(std::shared_ptr<Impl> impl) : impl_(std::move(impl)) {
    }
    InitGuard(InitGuard &&other) = default;
    InitGuard &operator=(InitGuard &&other) = default;
    InitGuard(const InitGuard &other) = delete;
    InitGuard &operator=(const InitGuard &other) = delete;

    void add_promise(Promise<> promise);
    Promise<> get_promise();
    bool empty() const;
    explicit operator bool() const;

   private:
    std::shared_ptr<Impl> impl_;
  };

  TD_WARN_UNUSED_RESULT InitGuard init_guard();
  TD_WARN_UNUSED_RESULT InitGuard add_promise_or_init(Promise<> promise);

 private:
  Options options_;
  std::weak_ptr<Impl> impl_;
};
}  // namespace td
