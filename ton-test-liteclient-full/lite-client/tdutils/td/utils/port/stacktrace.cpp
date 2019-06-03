#include "td/utils/port/stacktrace.h"
#include "td/utils/port/signals.h"

#if !TD_WINDOWS
#include <execinfo.h>
#include <sys/wait.h>
#include <unistd.h>

#if TD_LINUX
#include <sys/prctl.h>
#endif

#endif

namespace td {
namespace {
void print_backtrace(void) {
#if !TD_WINDOWS && !TD_ANDROID && !TD_FREEBSD
  void *buffer[128];
  int nptrs = backtrace(buffer, 128);
  td::signal_safe_write("------- Stack Backtrace -------\n", false);
  backtrace_symbols_fd(buffer, nptrs, 2);
  td::signal_safe_write("-------------------------------\n", false);
#endif
}
void print_backtrace_gdb(void) {
#if !TD_WINDOWS && !TD_DARWIN && !TD_ANDROID
  char pid_buf[30], *pid_buf_begin = pid_buf + sizeof(pid_buf);
  pid_t pid = getpid();
  *--pid_buf_begin = '\0';
  do {
    *--pid_buf_begin = static_cast<char>(pid % 10 + '0');
    pid /= 10;
  } while (pid > 0);

  char name_buf[512];
  ssize_t res = readlink("/proc/self/exe", name_buf, 511);  // TODO works only under Linux
  if (res >= 0) {
    name_buf[res] = 0;

#if TD_LINUX
    if (prctl(PR_SET_DUMPABLE, 1, 0, 0, 0) < 0) {
      td::signal_safe_write("Can't set dumpable\n");
      return;
    }
#endif

    int child_pid = fork();
    if (child_pid < 0) {
      td::signal_safe_write("Can't fork() to run gdb\n");
      return;
    }
    if (!child_pid) {
      dup2(2, 1);  // redirect output to stderr
      execlp("gdb", "gdb", "--batch", "-n", "-ex", "thread", "-ex", "thread apply all bt full", name_buf, pid_buf_begin,
             NULL);
      return;
    } else {
      waitpid(child_pid, nullptr, 0);
    }
  } else {
    td::signal_safe_write("Can't get name of executable file to pass to gdb\n");
  }
#endif
}
}  // namespace

void Stacktrace::print_to_stderr(const PrintOptions &options) {
  //print_backtrace();
  if (options.use_gdb) {
    print_backtrace_gdb();
  }
}
}  // namespace td
