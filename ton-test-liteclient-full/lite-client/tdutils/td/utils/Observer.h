#pragma once

#include "td/utils/common.h"

namespace td {

class ObserverBase {
 public:
  ObserverBase() = default;
  ObserverBase(const ObserverBase &) = delete;
  ObserverBase &operator=(const ObserverBase &) = delete;
  ObserverBase(ObserverBase &&) = delete;
  ObserverBase &operator=(ObserverBase &&) = delete;
  virtual ~ObserverBase() = default;

  virtual void notify() = 0;
};

class Observer : ObserverBase {
 public:
  Observer() = default;
  explicit Observer(unique_ptr<ObserverBase> &&ptr) : observer_ptr_(std::move(ptr)) {
  }

  void notify() override {
    if (observer_ptr_) {
      observer_ptr_->notify();
    }
  }

 private:
  unique_ptr<ObserverBase> observer_ptr_;
};

}  // namespace td
