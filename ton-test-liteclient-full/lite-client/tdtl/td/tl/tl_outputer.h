#pragma once

#include <string>

namespace td {
namespace tl {

class tl_outputer {
 public:
  virtual void append(const std::string &str) = 0;

  virtual ~tl_outputer() = 0;
};

}  // namespace tl
}  // namespace td
