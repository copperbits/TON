#include "tl_string_outputer.h"

namespace td {
namespace tl {

void tl_string_outputer::append(const std::string &str) {
  result += str;
}

std::string tl_string_outputer::get_result() const {
#if defined(_WIN32)
  std::string fixed_result;
  for (std::size_t i = 0; i < result.size(); i++) {
    if (result[i] == '\n') {
      fixed_result += '\r';
    }
    fixed_result += result[i];
  }
  return fixed_result;
#else
  return result;
#endif
}

}  // namespace tl
}  // namespace td
