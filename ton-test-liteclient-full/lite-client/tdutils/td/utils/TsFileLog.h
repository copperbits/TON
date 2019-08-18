#pragma once

#include "td/utils/FileLog.h"

namespace td {
class TsFileLog {
 public:
  static Result<td::unique_ptr<LogInterface>> create(string path);
};
}  // namespace td
