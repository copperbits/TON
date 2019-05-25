#pragma once

#include "td/utils/port/config.h"

#include "td/utils/port/detail/ThreadPthread.h"
#include "td/utils/port/detail/ThreadStl.h"

namespace td {

// clang-format off

#if TD_THREAD_PTHREAD
  using thread = detail::ThreadPthread;
  namespace this_thread = detail::this_thread_pthread;
#elif TD_THREAD_STL
  using thread = detail::ThreadStl;
  namespace this_thread = detail::this_thread_stl;
#elif TD_THREAD_UNSUPPORTED
  namespace this_thread {
    inline void yield() {}
  }
#else
  #error "Thread's implementation is not defined"
#endif

// clang-format on

}  // namespace td
