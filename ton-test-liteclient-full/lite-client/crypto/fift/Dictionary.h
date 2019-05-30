#pragma once

#include <functional>
#include <map>

#include "IntCtx.h"

namespace fift {
using td::Ref;
/*
 *
 *    WORD CLASSES
 *
 */

typedef std::function<void(vm::Stack&)> StackWordFunc;
typedef std::function<void(IntCtx&)> CtxWordFunc;

class WordDef : public td::CntObject {
 public:
  WordDef() = default;
  virtual ~WordDef() override = default;
  virtual void run(IntCtx& ctx) const = 0;
};

class StackWord : public WordDef {
  StackWordFunc f;

 public:
  StackWord(StackWordFunc _f);
  virtual ~StackWord() override = default;
  void run(IntCtx& ctx) const override;
};

class CtxWord : public WordDef {
  CtxWordFunc f;

 public:
  CtxWord(CtxWordFunc _f);
  virtual ~CtxWord() override = default;
  void run(IntCtx& ctx) const override;
};

class WordList : public WordDef {
  std::vector<Ref<WordDef>> list;

 public:
  virtual ~WordList() override = default;
  WordList() = default;
  WordList(std::vector<Ref<WordDef>>&& _list);
  WordList(const std::vector<Ref<WordDef>>& _list);
  WordList& push_back(Ref<WordDef> word_def);
  WordList& push_back(WordDef& wd);
  void run(IntCtx& ctx) const override;
  void close();
};

class WordRef {
  Ref<WordDef> def;
  bool active;

 public:
  WordRef() = delete;
  WordRef(const WordRef& ref) = default;
  WordRef(WordRef&& ref) = default;
  WordRef(Ref<WordDef> _def, bool _act = false);
  WordRef(StackWordFunc func);
  WordRef(CtxWordFunc func, bool _act = false);
  //WordRef(const std::vector<Ref<WordDef>>& word_list);
  //WordRef(std::vector<Ref<WordDef>>&& word_list);
  WordRef& operator=(const WordRef&) = default;
  WordRef& operator=(WordRef&&) = default;
  Ref<WordDef> get_def() const&;
  Ref<WordDef> get_def() &&;
  void operator()(IntCtx& ctx) const;
  bool is_active() const;
  ~WordRef() = default;
};

/*
WordRef::WordRef(const std::vector<Ref<WordDef>>& word_list) : def(Ref<WordList>{true, word_list}) {
}

WordRef::WordRef(std::vector<Ref<WordDef>>&& word_list) : def(Ref<WordList>{true, std::move(word_list)}) {
}
*/

/*
 *
 *    DICTIONARIES
 *
 */

class Dictionary {
 public:
  WordRef* lookup(td::Slice name);
  void def_ctx_word(std::string name, CtxWordFunc func);
  void def_active_word(std::string name, CtxWordFunc func);
  void def_stack_word(std::string name, StackWordFunc func);
  void def_word(std::string name, WordRef word);
  void undef_word(td::Slice name);

  auto begin() const {
    return words_.begin();
  }
  auto end() const {
    return words_.end();
  }

  static Ref<WordDef> nop_word_def;

 private:
  std::map<std::string, WordRef, std::less<>> words_;
};

/*
 *
 *      AUX FUNCTIONS FOR WORD DEFS
 *
 */

Ref<WordDef> pop_exec_token(vm::Stack& stack);
Ref<WordList> pop_word_list(vm::Stack& stack);
void push_argcount(vm::Stack& stack, int args);
}  // namespace fift
