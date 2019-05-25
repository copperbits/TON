#pragma once
#include "td/db/KeyValue.h"

#include <map>

namespace td {
class MemoryKeyValue : public KeyValue {
 public:
  Result<GetStatus> get(Slice key, std::string &value) override;
  Status set(Slice key, Slice value) override;
  Status erase(Slice key) override;
  Result<size_t> count(Slice prefix) override;

  Status begin_transaction() override;
  Status commit_transaction() override;
  Status abort_transaction() override;

  std::unique_ptr<KeyValueReader> snapshot() override;

  std::string stats() const override;

 private:
  class Cmp : public std::less<> {
   public:
    using is_transparent = void;
  };
  std::map<std::string, std::string, Cmp> map_;
  int64 get_count_{0};
};
}  // namespace td
