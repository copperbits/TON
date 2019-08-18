#pragma once

#include "td/utils/buffer.h"
#include "td/utils/Slice.h"
#include "td/utils/Status.h"

namespace td {

Result<BufferSlice> read_file(CSlice path, int64 size = -1, int64 offset = 0);
Result<string> read_file_str(CSlice path, int64 size = -1, int64 offset = 0);

Status copy_file(CSlice from, CSlice to, int64 size = -1) TD_WARN_UNUSED_RESULT;

Status write_file(CSlice to, Slice data) TD_WARN_UNUSED_RESULT;

string clean_filename(CSlice name);

}  // namespace td
