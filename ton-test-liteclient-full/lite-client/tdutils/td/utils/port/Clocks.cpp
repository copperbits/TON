#include "td/utils/port/Clocks.h"

#include <chrono>

namespace td {

ClocksDefault::Duration ClocksDefault::monotonic() {
  auto duration = std::chrono::steady_clock::now().time_since_epoch();
  return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count()) * 1e-9;
}

ClocksDefault::Duration ClocksDefault::system() {
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count()) * 1e-9;
}

}  // namespace td
