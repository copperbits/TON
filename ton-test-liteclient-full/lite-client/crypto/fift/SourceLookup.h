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
};

class OsFileLoader : public FileLoader {
 public:
  td::Result<File> read_file(td::CSlice filename) override;
  td::Status write_file(td::CSlice filename, td::Slice data) override;
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

 protected:
  std::unique_ptr<FileLoader> file_loader_;
  std::vector<std::string> source_include_path_;
};
}  // namespace fift
