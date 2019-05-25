#pragma once

namespace td {

class ClocksBase {
 public:
  using Duration = double;
};

// TODO: (maybe) write system specific functions.
class ClocksDefault {
 public:
  using Duration = ClocksBase::Duration;

  static Duration monotonic();

  static Duration system();
};

using Clocks = ClocksDefault;

}  // namespace td
