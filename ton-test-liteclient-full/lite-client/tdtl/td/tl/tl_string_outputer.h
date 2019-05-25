#pragma once

#include "tl_outputer.h"

#include <string>

namespace td {
namespace tl {

class tl_string_outputer : public tl_outputer {
  std::string result;

 public:
  virtual void append(const std::string &str);

  std::string get_result() const;
};

}  // namespace tl
}  // namespace td
