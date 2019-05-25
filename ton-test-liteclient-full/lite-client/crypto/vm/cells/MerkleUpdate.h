#pragma once
#include "vm/cells/Cell.h"
#include "vm/cells/CellSlice.h"
#include "vm/cells/CellBuilder.h"

#include "td/utils/Status.h"

#include <utility>

namespace vm {
class MerkleUpdate {
 public:
  // from + update == to
  static Ref<Cell> generate(Ref<Cell> from, Ref<Cell> to, CellUsageTree *usage_tree);
  // Returns empty Ref<Cell> if something go wrong. If validate(from).is_ok() and may_apply(from, to).is_ok(), then it
  // must not fail.
  static Ref<Cell> apply(Ref<Cell> from, Ref<Cell> update);

  // check if update is valid
  static TD_WARN_UNUSED_RESULT td::Status validate(Ref<Cell> update);
  // check that hash in from is same as hash stored in update. Do not validate update
  static TD_WARN_UNUSED_RESULT td::Status may_apply(Ref<Cell> from, Ref<Cell> update);

  static Ref<Cell> apply_raw(Ref<Cell> from, Ref<Cell> update_from, Ref<Cell> update_to, td::uint32 from_level,
                             td::uint32 to_level);
  static std::pair<Ref<Cell>, Ref<Cell>> generate_raw(Ref<Cell> from, Ref<Cell> to, CellUsageTree *usage_tree);
  static td::Status validate_raw(Ref<Cell> update_from, Ref<Cell> update_to, td::uint32 from_level,
                                 td::uint32 to_level);

  static Ref<Cell> combine(Ref<Cell> ab, Ref<Cell> bc);
};
}  // namespace vm
