#include "LevelMask.h"

namespace vm {
namespace detail {
td::StringBuilder& operator<<(td::StringBuilder& sb, LevelMask level_mask) {
  sb << "LevelMask{";
  for (int i = 0, level = level_mask.get_level(); i < level; i++) {
    sb << "01"[(level_mask.get_mask() >> i) % 2];
  }
  sb << "}";
  return sb;
}
}  // namespace detail
}  // namespace vm
