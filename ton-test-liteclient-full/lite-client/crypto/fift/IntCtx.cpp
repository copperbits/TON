#include "IntCtx.h"

namespace fift {
td::StringBuilder& operator<<(td::StringBuilder& os, const IntCtx& ctx) {
  if (ctx.include_depth) {
    return os << ctx.filename << ":" << ctx.line_no << ": ";
  } else {
    return os;
  }
}

std::ostream& operator<<(std::ostream& os, const IntCtx& ctx) {
  return os << (PSLICE() << ctx).c_str();
}

IntCtx::Savepoint::Savepoint(IntCtx& _ctx, std::string new_filename, std::string new_current_dir,
                             std::istream* new_input_stream)
    : ctx(_ctx)
    , old_line_no(_ctx.line_no)
    , old_filename(_ctx.filename)
    , old_current_dir(_ctx.currentd_dir)
    , old_input_stream(_ctx.input_stream)
    , old_curline(_ctx.str)
    , old_curpos(_ctx.input_ptr - _ctx.str.c_str()) {
  ctx.line_no = 0;
  ctx.filename = new_filename;
  ctx.currentd_dir = new_current_dir;
  ctx.input_stream = new_input_stream;
  ctx.str = "";
  ctx.input_ptr = 0;
  ++(ctx.include_depth);
}

IntCtx::Savepoint::~Savepoint() {
  ctx.line_no = old_line_no;
  ctx.filename = old_filename;
  ctx.currentd_dir = old_current_dir;
  ctx.input_stream = old_input_stream;
  ctx.str = old_curline;
  ctx.input_ptr = ctx.str.c_str() + old_curpos;
  --(ctx.include_depth);
}

bool IntCtx::load_next_line() {
  if (!std::getline(*input_stream, str)) {
    return false;
  }
  set_input(str);
  return true;
}

bool IntCtx::is_sb() const {
  return !eof() && line_no == 1 && *input_ptr == '#' && input_ptr[1] == '!';
}

std::string IntCtx::scan_word_to(char delim, bool err_endl) {
  std::string res;
  while (*input_ptr && *input_ptr != delim) {
    res += *input_ptr++;
  }
  if (*input_ptr) {
    ++input_ptr;
  } else if (err_endl && delim) {
    throw IntError{std::string{"end delimiter `"} + delim + "` not found"};
  }
  return res;
}

std::string IntCtx::scan_word() {
  skipspc(true);
  std::string res;
  while (*input_ptr && *input_ptr != ' ' && *input_ptr != '\t') {
    res += *input_ptr++;
  }
  skipspc();
  return res;
}

void IntCtx::skipspc(bool skip_eol) {
  do {
    while (*input_ptr == ' ' || *input_ptr == '\t') {
      ++input_ptr;
    }
    if (!skip_eol || *input_ptr) {
      break;
    }
  } while (load_next_line());
}

void check_compile(const IntCtx& ctx) {
  if (ctx.state <= 0) {
    throw IntError{"compilation mode only"};
  }
}

void check_execute(const IntCtx& ctx) {
  if (ctx.state != 0) {
    throw IntError{"interpret mode only"};
  }
}

void check_not_int_exec(const IntCtx& ctx) {
  if (ctx.state < 0) {
    throw IntError{"not allowed in internal interpret mode"};
  }
}

void check_int_exec(const IntCtx& ctx) {
  if (ctx.state >= 0) {
    throw IntError{"internal interpret mode only"};
  }
}
}  // namespace fift
