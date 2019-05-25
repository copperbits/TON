#pragma once
#include <utility>
#include <memory>
#include <atomic>

#include "td/utils/common.h"

namespace td {
class FileSyncState {
  struct Self;

 public:
  class Reader {
   public:
    Reader() = default;
    Reader(std::shared_ptr<Self> self);
    bool set_requested_sync_size(size_t size) const;
    size_t synced_size() const;
    size_t flushed_size() const;

   private:
    std::shared_ptr<Self> self;
  };

  class Writer {
   public:
    Writer() = default;
    Writer(std::shared_ptr<Self> self);
    size_t get_requested_synced_size();
    bool set_synced_size(size_t size);
    bool set_flushed_size(size_t size);

   private:
    std::shared_ptr<Self> self;
  };

  static std::pair<Reader, Writer> create();

 private:
  struct Self {
    std::atomic<size_t> requested_synced_size{0};

    std::atomic<size_t> synced_size{0};
    std::atomic<size_t> flushed_size{0};
  };
};
}  // namespace td
