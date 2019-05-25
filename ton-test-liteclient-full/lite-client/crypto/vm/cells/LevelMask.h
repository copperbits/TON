#pragma once

#include "td/utils/int_types.h"
#include "td/utils/bits.h"

namespace td {
class StringBuilder;
}

namespace vm {
namespace detail {
class LevelMask {
 public:
  explicit LevelMask(td::uint32 new_mask = 0) : mask_(new_mask) {
  }
  td::uint32 get_mask() const {
    return mask_;
  }
  td::uint32 get_level() const {
    return 32 - td::count_leading_zeroes32(mask_);
  }
  td::uint32 get_hash_i() const {
    return td::count_bits32(mask_);
  }
  td::uint32 get_hashes_count() const {
    return get_hash_i() + 1;
  }
  LevelMask apply(td::uint32 level) const {
    DCHECK(level < 32);
    return LevelMask{mask_ & ((1u << level) - 1)};
  }
  LevelMask apply_or(LevelMask other) const {
    return LevelMask{mask_ | other.mask_};
  }
  LevelMask shift_right() const {
    return LevelMask{mask_ >> 1};
  }
  bool is_significant(td::uint32 level) const {
    DCHECK(level < 32);
    bool res = level == 0 || ((mask_ >> (level - 1)) % 2 != 0);
    CHECK(res == (apply(level).get_level() == level));
    return res;
  }

  bool operator==(const LevelMask& other) const {
    return mask_ == other.mask_;
  }
  bool operator!=(const LevelMask& other) const {
    return !(*this == other);
  }

  static LevelMask one_level(td::uint32 level) {
    DCHECK(level < 32);
    if (level == 0) {
      return LevelMask(0);
    }
    return LevelMask(1 << (level - 1));
  }

 private:
  td::uint32 mask_;
};
td::StringBuilder& operator<<(td::StringBuilder& sb, LevelMask level_mask);
}  // namespace detail
}  // namespace vm
