#include "BinlogReaderHelper.h"
#include "BinlogReaderInterface.h"

#include "td/utils/misc.h"

namespace td {
td::Status BinlogReaderHelper::parse(BinlogReaderInterface& reader, td::Slice data) {
  SCOPE_EXIT {
    reader.flush();
  };
  while (true) {
    if (expected_prefix_size_ > 0 && expected_prefix_size_ == prefix_size_) {
      TRY_RESULT(size, reader.parse(MutableSlice(buf_.data(), prefix_size_)));
      if (size < 0) {
        if (expected_prefix_size_ > td::narrow_cast<size_t>(-size)) {
          return td::Status::Error("BinlogReader decreased logevent size estimation (1)");
        }
        expected_prefix_size_ = -size;
      } else {
        if (expected_prefix_size_ != td::narrow_cast<size_t>(size)) {
          return td::Status::Error("BinlogReader changed logevent");
        }
        prefix_size_ = 0;
        expected_prefix_size_ = 0;
      }
    }

    if (data.empty()) {
      break;
    }

    if (expected_prefix_size_ > 0) {
      CHECK(expected_prefix_size_ < buf_.size());
      CHECK(prefix_size_ < expected_prefix_size_);
      auto got = data.copy().truncate(expected_prefix_size_ - prefix_size_);
      reader.flush();
      auto dest = td::MutableSlice(buf_.data(), buf_.size()).substr(prefix_size_);
      if (dest.size() < got.size()) {
        return td::Status::Error("Too big logevent");
      }
      dest.copy_from(got);
      prefix_size_ += got.size();
      data = data.substr(got.size());
      continue;
    }

    CHECK(!data.empty());

    TRY_RESULT(size, reader.parse(data));
    if (size < 0) {
      expected_prefix_size_ = td::narrow_cast<size_t>(-size);
      prefix_size_ = data.size();
      if (expected_prefix_size_ < prefix_size_) {
        return td::Status::Error("BinlogReader waits for less data than it already has");
      }
      if (expected_prefix_size_ > buf_.size()) {
        return td::Status::Error("BinlogReader waits for too big logevent");
      }
      reader.flush();
      td::MutableSlice(buf_.data(), prefix_size_).copy_from(data);
      break;
    }
    if (size == 0) {
      return td::Status::Error("BinlogReader parseed nothing and asked for nothing");
    }
    if (td::narrow_cast<size_t>(size) > data.size()) {
      return td::Status::Error("BinlogReader parseed more than was given");
    }
    data = data.substr(size);
  }
  return td::Status::OK();
}

size_t BinlogReaderHelper::unparsed_size() const {
  return prefix_size_;
}

}  // namespace td
