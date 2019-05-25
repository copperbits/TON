#pragma once

#include "crypto/vm/db/TonDb.h"  // FIXME
#include "crypto/vm/stack.hpp"

#include <cstdint>
#include <iostream>
#include <string>

namespace fift {
class Dictionary;
class SourceLookup;

struct IntError {
  std::string msg;
  IntError(std::string _msg) : msg(_msg) {
  }
};

struct IntCtx {
  vm::Stack stack;
  int state{0};
  int include_depth{0};
  int line_no{0};
  std::string filename;
  std::string currentd_dir;
  std::istream* input_stream{nullptr};
  std::ostream* output_stream{nullptr};
  std::ostream* error_stream{nullptr};

  vm::TonDb* ton_db{nullptr};
  Dictionary* dictionary{nullptr};
  SourceLookup* source_lookup{nullptr};

 private:
  std::string str;
  const char* input_ptr;

 public:
  IntCtx() = default;

  operator vm::Stack&() {
    return stack;
  }

  std::string scan_word_to(char delim, bool err_endl = true);
  std::string scan_word();
  void skipspc(bool skip_eol = false);

  bool eof() const {
    return !*input_stream;
  }

  bool not_eof() const {
    return !eof();
  }

  void set_input(std::string input_str) {
    str = input_str;
    input_ptr = str.c_str();
    ++line_no;
  }
  void set_input(const char* ptr) {
    input_ptr = ptr;
  }
  const char* get_input() const {
    return input_ptr;
  }

  bool load_next_line();

  bool is_sb() const;

  void clear() {
    state = 0;
    stack.clear();
  }
  class Savepoint {
    IntCtx& ctx;
    int old_line_no;
    std::string old_filename;
    std::string old_current_dir;
    std::istream* old_input_stream;
    std::string old_curline;
    std::ptrdiff_t old_curpos;

   public:
    Savepoint(IntCtx& _ctx, std::string new_filename, std::string new_current_dir, std::istream* new_input_stream);
    ~Savepoint();
  };
};

void check_compile(const IntCtx& ctx);
void check_execute(const IntCtx& ctx);
void check_not_int_exec(const IntCtx& ctx);
void check_int_exec(const IntCtx& ctx);

td::StringBuilder& operator<<(td::StringBuilder& os, const IntCtx& ctx);
std::ostream& operator<<(std::ostream& os, const IntCtx& ctx);
}  // namespace fift
