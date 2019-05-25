#include "td/db/MemoryKeyValue.h"

#include "td/utils/format.h"

namespace td {
Result<MemoryKeyValue::GetStatus> MemoryKeyValue::get(Slice key, std::string &value) {
  auto it = map_.find(key);
  if (it == map_.end()) {
    return GetStatus::NotFound;
  }
  value = it->second;
  return GetStatus::Ok;
}
Status MemoryKeyValue::set(Slice key, Slice value) {
  map_[key.str()] = value.str();
  return Status::OK();
}
Status MemoryKeyValue::erase(Slice key) {
  auto it = map_.find(key);
  if (it != map_.end()) {
    map_.erase(it);
  }
  return Status::OK();
}

Result<size_t> MemoryKeyValue::count(Slice prefix) {
  size_t res = 0;
  for (auto it = map_.lower_bound(prefix); it != map_.end(); it++) {
    if (Slice(it->first).truncate(prefix.size()) != prefix) {
      break;
    }
    res++;
  }
  return res;
}

std::unique_ptr<KeyValueReader> MemoryKeyValue::snapshot() {
  auto res = std::make_unique<MemoryKeyValue>();
  res->map_ = map_;
  return std::move(res);
}

std::string MemoryKeyValue::stats() const {
  return PSTRING() << "MemoryKeyValueStats{" << tag("get_count", get_count_) << "}";
}

Status MemoryKeyValue::begin_transaction() {
  UNREACHABLE();
}
Status MemoryKeyValue::commit_transaction() {
  UNREACHABLE();
}
Status MemoryKeyValue::abort_transaction() {
  UNREACHABLE();
}
}  // namespace td
