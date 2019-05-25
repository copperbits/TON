#pragma once
#include "common/refcnt.hpp"
#include "common/bitstring.h"

#include "vm/cells/CellHash.h"
#include "vm/cells/CellTraits.h"
#include "vm/cells/CellUsageTree.h"
#include "vm/cells/LevelMask.h"
#include "vm/cells/VirtualizationParameters.h"

#include "td/utils/Status.h"

#include <iostream>

namespace vm {
using td::Ref;
class DataCell;

class Cell : public CellTraits {
 public:
  using LevelMask = detail::LevelMask;
  using VirtualizationParameters = detail::VirtualizationParameters;
  struct LoadedCell {
    Ref<DataCell> data_cell;
    VirtualizationParameters virt;
    CellUsageTree::NodePtr tree_node;  // TODO: inline_vector?
  };

  using Hash = CellHash;
  static_assert(std::is_standard_layout<Hash>::value, "Cell::Hash is not a standard layout type");
  static_assert(sizeof(Hash) == hash_bytes, "Cell::Hash size is not equal to hash_bytes");
  //typedef td::BitArray<hash_bits> hash_t;

  Cell* make_copy() const final {
    throw WriteError();
  }

  // load interface
  virtual td::Result<LoadedCell> load_cell() const = 0;
  virtual Ref<Cell> virtualize(VirtualizationParameters virt) const;
  virtual td::uint32 get_virtualization() const = 0;
  virtual bool is_loaded() const = 0;

  // hash and level
  virtual LevelMask get_level_mask() const = 0;

  // level helper function
  td::uint32 get_level() const {
    return get_level_mask().get_level();
  }

  // hash helper functions
  const Hash get_hash(int level = max_level) const {
    return do_get_hash(level);
  }

  // depth helper function
  td::uint16 get_depth(int level = max_level) const {
    return do_get_depth(level);
  }

  td::Status check_equals_unloaded(const Ref<Cell>& other) const;

 private:
  virtual td::uint16 do_get_depth(td::uint32 level) const = 0;
  virtual const Hash do_get_hash(td::uint32 level) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Cell& c);
}  // namespace vm
