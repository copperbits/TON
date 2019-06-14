#include "vm/stack.hpp"
#include "vm/continuation.h"
#include "vm/box.hpp"

namespace td {
template class td::Cnt<std::string>;
template class td::Ref<td::Cnt<std::string>>;
template class td::Cnt<std::vector<vm::StackEntry>>;
template class td::Ref<td::Cnt<std::vector<vm::StackEntry>>>;
}  // namespace td

namespace vm {

struct from_object_t from_object;

const char* exception_messages[(int)(Excno::total)] = {
    "normal termination",   "alternative termination", "stack underflow",  "stack overflow", "integer overflow",
    "integer out of range", "invalid opcode",          "type check error", "cell overflow",  "cell underflow",
    "dictionary error",     "unknown error",           "fatal error"};

const char* get_exception_msg(Excno exc_no) {
  if (exc_no >= Excno::none && exc_no < Excno::total) {
    return exception_messages[static_cast<int>(exc_no)];
  } else {
    return "unknown vm exception";
  }
}

static const char HEX_digits[] = "0123456789ABCDEF";

std::string str_to_hex(std::string data, std::string prefix) {
  prefix.reserve(prefix.size() + data.size() * 2);
  for (char c : data) {
    prefix += HEX_digits[(c >> 4) & 15];
    prefix += HEX_digits[c & 15];
  }
  return prefix;
}

std::string StackEntry::to_string() const {
  std::ostringstream os;
  dump(os);
  return std::move(os).str();
}

void StackEntry::dump(std::ostream& os) const {
  switch (tp) {
    case t_null:
      os << "(null)";
      break;
    case t_int:
      os << dec_string(as_int());
      break;
    case t_cell:
      os << "C{" << static_cast<Ref<Cell>>(ref)->get_hash().to_hex() << "}";
      break;
    case t_builder:
      os << "BC{" << static_cast<Ref<CellBuilder>>(ref)->to_hex() << "}";
      break;
    case t_slice: {
      os << "CS{";
      static_cast<Ref<CellSlice>>(ref)->dump(os, 1, false);
      os << '}';
      break;
    }
    case t_string:
      os << "\"" << as_string() << "\"";
      break;
    case t_bytes:
      os << "BYTES:" << str_to_hex(as_bytes());
      break;
    case t_box: {
      os << "Box{" << (const void*)&*ref << "}";
      break;
    }
    case t_tuple: {
      const auto& tuple = *static_cast<Ref<Tuple>>(ref);
      auto n = tuple.size();
      if (!n) {
        os << "[]";
      } else if (n == 1) {
        os << "[ ";
        tuple[0].dump(os);
        os << " ]";
      } else {
        os << "[ ";
        for (const auto& entry : tuple) {
          entry.dump(os);
          os << ' ';
        }
        os << ']';
      }
      break;
    }
    case t_object: {
      os << "Object{" << (const void*)&*ref << "}";
      break;
    }
    default:
      os << "???";
  }
}

void StackEntry::print_list(std::ostream& os) const {
  switch (tp) {
    case t_null:
      os << "()";
      break;
    case t_tuple: {
      const auto& tuple = *static_cast<Ref<Tuple>>(ref);
      auto n = tuple.size();
      if (!n) {
        os << "[]";
      } else if (n == 1) {
        os << "[";
        tuple[0].print_list(os);
        os << "]";
      } else if (n != 2) {
        os << "[";
        unsigned c = 0;
        for (const auto& entry : tuple) {
          if (c++) {
            os << ", ";
          }
          entry.print_list(os);
        }
        os << ']';
      } else {
        os << '(';
        tuple[0].print_list(os);
        tuple[1].print_list_tail(os);
      }
      break;
    }
    default:
      dump(os);
  }
}

void StackEntry::print_list_tail(std::ostream& os) const {
  switch (tp) {
    case t_null:
      os << ')';
      break;
    case t_tuple: {
      const auto& tuple = *static_cast<Ref<Tuple>>(ref);
      if (tuple.size() == 2) {
        os << ' ';
        tuple[0].print_list(os);
        tuple[1].print_list_tail(os);
        break;
      }
    }
    // fall through
    default:
      os << " . ";
      print_list(os);
      os << ')';
  }
}

StackEntry::StackEntry(Ref<Stack> stack_ref) : ref(std::move(stack_ref)), tp(t_stack) {
}

StackEntry::StackEntry(Ref<Continuation> cont_ref) : ref(std::move(cont_ref)), tp(t_vmcont) {
}

Ref<Continuation> StackEntry::as_cont() const & {
  return as<Continuation, t_vmcont>();
}

Ref<Continuation> StackEntry::as_cont() && {
  return move_as<Continuation, t_vmcont>();
}

StackEntry::StackEntry(Ref<Box> box_ref) : ref(std::move(box_ref)), tp(t_box) {
}

Ref<Box> StackEntry::as_box() const & {
  return as<Box, t_box>();
}

Ref<Box> StackEntry::as_box() && {
  return move_as<Box, t_box>();
}

StackEntry::StackEntry(Ref<Tuple> tuple_ref) : ref(std::move(tuple_ref)), tp(t_tuple) {
}

Ref<Tuple> StackEntry::as_tuple() const & {
  return as<Tuple, t_tuple>();
}

Ref<Tuple> StackEntry::as_tuple() && {
  return move_as<Tuple, t_tuple>();
}

Ref<Tuple> StackEntry::as_tuple_range(unsigned max_len, unsigned min_len) const & {
  auto t = as<Tuple, t_tuple>();
  if (t.not_null() && t->size() <= max_len && t->size() >= min_len) {
    return t;
  } else {
    return {};
  }
}

Ref<Tuple> StackEntry::as_tuple_range(unsigned max_len, unsigned min_len) && {
  auto t = move_as<Tuple, t_tuple>();
  if (t.not_null() && t->size() <= max_len && t->size() >= min_len) {
    return t;
  } else {
    return {};
  }
}

Stack::Stack(const Stack& old_stack, unsigned copy_elem, unsigned skip_top) {
  push_from_stack(old_stack, copy_elem, skip_top);
}

Stack::Stack(Stack&& old_stack, unsigned copy_elem, unsigned skip_top) {
  push_from_stack(old_stack, copy_elem, skip_top);
}

void Stack::push_from_stack(const Stack& old_stack, unsigned copy_elem, unsigned skip_top) {
  unsigned n = old_stack.depth();
  if (skip_top > n || copy_elem > n - skip_top) {
    throw VmError{Excno::stk_und, "cannot construct stack from another one: not enough elements"};
  }
  stack.reserve(stack.size() + copy_elem);
  auto it = old_stack.stack.cend() - skip_top;
  std::copy(it - copy_elem, it, std::back_inserter(stack));
}

void Stack::push_from_stack(Stack&& old_stack, unsigned copy_elem, unsigned skip_top) {
  unsigned n = old_stack.depth();
  if (skip_top > n || copy_elem > n - skip_top) {
    throw VmError{Excno::stk_und, "cannot construct stack from another one: not enough elements"};
  }
  stack.reserve(stack.size() + copy_elem);
  auto it = old_stack.stack.cend() - skip_top;
  std::move(it - copy_elem, it, std::back_inserter(stack));
}

void Stack::move_from_stack(Stack& old_stack, unsigned copy_elem) {
  unsigned n = old_stack.depth();
  if (copy_elem > n) {
    throw VmError{Excno::stk_und, "cannot construct stack from another one: not enough elements"};
  }
  LOG(DEBUG) << "moving " << copy_elem << " top elements to another stack\n";
  stack.reserve(stack.size() + copy_elem);
  auto it = old_stack.stack.cend();
  std::move(it - copy_elem, it, std::back_inserter(stack));
  old_stack.pop_many(copy_elem);
}

td::RefInt256 Stack::pop_int() {
  check_underflow(1);
  td::RefInt256 res = pop().as_int();
  if (res.is_null()) {
    throw VmError{Excno::type_chk, "not an integer"};
  }
  return res;
}

td::RefInt256 Stack::pop_int_finite() {
  auto res = pop_int();
  if (!res->is_valid()) {
    throw VmError{Excno::int_ov};
  }
  return res;
}

bool Stack::pop_bool() {
  return sgn(pop_int_finite()) != 0;
}

long long Stack::pop_long() {
  return pop_int()->to_long();
}

long long Stack::pop_long_range(long long max, long long min) {
  auto res = pop_long();
  if (res > max || res < min) {
    throw VmError{Excno::range_chk};
  }
  return res;
}

int Stack::pop_smallint_range(int max, int min) {
  return (int)pop_long_range(max, min);
}

Ref<Cell> Stack::pop_cell() {
  check_underflow(1);
  auto res = pop().as_cell();
  if (res.is_null()) {
    throw VmError{Excno::type_chk, "not a cell"};
  }
  return res;
}

Ref<CellBuilder> Stack::pop_builder() {
  check_underflow(1);
  auto res = pop().as_builder();
  if (res.is_null()) {
    throw VmError{Excno::type_chk, "not a cell builder"};
  }
  return res;
}

Ref<CellSlice> Stack::pop_cellslice() {
  check_underflow(1);
  auto res = pop().as_slice();
  if (res.is_null()) {
    throw VmError{Excno::type_chk, "not a cell slice"};
  }
  return res;
}

std::string Stack::pop_string() {
  check_underflow(1);
  auto res = pop().as_string_ref();
  if (res.is_null()) {
    throw VmError{Excno::type_chk, "not a string"};
  }
  return *res;
}

std::string Stack::pop_bytes() {
  check_underflow(1);
  auto res = pop().as_bytes_ref();
  if (res.is_null()) {
    throw VmError{Excno::type_chk, "not a bytes chunk"};
  }
  return *res;
}

Ref<Continuation> Stack::pop_cont() {
  check_underflow(1);
  auto res = pop().as_cont();
  if (res.is_null()) {
    throw VmError{Excno::type_chk, "not a continuation"};
  }
  return res;
}

Ref<Box> Stack::pop_box() {
  check_underflow(1);
  auto res = pop().as_box();
  if (res.is_null()) {
    throw VmError{Excno::type_chk, "not a box"};
  }
  return res;
}

Ref<Tuple> Stack::pop_tuple() {
  check_underflow(1);
  auto res = pop().as_tuple();
  if (res.is_null()) {
    throw VmError{Excno::type_chk, "not a tuple"};
  }
  return res;
}

Ref<Tuple> Stack::pop_tuple_range(unsigned max_len, unsigned min_len) {
  check_underflow(1);
  auto res = pop().as_tuple();
  if (res.is_null() || res->size() > max_len || res->size() < min_len) {
    throw VmError{Excno::type_chk, "not a tuple of valid size"};
  }
  return res;
}

void Stack::push_int(td::RefInt256 val) {
  if (!val->signed_fits_bits(257)) {
    throw VmError{Excno::int_ov};
  }
  push(std::move(val));
}

void Stack::push_int_quiet(td::RefInt256 val, bool quiet) {
  if (!val->signed_fits_bits(257)) {
    if (!quiet) {
      throw VmError{Excno::int_ov};
    } else if (val->is_valid()) {
      push(td::RefInt256{true});
      return;
    }
  }
  push(std::move(val));
}

void Stack::push_string(std::string str) {
  push(std::move(str));
}

void Stack::push_bytes(std::string str) {
  push(std::move(str), true);
}

void Stack::push_cell(Ref<Cell> cell) {
  push(std::move(cell));
}

void Stack::push_builder(Ref<CellBuilder> cb) {
  push(std::move(cb));
}

void Stack::push_smallint(long long val) {
  push(td::RefInt256{true, val});
}

void Stack::push_bool(bool val) {
  push_smallint(val ? -1 : 0);
}

void Stack::push_cont(Ref<Continuation> cont) {
  push(std::move(cont));
}

void Stack::push_box(Ref<Box> box) {
  push(std::move(box));
}

void Stack::push_tuple(Ref<Tuple> tuple) {
  push(std::move(tuple));
}

Ref<Stack> Stack::split_top(unsigned top_cnt, unsigned drop_cnt) {
  unsigned n = depth();
  if (top_cnt > n || drop_cnt > n - top_cnt) {
    return Ref<Stack>{};
  }
  Ref<Stack> new_stk = Ref<Stack>{true};
  if (top_cnt) {
    new_stk.unique_write().move_from_stack(*this, top_cnt);
  }
  if (drop_cnt) {
    pop_many(drop_cnt);
  }
  return new_stk;
}

void Stack::dump(std::ostream& os, bool cr) const {
  os << " [ ";
  for (const auto& x : stack) {
    os << x.to_string() << ' ';
  }
  os << "] ";
  if (cr) {
    os << std::endl;
  }
}
void Stack::push_cellslice(Ref<CellSlice> cs) {
  push(std::move(cs));
}

}  // namespace vm
