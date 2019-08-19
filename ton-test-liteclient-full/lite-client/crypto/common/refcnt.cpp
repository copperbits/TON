#include "refcnt.hpp"

#include "td/utils/ScopeGuard.h"

namespace td {
namespace detail {
struct SafeDeleter {
 public:
  void retire(const CntObject *ptr) {
    if (is_active_) {
      to_delete_.push_back(ptr);
      return;
    }
    is_active_ = true;
    SCOPE_EXIT {
      is_active_ = false;
    };
    delete ptr;
    while (!to_delete_.empty()) {
      auto *ptr = to_delete_.back();
      to_delete_.pop_back();
      delete ptr;
    }
  }

 private:
  std::vector<const CntObject *> to_delete_;
  bool is_active_{false};
};

TD_THREAD_LOCAL SafeDeleter *deleter;
void safe_delete(const CntObject *ptr) {
  init_thread_local<SafeDeleter>(deleter);
  deleter->retire(ptr);
}
}  // namespace detail
}  // namespace td
