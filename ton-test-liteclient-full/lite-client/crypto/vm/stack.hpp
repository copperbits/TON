#pragma once

#include <cassert>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include "common/refcnt.hpp"
#include "common/bigint.hpp"
#include "common/refint.h"
#include "common/bitstring.h"
#include "vm/cells.h"
#include "vm/cellslice.h"
#include "vm/excno.hpp"

namespace td {
extern template class td::Cnt<std::string>;
extern template class td::Ref<td::Cnt<std::string>>;
}  // namespace td

namespace vm {

using td::Cnt;
using td::Ref;
using td::RefAny;

const char* get_exception_msg(Excno exc_no);
std::string str_to_hex(std::string data, std::string prefix = "");

class Stack;
class Continuation;

extern struct from_object_t {
} from_object;

class StackEntry {
 public:
  enum Type { t_null, t_int, t_cell, t_builder, t_slice, t_vmcont, t_stack, t_string, t_bytes, t_bitstring, t_object };

 private:
  RefAny ref;
  Type tp;

 public:
  StackEntry() : ref(), tp(t_null) {
  }
  ~StackEntry() {
  }
  StackEntry(Ref<Cell> cell_ref) : ref(std::move(cell_ref)), tp(t_cell) {
  }
  StackEntry(Ref<CellBuilder> cb_ref) : ref(std::move(cb_ref)), tp(t_builder) {
  }
  StackEntry(Ref<CellSlice> cs_ref) : ref(std::move(cs_ref)), tp(t_slice) {
  }
  StackEntry(td::RefInt256 int_ref) : ref(std::move(int_ref)), tp(t_int) {
  }
  StackEntry(std::string str, bool bytes = false) : ref(), tp(bytes ? t_bytes : t_string) {
    auto cnt_str = new Cnt<std::string>{std::move(str)};
    ref = Ref<Cnt<std::string>>{cnt_str};
  }
  StackEntry(Ref<Stack> stack_ref);
  StackEntry(Ref<Continuation> cont_ref);
  StackEntry(const StackEntry& se) noexcept : ref(se.ref), tp(se.tp) {
  }
  StackEntry(StackEntry&& se) noexcept : ref(std::move(se.ref)), tp(se.tp) {
    se.tp = t_null;
  }
  template <class T>
  StackEntry(from_object_t, Ref<T> obj_ref) : ref(std::move(obj_ref)), tp(t_object) {
  }
  StackEntry& operator=(const StackEntry& se) {
    ref = se.ref;
    tp = se.tp;
    return *this;
  }
  StackEntry& operator=(StackEntry&& se) {
    ref = std::move(se.ref);
    tp = se.tp;
    se.tp = t_null;
    return *this;
  }
  StackEntry& clear() {
    ref.clear();
    tp = t_null;
    return *this;
  }
  void swap(StackEntry& se) {
    ref.swap(se.ref);
    std::swap(tp, se.tp);
  }
  Type type() const {
    return tp;
  }
  td::RefInt256 as_int() const & {
    return tp == t_int ? static_cast<td::RefInt256>(ref) : td::RefInt256{false};
  }
  td::RefInt256 as_int() && {
    return tp == t_int ? static_cast<td::RefInt256>(std::move(ref)) : td::RefInt256{};
  }
  Ref<Cell> as_cell() const & {
    return tp == t_cell ? static_cast<Ref<Cell>>(ref) : Ref<Cell>{};
  }
  Ref<Cell> as_cell() && {
    return tp == t_cell ? static_cast<Ref<Cell>>(std::move(ref)) : Ref<Cell>{};
  }
  Ref<CellBuilder> as_builder() const & {
    return tp == t_builder ? static_cast<Ref<CellBuilder>>(ref) : Ref<CellBuilder>{};
  }
  Ref<CellBuilder> as_builder() && {
    return tp == t_builder ? static_cast<Ref<CellBuilder>>(std::move(ref)) : Ref<CellBuilder>{};
  }
  Ref<CellSlice> as_slice() const & {
    return tp == t_slice ? static_cast<Ref<CellSlice>>(ref) : Ref<CellSlice>{};
  }
  Ref<CellSlice> as_slice() && {
    return tp == t_slice ? static_cast<Ref<CellSlice>>(std::move(ref)) : Ref<CellSlice>{};
  }
  Ref<Continuation> as_cont() const &;
  Ref<Continuation> as_cont() &&;
  Ref<Cnt<std::string>> as_string_ref() const {
    return tp == t_string ? static_cast<Ref<Cnt<std::string>>>(ref) : Ref<Cnt<std::string>>{};
  }
  Ref<Cnt<std::string>> as_bytes_ref() const {
    return tp == t_bytes ? static_cast<Ref<Cnt<std::string>>>(ref) : Ref<Cnt<std::string>>{};
  }
  std::string as_string() const {
    assert(!as_string_ref().is_null());
    return tp == t_string ? **as_string_ref() : "";
  }
  std::string as_bytes() const {
    return tp == t_bytes ? **as_bytes_ref() : "";
  }
  template <class T>
  Ref<T> as_object() const & {
    return tp == t_object ? static_cast<Ref<T>>(ref) : Ref<T>{};
  }
  template <class T>
  Ref<T> as_object() && {
    return tp == t_object ? static_cast<Ref<T>>(std::move(ref)) : Ref<T>{};
  }
  std::string to_string() const;
};

inline void swap(StackEntry& se1, StackEntry& se2) {
  se1.swap(se2);
}

class Stack : public td::CntObject {
  std::vector<StackEntry> stack;

 public:
  Stack() {
  }
  ~Stack() override = default;
  Stack(const std::vector<StackEntry>& _stack) : stack(_stack) {
  }
  Stack(std::vector<StackEntry>&& _stack) : stack(std::move(_stack)) {
  }
  Stack(const Stack& old_stack, unsigned copy_elem, unsigned skip_top);
  Stack(Stack&& old_stack, unsigned copy_elem, unsigned skip_top);
  td::CntObject* make_copy() const override {
    std::cerr << "copy stack at " << (const void*)this << " (" << depth() << " entries)\n";
    return new Stack{stack};
  }
  void push_from_stack(const Stack& old_stack, unsigned copy_elem, unsigned skip_top = 0);
  void push_from_stack(Stack&& old_stack, unsigned copy_elem, unsigned skip_top = 0);
  void move_from_stack(Stack& old_stack, unsigned copy_elem);
  Ref<Stack> split_top(unsigned top_cnt, unsigned drop_cnt = 0);

  StackEntry& push() {
    stack.emplace_back();
    return stack.back();
  }
  template <typename... Args>
  StackEntry& push(Args&&... args) {
    stack.emplace_back(args...);
    return stack.back();
  }
  StackEntry& push(const StackEntry& se) {
    stack.push_back(se);
    return stack.back();
  }
  StackEntry& push(StackEntry&& se) {
    stack.emplace_back(std::move(se));
    return stack.back();
  }
  void pop(StackEntry& se) {
    stack.back().swap(se);
    stack.pop_back();
  }
  StackEntry pop() {
    StackEntry res = std::move(stack.back());
    stack.pop_back();
    return res;
  }
  void pop_many(int count) {
    stack.resize(stack.size() - count);
  }
  void drop_bottom(int count) {
    std::move(stack.cbegin() + count, stack.cend(), stack.begin());
    pop_many(count);
  }
  StackEntry& operator[](int idx) {  // NB: we sometimes use idx=-1
    return stack[stack.size() - idx - 1];
  }
  const StackEntry& operator[](int idx) const {
    return stack[stack.size() - idx - 1];
  }
  StackEntry& at(int idx) {
    return stack.at(stack.size() - idx - 1);
  }
  const StackEntry& at(int idx) const {
    return stack.at(stack.size() - idx - 1);
  }
  StackEntry fetch(int idx) const {
    return stack[stack.size() - idx - 1];
  }
  StackEntry& tos() {
    return stack.back();
  }
  const StackEntry& tos() const {
    return stack.back();
  }
  bool is_empty() const {
    return stack.empty();
  }
  int depth() const {
    return (int)stack.size();
  }
  std::vector<StackEntry>::iterator top() {
    return stack.end();
  }
  std::vector<StackEntry>::const_iterator top() const {
    return stack.cend();
  }
  std::vector<StackEntry>::iterator from_top(int offs) {
    return stack.end() - offs;
  }
  std::vector<StackEntry>::const_iterator from_top(int offs) const {
    return stack.cend() - offs;
  }
  bool at_least(int req) const {
    return depth() >= req;
  }
  template <typename... Args>
  bool at_least(int req, Args... args) const {
    return at_least(req) && at_least(args...);
  }
  bool more_than(int req) const {
    return depth() > req;
  }
  template <typename... Args>
  bool more_than(int req, Args... args) const {
    return more_than(req) && more_than(args...);
  }
  void clear() {
    stack.clear();
  }
  Stack& set_contents(const Stack& other_stack) {
    stack = other_stack.stack;
    return *this;
  }
  Stack& set_contents(Stack&& other_stack) {
    stack = std::move(other_stack.stack);
    return *this;
  }
  Stack& set_contents(Ref<Stack> ref) {
    if (ref.is_null()) {
      clear();
    } else if (ref->is_unique()) {
      set_contents(std::move(ref.unique_write()));
    } else {
      set_contents(*ref);
    }
    return *this;
  }
  template <typename... Args>
  const Stack& check_underflow(Args... args) const {
    if (!at_least(args...)) {
      throw VmError{Excno::stk_und};
    }
    return *this;
  }
  template <typename... Args>
  Stack& check_underflow(Args... args) {
    if (!at_least(args...)) {
      throw VmError{Excno::stk_und};
    }
    return *this;
  }
  template <typename... Args>
  const Stack& check_underflow_p(Args... args) const {
    if (!more_than(args...)) {
      throw VmError{Excno::stk_und};
    }
    return *this;
  }
  template <typename... Args>
  Stack& check_underflow_p(Args... args) {
    if (!more_than(args...)) {
      throw VmError{Excno::stk_und};
    }
    return *this;
  }
  Stack& reserve(int cnt) {
    stack.reserve(cnt);
    return *this;
  }
  td::RefInt256 pop_int();
  td::RefInt256 pop_int_finite();
  bool pop_bool();
  long long pop_long();
  long long pop_long_range(long long max, long long min = 0);
  int pop_smallint_range(int max, int min = 0);
  Ref<Cell> pop_cell();
  Ref<CellBuilder> pop_builder();
  Ref<CellSlice> pop_cellslice();
  Ref<Continuation> pop_cont();
  std::string pop_string();
  std::string pop_bytes();
  void push_int(td::RefInt256 val);
  void push_int_quiet(td::RefInt256 val, bool quiet = true);
  void push_smallint(long long val);
  void push_bool(bool val);
  void push_string(std::string str);
  void push_bytes(std::string str);
  void push_cell(Ref<Cell> cell);
  void push_builder(Ref<CellBuilder> cb);
  void push_cellslice(Ref<CellSlice> cs);
  void push_cont(Ref<Continuation> cont);
  void dump(std::ostream& os, bool cr = true) const;
};

}  // namespace vm
