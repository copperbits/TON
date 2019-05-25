#include "vm/cells/Cell.h"
#include "vm/cells/VirtualCell.h"
#include "vm/cells/DataCell.h"

#include <iostream>

namespace vm {
td::Status Cell::check_equals_unloaded(const Ref<Cell>& other) const {
  auto level_mask = get_level_mask();
  if (level_mask != other->get_level_mask()) {
    return td::Status::Error("level mismatch");
  }
  auto level = level_mask.get_level();
  for (unsigned i = 0; i <= level; i++) {
    if (!get_level_mask().is_significant(i)) {
      continue;
    }
    if (get_hash(i) != other->get_hash(i)) {
      return td::Status::Error("hash mismatch");
    }
  }
  for (unsigned i = 0; i <= level; i++) {
    if (!get_level_mask().is_significant(i)) {
      continue;
    }
    if (get_depth(i) != other->get_depth(i)) {
      return td::Status::Error("depth mismatch");
    }
  }
  return td::Status::OK();
}

Ref<Cell> Cell::virtualize(VirtualizationParameters virt) const {
  return VirtualCell::create(virt, Ref<Cell>(this));
}

std::ostream& operator<<(std::ostream& os, const Cell& c) {
  return os << c.get_hash().to_hex();
}

}  // namespace vm
