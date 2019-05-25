#pragma once

#include "td/utils/Slice.h"
#include "td/utils/Status.h"

namespace td {

class BinlogReaderInterface {
 public:
  virtual ~BinlogReaderInterface() {
  }
  // returns error or size
  // negative size means reader expects data.size() to be at least -size
  // positive size means first size bytes of data are processed and could be skipped
  virtual td::Result<td::int64> parse(td::Slice data) = 0;

  // called when all passed slices are invalidated
  // Till it is called reader may resue all slices given to it.
  // It makes possible to calculate crc32c in larger chunks
  // TODO: maybe we should just process all data that we can at once
  virtual void flush() {
  }
};
}  // namespace td
