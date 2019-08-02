#pragma once

#define TD_DUMMY_CHECK(condition) ((void)(condition))

#define CHECK(condition)                                               \
  if (!(condition)) {                                                  \
    ::td::detail::process_check_error(#condition, __FILE__, __LINE__); \
  }

// clang-format off
#ifdef NDEBUG
  #define DCHECK TD_DUMMY_CHECK
#else
  #define DCHECK CHECK
#endif
// clang-format on

#define UNREACHABLE() ::td::detail::process_check_error("Unreachable", __FILE__, __LINE__)

namespace td {
namespace detail {

[[noreturn]] void process_check_error(const char *message, const char *file, int line);

}  // namespace detail
}  // namespace td
