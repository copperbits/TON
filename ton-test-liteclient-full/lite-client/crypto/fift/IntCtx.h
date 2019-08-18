#pragma once

#include "crypto/vm/db/TonDb.h"  // FIXME
#include "crypto/vm/stack.hpp"
#include "crypto/common/bitstring.h"

#include <cstdint>
#include <cstring>
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

class CharClassifier {
  unsigned char data_[64];

 public:
  CharClassifier() {
    memset(data_, 0, sizeof(data_));
  }
  CharClassifier(td::Slice str, int space_cls = 3) : CharClassifier() {
    import_from_string(str, space_cls);
  }
  CharClassifier(std::string str, int space_cls = 3) : CharClassifier(td::Slice{str}, space_cls) {
  }
  CharClassifier(const char* str, int space_cls = 3) : CharClassifier(td::Slice{str}, space_cls) {
  }
  void import_from_string(td::Slice str, int space_cls = 3);
  void import_from_string(std::string str, int space_cls = 3);
  void import_from_string(const char* str, int space_cls = 3);
  static CharClassifier from_string(td::Slice str, int space_cls = 3);
  void set_char_class(int c, int cl);
  int classify(int c) const {
    c &= 0xff;
    int offs = (c & 3) * 2;
    return (data_[(unsigned)c >> 2] >> offs) & 3;
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

  td::Slice scan_word_to(char delim, bool err_endl = true);
  td::Slice scan_word();
  td::Slice scan_word_ext(const CharClassifier& classifier);
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
