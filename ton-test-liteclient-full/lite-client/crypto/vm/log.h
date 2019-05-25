#pragma once

#include "td/utils/logging.h"

#define VM_LOG_IMPL(st, mask)                                                             \
  LOG_IMPL_FULL(get_log_interface(st), get_log_options(st), DEBUG, VERBOSITY_NAME(DEBUG), \
                (get_log_mask(st) & mask) != 0, "")

#define VM_LOG(st) VM_LOG_IMPL(st, 1)
#define VM_LOG_MASK(st, mask) VM_LOG_IMPL(st, mask)

namespace vm {
struct VmLog {
  td::LogInterface *log_interface{td::log_interface};
  td::LogOptions log_options{td::log_options};
  enum { DumpStack = 2 };
  int log_mask{1};
};

template <class State>
td::LogInterface &get_log_interface(State *st) {
  return st ? *st->get_log().log_interface : *::td::log_interface;
}

template <class State>
auto get_log_options(State *st) {
  return st ? st->get_log().log_options : ::td::log_options;
}

template <class State>
auto get_log_mask(State *st) {
  return st ? st->get_log().log_mask : 1;
}

}  // namespace vm
