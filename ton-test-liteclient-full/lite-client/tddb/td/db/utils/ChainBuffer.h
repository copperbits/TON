#pragma once
#include "td/utils/common.h"

#include "StreamInterface.h"

namespace td {
class ChainBuffer {
 public:
  struct Options {
    Options() {
    }
    int64 chunk_size{1024 * 1024 / 8};  // default size of one chunk in chain buffer
    size_t max_io_slices{128};          // size of buffer for writev
  };
  using Reader = StreamReader;
  using Writer = StreamWriter;
  static std::pair<Reader, Writer> create(Options options = {});
};
}  // namespace td
