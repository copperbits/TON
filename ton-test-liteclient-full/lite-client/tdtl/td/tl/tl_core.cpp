#include "tl_core.h"

#include <cassert>

namespace td {
namespace tl {

void tl_type::add_constructor(tl_combinator *new_constructor) {
  constructors.push_back(new_constructor);

  assert(constructors.size() <= constructors_num);
}

}  // namespace tl
}  // namespace td
