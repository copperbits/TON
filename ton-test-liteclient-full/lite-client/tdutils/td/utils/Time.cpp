#include "td/utils/Time.h"

#include <cmath>

namespace td {

bool operator==(Timestamp a, Timestamp b) {
  return std::abs(a.at() - b.at()) < 1e-6;
}
double Time::now() {
  return Clocks::monotonic();
}

}  // namespace td
