
#include "FileSyncState.h"
namespace td {
std::pair<FileSyncState::Reader, FileSyncState::Writer> FileSyncState::create() {
  auto self = std::make_shared<Self>();
  return {Reader(self), Writer(self)};
}

FileSyncState::Reader::Reader(std::shared_ptr<Self> self) : self(std::move(self)) {
}
bool FileSyncState::Reader::set_requested_sync_size(size_t size) const {
  if (self->requested_synced_size.load(std::memory_order_relaxed) == size) {
    return false;
  }
  self->requested_synced_size.store(size, std::memory_order_release);
  return true;
}

size_t FileSyncState::Reader::synced_size() const {
  return self->synced_size;
}
size_t FileSyncState::Reader::flushed_size() const {
  return self->flushed_size;
}

FileSyncState::Writer::Writer(std::shared_ptr<Self> self) : self(std::move(self)) {
}

size_t FileSyncState::Writer::get_requested_synced_size() {
  return self->requested_synced_size.load(std::memory_order_acquire);
}

bool FileSyncState::Writer::set_synced_size(size_t size) {
  if (self->synced_size.load(std::memory_order_relaxed) == size) {
    return false;
  }
  self->synced_size.store(size, std::memory_order_release);
  return true;
}

bool FileSyncState::Writer::set_flushed_size(size_t size) {
  if (self->flushed_size.load(std::memory_order_relaxed) == size) {
    return false;
  }
  self->flushed_size.store(size, std::memory_order_release);
  return true;
}

}  // namespace td
