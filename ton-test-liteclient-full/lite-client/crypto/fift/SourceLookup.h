#pragma once
#include <iostream>

#include "td/utils/Status.h"

namespace fift {
class FileLoader {
 public:
  virtual ~FileLoader() = default;
  struct File {
    std::string data;
    std::string path;
  };
  virtual td::Result<File> read_file(td::CSlice filename) = 0;
  virtual td::Status write_file(td::CSlice filename, td::Slice data) = 0;
  virtual td::Result<File> read_file_part(td::CSlice filename, td::int64 size, td::int64 offset) = 0;
  virtual bool is_file_exists(td::CSlice filename) = 0;
};

class OsFileLoader : public FileLoader {
 public:
  td::Result<File> read_file(td::CSlice filename) override;
  td::Status write_file(td::CSlice filename, td::Slice data) override;
  td::Result<File> read_file_part(td::CSlice filename, td::int64 size, td::int64 offset) override;
  bool is_file_exists(td::CSlice filename) override;
};

class SourceLookup {
 public:
  SourceLookup() = default;
  explicit SourceLookup(std::unique_ptr<FileLoader> file_loader) : file_loader_(std::move(file_loader)) {
  }
  void add_include_path(td::string path);
  td::Result<FileLoader::File> lookup_source(std::string filename, std::string current_dir);

  td::Result<FileLoader::File> read_file(td::CSlice path) {
    return file_loader_->read_file(path);
  }
  td::Status write_file(td::CSlice path, td::Slice data) {
    return file_loader_->write_file(path, data);
  }
  td::Result<FileLoader::File> read_file_part(td::CSlice filename, td::int64 size, td::int64 offset) {
    return file_loader_->read_file_part(filename, size, offset);
  }
  bool is_file_exists(td::CSlice filename) {
    return file_loader_->is_file_exists(filename);
  }

 protected:
  std::unique_ptr<FileLoader> file_loader_;
  std::vector<std::string> source_include_path_;
};
}  // namespace fift
