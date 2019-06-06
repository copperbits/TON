#pragma once
#include "vm/stack.hpp"

namespace vm {
using td::Ref;

class Box : public td::CntObject {
  mutable StackEntry data_;

 public:
  Box() = default;
  Box(const Box&) = default;
  Box(Box&&) = default;
  template <typename... Args>
  Box(Args... args) : data_{std::move(args...)} {
  }
  ~Box() override = default;
  Box(const StackEntry& data) : data_(data) {
  }
  Box(StackEntry&& data) : data_(std::move(data)) {
  }
  void operator=(const StackEntry& data) const {
    data_ = data;
  }
  void operator=(StackEntry&& data) const {
    data_ = data;
  }
  void set(const StackEntry& data) const {
    data_ = data;
  }
  void set(StackEntry&& data) const {
    data_ = data;
  }
  const StackEntry& get() const {
    return data_;
  }
  void clear() const {
    data_.clear();
  }
  bool empty() const {
    return data_.empty();
  }
};

}  // namespace vm
