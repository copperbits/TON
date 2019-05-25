#pragma once

#include "td/utils/Slice.h"
#include "td/utils/Span.h"

#if TD_PORT_POSIX
#include <sys/uio.h>
#endif

namespace td {
#if TD_PORT_POSIX
using IoSlice = struct iovec;
inline IoSlice as_io_slice(Slice slice) {
  IoSlice res;
  res.iov_len = slice.size();
  res.iov_base = const_cast<char *>(slice.data());
  return res;
}
inline Slice as_slice(const IoSlice io_slice) {
  return Slice(reinterpret_cast<const char *>(io_slice.iov_base), io_slice.iov_len);
}
#else
using IoSlice = Slice;
inline IoSlice as_io_slice(Slice slice) {
  return slice;
}
#endif
}  // namespace td
