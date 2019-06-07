#pragma once

#include "td/utils/Status.h"

namespace td {

inline td::Status status_prefix(td::Status &&status, std::string prefix) {
  if (status.is_ok()) {
    return std::move(status);
  } else {
    return td::Status::Error(status.code(), prefix + status.message().str());
  }
}

}  // namespace td
