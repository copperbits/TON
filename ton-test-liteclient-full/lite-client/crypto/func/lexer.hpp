namespace src {

/*
 *
 *   LEXER
 *
 */

int lexem_is_special(std::string str);         // return 0 if no special lexems are needed
int compute_symbol_subclass(std::string str);  // return 0 if unneeded

struct Lexem {
  enum { Undefined = -2, Eof = -1, Unknown = 0, Ident = 0, Number = 1, Special = 2 };
  int tp;
  int val;
  std::string str;
  SrcLocation loc;
  int classify();
  Lexem(std::string _str = "", const SrcLocation& _loc = {}, int _tp = Unknown, int _val = 0)
      : tp(_tp), val(_val), str(_str), loc(_loc) {
    classify();
  }
  int set(std::string _str = "", const SrcLocation& _loc = {}, int _tp = Unknown, int _val = 0);
  Lexem& clear(const SrcLocation& _loc = {}, int _tp = Unknown, int _val = 0) {
    tp = _tp;
    val = _val;
    loc = _loc;
    str = "";
    return *this;
  }
  bool valid() const {
    return tp != Undefined;
  }
  std::string name_str() const;
  void error(std::string _str) const {
    throw ParseError{loc, _str};
  }
  void error_at(std::string str1, std::string str2) const {
    error(str1 + str + str2);
  }

  static std::string lexem_name_str(int idx);
};

class Lexer {
  SourceReader& src;
  bool eof;
  Lexem lexem, peek_lexem;
  unsigned char char_class[128];
  std::array<int, 3> eol_cmt, cmt_op, cmt_cl;
  enum cc { left_active = 2, right_active = 1, active = 3, allow_repeat = 4 };

 public:
  bool eof_found() const {
    return eof;
  }
  Lexer(SourceReader& _src, bool init = false, std::string active_chars = ":;,()", std::string eol_cmts = ";;",
        std::string open_cmts = "{-", std::string close_cmts = "-}");
  const Lexem& next();
  const Lexem& cur() const {
    return lexem;
  }
  const Lexem& peek();
  int tp() const {
    return lexem.tp;
  }
  void expect(int exp_tp, const char* msg = 0);
  int classify_char(unsigned c) const {
    return c < 0x80 ? char_class[c] : 0;
  }
  bool is_active(int c) const {
    return (classify_char(c) & cc::active) == cc::active;
  }
  bool is_left_active(int c) const {
    return (classify_char(c) & cc::left_active);
  }
  bool is_right_active(int c) const {
    return (classify_char(c) & cc::right_active);
  }
  bool is_repeatable(int c) const {
    return (classify_char(c) & cc::allow_repeat);
  }

 private:
  void set_spec(std::array<int, 3>& arr, std::string setup);
};

typedef int sym_idx_t;

struct Symbol {
  std::string str;
  sym_idx_t idx;
  int subclass;
  Symbol(std::string _str, sym_idx_t _idx, int _sc) : str(_str), idx(_idx), subclass(_sc) {
  }
  Symbol(std::string _str, sym_idx_t _idx) : str(_str), idx(_idx) {
    subclass = compute_symbol_subclass(std::move(_str));
  }
};

namespace {

std::string unknown_symbol_name(sym_idx_t i) {
  if (!i) {
    return "_";
  } else {
    std::ostringstream os;
    os << "SYM#" << i;
    return os.str();
  }
}

}  // namespace

template <int p>
class SymTable {
 public:
  constexpr static int hprime = p;
  constexpr static sym_idx_t not_found = 0;
  constexpr static int max_kw_idx = 10000;
  static int size() {
    return p + 1;
  }

 private:
  sym_idx_t def_kw, def_sym;
  std::unique_ptr<Symbol> sym[p + 1];
  sym_idx_t keywords[max_kw_idx];
  sym_idx_t gen_lookup(std::string str, int mode = 0, sym_idx_t idx = 0);

 public:
  sym_idx_t lookup(std::string str, int mode = 0) {
    return gen_lookup(str, mode);
  }
  sym_idx_t lookup_add(std::string str) {
    return gen_lookup(str, 1);
  }
  SymTable& add_keyword(std::string str, sym_idx_t idx = 0);
  SymTable& add_kw_char(char c) {
    return add_keyword(std::string{c}, c);
  }
  Symbol* operator[](sym_idx_t i) const {
    return sym[i].get();
  }
  bool is_keyword(sym_idx_t i) const {
    return sym[i] && sym[i]->idx < 0;
  }
  std::string get_name(sym_idx_t i) const {
    return sym[i] ? sym[i]->str : unknown_symbol_name(i);
  }
  int get_subclass(sym_idx_t i) const {
    return sym[i] ? sym[i]->subclass : 0;
  }
  Symbol* get_keyword(int i) const {
    return ((unsigned)i < (unsigned)max_kw_idx) ? sym[keywords[i]].get() : nullptr;
  }
  SymTable() : def_kw(0x100), def_sym(0) {
    std::memset(keywords, 0, sizeof(keywords));
  }
};

struct SymTableOverflow {
  int sym_def;
  SymTableOverflow(int x) : sym_def(x) {
  }
};

struct SymTableKwRedef {
  std::string kw;
  SymTableKwRedef(std::string _kw) : kw(_kw) {
  }
};

template <int p>
sym_idx_t SymTable<p>::gen_lookup(std::string str, int mode, sym_idx_t idx) {
  unsigned long long h1 = 1, h2 = 1;
  for (char c : str) {
    h1 = ((h1 * 239) + (unsigned char)(c)) % p;
    h2 = ((h2 * 17) + (unsigned char)(c)) % (p - 1);
  }
  ++h2;
  ++h1;
  while (true) {
    if (sym[h1]) {
      if (sym[h1]->str == str) {
        return (mode & 2) ? not_found : sym_idx_t(h1);
      }
      h1 += h2;
      if (h1 > p) {
        h1 -= p;
      }
    } else {
      if (!(mode & 1)) {
        return not_found;
      }
      if (def_sym >= ((long)p * 3) / 4) {
        throw SymTableOverflow{def_sym};
      }
      sym[h1] = std::make_unique<Symbol>(str, idx <= 0 ? sym_idx_t(h1) : -idx);
      ++def_sym;
      return sym_idx_t(h1);
    }
  }
}

template <int p>
SymTable<p>& SymTable<p>::add_keyword(std::string str, sym_idx_t idx) {
  if (idx <= 0) {
    idx = ++def_kw;
  }
  sym_idx_t res = gen_lookup(str, -1, idx);
  if (!res) {
    throw SymTableKwRedef{str};
  }
  if (idx < max_kw_idx) {
    keywords[idx] = res;
  }
  return *this;
}

SymTable<100003> symbols;

std::string Lexem::lexem_name_str(int idx) {
  if (idx == Eof) {
    return "end of file";
  } else if (idx == Ident) {
    return "identifier";
  } else if (idx == Number) {
    return "number";
  } else if (idx == Special) {
    return "special";
  } else if (symbols.get_keyword(idx)) {
    return "`" + symbols.get_keyword(idx)->str + "`";
  } else {
    std::ostringstream os{"<unknown lexem of type "};
    os << idx << ">";
    return os.str();
  }
}

std::string Lexem::name_str() const {
  if (tp == Ident) {
    return std::string{"identifier `"} + symbols.get_name(val) + "`";
  } else {
    return lexem_name_str(tp);
  }
}

bool is_number(std::string str) {
  auto st = str.begin(), en = str.end();
  if (st == en) {
    return false;
  }
  if (*st == '-') {
    st++;
  }
  bool hex = false;
  if (st + 1 < en && *st == '0' && st[1] == 'x') {
    st += 2;
    hex = true;
  }
  if (st == en) {
    return false;
  }
  while (st < en) {
    int c = *st;
    if (c >= '0' && c <= '9') {
      ++st;
      continue;
    }
    if (!hex) {
      return false;
    }
    c |= 0x20;
    if (c < 'a' || c > 'f') {
      return false;
    }
  }
  return true;
}

int Lexem::classify() {
  if (tp != Unknown) {
    return tp;
  }
  sym_idx_t i = symbols.lookup(str);
  if (i) {
    assert(str == symbols[i]->str);
    str = symbols[i]->str;
    sym_idx_t idx = symbols[i]->idx;
    tp = (idx < 0 ? -idx : Ident);
    val = i;
  } else if (is_number(str)) {
    tp = Number;
  } else {
    tp = lexem_is_special(str);
  }
  if (tp == Unknown) {
    tp = Ident;
    val = symbols.lookup(str, 1);
  }
  return tp;
}

int Lexem::set(std::string _str, const SrcLocation& _loc, int _tp, int _val) {
  str = _str;
  loc = _loc;
  tp = _tp;
  val = _val;
  return classify();
}

Lexer::Lexer(SourceReader& _src, bool init, std::string active_chars, std::string eol_cmts, std::string open_cmts,
             std::string close_cmts)
    : src(_src), eof(false), lexem("", src.here(), Lexem::Undefined), peek_lexem("", {}, Lexem::Undefined) {
  memset(char_class, 0, sizeof(char_class));
  unsigned char activity = cc::active;
  for (char c : active_chars) {
    if (c == ' ') {
      if (!--activity) {
        activity = cc::allow_repeat;
      }
    } else if ((unsigned)c < 0x80) {
      char_class[(unsigned)c] |= activity;
    }
  }
  set_spec(eol_cmt, eol_cmts);
  set_spec(cmt_op, open_cmts);
  set_spec(cmt_cl, close_cmts);
  if (init) {
    next();
  }
}

void Lexer::set_spec(std::array<int, 3>& arr, std::string setup) {
  arr[0] = arr[1] = arr[2] = -0x100;
  std::size_t n = setup.size(), i;
  for (i = 0; i < n; i++) {
    if (setup[i] == ' ') {
      continue;
    }
    if (i == n - 1 || setup[i + 1] == ' ') {
      arr[0] = setup[i];
    } else if (i == n - 2 || (i < n - 2 && setup[i + 2] == ' ')) {
      arr[1] = setup[i];
      arr[2] = setup[++i];
    } else {
      while (i < n && setup[i] != ' ') {
        i++;
      }
    }
  }
}

void Lexer::expect(int exp_tp, const char* msg) {
  if (tp() != exp_tp) {
    throw ParseError{lexem.loc, (msg ? std::string{msg} : Lexem::lexem_name_str(exp_tp)) + " expected instead of " +
                                    cur().name_str()};
  }
  next();
}

const Lexem& Lexer::next() {
  if (peek_lexem.valid()) {
    lexem = std::move(peek_lexem);
    peek_lexem.clear({}, Lexem::Undefined);
    eof = (lexem.tp == Lexem::Eof);
    return lexem;
  }
  if (eof) {
    return lexem.clear(src.here(), Lexem::Eof);
  }
  long long comm = 1;
  while (!src.seek_eof()) {
    int cc = src.cur_char(), nc = src.next_char();
    if (cc == eol_cmt[0] || (cc == eol_cmt[1] && nc == eol_cmt[2])) {
      src.load_line();
    } else if (cc == cmt_op[1] && nc == cmt_op[2]) {
      src.advance(2);
      comm = comm * 2 + 1;
    } else if (cc == cmt_op[0]) {
      src.advance(1);
      comm *= 2;
    } else if (comm == 1) {
      break;
    } else if (cc == cmt_cl[1] && nc == cmt_cl[2]) {
      if (!(comm & 1)) {
        src.error(std::string{"a `"} + (char)cmt_op[0] + "` comment closed by `" + (char)cmt_cl[1] + (char)cmt_cl[2] +
                  "`");
      }
      comm >>= 1;
      src.advance(2);
    } else if (cc == cmt_cl[0]) {
      if (!(comm & 1)) {
        src.error(std::string{"a `"} + (char)cmt_op[1] + (char)cmt_op[2] + "` comment closed by `" + (char)cmt_cl[0] +
                  "`");
      }
      comm >>= 1;
      src.advance(1);
    } else {
      src.advance(1);
    }
    if (comm < 0) {
      src.error("too many nested comments");
    }
  }
  if (src.seek_eof()) {
    eof = true;
    if (comm > 1) {
      if (comm & 1) {
        src.error(std::string{"`"} + (char)cmt_op[1] + (char)cmt_op[2] + "` comment extends past end of file");
      } else {
        src.error(std::string{"`"} + (char)cmt_op[0] + "` comment extends past end of file");
      }
    }
    return lexem.clear(src.here(), Lexem::Eof);
  }
  char c = src.cur_char();
  const char* end = src.get_ptr();
  if (c == '`') {
    ++end;
    while (end < src.get_end_ptr() && *end != '`') {
      ++end;
    }
    if (*end != '`') {
      src.error("a `back-quoted` token extends past end of line");
    }
    lexem.set(std::string{src.get_ptr() + 1, end}, src.here());
    src.set_ptr(end + 1);
    return lexem;
  }
  int len = 0, pc = -0x100;
  while (end < src.get_end_ptr()) {
    c = *end;
    bool repeated = (c == pc && is_repeatable(c));
    if (c == ' ' || c == 9 || (len && is_left_active(c) && !repeated)) {
      break;
    }
    ++len;
    ++end;
    if (is_right_active(c) && !repeated) {
      break;
    }
    pc = c;
  }
  lexem.set(std::string{src.get_ptr(), end}, src.here());
  src.set_ptr(end);
  return lexem;
}

const Lexem& Lexer::peek() {
  if (peek_lexem.valid()) {
    return peek_lexem;
  }
  if (eof) {
    return lexem.clear(src.here(), Lexem::Eof);
  }
  Lexem keep = std::move(lexem);
  next();
  peek_lexem = std::move(lexem);
  lexem = std::move(keep);
  eof = false;
  return peek_lexem;
}

}  // namespace src
