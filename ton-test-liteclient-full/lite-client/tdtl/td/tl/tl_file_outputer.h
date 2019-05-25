#pragma once

#include "tl_outputer.h"

#include <cstdio>
#include <string>

namespace td {
namespace tl {

class tl_file_outputer : public tl_outputer {
  FILE *f;

  void close();

 public:
  tl_file_outputer();

  bool open(const std::string &file_name);

  virtual void append(const std::string &str);

  virtual ~tl_file_outputer();
};

}  // namespace tl
}  // namespace td
