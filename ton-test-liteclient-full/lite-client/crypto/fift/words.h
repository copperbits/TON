#pragma once
#include "Dictionary.h"

namespace fift {

// thrown by 'quit', 'bye' and 'halt' for exiting to top level
struct Quit {
  int res;
  Quit() : res(0) {
  }
  Quit(int _res) : res(_res) {
  }
};

void init_words_common(Dictionary& dictionary);
void init_words_vm(Dictionary& dictionary);
void init_words_ton(Dictionary& dictionary);

void import_cmdline_args(Dictionary& d, std::string arg0, int n, const char* const argv[]);

int funny_interpret_loop(IntCtx& ctx);

}  // namespace fift
