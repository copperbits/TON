#pragma once

#include "td/utils/common.h"
#include "td/utils/Slice.h"

namespace td {

class Named {
 public:
  Slice get_name() const {
    return name_;
  }
  void set_name(Slice name) {
    name_ = name.str();
  }

 private:
  string name_;
};

}  // namespace td
