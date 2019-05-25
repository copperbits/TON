namespace src {

/*
 *
 *   SOURCE FILE READER
 *
 */

struct FileDescr {
  std::string filename;
  bool is_stdin;
  FileDescr(std::string _fname, bool _stdin = false) : filename(std::move(_fname)), is_stdin(_stdin) {
  }
};

std::ostream& operator<<(std::ostream& os, const FileDescr* fdescr) {
  return os << (fdescr ? (fdescr->is_stdin ? "stdin" : fdescr->filename) : "unknown-location");
}

struct Fatal {
  std::string message;
  Fatal(std::string _msg) : message(std::move(_msg)) {
  }
  std::string get_msg() const {
    return message;
  }
};

std::ostream& operator<<(std::ostream& os, const Fatal& fatal) {
  return os << fatal.get_msg();
}

struct SrcLocation {
  const FileDescr* fdescr;
  int line_no;
  int line_pos;
  std::string text;
  SrcLocation() : fdescr(nullptr), line_no(0), line_pos(-1) {
  }
  SrcLocation(const FileDescr* _fdescr, int line = 0, int pos = -1) : fdescr(_fdescr), line_no(line), line_pos(pos) {
  }
  bool defined() const {
    return fdescr;
  }
  void show(std::ostream& os) const;
  bool show_context(std::ostream& os) const;
  void show_gen_error(std::ostream& os, std::string message, std::string err_type = "") const;
  void show_note(std::string err_msg) const {
    show_gen_error(std::cerr, err_msg, "note");
  }
  void show_warning(std::string err_msg) const {
    show_gen_error(std::cerr, err_msg, "warning");
  }
  void show_error(std::string err_msg) const {
    show_gen_error(std::cerr, err_msg, "error");
  }
};

void SrcLocation::show(std::ostream& os) const {
  os << fdescr;
  if (line_no > 0) {
    os << ':' << line_no;
    if (line_pos >= 0) {
      os << ':' << (line_pos + 1);
    }
  }
}

bool SrcLocation::show_context(std::ostream& os) const {
  if (text.empty() || line_pos < 0 || (unsigned)line_pos > text.size()) {
    return false;
  }
  bool skip_left = (line_pos > 200), skip_right = (line_pos + 200u < text.size());
  const char* start = skip_left ? text.c_str() + line_pos - 100 : text.c_str();
  const char* end = skip_right ? text.c_str() + line_pos + 100 : text.c_str() + text.size();
  const char* here = text.c_str() + line_pos;
  os << "  ";
  if (skip_left) {
    os << "... ";
  }
  for (const char* ptr = start; ptr < end; ptr++) {
    os << (char)*ptr;
  }
  if (skip_right) {
    os << " ...";
  }
  os << std::endl;
  os << "  ";
  if (skip_left) {
    os << "... ";
  }
  for (const char* ptr = start; ptr < here; ptr++) {
    char c = *ptr;
    os << (c == 9 || c == 10 ? c : ' ');
  }
  os << '^' << std::endl;
  return true;
}

std::ostream& operator<<(std::ostream& os, const SrcLocation& loc) {
  loc.show(os);
  return os;
}

void SrcLocation::show_gen_error(std::ostream& os, std::string message, std::string err_type) const {
  show(os);
  if (!err_type.empty()) {
    os << ": " << err_type;
  }
  os << ": " << message << std::endl;
  show_context(os);
}

struct Error {
  virtual ~Error() = default;
  virtual void show(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Error& error) {
  error.show(os);
  return os;
}

struct ParseError : Error {
  SrcLocation where;
  std::string message;
  ParseError(const SrcLocation& _where, std::string _msg) : where(_where), message(_msg) {
  }
  ParseError(const SrcLocation* _where, std::string _msg) : message(_msg) {
    if (_where) {
      where = *_where;
    }
  }
  ~ParseError() override = default;
  void show(std::ostream& os) const override;
};

void ParseError::show(std::ostream& os) const {
  os << where << ": error: " << message << std::endl;
  where.show_context(os);
}

class SourceReader {
  std::istream* ifs;
  SrcLocation loc;
  bool eof;
  std::string cur_line;
  int cur_line_len;
  void set_eof();
  const char *start, *cur, *end;

 public:
  SourceReader(std::istream* _is, const FileDescr* _fdescr);
  bool load_line();
  bool is_eof() const {
    return eof;
  }
  int is_eoln() const {
    return cur == end;
  }
  int skip_spc();
  bool seek_eoln() {
    skip_spc();
    return is_eoln();
  }
  bool seek_eof();
  const char* cur_line_cstr() const {
    return cur_line.c_str();
  }
  const SrcLocation& here() const {
    return loc;
  }
  char cur_char() const {
    return *cur;
  }
  char next_char() const {
    return cur[1];
  }
  const char* get_ptr() const {
    return cur;
  }
  const char* get_end_ptr() const {
    return end;
  }
  const char* set_ptr(const char* ptr);
  void advance(int n) {
    set_ptr(get_ptr() + n);
  }
  void error(std::string err_msg) {
    throw ParseError{loc, err_msg};
  }
};

SourceReader::SourceReader(std::istream* _is, const FileDescr* _fdescr)
    : ifs(_is), loc(_fdescr), eof(false), cur_line_len(0), start(0), cur(0), end(0) {
  load_line();
}

void SourceReader::set_eof() {
  if (!eof) {
    eof = true;
    start = cur = end = 0;
  }
}

int SourceReader::skip_spc() {
  if (!cur) {
    return 0;
  }
  const char* ptr = cur;
  int res = 0;
  while (*ptr == ' ' || *ptr == 9) {
    ++ptr;
    ++res;
  }
  set_ptr(ptr);
  return res;
}

bool SourceReader::seek_eof() {
  while (seek_eoln()) {
    if (!load_line()) {
      return true;
    }
  }
  return false;
}

const char* SourceReader::set_ptr(const char* ptr) {
  if (ptr != cur) {
    if (ptr < cur || ptr > end) {
      error("parsing position went outside of line");
    }
    loc.line_pos = (int)(ptr - start);
    cur = ptr;
  }
  return ptr;
}

bool SourceReader::load_line() {
  if (eof) {
    return false;
  }
  if (ifs->eof()) {
    set_eof();
    return false;
  }
  ++loc.line_no;
  loc.line_pos = -1;
  std::getline(*ifs, cur_line);
  if (ifs->fail()) {
    set_eof();
    if (!ifs->eof()) {
      error("cannot read line from source stream");
    }
    return false;
  }
  std::size_t len = cur_line.size();
  if (len > 0xffffff) {
    set_eof();
    error("line too long");
    return false;
  }
  loc.text = cur_line;
  cur_line_len = (int)len;
  loc.line_pos = 0;
  cur = start = cur_line.c_str();
  end = start + cur_line_len;
  return true;
}

}  // namespace src
