#pragma once

#include "vm/cells/CellTraits.h"

#include "td/utils/int_types.h"
#include "td/utils/logging.h"

namespace vm {
class CellUsageTree : public std::enable_shared_from_this<CellUsageTree> {
 public:
  using NodeId = td::uint32;

  struct NodePtr {
   public:
    NodePtr() = default;
    NodePtr(std::weak_ptr<CellUsageTree> tree_weak, NodeId node_id)
        : tree_weak_(std::move(tree_weak)), node_id_(node_id) {
    }
    bool empty() const {
      return node_id_ == 0 || tree_weak_.expired();
    }

    bool on_load() const;
    NodePtr create_child(unsigned ref_id) const;
    bool mark_path(CellUsageTree* master_tree) const;
    bool is_from_tree(CellUsageTree* master_tree) const;

   private:
    std::weak_ptr<CellUsageTree> tree_weak_;
    NodeId node_id_{0};
  };

  NodePtr root_ptr();
  NodeId root_id() const;
  bool is_loaded(NodeId node_id) const;
  bool has_mark(NodeId node_id) const;
  void set_mark(NodeId node_id, bool mark = true);
  void mark_path(NodeId node_id);
  NodeId get_parent(NodeId node_id);
  NodeId get_child(NodeId node_id, unsigned ref_id);
  void set_use_mark_for_is_loaded(bool use_mark = true);
  NodeId create_child(NodeId node_id, unsigned ref_id);

 private:
  struct Node {
    bool is_loaded{false};
    bool has_mark{false};
    NodeId parent{0};
    std::array<td::uint32, CellTraits::max_refs> children{};
  };
  bool use_mark_{false};
  std::vector<Node> nodes_{2};

  void on_load(NodeId node_id);
  NodeId create_node(NodeId parent);
};
}  // namespace vm
