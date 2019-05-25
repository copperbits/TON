#pragma once

#include "td/utils/Slice.h"

namespace td {

class GitInfo {
 public:
  static CSlice commit();
  static bool is_dirty();
};

}  // namespace td
