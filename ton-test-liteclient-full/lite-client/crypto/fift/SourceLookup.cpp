#include "SourceLookup.h"

#include "td/utils/PathView.h"
#include "td/utils/PathView.h"
#include "td/utils/port/path.h"
#include "td/utils/filesystem.h"

#include <fstream>

namespace fift {
td::Result<FileLoader::File> OsFileLoader::read_file(td::CSlice filename) {
  File res;
  TRY_RESULT(data, td::read_file_str(filename));
  res.data = std::move(data);
  TRY_RESULT(path, td::realpath(filename));
  res.path = std::move(path);
  return std::move(res);
}

td::Status OsFileLoader::write_file(td::CSlice filename, td::Slice data) {
  return td::write_file(filename, data);
}

td::Result<FileLoader::File> OsFileLoader::read_file_part(td::CSlice filename, td::int64 size, td::int64 offset) {
  File res;
  TRY_RESULT(data, td::read_file_str(filename, size, offset));
  res.data = std::move(data);
  TRY_RESULT(path, td::realpath(filename));
  res.path = std::move(path);
  return std::move(res);
}

bool OsFileLoader::is_file_exists(td::CSlice filename) {
  return td::stat(filename).is_ok();
}

void SourceLookup::add_include_path(td::string path) {
  if (path.empty()) {
    return;
  }
  if (!td::PathView(path).is_dir()) {
    path += TD_DIR_SLASH;
  }

  source_include_path_.push_back(std::move(path));
}

td::Result<FileLoader::File> SourceLookup::lookup_source(std::string filename, std::string current_dir) {
  CHECK(file_loader_);
  if (!current_dir.empty() && !td::PathView(current_dir).is_dir()) {
    current_dir += TD_DIR_SLASH;
  }
  if (td::PathView(filename).is_absolute()) {
    return read_file(filename);
  }
  if (!current_dir.empty()) {
    auto res = read_file(current_dir + filename);
    if (res.is_ok()) {
      return res;
    }
  }
  for (auto& dir : source_include_path_) {
    auto res = read_file(dir + filename);
    if (res.is_ok()) {
      return res;
    }
  }

  return td::Status::Error(PSLICE() << "failed to lookup file: " << filename);
}
}  // namespace fift
