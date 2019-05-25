#pragma once

namespace td {

template <class T, T empty_val = T()>
class MovableValue {
 public:
  MovableValue() = default;
  MovableValue(T val) : val_(val) {
  }
  MovableValue(MovableValue &&other) : val_(other.val_) {
    other.clear();
  }
  MovableValue &operator=(MovableValue &&other) {
    val_ = other.val_;
    other.clear();
    return *this;
  }
  MovableValue(const MovableValue &) = delete;
  MovableValue &operator=(const MovableValue &) = delete;
  ~MovableValue() = default;

  void clear() {
    val_ = empty_val;
  }
  const T &get() const {
    return val_;
  }

 private:
  T val_ = empty_val;
};

}  // namespace td
