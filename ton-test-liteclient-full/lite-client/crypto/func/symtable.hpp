namespace sym {

/*
 *
 *   SYMBOL VALUES (DECLARED)
 *
 */

typedef int var_idx_t;

struct SymValBase {
  enum { _Param, _Var, _Func, _Typename };
  int type;
  int idx;
  SymValBase(int _type, int _idx) : type(_type), idx(_idx) {
  }
  virtual ~SymValBase() = default;
};

/*
 *
 *   SYMBOL TABLE
 *
 */

int scope_level;

struct SymDef {
  int level;
  src::sym_idx_t sym_idx;
  SymValBase* value;
  src::SrcLocation loc;
  SymDef(int lvl, src::sym_idx_t idx, const src::SrcLocation& _loc = {}, SymValBase* val = 0)
      : level(lvl), sym_idx(idx), value(val), loc(_loc) {
  }
  bool has_name() const {
    return sym_idx;
  }
  std::string name() const {
    return src::symbols.get_name(sym_idx);
  }
};

SymDef* sym_def[src::symbols.hprime];
SymDef* global_sym_def[src::symbols.hprime];
std::vector<std::pair<int, SymDef>> symbol_stack;
std::vector<src::SrcLocation> scope_opened_at;

void open_scope(src::Lexer& lex) {
  ++scope_level;
  scope_opened_at.push_back(lex.cur().loc);
}

void close_scope(src::Lexer& lex) {
  if (!scope_level) {
    throw src::Fatal{"cannot close the outer scope"};
  }
  while (!symbol_stack.empty() && symbol_stack.back().first == scope_level) {
    SymDef old_def = symbol_stack.back().second;
    auto idx = old_def.sym_idx;
    symbol_stack.pop_back();
    SymDef* cur_def = sym_def[idx];
    assert(cur_def);
    assert(cur_def->level == scope_level && cur_def->sym_idx == idx);
    //std::cerr << "restoring local symbol `" << old_def.name << "` of level " << scope_level << " to its previous level " << old_def.level << std::endl;
    if (cur_def->value) {
      //std::cerr << "deleting value of symbol " << old_def.name << ":" << old_def.level << " at " << (const void*) it->second.value << std::endl;
      delete cur_def->value;
    }
    if (!old_def.level && !old_def.value) {
      delete cur_def;  // ??? keep the definition always?
      sym_def[idx] = nullptr;
    } else {
      cur_def->value = std::move(old_def.value);
      cur_def->level = old_def.level;
    }
    old_def.value = nullptr;
  }
  --scope_level;
  scope_opened_at.pop_back();
}

SymDef* lookup_symbol(src::sym_idx_t idx, int flags = 3) {
  if (!idx) {
    return nullptr;
  }
  if ((flags & 1) && sym_def[idx]) {
    return sym_def[idx];
  }
  if ((flags & 2) && global_sym_def[idx]) {
    return global_sym_def[idx];
  }
  return nullptr;
}

SymDef* lookup_symbol(std::string name, int flags = 3) {
  return lookup_symbol(src::symbols.lookup(name), flags);
}

SymDef* define_global_symbol(src::sym_idx_t name_idx, bool force_new = false, const src::SrcLocation& loc = {}) {
  if (!name_idx) {
    return nullptr;
  }
  auto found = global_sym_def[name_idx];
  if (found) {
    return force_new && found->value ? nullptr : found;
  }
  return global_sym_def[name_idx] = new SymDef(0, name_idx, loc);
}

SymDef* define_symbol(src::sym_idx_t name_idx, bool force_new = false, const src::SrcLocation& loc = {}) {
  if (!name_idx) {
    return nullptr;
  }
  if (!scope_level) {
    return define_global_symbol(name_idx, force_new, loc);
  }
  auto found = sym_def[name_idx];
  if (found) {
    if (found->level < scope_level) {
      symbol_stack.push_back(std::make_pair(scope_level, *found));
      found->level = scope_level;
    } else if (found->value && force_new) {
      return nullptr;
    }
    found->value = 0;
    found->loc = loc;
    return found;
  }
  found = sym_def[name_idx] = new SymDef(scope_level, name_idx, loc);
  symbol_stack.push_back(std::make_pair(scope_level, SymDef{0, name_idx}));
  return found;
}

}  // namespace sym
