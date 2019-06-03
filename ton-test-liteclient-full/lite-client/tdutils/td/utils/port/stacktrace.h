#pragma once
namespace td {
class Stacktrace {
 public:
  struct PrintOptions {
    bool use_gdb = false;
    PrintOptions() {
    }
  };
  static void print_to_stderr(const PrintOptions &options = PrintOptions());
};

}  // namespace td
