#include "td/utils/check.h"

#include "td/utils/logging.h"
#include "td/utils/Slice.h"

namespace td {
namespace detail {

void process_check_error(const char *message, const char *file, int line) {
  ::td::Logger(*log_interface, log_options, VERBOSITY_NAME(FATAL), Slice(file), line, Slice())
      << "Check `" << message << "` failed";
  ::td::process_fatal_error(PSLICE() << "Check `" << message << "` failed in " << file << " at " << line);
}

}  // namespace detail
}  // namespace td
