#pragma once

#include "td/utils/int_types.h"
#include "td/utils/logging.h"

#include <limits>

namespace vm {
namespace detail {
class VirtualizationParameters {
 public:
  static constexpr td::uint8 max_level() {
    return std::numeric_limits<td::uint8>::max();
  }

  VirtualizationParameters() = default;

  VirtualizationParameters(td::uint8 level, td::uint8 virtualization) : level_(level), virtualization_(virtualization) {
    CHECK(virtualization_ != 0 || empty());
  }

  bool empty() const {
    return level_ == max_level() && virtualization_ == 0;
  }

  VirtualizationParameters apply(VirtualizationParameters outer) const {
    if (outer.level_ >= level_) {
      return *this;
    }
    CHECK(virtualization_ <= outer.virtualization_);
    return {outer.level_, outer.virtualization_};
  }

  td::uint8 get_level() const {
    return level_;
  }

  td::uint8 get_virtualization() const {
    return virtualization_;
  }

  bool operator==(const VirtualizationParameters &other) const {
    return level_ == other.level_ && virtualization_ == other.virtualization_;
  }

 private:
  td::uint8 level_ = max_level();
  td::uint8 virtualization_ = 0;
};
inline td::StringBuilder &operator<<(td::StringBuilder &sb, const VirtualizationParameters &virt) {
  return sb << "{level: " << virt.get_level() << ", virtualization: " << virt.get_virtualization() << "}";
}
}  // namespace detail
}  // namespace vm
