#pragma once
#include "common/refcnt.hpp"
#include "vm/cells.h"

#include "td/utils/Context.h"

namespace vm {
using td::Ref;

class VmStateInterface : public td::Context<VmStateInterface> {
 public:
  virtual ~VmStateInterface() = default;
  virtual Ref<vm::Cell> load_library(
      td::ConstBitPtr hash) = 0;  // may throw a dictionary exception; returns nullptr if library is not found
  virtual void register_cell_load(){};
  virtual void register_cell_create(){};
};

}  // namespace vm
