#pragma once
#include "td/utils/buffer.h"

namespace vm {
class BlobView {
 public:
  virtual ~BlobView() = default;
  td::Result<td::Slice> view(td::MutableSlice slice, td::uint64 offset);
  virtual size_t size() = 0;

 private:
  virtual td::Result<td::Slice> view_impl(td::MutableSlice slice, td::uint64 offset) = 0;
};

class BufferSliceBlobView {
 public:
  static std::unique_ptr<BlobView> create(td::BufferSlice slice);
};
class FileBlobView {
 public:
  static td::Result<std::unique_ptr<BlobView>> create(td::CSlice file_path, td::uint64 file_size = 0);
};
class FileMemoryMappingBlobView {
 public:
  static td::Result<std::unique_ptr<BlobView>> create(td::CSlice file_path, td::uint64 file_size = 0);
};
}  // namespace vm
