#include "Dictionary.h"

namespace fift {
//
// StackWord
//
StackWord::StackWord(StackWordFunc _f) : f(std::move(_f)) {
}
void StackWord::run(IntCtx& ctx) const {
  f(ctx.stack);
}

//
// CtxWord
//
CtxWord::CtxWord(CtxWordFunc _f) : f(std::move(_f)) {
}
void CtxWord::run(IntCtx& ctx) const {
  f(ctx);
}

//
// WordList
//
WordList::WordList(std::vector<Ref<WordDef>>&& _list) : list(std::move(_list)) {
}
WordList::WordList(const std::vector<Ref<WordDef>>& _list) : list(_list) {
}
WordList& WordList::push_back(Ref<WordDef> word_def) {
  list.push_back(std::move(word_def));
  return *this;
}
WordList& WordList::push_back(WordDef& wd) {
  list.emplace_back(&wd);
  return *this;
}
void WordList::run(IntCtx& ctx) const {
  for (auto const& word : list) {
    word->run(ctx);
  }
}
void WordList::close() {
  list.shrink_to_fit();
}

//
// WordRef
//

WordRef::WordRef(Ref<WordDef> _def, bool _act) : def(std::move(_def)), active(_act) {
}
WordRef::WordRef(StackWordFunc func) : def(Ref<StackWord>{true, std::move(func)}), active(false) {
}
WordRef::WordRef(CtxWordFunc func, bool _act) : def(Ref<CtxWord>{true, std::move(func)}), active(_act) {
}
Ref<WordDef> WordRef::get_def() const& {
  return def;
}
Ref<WordDef> WordRef::get_def() && {
  return std::move(def);
}
void WordRef::operator()(IntCtx& ctx) const {
  def->run(ctx);
}
bool WordRef::is_active() const {
  return active;
}

//
// Dictionary
//
WordRef* Dictionary::lookup(td::Slice name) {
  auto it = words_.find(name);
  if (it == words_.end()) {
    return nullptr;
  }
  return &it->second;
}
void Dictionary::def_ctx_word(std::string name, CtxWordFunc func) {
  def_word(std::move(name), std::move(func));
}

void Dictionary::def_active_word(std::string name, CtxWordFunc func) {
  Ref<WordDef> wdef = Ref<CtxWord>{true, std::move(func)};
  def_word(std::move(name), {std::move(wdef), true});
}

void Dictionary::def_stack_word(std::string name, StackWordFunc func) {
  def_word(std::move(name), std::move(func));
}

void Dictionary::def_word(std::string name, WordRef word) {
  auto res = words_.emplace(std::move(name), std::move(word));
  LOG_IF(FATAL, !res.second) << "Cannot redefine word: " << name;
}
void Dictionary::undef_word(td::Slice name) {
  auto it = words_.find(name);
  if (it == words_.end()) {
    return;
  }
  words_.erase(it);
}

void interpret_nop(vm::Stack& stack) {
}
Ref<WordDef> Dictionary::nop_word_def = Ref<StackWord>{true, interpret_nop};

//
// functions for wordef
//
Ref<WordDef> pop_exec_token(vm::Stack& stack) {
  stack.check_underflow(1);
  auto wd_ref = stack.pop().as_object<WordDef>();
  if (wd_ref.is_null()) {
    throw IntError{"execution token expected"};
  }
  return wd_ref;
}

Ref<WordList> pop_word_list(vm::Stack& stack) {
  stack.check_underflow(1);
  auto wl_ref = stack.pop().as_object<WordList>();
  if (wl_ref.is_null()) {
    throw IntError{"word list expected"};
  }
  return wl_ref;
}

void push_argcount(vm::Stack& stack, int args) {
  stack.push_smallint(args);
  stack.push({vm::from_object, Dictionary::nop_word_def});
}

}  // namespace fift
