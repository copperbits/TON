#pragma once

#include "td/utils/StringBuilder.h"

namespace td {

class Timer {
 public:
  Timer();
  double elapsed() const;

 private:
  friend StringBuilder &operator<<(StringBuilder &string_builder, const Timer &timer);

  double start_time_;
};

class PerfWarningTimer {
 public:
  explicit PerfWarningTimer(string name, double max_duration = 0.1);
  PerfWarningTimer(const PerfWarningTimer &) = delete;
  PerfWarningTimer &operator=(const PerfWarningTimer &) = delete;
  PerfWarningTimer(PerfWarningTimer &&other);
  PerfWarningTimer &operator=(PerfWarningTimer &&) = delete;
  ~PerfWarningTimer();
  void reset();

 private:
  string name_;
  double start_at_{0};
  double max_duration_{0};
};

}  // namespace td
