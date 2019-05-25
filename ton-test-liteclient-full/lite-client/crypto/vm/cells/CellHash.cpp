#include "vm/cells/CellHash.h"

#include "td/utils/StringBuilder.h"
#include "td/utils/Slice.h"

namespace vm {
td::StringBuilder &operator<<(td::StringBuilder &sb, const CellHash &hash) {
  return sb << hash.to_hex();
}
}  // namespace vm
