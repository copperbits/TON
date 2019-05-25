#pragma once

#include "td/utils/buffer.h"
#include "td/utils/common.h"
#include "td/utils/Slice.h"

namespace td {

bool find_boundary(ChainBufferReader range, Slice boundary, size_t &already_read);

}  // namespace td
