#pragma once

#include "td/utils/Slice.h"

#include <set>

namespace vm {
template <class InfoT>
class CellHashTable {
 public:
  template <class F>
  InfoT &apply(td::Slice hash, F &&f) {
    auto it = set_.find(hash);
    if (it != set_.end()) {
      auto &res = const_cast<InfoT &>(*it);
      f(res);
      return res;
    }
    InfoT info;
    f(info);
    auto &res = const_cast<InfoT &>(*(set_.insert(std::move(info)).first));
    return res;
  }

  template <class F>
  void for_each(F &&f) {
    for (auto &info : set_) {
      f(info);
    }
  }
  template <class F>
  void filter(F &&f) {
    for (auto it = set_.begin(); it != set_.end();) {
      if (f(*it)) {
        it++;
      } else {
        it = set_.erase(it);
      }
    }
  }
  void erase(td::Slice hash) {
    auto it = set_.find(hash);
    CHECK(it != set_.end());
    set_.erase(it);
  }
  size_t size() const {
    return set_.size();
  }

 private:
  std::set<InfoT, std::less<>> set_;
};
};  // namespace vm
