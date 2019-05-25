#pragma once
#include "vm/cells/Cell.h"

#include <utility>
#include <functional>

namespace vm {
class MerkleProof {
 public:
  using IsPrunnedFunction = std::function<bool(const Ref<Cell> &)>;

  // works with proofs wrapped in MerkleProof special cell
  // cells must have zero level
  static Ref<Cell> generate(Ref<Cell> cell, IsPrunnedFunction is_prunned);
  static Ref<Cell> generate(Ref<Cell> cell, CellUsageTree *usage_tree);

  // cell must have zero level and must be a MerkleProof
  static Ref<Cell> virtualize(Ref<Cell> cell, int virtualization);

  // works with upwrapped proofs
  // works fine with cell of non-zero level, but this is not supported (yet?) in MerkeProof special cell
  static Ref<Cell> generate_raw(Ref<Cell> cell, IsPrunnedFunction is_prunned);
  static Ref<Cell> generate_raw(Ref<Cell> cell, CellUsageTree *usage_tree);
  static Ref<Cell> virtualize_raw(Ref<Cell> cell, Cell::VirtualizationParameters virt);
};
}  // namespace vm
