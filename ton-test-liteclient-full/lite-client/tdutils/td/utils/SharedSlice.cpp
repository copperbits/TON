#include "td/utils/SharedSlice.h"
#include "td/utils/buffer.h"

namespace td {
td::BufferSlice SharedSlice::clone_as_buffer_slice() const {
  return td::BufferSlice{as_slice().str()};
}
}  // namespace td
