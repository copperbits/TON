#pragma once
#include "vm/cells/Cell.h"

namespace vm {
class VirtualCell : public Cell {
 private:
  struct PrivateTag {};

 public:
  static Ref<Cell> create(VirtualizationParameters virt, Ref<Cell> cell) {
    if (cell->get_level() <= virt.get_level()) {
      return cell;
    }
    return Ref<VirtualCell>{true, virt, std::move(cell), PrivateTag{}};
  }

  VirtualCell(VirtualizationParameters virt, Ref<Cell> cell, PrivateTag) : virt_(virt), cell_(std::move(cell)) {
    CHECK(cell_->get_virtualization() <= virt_.get_virtualization());
  }

  // load interface
  td::Result<LoadedCell> load_cell() const override {
    TRY_RESULT(loaded_cell, cell_->load_cell());
    loaded_cell.virt = loaded_cell.virt.apply(virt_);
    return std::move(loaded_cell);
  }

  Ref<Cell> virtualize(VirtualizationParameters virt) const override {
    auto new_virt = virt_.apply(virt);
    if (new_virt == virt_) {
      return Ref<Cell>(this);
    }
    return create(new_virt, cell_);
  }

  td::uint32 get_virtualization() const override {
    return virt_.get_virtualization();
  }

  bool is_loaded() const override {
    return cell_->is_loaded();
  }

  // hash and level
  LevelMask get_level_mask() const override {
    return cell_->get_level_mask().apply(virt_.get_level());
  }

 protected:
  const Hash do_get_hash(td::uint32 level) const override {
    return cell_->get_hash(fix_level(level));
  }
  td::uint16 do_get_depth(td::uint32 level) const override {
    return cell_->get_depth(fix_level(level));
  }

 private:
  VirtualizationParameters virt_;
  Ref<Cell> cell_;

  int fix_level(int level) const {
    return get_level_mask().apply(level).get_level();
  }
};
}  // namespace vm
