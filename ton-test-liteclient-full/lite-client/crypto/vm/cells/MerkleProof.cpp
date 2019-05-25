#include "vm/cells/MerkleProof.h"
#include "vm/cells/CellBuilder.h"
#include "vm/cells/CellSlice.h"

#include <absl/container/flat_hash_set.h>
#include <absl/container/flat_hash_map.h>

namespace vm {
namespace detail {
class MerkleProofImpl {
 public:
  explicit MerkleProofImpl(MerkleProof::IsPrunnedFunction is_prunned) : is_prunned_(std::move(is_prunned)) {
  }
  explicit MerkleProofImpl(CellUsageTree *usage_tree) : usage_tree_(usage_tree) {
  }

  Ref<Cell> create_from(Ref<Cell> cell) {
    if (!is_prunned_) {
      CHECK(usage_tree_);
      dfs_usage_tree(cell, usage_tree_->root_id());
      is_prunned_ = [this](const Ref<Cell> &cell) { return visited_cells_.count(cell->get_hash()) == 0; };
    }
    return dfs(cell, cell->get_level());
  }

 private:
  using Key = std::pair<Cell::Hash, int>;
  absl::flat_hash_map<Key, Ref<Cell>> cells_;
  absl::flat_hash_set<Cell::Hash> visited_cells_;
  CellUsageTree *usage_tree_{nullptr};
  MerkleProof::IsPrunnedFunction is_prunned_;

  void dfs_usage_tree(Ref<Cell> cell, CellUsageTree::NodeId node_id) {
    if (!usage_tree_->is_loaded(node_id)) {
      return;
    }
    visited_cells_.insert(cell->get_hash());
    CellSlice cs(NoVm(), cell);
    for (unsigned i = 0; i < cs.size_refs(); i++) {
      dfs_usage_tree(cs.prefetch_ref(i), usage_tree_->get_child(node_id, i));
    }
  }

  Ref<Cell> dfs(Ref<Cell> cell, int merkle_depth) {
    CHECK(cell.not_null());
    Key key{cell->get_hash(), merkle_depth};
    {
      auto it = cells_.find(key);
      if (it != cells_.end()) {
        CHECK(it->second.not_null());
        return it->second;
      }
    }

    if (is_prunned_(cell)) {
      auto res = CellBuilder::create_pruned_branch(cell, merkle_depth + 1);
      CHECK(res.not_null());
      cells_.emplace(key, res);
      return res;
    }
    CellSlice cs(NoVm(), cell);
    int children_merkle_depth = cs.child_merkle_depth(merkle_depth);
    CellBuilder cb;
    cb.store_bits(cs.fetch_bits(cs.size()));
    for (unsigned i = 0; i < cs.size_refs(); i++) {
      cb.store_ref(dfs(cs.prefetch_ref(i), children_merkle_depth));
    }
    auto res = cb.finalize(cs.is_special());
    CHECK(res.not_null());
    cells_.emplace(key, res);
    return res;
  }
};
}  // namespace detail

Ref<Cell> MerkleProof::generate_raw(Ref<Cell> cell, IsPrunnedFunction is_prunned) {
  ;
  return detail::MerkleProofImpl(is_prunned).create_from(cell);
}

Ref<Cell> MerkleProof::generate_raw(Ref<Cell> cell, CellUsageTree *usage_tree) {
  return detail::MerkleProofImpl(usage_tree).create_from(cell);
}

Ref<Cell> MerkleProof::virtualize_raw(Ref<Cell> cell, Cell::VirtualizationParameters virt) {
  return cell->virtualize(virt);
}

Ref<Cell> MerkleProof::generate(Ref<Cell> cell, IsPrunnedFunction is_prunned) {
  int cell_level = cell->get_level();
  if (cell_level != 0) {
    return {};
  }
  auto raw = generate_raw(std::move(cell), is_prunned);
  return CellBuilder::create_merkle_proof(std::move(raw));
}

Ref<Cell> MerkleProof::generate(Ref<Cell> cell, CellUsageTree *usage_tree) {
  int cell_level = cell->get_level();
  if (cell_level != 0) {
    return {};
  }
  auto raw = generate_raw(std::move(cell), usage_tree);
  return CellBuilder::create_merkle_proof(std::move(raw));
}

Ref<Cell> MerkleProof::virtualize(Ref<Cell> cell, int virtualization) {
  td::uint8 level = static_cast<td::uint8>(cell->get_level());
  if (level != 0) {
    return {};
  }
  CellSlice cs(NoVm(), std::move(cell));
  if (cs.special_type() != Cell::SpecialType::MerkleProof) {
    return {};
  }
  cs.prefetch_ref(0);
  return virtualize_raw(cs.prefetch_ref(0), {level, static_cast<td::uint8>(virtualization)});
}
}  // namespace vm
