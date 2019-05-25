#pragma once
#include <utility>

#include "StreamInterface.h"

namespace td {
class CyclicBuffer {
 public:
  struct Options {
    Options() {
    }
    int64 chunk_size{1024 * 1024 / 8};
    int64 count{16};
    int64 alignment{1024};

    int64 size() {
      return chunk_size * count;
    }
    int64 max_writable_size() {
      return size() - chunk_size;
    }
  };
  using Reader = StreamReader;
  using Writer = StreamWriter;
  static std::pair<Reader, Writer> create(Options options = {});
};
}  // namespace td
