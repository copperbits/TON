#include <vector>
#include <map>
#include <string>
#include <stack>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <getopt.h>
#include "common/refcnt.hpp"
#include "common/bigint.hpp"
#include "common/refint.h"
#include "srcread.hpp"
#include "lexer.hpp"
#include "symtable.hpp"
#include "func.h"

namespace src {

int lexem_is_special(std::string str) {
  return 0;  // no special lexems
}

int compute_symbol_subclass(std::string str) {
  return 0;  // no symbol/identifier subclasses
}

/*
 * 
 *   KEYWORD DEFINITION
 * 
 */

void define_keywords() {
  symbols.add_kw_char('+');
  symbols.add_kw_char('-');
  symbols.add_kw_char('*');
  symbols.add_kw_char('/');
  symbols.add_kw_char('%');
  symbols.add_kw_char(':');
  symbols.add_kw_char(',');
  symbols.add_kw_char(';');
  symbols.add_kw_char('(');
  symbols.add_kw_char(')');
  symbols.add_kw_char('{');
  symbols.add_kw_char('}');
  symbols.add_kw_char('=');
  symbols.add_kw_char('_');
  symbols.add_kw_char('<');
  symbols.add_kw_char('>');
  symbols.add_kw_char('&');
  symbols.add_kw_char('|');

  using Kw = funC::Keyword;
  symbols.add_keyword("==", Kw::_Eq);
  symbols.add_keyword("!=", Kw::_Neq);
  symbols.add_keyword("<=", Kw::_Leq);
  symbols.add_keyword(">=", Kw::_Geq);
  symbols.add_keyword("<<", Kw::_Lshift);
  symbols.add_keyword(">>", Kw::_Rshift);
  symbols.add_keyword(">>~", Kw::_RshiftR);
  symbols.add_keyword(">>^", Kw::_RshiftC);
  symbols.add_keyword("/~", Kw::_DivR);
  symbols.add_keyword("/^", Kw::_DivC);
  symbols.add_keyword("/%", Kw::_DivMod);
  symbols.add_keyword("+=", Kw::_PlusLet);
  symbols.add_keyword("-=", Kw::_MinusLet);
  symbols.add_keyword("*=", Kw::_TimesLet);
  symbols.add_keyword("/=", Kw::_DivLet);
  symbols.add_keyword("%=", Kw::_ModLet);
  symbols.add_keyword("/~=", Kw::_DivRLet);
  symbols.add_keyword("/^=", Kw::_DivCLet);
  symbols.add_keyword("<<=", Kw::_LshiftLet);
  symbols.add_keyword(">>=", Kw::_RshiftLet);
  symbols.add_keyword(">>~=", Kw::_RshiftRLet);
  symbols.add_keyword(">>^=", Kw::_RshiftCLet);

  symbols.add_keyword("return", Kw::_Return);
  symbols.add_keyword("var", Kw::_Var);
  symbols.add_keyword("repeat", Kw::_Repeat);
  symbols.add_keyword("do", Kw::_Do);
  symbols.add_keyword("while", Kw::_While);
  symbols.add_keyword("until", Kw::_Until);
  symbols.add_keyword("if", Kw::_If);
  symbols.add_keyword("then", Kw::_Then);
  symbols.add_keyword("else", Kw::_Else);
  symbols.add_keyword("elseif", Kw::_Elseif);

  symbols.add_keyword("int", Kw::_Int);
  symbols.add_keyword("cell", Kw::_Cell);
  symbols.add_keyword("slice", Kw::_Slice);
  symbols.add_keyword("builder", Kw::_Builder);
  symbols.add_keyword("cont", Kw::_Cont);
  symbols.add_keyword("->", Kw::_Mapsto);

  symbols.add_keyword("extern", Kw::_Extern);
  symbols.add_keyword("operator", Kw::_Operator);
  symbols.add_keyword("infix", Kw::_Infix);
  symbols.add_keyword("infixl", Kw::_Infixl);
  symbols.add_keyword("infixr", Kw::_Infixr);
}

}  // namespace src

namespace funC {
using src::Lexer;
using src::symbols;
using td::Ref;

/*
 * 
 *   TYPE EXPRESSIONS
 * 
 */

int TypeExpr::holes = 0;  // not thread safe, but it is ok for now

void TypeExpr::compute_width() {
  switch (constr) {
    case te_Atomic:
    case te_Map:
      minw = maxw = 1;
      break;
    case te_Tensor:
      minw = maxw = 0;
      for (TypeExpr* arg : args) {
        minw += arg->minw;
        maxw += arg->maxw;
      }
      if (minw > w_inf) {
        minw = w_inf;
      }
      if (maxw > w_inf) {
        maxw = w_inf;
      }
      break;
    case te_Indirect:
      minw = args[0]->minw;
      maxw = args[0]->maxw;
      break;
    default:
      minw = 0;
      maxw = w_inf;
      break;
  }
}

bool TypeExpr::recompute_width() {
  switch (constr) {
    case te_Tensor:
    case te_Indirect: {
      int min = 0, max = 0;
      for (TypeExpr* arg : args) {
        min += arg->minw;
        max += arg->maxw;
      }
      if (min > maxw || max < minw) {
        return false;
      }
      if (min > w_inf) {
        min = w_inf;
      }
      if (max > w_inf) {
        max = w_inf;
      }
      if (minw < min) {
        minw = min;
      }
      if (maxw > max) {
        maxw = max;
      }
      return true;
    }
    default:
      return false;
  }
}

int TypeExpr::extract_components(std::vector<TypeExpr*>& comp_list) {
  if (constr != te_Indirect && constr != te_Tensor) {
    comp_list.push_back(this);
    return 1;
  }
  int res = 0;
  for (TypeExpr* arg : args) {
    res += arg->extract_components(comp_list);
  }
  return res;
}

TypeExpr* TypeExpr::new_map(TypeExpr* from, TypeExpr* to) {
  return new TypeExpr{te_Map, std::vector<TypeExpr*>{from, to}};
}

void TypeExpr::replace_with(TypeExpr* te2) {
  if (te2 == this) {
    return;
  }
  constr = te_Indirect;
  value = 0;
  minw = te2->minw;
  maxw = te2->maxw;
  args.clear();
  args.push_back(te2);
}

bool TypeExpr::remove_indirect(TypeExpr*& te, TypeExpr* forbidden) {
  assert(te);
  while (te->constr == te_Indirect) {
    te = te->args[0];
  }
  if (te->constr == te_Unknown) {
    return te == forbidden;
  }
  bool res = false;
  for (auto& x : te->args) {
    res |= remove_indirect(x, forbidden);
  }
  return res;
}

void TypeExpr::show_width(std::ostream& os) {
  os << minw;
  if (maxw != minw) {
    os << "..";
    if (maxw < w_inf) {
      os << maxw;
    }
  }
}

std::ostream& operator<<(std::ostream& os, TypeExpr* type_expr) {
  if (!type_expr) {
    return os << "(null-type-ptr)";
  }
  return type_expr->print(os);
}

std::ostream& TypeExpr::print(std::ostream& os, int lex_level) {
  switch (constr) {
    case te_Unknown:
      return os << "??" << value;
    case te_Indirect:
      return os << args[0];
    case te_Atomic: {
      switch (value) {
        case _Int:
          return os << "int";
        case _Cell:
          return os << "cell";
        case _Slice:
          return os << "slice";
        case _Builder:
          return os << "builder";
        case _Cont:
          return os << "cont";
        case _Type:
          return os << "type";
        default:
          return os << "atomic-type-" << value;
      }
    }
    case te_Tensor: {
      os << "(";
      auto c = args.size();
      if (c) {
        for (const auto& x : args) {
          x->print(os);
          if (--c) {
            os << ", ";
          }
        }
      }
      return os << ")";
    }
    case te_Map: {
      assert(args.size() == 2);
      if (lex_level > 0) {
        os << "(";
      }
      args[0]->print(os, 1);
      os << " -> ";
      args[1]->print(os);
      if (lex_level > 0) {
        os << ")";
      }
      return os;
    }
    default:
      return os << "unknown-type-expr-" << constr;
  }
}

struct UniformizeError {
  TypeExpr* te1;
  TypeExpr* te2;
  std::string msg;
  UniformizeError(TypeExpr* _te1, TypeExpr* _te2, std::string _msg = "") : te1(_te1), te2(_te2), msg(_msg) {
  }
  void print_message(std::ostream& os) const;
  std::string message() const;
};

void UniformizeError::print_message(std::ostream& os) const {
  os << "cannot unify type " << te1 << " with " << te2;
  if (!msg.empty()) {
    os << ": " << msg;
  }
}

std::ostream& operator<<(std::ostream& os, const UniformizeError& ue) {
  ue.print_message(os);
  return os;
}

std::string UniformizeError::message() const {
  std::ostringstream os;
  UniformizeError::print_message(os);
  return os.str();
}

void check_width_compat(TypeExpr* te1, TypeExpr* te2) {
  if (te1->minw > te2->maxw || te2->minw > te1->maxw) {
    std::ostringstream os{"cannot uniformize types of widths "};
    te1->show_width(os);
    os << " and ";
    te2->show_width(os);
    throw UniformizeError{te1, te2, os.str()};
  }
}

void check_update_widths(TypeExpr* te1, TypeExpr* te2) {
  check_width_compat(te1, te2);
  te1->minw = te2->minw = std::max(te1->minw, te2->minw);
  te1->maxw = te2->maxw = std::min(te1->maxw, te2->maxw);
  assert(te1->minw <= te2->minw);
}

void uniformize(TypeExpr*& te1, TypeExpr*& te2) {
  assert(te1 && te2);
  // std::cerr << "uniformize( " << te1 << " , " << te2 << " )\n";
  while (te1->constr == TypeExpr::te_Indirect) {
    te1 = te1->args[0];
  }
  while (te2->constr == TypeExpr::te_Indirect) {
    te2 = te2->args[0];
  }
  if (te1 == te2) {
    return;
  }
  if (te1->constr == TypeExpr::te_Unknown) {
    if (te2->constr == TypeExpr::te_Unknown) {
      assert(te1->value != te2->value);
    }
    if (TypeExpr::remove_indirect(te2, te1)) {
      throw UniformizeError{te1, te2, "uniformization results in an infinite cyclic type"};
    }
    check_update_widths(te1, te2);
    te1->replace_with(te2);
    te1 = te2;
    return;
  }
  if (te2->constr == TypeExpr::te_Unknown) {
    if (TypeExpr::remove_indirect(te1, te2)) {
      throw UniformizeError{te2, te1, "uniformization results in an infinite cyclic type"};
    }
    check_update_widths(te2, te1);
    te2->replace_with(te1);
    te2 = te1;
    return;
  }
  if (te1->constr != te2->constr || te1->value != te2->value || te1->args.size() != te2->args.size()) {
    throw UniformizeError{te1, te2};
  }
  for (std::size_t i = 0; i < te1->args.size(); i++) {
    uniformize(te1->args[i], te2->args[i]);
  }
  if (te1->constr == TypeExpr::te_Tensor) {
    if (!te1->recompute_width()) {
      throw UniformizeError{te1, te2, "uniformization incompatible with known width of first type"};
    }
    if (!te2->recompute_width()) {
      throw UniformizeError{te2, te1, "uniformization incompatible with known width of first type"};
    }
    check_update_widths(te1, te2);
  }
  te1->replace_with(te2);
  te1 = te2;
}

/*
 * 
 *   ABSTRACT CODE
 * 
 */

TmpVar::TmpVar(var_idx_t _idx, int _cls, TypeExpr* _type, SymDef* sym, const SrcLocation* loc)
    : v_type(_type), idx(_idx), cls(_cls), coord(0) {
  if (sym) {
    name = sym->sym_idx;
    sym->value->idx = _idx;
  }
  if (loc) {
    where = std::make_unique<SrcLocation>(*loc);
  }
  if (!_type) {
    v_type = TypeExpr::new_hole();
  }
}

void TmpVar::set_location(const SrcLocation& loc) {
  if (where) {
    *where = loc;
  } else {
    where = std::make_unique<SrcLocation>(loc);
  }
}

void TmpVar::dump(std::ostream& os) const {
  show(os);
  os << " : " << v_type << " (width ";
  v_type->show_width(os);
  os << ")";
  if (coord > 0) {
    os << " = _" << (coord >> 8) << '.' << (coord & 255);
  } else if (coord < 0) {
    int n = (~coord >> 8), k = (~coord & 0xff);
    if (k) {
      os << " = (_" << n << ".._" << (n + k - 1) << ")";
    } else {
      os << " = ()";
    }
  }
  os << std::endl;
}

void TmpVar::show(std::ostream& os, int omit_idx) const {
  if (cls & _Named) {
    os << symbols.get_name(name);
    if (omit_idx && (omit_idx >= 2 || (cls & _UniqueName))) {
      return;
    }
  }
  os << '_' << idx;
}

std::ostream& operator<<(std::ostream& os, const TmpVar& var) {
  var.show(os);
  return os;
}

void VarDescr::show_value(std::ostream& os) const {
  if (val & _Int) {
    os << 'i';
  }
  if (val & _Const) {
    os << 'c';
  }
  if (val & _Zero) {
    os << '0';
  }
  if (val & _NonZero) {
    os << '!';
  }
  if (val & _Pos) {
    os << '>';
  }
  if (val & _Neg) {
    os << '<';
  }
  if (val & _Bool) {
    os << 'B';
  }
  if (val & _Bit) {
    os << 'b';
  }
  if (val & _Even) {
    os << 'E';
  }
  if (val & _Odd) {
    os << 'O';
  }
  if (val & _Finite) {
    os << 'f';
  }
  if (val & _Nan) {
    os << 'N';
  }
  if (int_const.not_null()) {
    os << '=' << int_const;
  }
}

void VarDescr::set_const(td::RefInt256 value) {
  int_const = std::move(value);
  if (!int_const->signed_fits_bits(257)) {
    int_const.write().invalidate();
  }
  val = _Const | _Int;
  int s = sgn(int_const);
  if (s < -1) {
    val |= _Nan | _NonZero;
  } else if (s < 0) {
    val |= _NonZero | _Neg | _Finite;
    if (*int_const == -1) {
      val |= _Bool;
    }
  } else if (s > 0) {
    val |= _NonZero | _Pos | _Finite;
  } else if (!s) {
    if (*int_const == 1) {
      val |= _Bit;
    }
    val |= _Zero | _Neg | _Pos | _Finite | _Bool | _Bit;
  }
  if (val & _Finite) {
    val |= int_const->get_bit(0) ? _Odd : _Even;
  }
}

void VarDescr::set_const_nan() {
  set_const(td::RefInt256{true});
}

void VarDescr::operator|=(const VarDescr& y) {
  val &= y.val;
  if (is_int_const() && cmp(int_const, y.int_const) != 0) {
    val &= ~_Const;
  }
  if (!(val & _Const)) {
    int_const.clear();
  }
}

void VarDescr::operator&=(const VarDescr& y) {
  val |= y.val;
  if (y.int_const.not_null() && int_const.is_null()) {
    int_const = y.int_const;
  }
}

void VarDescr::set_value(const VarDescr& y) {
  val = y.val;
  int_const = y.int_const;
}

void VarDescr::set_value(VarDescr&& y) {
  val = y.val;
  int_const = std::move(y.int_const);
}

void VarDescr::clear_value() {
  val = 0;
  int_const.clear();
}

ListIterator<Op> begin(const std::unique_ptr<Op>& op_list) {
  return ListIterator<Op>{op_list.get()};
}

ListIterator<Op> end(const std::unique_ptr<Op>& op_list) {
  return ListIterator<Op>{};
}

ListIterator<const Op> cbegin(const Op* op_list) {
  return ListIterator<const Op>{op_list};
}

ListIterator<const Op> cend(const Op* op_list) {
  return ListIterator<const Op>{};
}

ListIterator<const Op> begin(const Op* op_list) {
  return ListIterator<const Op>{op_list};
}

ListIterator<const Op> end(const Op* op_list) {
  return ListIterator<const Op>{};
}

ListIterator<Op> begin(Op* op_list) {
  return ListIterator<Op>{op_list};
}

ListIterator<Op> end(Op* op_list) {
  return ListIterator<Op>{};
}

void Op::flags_set_clear(int set, int clear) {
  flags = (flags | set) & ~clear;
  for (auto& op : block0) {
    op.flags_set_clear(set, clear);
  }
  for (auto& op : block1) {
    op.flags_set_clear(set, clear);
  }
}
void Op::split_vars(const std::vector<TmpVar>& vars) {
  split_var_list(left, vars);
  split_var_list(right, vars);
  for (auto& op : block0) {
    op.split_vars(vars);
  }
  for (auto& op : block1) {
    op.split_vars(vars);
  }
}

void Op::split_var_list(std::vector<var_idx_t>& var_list, const std::vector<TmpVar>& vars) {
  int new_size = 0, changes = 0;
  for (var_idx_t v : var_list) {
    int c = vars.at(v).coord;
    if (c < 0) {
      ++changes;
      new_size += (~c & 0xff);
    } else {
      ++new_size;
    }
  }
  if (!changes) {
    return;
  }
  std::vector<var_idx_t> new_var_list;
  new_var_list.reserve(new_size);
  for (var_idx_t v : var_list) {
    int c = vars.at(v).coord;
    if (c < 0) {
      int n = (~c >> 8), k = (~c & 0xff);
      while (k-- > 0) {
        new_var_list.push_back(n++);
      }
    } else {
      new_var_list.push_back(v);
    }
  }
  var_list = std::move(new_var_list);
}

void Op::show(std::ostream& os, const std::vector<TmpVar>& vars, std::string pfx, int mode) const {
  if (mode & 2) {
    os << pfx << " [";
    for (const auto& v : var_info.list) {
      os << ' ';
      if (v.flags & VarDescr::_Last) {
        os << '*';
      }
      os << vars[v.idx];
      if (mode & 4) {
        os << ':';
        v.show_value(os);
      }
    }
    os << " ]\n";
  }
  std::string dis = disabled() ? "<disabled> " : "";
  if (noreturn()) {
    dis += "<noret> ";
  }
  switch (cl) {
    case _Undef:
      os << pfx << dis << "???\n";
      break;
    case _Nop:
      os << pfx << dis << "NOP\n";
      break;
    case _Call:
      os << pfx << dis << "CALL: ";
      show_var_list(os, left, vars);
      os << " := " << (fun_ref ? fun_ref->name() : "(null)") << " ";
      if ((mode & 4) && args.size() == right.size()) {
        show_var_list(os, args, vars);
      } else {
        show_var_list(os, right, vars);
      }
      os << std::endl;
      break;
    case _CallInd:
      os << pfx << dis << "CALLIND: ";
      show_var_list(os, left, vars);
      os << " := EXEC ";
      show_var_list(os, right, vars);
      os << std::endl;
      break;
    case _Let:
      os << pfx << dis << "LET ";
      show_var_list(os, left, vars);
      os << " := ";
      show_var_list(os, right, vars);
      os << std::endl;
      break;
    case _IntConst:
      os << pfx << dis << "CONST ";
      show_var_list(os, left, vars);
      os << " := " << int_const << std::endl;
      break;
    case _Import:
      os << pfx << dis << "IMPORT ";
      show_var_list(os, left, vars);
      os << std::endl;
      break;
    case _Return:
      os << pfx << dis << "RETURN ";
      show_var_list(os, left, vars);
      os << std::endl;
      break;
    case _GlobVar:
      os << pfx << dis << "GLOBVAR ";
      show_var_list(os, left, vars);
      os << " := " << (fun_ref ? fun_ref->name() : "(null)") << std::endl;
      break;
    case _Repeat:
      os << pfx << dis << "REPEAT ";
      show_var_list(os, left, vars);
      os << ' ';
      show_block(os, block0.get(), vars, pfx);
      os << std::endl;
      break;
    case _If:
      os << pfx << dis << "IF ";
      show_var_list(os, left, vars);
      os << ' ';
      show_block(os, block0.get(), vars, pfx);
      os << " ELSE ";
      show_block(os, block1.get(), vars, pfx);
      os << std::endl;
      break;
    case _While:
      os << pfx << dis << "WHILE ";
      show_var_list(os, left, vars);
      os << ' ';
      show_block(os, block0.get(), vars, pfx);
      os << " DO ";
      show_block(os, block1.get(), vars, pfx);
      os << std::endl;
      break;
    case _Until:
      os << pfx << dis << "UNTIL ";
      show_var_list(os, left, vars);
      os << ' ';
      show_block(os, block0.get(), vars, pfx);
      os << std::endl;
      break;
    case _Again:
      os << pfx << dis << "AGAIN ";
      show_var_list(os, left, vars);
      os << ' ';
      show_block(os, block0.get(), vars, pfx);
      os << std::endl;
      break;
    default:
      os << pfx << dis << "<???" << cl << "> ";
      show_var_list(os, left, vars);
      os << " -- ";
      show_var_list(os, right, vars);
      os << std::endl;
      break;
  }
}

void Op::show_var_list(std::ostream& os, const std::vector<var_idx_t>& idx_list,
                       const std::vector<TmpVar>& vars) const {
  if (!idx_list.size()) {
    os << "()";
  } else if (idx_list.size() == 1) {
    os << vars.at(idx_list[0]);
  } else {
    os << "(" << vars.at(idx_list[0]);
    for (std::size_t i = 1; i < idx_list.size(); i++) {
      os << "," << vars.at(idx_list[i]);
    }
    os << ")";
  }
}

void Op::show_var_list(std::ostream& os, const std::vector<VarDescr>& list, const std::vector<TmpVar>& vars) const {
  auto n = list.size();
  if (!n) {
    os << "()";
  } else {
    os << "( ";
    for (std::size_t i = 0; i < list.size(); i++) {
      if (i) {
        os << ", ";
      }
      if (list[i].is_unused()) {
        os << '?';
      }
      os << vars.at(list[i].idx) << ':';
      list[i].show_value(os);
    }
    os << " )";
  }
}

void Op::show_block(std::ostream& os, const Op* block, const std::vector<TmpVar>& vars, std::string pfx, int mode) {
  os << "{" << std::endl;
  std::string pfx2 = pfx + "  ";
  for (const Op& op : block) {
    op.show(os, vars, pfx2, mode);
  }
  os << pfx << "}";
}

void CodeBlob::flags_set_clear(int set, int clear) {
  for (auto& op : ops) {
    op.flags_set_clear(set, clear);
  }
}

std::ostream& operator<<(std::ostream& os, const CodeBlob& code) {
  code.print(os);
  return os;
}

void CodeBlob::print(std::ostream& os, int flags) const {
  os << "CODE BLOB: " << var_cnt << " variables, " << in_var_cnt << " input\n";
  for (const auto& var : vars) {
    var.dump(os);
    if (var.where && (flags & 1) != 0) {
      var.where->show(os);
      os << " defined here:\n";
      var.where->show_context(os);
    }
  }
  os << "------- BEGIN --------\n";
  for (const auto& op : ops) {
    op.show(os, vars, "", flags);
  }
  os << "-------- END ---------\n\n";
}

var_idx_t CodeBlob::create_var(int cls, TypeExpr* var_type, SymDef* sym, const SrcLocation* location) {
  vars.emplace_back(var_cnt, cls, var_type, sym, location);
  if (sym) {
    sym->value->idx = var_cnt;
  }
  return var_cnt++;
}

bool CodeBlob::import_params(FormalArgList arg_list) {
  if (var_cnt || in_var_cnt || op_cnt) {
    return false;
  }
  std::vector<var_idx_t> list;
  for (const auto& par : arg_list) {
    TypeExpr* arg_type;
    SymDef* arg_sym;
    SrcLocation arg_loc;
    std::tie(arg_type, arg_sym, arg_loc) = par;
    list.push_back(create_var(arg_sym ? (TmpVar::_In | TmpVar::_Named) : TmpVar::_In, arg_type, arg_sym, &arg_loc));
  }
  emplace_back(loc, Op::_Import, list);
  in_var_cnt = var_cnt;
  return true;
}

/*
 *
 *   SYMBOL VALUES
 * 
 */

int glob_func_cnt, undef_func_cnt;
std::vector<SymDef*> glob_func;

SymDef* predefine_builtin_func(std::string name, TypeExpr* func_type) {
  sym_idx_t name_idx = symbols.lookup(name, 1);
  if (symbols.is_keyword(name_idx)) {
    std::cerr << "fatal: global function `" << name << "` already defined as a keyword" << std::endl;
  }
  SymDef* def = sym::define_global_symbol(name_idx, true);
  if (!def) {
    std::cerr << "fatal: global function `" << name << "` already defined" << std::endl;
    std::exit(1);
  }
  return def;
}

void define_builtin_func(std::string name, TypeExpr* func_type, const AsmOp& macro) {
  SymDef* def = predefine_builtin_func(name, func_type);
  def->value = new SymValBuiltinFunc{func_type, macro};
}

void define_builtin_func(std::string name, TypeExpr* func_type, const simple_compile_func_t func) {
  SymDef* def = predefine_builtin_func(name, func_type);
  def->value = new SymValBuiltinFunc{func_type, func};
}

/*
 * 
 *   EXPRESSIONS
 * 
 */

Expr* Expr::copy() const {
  auto res = new Expr{*this};
  for (auto& arg : res->args) {
    arg = arg->copy();
  }
  return res;
}

Expr::Expr(int c, sym_idx_t name_idx, std::initializer_list<Expr*> _arglist)
    : cls(c), val(0), sym(nullptr), e_type(nullptr), args(std::move(_arglist)) {
  sym = sym::lookup_symbol(name_idx);
  if (!sym) {
  }
}

void Expr::chk_rvalue(const Lexem& lem) const {
  if (!is_rvalue()) {
    lem.error_at("rvalue expected before `", "`");
  }
}

void Expr::chk_lvalue(const Lexem& lem) const {
  if (!is_lvalue()) {
    lem.error_at("lvalue expected before `", "`");
  }
}

void Expr::chk_type(const Lexem& lem) const {
  if (!is_type()) {
    lem.error_at("type expression expected before `", "`");
  }
}

bool Expr::deduce_type(const Lexem& lem) {
  if (e_type) {
    return true;
  }
  switch (cls) {
    case _Apply: {
      if (!sym) {
        return false;
      }
      SymVal* sym_val = dynamic_cast<SymVal*>(sym->value);
      if (!sym_val || !sym_val->get_type()) {
        return false;
      }
      std::vector<TypeExpr*> arg_types;
      for (const auto& arg : args) {
        arg_types.push_back(arg->e_type);
      }
      TypeExpr* fun_type = TypeExpr::new_map(TypeExpr::new_tensor(arg_types), TypeExpr::new_hole());
      try {
        uniformize(fun_type, sym_val->sym_type);
      } catch (UniformizeError& ue) {
        std::ostringstream os;
        os << "cannot apply function " << sym->name() << " : " << sym_val->get_type() << " to arguments of type "
           << fun_type->args[0] << ": " << ue;
        lem.error(os.str());
      }
      e_type = fun_type->args[1];
      TypeExpr::remove_indirect(e_type);
      return true;
    }
    case _VarApply: {
      assert(args.size() == 2);
      TypeExpr* fun_type = TypeExpr::new_map(args[1]->e_type, TypeExpr::new_hole());
      try {
        uniformize(fun_type, args[0]->e_type);
      } catch (UniformizeError& ue) {
        std::ostringstream os;
        os << "cannot apply expression of type " << args[0]->e_type << " to an expression of type " << args[1]->e_type
           << ": " << ue;
        lem.error(os.str());
      }
      e_type = fun_type->args[1];
      TypeExpr::remove_indirect(e_type);
      return true;
    }
    case _Letop: {
      assert(args.size() == 2);
      try {
        // std::cerr << "in assignment: ";
        uniformize(args[0]->e_type, args[1]->e_type);
      } catch (UniformizeError& ue) {
        std::ostringstream os;
        os << "cannot assign an expression of type " << args[1]->e_type << " to a variable or pattern of type "
           << args[0]->e_type << ": " << ue;
        lem.error(os.str());
      }
      e_type = args[0]->e_type;
      TypeExpr::remove_indirect(e_type);
      return true;
    }
  }
  return false;
}

int Expr::define_new_vars(CodeBlob& code) {
  switch (cls) {
    case _Tuple:
    case _TypeApply: {
      int res = 0;
      for (const auto& x : args) {
        res += x->define_new_vars(code);
      }
      return res;
    }
    case _Var:
      if (val < 0) {
        val = code.create_var(TmpVar::_Named, e_type, sym, &here);
        return 1;
      }
      break;
    case _Hole:
      if (val < 0) {
        val = code.create_var(TmpVar::_Tmp, e_type, nullptr, &here);
      }
      break;
  }
  return 0;
}

int Expr::predefine_vars() {
  switch (cls) {
    case _Tuple:
    case _TypeApply: {
      int res = 0;
      for (const auto& x : args) {
        res += x->predefine_vars();
      }
      return res;
    }
    case _Var:
      if (!sym) {
        assert(val < 0 && here.defined());
        sym = sym::define_symbol(~val, false, here);
        if (!sym) {
          throw src::ParseError{here, std::string{"redefined variable `"} + symbols.get_name(~val) + "`"};
        }
        sym->value = new SymVal{SymVal::_Var, -1, e_type};
        return 1;
      }
      break;
  }
  return 0;
}

std::vector<var_idx_t> Expr::pre_compile(CodeBlob& code) const {
  switch (cls) {
    case _Apply:
    case _Tuple: {
      std::vector<var_idx_t> res;
      for (const auto& x : args) {
        auto add = x->pre_compile(code);
        res.insert(res.end(), add.cbegin(), add.cend());
      }
      if (cls == _Tuple) {
        return res;
      }
      var_idx_t rv = code.create_var(TmpVar::_Tmp, e_type, nullptr, &here);
      std::vector<var_idx_t> rvect{rv};
      code.emplace_back(here, Op::_Call, rvect, std::move(res), sym);
      return rvect;
    }
    case _TypeApply:
      return args[0]->pre_compile(code);
    case _Var:
    case _Hole:
      return {val};
    case _VarApply:
      if (args[0]->cls == _Glob) {
        std::vector<var_idx_t> res = args[1]->pre_compile(code);
        var_idx_t rv = code.create_var(TmpVar::_Tmp, e_type, nullptr, &here);
        std::vector<var_idx_t> rvect{rv};
        code.emplace_back(here, Op::_Call, rvect, std::move(res), args[0]->sym);
        return rvect;
      } else {
        std::vector<var_idx_t> res = args[1]->pre_compile(code);
        std::vector<var_idx_t> tfunc = args[0]->pre_compile(code);
        if (tfunc.size() != 1) {
          throw src::Fatal{"stack tuple used as a function"};
        }
        res.push_back(tfunc[0]);
        var_idx_t rv = code.create_var(TmpVar::_Tmp, e_type, nullptr, &here);
        std::vector<var_idx_t> rvect{rv};
        code.emplace_back(here, Op::_CallInd, rvect, std::move(res));
        return rvect;
      }
    case _Const: {
      var_idx_t rv = code.create_var(TmpVar::_Tmp, e_type, nullptr, &here);
      std::vector<var_idx_t> rvect{rv};
      code.emplace_back(here, Op::_IntConst, rvect, intval);
      return rvect;
    }
    case _Glob: {
      var_idx_t rv = code.create_var(TmpVar::_Tmp, e_type, nullptr, &here);
      std::vector<var_idx_t> rvect{rv};
      code.emplace_back(here, Op::_GlobVar, rvect, std::vector<var_idx_t>{}, sym);
      return rvect;
    }
    case _Letop: {
      std::vector<var_idx_t> right = args[1]->pre_compile(code);
      std::vector<var_idx_t> left = args[0]->pre_compile(code);
      code.emplace_back(here, Op::_Let, left, std::move(right));
      return left;
    }
    default:
      std::cerr << "expression constructor is " << cls << std::endl;
      throw src::Fatal{"cannot compile expression with unknown constructor"};
  }
}

/*
 * 
 *   PARSE SOURCE
 * 
 */

// TE ::= TA | TA -> TE
// TA ::= int | ... | cont | var | _ | () | ( TE { , TE } )
TypeExpr* parse_type(Lexer& lex);

TypeExpr* parse_type1(Lexer& lex) {
  switch (lex.tp()) {
    case _Int:
      lex.next();
      return TypeExpr::new_atomic(_Int);
    case _Cell:
      lex.next();
      return TypeExpr::new_atomic(_Cell);
    case _Slice:
      lex.next();
      return TypeExpr::new_atomic(_Slice);
    case _Builder:
      lex.next();
      return TypeExpr::new_atomic(_Builder);
    case _Cont:
      lex.next();
      return TypeExpr::new_atomic(_Cont);
    case _Var:
    case '_':
      lex.next();
      return TypeExpr::new_hole();
  }
  lex.expect('(');
  if (lex.tp() == ')') {
    lex.next();
    return TypeExpr::new_unit();
  }
  auto t1 = parse_type(lex);
  if (lex.tp() != ',') {
    lex.expect(')');
    return t1;
  }
  std::vector<TypeExpr*> tlist{1, t1};
  while (lex.tp() == ',') {
    lex.next();
    tlist.push_back(parse_type(lex));
  }
  lex.expect(')');
  return TypeExpr::new_tensor(std::move(tlist));
}

TypeExpr* parse_type(Lexer& lex) {
  auto res = parse_type1(lex);
  if (lex.tp() == _Mapsto) {
    lex.next();
    auto to = parse_type(lex);
    return TypeExpr::new_map(res, to);
  } else {
    return res;
  }
}

FormalArg parse_formal_arg(Lexer& lex, int fa_idx) {
  TypeExpr* arg_type = 0;
  SrcLocation loc = lex.cur().loc;
  if (lex.tp() == '_') {
    lex.next();
    if (lex.tp() == ',' || lex.tp() == ')') {
      return std::make_tuple(TypeExpr::new_hole(), (SymDef*)nullptr, loc);
    }
    arg_type = TypeExpr::new_hole();
    loc = lex.cur().loc;
  } else if (lex.tp() != _Ident) {
    arg_type = parse_type(lex);
  } else {
    arg_type = TypeExpr::new_hole();
  }
  if (lex.tp() == '_' || lex.tp() == ',' || lex.tp() == ')') {
    if (lex.tp() == '_') {
      loc = lex.cur().loc;
      lex.next();
    }
    return std::make_tuple(arg_type, (SymDef*)nullptr, loc);
  }
  if (lex.tp() != _Ident) {
    lex.expect(_Ident, "formal parameter name");
  }
  loc = lex.cur().loc;
  SymDef* new_sym_def = sym::define_symbol(lex.cur().val, true, loc);
  if (new_sym_def->value) {
    lex.cur().error_at("redefined formal parameter `", "`");
  }
  new_sym_def->value = new SymVal{SymVal::_Param, fa_idx, arg_type};
  lex.next();
  return std::make_tuple(arg_type, new_sym_def, loc);
}

FormalArgList parse_formal_args(Lexer& lex) {
  FormalArgList args;
  lex.expect('(', "formal argument list");
  if (lex.tp() == ')') {
    lex.next();
    return args;
  }
  int fa_idx = 0;
  args.push_back(parse_formal_arg(lex, fa_idx++));
  while (lex.tp() == ',') {
    lex.next();
    args.push_back(parse_formal_arg(lex, fa_idx++));
  }
  lex.expect(')');
  return args;
}

TypeExpr* extract_total_arg_type(const FormalArgList& arg_list) {
  if (arg_list.empty()) {
    return TypeExpr::new_unit();
  }
  if (arg_list.size() == 1) {
    return std::get<0>(arg_list[0]);
  }
  std::vector<TypeExpr*> type_list;
  for (auto& x : arg_list) {
    type_list.push_back(std::get<0>(x));
  }
  return TypeExpr::new_tensor(std::move(type_list));
}

SymValFunc* make_new_glob_func(SymDef* func_sym, TypeExpr* func_type) {
  SymValFunc* res = new SymValFunc{glob_func_cnt, func_type};
  func_sym->value = res;
  glob_func.push_back(func_sym);
  glob_func_cnt++;
  return res;
}

bool check_global_func(const Lexem& cur, sym_idx_t func_name = 0) {
  if (!func_name) {
    func_name = cur.val;
  }
  SymDef* def = sym::lookup_symbol(func_name);
  if (!def) {
    cur.loc.show_error(std::string{"undefined function `"} + symbols.get_name(func_name) +
                       "`, defining a global function of unknown type");
    def = sym::define_global_symbol(func_name, 0, cur.loc);
    assert(def && "cannot define global function");
    ++undef_func_cnt;
    make_new_glob_func(def, TypeExpr::new_hole());  // was: ... ::new_func()
    return true;
  }
  SymVal* val = dynamic_cast<SymVal*>(def->value);
  if (!val) {
    cur.error(std::string{"symbol `"} + symbols.get_name(func_name) + "` has no value and no type");
    return false;
  } else if (!val->get_type()) {
    cur.error(std::string{"symbol `"} + symbols.get_name(func_name) + "` has no type, possibly not a function");
    return false;
  } else {
    return true;
  }
}

Expr* parse_expr(Lexer& lex, CodeBlob& code, bool nv = false);

// parse ( E { , E } ) | () | id | num | _
Expr* parse_expr100(Lexer& lex, CodeBlob& code, bool nv) {
  if (lex.tp() == '(') {
    SrcLocation loc{lex.cur().loc};
    lex.next();
    if (lex.tp() == ')') {
      lex.next();
      Expr* res = new Expr{Expr::_Tuple, {}};
      res->flags = Expr::_IsRvalue;
      res->here = loc;
      return res;
    }
    Expr* res = parse_expr(lex, code, nv);
    if (lex.tp() != ',') {
      lex.expect(')');
      return res;
    }
    std::vector<TypeExpr*> type_list;
    type_list.push_back(res->e_type);
    int f = res->flags;
    res = new Expr{Expr::_Tuple, {res}};
    while (lex.tp() == ',') {
      lex.next();
      auto x = parse_expr(lex, code, nv);
      res->pb_arg(x);
      if ((f ^ x->flags) & Expr::_IsType) {
        lex.cur().error("mixing type and non-type expressions inside the same tuple");
      }
      f &= x->flags;
      type_list.push_back(x->e_type);
    }
    res->here = loc;
    res->flags = f;
    res->e_type = TypeExpr::new_tensor(std::move(type_list));
    lex.expect(')');
    return res;
  }
  int t = lex.tp();
  if (t == Lexem::Number) {
    Expr* res = new Expr{Expr::_Const, lex.cur().loc};
    res->flags = Expr::_IsRvalue;
    td::RefInt256 val{true};
    if (!val.unique_write().parse_dec(lex.cur().str)) {
      lex.cur().error_at("invalid integer constant `", "`");
    }
    res->intval = std::move(val);
    res->e_type = TypeExpr::new_atomic(_Int);
    lex.next();
    return res;
  }
  if (t == '_') {
    Expr* res = new Expr{Expr::_Hole, lex.cur().loc};
    res->val = -1;
    res->flags = (Expr::_IsLvalue | Expr::_IsHole | Expr::_IsNewVar);
    res->e_type = TypeExpr::new_hole();
    lex.next();
    return res;
  }
  if (t == _Var) {
    Expr* res = new Expr{Expr::_Type, lex.cur().loc};
    res->flags = Expr::_IsType;
    res->e_type = TypeExpr::new_hole();
    lex.next();
    return res;
  }
  if (t == _Int || t == _Cell || t == _Slice || t == _Builder || t == _Cont || t == _Type) {
    Expr* res = new Expr{Expr::_Type, lex.cur().loc};
    res->flags = Expr::_IsType;
    res->e_type = TypeExpr::new_atomic(t);
    lex.next();
    return res;
  }
  if (t == Lexem::Ident) {
    Expr* res = new Expr{Expr::_Var, lex.cur().loc};
    if (nv) {
      res->val = ~lex.cur().val;
      res->e_type = TypeExpr::new_hole();
      res->flags = Expr::_IsLvalue | Expr::_IsNewVar;
      // std::cerr << "defined new variable " << lex.cur().str << " : " << res->e_type << std::endl;
    } else {
      res->sym = sym::lookup_symbol(lex.cur().val);
      if (!res->sym) {
        check_global_func(lex.cur());
        res->sym = sym::lookup_symbol(lex.cur().val);
      }
      SymVal* val = nullptr;
      if (res->sym) {
        val = dynamic_cast<SymVal*>(res->sym->value);
      }
      if (!val) {
        lex.cur().error_at("undefined identifier `", "`");
      } else if (val->type == SymVal::_Func) {
        res->e_type = val->get_type();
        res->cls = Expr::_Glob;
      } else if (val->idx < 0) {
        lex.cur().error_at("accessing variable `", "` being defined");
      } else {
        res->val = val->idx;
        res->e_type = val->get_type();
        // std::cerr << "accessing variable " << lex.cur().str << " : " << res->e_type << std::endl;
      }
      res->flags = Expr::_IsLvalue | Expr::_IsRvalue;
    }
    res->deduce_type(lex.cur());
    lex.next();
    return res;
  }
  lex.expect(Lexem::Ident);
  return nullptr;
}

// parse E { E }
Expr* parse_expr90(Lexer& lex, CodeBlob& code, bool nv) {
  Expr* res = parse_expr100(lex, code, nv);
  while (lex.tp() == '(' || lex.tp() == _Ident) {
    if (res->is_type()) {
      Expr* x = parse_expr100(lex, code, true);
      x->chk_lvalue(lex.cur());  // chk_lrvalue() ?
      TypeExpr* tp = res->e_type;
      delete res;
      res = new Expr{Expr::_TypeApply, {x}};
      res->e_type = tp;
      res->here = lex.cur().loc;
      try {
        uniformize(res->e_type, x->e_type);
      } catch (UniformizeError& ue) {
        std::ostringstream os;
        os << "cannot transform expression of type " << x->e_type << " to explicitly requested type " << res->e_type
           << ": " << ue;
        lex.cur().error(os.str());
      }
      res->flags = x->flags;
    } else {
      Expr* x = parse_expr100(lex, code, false);
      x->chk_rvalue(lex.cur());
      res = new Expr{Expr::_VarApply, {res, x}};
      res->flags = Expr::_IsRvalue;
      res->here = lex.cur().loc;
      res->deduce_type(lex.cur());
    }
  }
  return res;
}

// parse E { (* | / | % | /% ) E }
Expr* parse_expr30(Lexer& lex, CodeBlob& code, bool nv) {
  Expr* res = parse_expr90(lex, code, nv);
  while (lex.tp() == '*' || lex.tp() == '/' || lex.tp() == '%' || lex.tp() == _DivMod || lex.tp() == _DivC ||
         lex.tp() == _DivR || lex.tp() == '&') {
    res->chk_rvalue(lex.cur());
    int t = lex.tp();
    sym_idx_t name = symbols.lookup_add(std::string{"_"} + lex.cur().str + "_");
    SrcLocation loc{lex.cur().loc};
    check_global_func(lex.cur(), name);
    lex.next();
    auto x = parse_expr90(lex, code, false);
    x->chk_rvalue(lex.cur());
    res = new Expr{Expr::_Apply, name, {res, x}};
    res->here = loc;
    res->set_val(t);
    res->flags = Expr::_IsRvalue;
    res->deduce_type(lex.cur());
  }
  return res;
}

// parse [-] E { (+ | - | `|` ) E }
Expr* parse_expr20(Lexer& lex, CodeBlob& code, bool nv) {
  Expr* res;
  int t = lex.tp();
  if (t == '-') {
    sym_idx_t name = symbols.lookup_add("-_");
    check_global_func(lex.cur(), name);
    SrcLocation loc{lex.cur().loc};
    lex.next();
    auto x = parse_expr30(lex, code, false);
    x->chk_rvalue(lex.cur());
    res = new Expr{Expr::_Apply, name, {x}};
    res->here = loc;
    res->set_val(t);
    res->flags = Expr::_IsRvalue;
    res->deduce_type(lex.cur());
  } else {
    res = parse_expr30(lex, code, nv);
  }
  while (lex.tp() == '-' || lex.tp() == '+' || lex.tp() == '|') {
    res->chk_rvalue(lex.cur());
    t = lex.tp();
    sym_idx_t name = symbols.lookup_add(std::string{"_"} + lex.cur().str + "_");
    check_global_func(lex.cur(), name);
    SrcLocation loc{lex.cur().loc};
    lex.next();
    auto x = parse_expr30(lex, code, false);
    x->chk_rvalue(lex.cur());
    res = new Expr{Expr::_Apply, name, {res, x}};
    res->here = loc;
    res->set_val(t);
    res->flags = Expr::_IsRvalue;
    res->deduce_type(lex.cur());
  }
  return res;
}

// parse E { ( << | >> | >>~ | >>^ ) E }
Expr* parse_expr17(Lexer& lex, CodeBlob& code, bool nv) {
  Expr* res = parse_expr20(lex, code, nv);
  while (lex.tp() == _Lshift || lex.tp() == _Rshift || lex.tp() == _RshiftC || lex.tp() == _RshiftR) {
    res->chk_rvalue(lex.cur());
    int t = lex.tp();
    sym_idx_t name = symbols.lookup_add(std::string{"_"} + lex.cur().str + "_");
    check_global_func(lex.cur(), name);
    SrcLocation loc{lex.cur().loc};
    lex.next();
    auto x = parse_expr20(lex, code, false);
    x->chk_rvalue(lex.cur());
    res = new Expr{Expr::_Apply, name, {res, x}};
    res->here = loc;
    res->set_val(t);
    res->flags = Expr::_IsRvalue;
    res->deduce_type(lex.cur());
  }
  return res;
}

// parse E [ (== | < | > | <= | >= | != ) E ]
Expr* parse_expr15(Lexer& lex, CodeBlob& code, bool nv) {
  Expr* res = parse_expr17(lex, code, nv);
  if (lex.tp() == _Eq || lex.tp() == '<' || lex.tp() == '>' || lex.tp() == _Leq || lex.tp() == _Geq ||
      lex.tp() == _Neq) {
    res->chk_rvalue(lex.cur());
    int t = lex.tp();
    sym_idx_t name = symbols.lookup_add(std::string{"_"} + lex.cur().str + "_");
    check_global_func(lex.cur(), name);
    SrcLocation loc{lex.cur().loc};
    lex.next();
    auto x = parse_expr17(lex, code, false);
    x->chk_rvalue(lex.cur());
    res = new Expr{Expr::_Apply, name, {res, x}};
    res->here = loc;
    res->set_val(t);
    res->flags = Expr::_IsRvalue;
    res->deduce_type(lex.cur());
  }
  return res;
}

// parse LE1 (= | += | -= | ... ) E2
Expr* parse_expr10(Lexer& lex, CodeBlob& code, bool nv) {
  auto x = parse_expr15(lex, code, nv);
  int t = lex.tp();
  if (t == _PlusLet || t == _MinusLet || t == _TimesLet || t == _DivLet || t == _DivRLet || t == _DivCLet ||
      t == _ModLet || t == _LshiftLet || t == _RshiftLet || t == _RshiftCLet || t == _RshiftRLet) {
    x->chk_lvalue(lex.cur());
    x->chk_rvalue(lex.cur());
    sym_idx_t name = symbols.lookup_add(std::string{"^_"} + lex.cur().str + "_");
    check_global_func(lex.cur(), name);
    SrcLocation loc{lex.cur().loc};
    lex.next();
    auto y = parse_expr10(lex, code, false);
    y->chk_rvalue(lex.cur());
    Expr* z = new Expr{Expr::_Apply, name, {x, y}};
    z->here = loc;
    z->set_val(t);
    z->flags = Expr::_IsRvalue;
    z->deduce_type(lex.cur());
    Expr* res = new Expr{Expr::_Letop, {x->copy(), z}};
    res->here = loc;
    res->flags = (x->flags & ~Expr::_IsType) | Expr::_IsRvalue;
    res->set_val(t);
    res->deduce_type(lex.cur());
    return res;
  } else if (t == '=') {
    x->chk_lvalue(lex.cur());
    SrcLocation loc{lex.cur().loc};
    lex.next();
    auto y = parse_expr10(lex, code, false);
    y->chk_rvalue(lex.cur());
    x->predefine_vars();
    x->define_new_vars(code);
    Expr* res = new Expr{Expr::_Letop, {x, y}};
    res->here = loc;
    res->flags = (x->flags & ~Expr::_IsType) | Expr::_IsRvalue;
    res->set_val(t);
    res->deduce_type(lex.cur());
    return res;
  } else {
    return x;
  }
}

Expr* parse_expr(Lexer& lex, CodeBlob& code, bool nv) {
  return parse_expr10(lex, code, nv);
}

namespace blk_fl {
enum { end = 1, ret = 2, empty = 4 };
typedef int val;
constexpr val init = end | empty;
void combine(val& x, const val y) {
  x |= y & ret;
  x &= y | ~(end | empty);
}
void combine_parallel(val& x, const val y) {
  x &= y | ~(ret | empty);
  x |= y & end;
}
}  // namespace blk_fl

blk_fl::val parse_return_stmt(Lexer& lex, CodeBlob& code) {
  auto expr = parse_expr(lex, code);
  expr->chk_rvalue(lex.cur());
  try {
    // std::cerr << "in return: ";
    uniformize(expr->e_type, code.ret_type);
  } catch (UniformizeError& ue) {
    std::ostringstream os;
    os << "previous function return type " << code.ret_type
       << " cannot be unified with return statement expression type " << expr->e_type << ": " << ue;
    lex.cur().error(os.str());
  }
  std::vector<var_idx_t> tmp_vars = expr->pre_compile(code);
  code.emplace_back(lex.cur().loc, Op::_Return, std::move(tmp_vars));
  lex.expect(';');
  return blk_fl::ret;
}

blk_fl::val parse_implicit_ret_stmt(Lexer& lex, CodeBlob& code) {
  auto ret_type = TypeExpr::new_unit();
  try {
    // std::cerr << "in implicit return: ";
    uniformize(ret_type, code.ret_type);
  } catch (UniformizeError& ue) {
    std::ostringstream os;
    os << "previous function return type " << code.ret_type
       << " cannot be unified with implicit end-of-block return type " << ret_type << ": " << ue;
    lex.cur().error(os.str());
  }
  code.emplace_back(lex.cur().loc, Op::_Return);
  return blk_fl::ret;
}

blk_fl::val parse_stmt(Lexer& lex, CodeBlob& code);

blk_fl::val parse_block_stmt(Lexer& lex, CodeBlob& code) {
  lex.expect('{');
  sym::open_scope(lex);
  blk_fl::val res = blk_fl::init;
  bool warned = false;
  while (lex.tp() != '}') {
    if (!(res & blk_fl::end) && !warned) {
      lex.cur().loc.show_warning("unreachable code");
      warned = true;
    }
    blk_fl::combine(res, parse_stmt(lex, code));
  }
  sym::close_scope(lex);
  lex.expect('}');
  return res;
}

blk_fl::val parse_repeat_stmt(Lexer& lex, CodeBlob& code) {
  SrcLocation loc{lex.cur().loc};
  lex.expect(_Repeat);
  auto expr = parse_expr(lex, code);
  expr->chk_rvalue(lex.cur());
  auto cnt_type = TypeExpr::new_atomic(_Int);
  try {
    uniformize(expr->e_type, cnt_type);
  } catch (UniformizeError& ue) {
    std::ostringstream os;
    os << "repeat count value of type " << expr->e_type << " is not an integer: " << ue;
    lex.cur().error(os.str());
  }
  std::vector<var_idx_t> tmp_vars = expr->pre_compile(code);
  if (tmp_vars.size() != 1) {
    lex.cur().error("repeat count value is not a singleton");
  }
  Op& repeat_op = code.emplace_back(loc, Op::_Repeat, tmp_vars);
  code.push_set_cur(repeat_op.block0);
  blk_fl::val res = parse_block_stmt(lex, code);
  code.close_pop_cur(lex.cur().loc);
  return res | blk_fl::end;
}

blk_fl::val parse_while_stmt(Lexer& lex, CodeBlob& code) {
  SrcLocation loc{lex.cur().loc};
  lex.expect(_While);
  auto expr = parse_expr(lex, code);
  expr->chk_rvalue(lex.cur());
  auto cnt_type = TypeExpr::new_atomic(_Int);
  try {
    uniformize(expr->e_type, cnt_type);
  } catch (UniformizeError& ue) {
    std::ostringstream os;
    os << "while condition value of type " << expr->e_type << " is not an integer: " << ue;
    lex.cur().error(os.str());
  }
  Op& while_op = code.emplace_back(loc, Op::_While);
  code.push_set_cur(while_op.block0);
  while_op.left = expr->pre_compile(code);
  code.close_pop_cur(lex.cur().loc);
  if (while_op.left.size() != 1) {
    lex.cur().error("while condition value is not a singleton");
  }
  code.push_set_cur(while_op.block1);
  blk_fl::val res1 = parse_block_stmt(lex, code);
  code.close_pop_cur(lex.cur().loc);
  return res1 | blk_fl::end;
}

blk_fl::val parse_do_stmt(Lexer& lex, CodeBlob& code) {
  Op& while_op = code.emplace_back(lex.cur().loc, Op::_Until);
  lex.expect(_Do);
  code.push_set_cur(while_op.block0);
  blk_fl::val res = parse_block_stmt(lex, code);
  lex.expect(_Until);
  auto expr = parse_expr(lex, code);
  expr->chk_rvalue(lex.cur());
  auto cnt_type = TypeExpr::new_atomic(_Int);
  try {
    uniformize(expr->e_type, cnt_type);
  } catch (UniformizeError& ue) {
    std::ostringstream os;
    os << "`until` condition value of type " << expr->e_type << " is not an integer: " << ue;
    lex.cur().error(os.str());
  }
  while_op.left = expr->pre_compile(code);
  code.close_pop_cur(lex.cur().loc);
  if (while_op.left.size() != 1) {
    lex.cur().error("`until` condition value is not a singleton");
  }
  return res & ~blk_fl::empty;
}

blk_fl::val parse_if_stmt(Lexer& lex, CodeBlob& code, int first_lex = _If) {
  SrcLocation loc{lex.cur().loc};
  lex.expect(first_lex);
  auto expr = parse_expr(lex, code);
  expr->chk_rvalue(lex.cur());
  auto flag_type = TypeExpr::new_atomic(_Int);
  try {
    uniformize(expr->e_type, flag_type);
  } catch (UniformizeError& ue) {
    std::ostringstream os;
    os << "`if` condition value of type " << expr->e_type << " is not an integer: " << ue;
    lex.cur().error(os.str());
  }
  std::vector<var_idx_t> tmp_vars = expr->pre_compile(code);
  if (tmp_vars.size() != 1) {
    lex.cur().error("condition value is not a singleton");
  }
  Op& if_op = code.emplace_back(loc, Op::_If, tmp_vars);
  code.push_set_cur(if_op.block0);
  blk_fl::val res1 = parse_block_stmt(lex, code);
  blk_fl::val res2 = blk_fl::init;
  code.close_pop_cur(lex.cur().loc);
  if (lex.tp() == _Else) {
    lex.expect(_Else);
    code.push_set_cur(if_op.block1);
    res2 = parse_block_stmt(lex, code);
    code.close_pop_cur(lex.cur().loc);
  } else if (lex.tp() == _Elseif) {
    code.push_set_cur(if_op.block1);
    res2 = parse_if_stmt(lex, code, _Elseif);
    code.close_pop_cur(lex.cur().loc);
  }
  blk_fl::combine_parallel(res1, res2);
  return res1;
}

blk_fl::val parse_stmt(Lexer& lex, CodeBlob& code) {
  switch (lex.tp()) {
    case _Return: {
      lex.next();
      return parse_return_stmt(lex, code);
    }
    case '{': {
      return parse_block_stmt(lex, code);
    }
    case ';': {
      lex.next();
      return blk_fl::init;
    }
    case _Repeat:
      return parse_repeat_stmt(lex, code);
    case _If:
      return parse_if_stmt(lex, code);
    case _Do:
      return parse_do_stmt(lex, code);
    case _While:
      return parse_while_stmt(lex, code);
    default: {
      auto expr = parse_expr(lex, code);
      expr->chk_rvalue(lex.cur());
      expr->pre_compile(code);
      lex.expect(';');
      return blk_fl::end;
    }
  }
}

CodeBlob* parse_func_body(Lexer& lex, FormalArgList arg_list, TypeExpr* ret_type) {
  lex.expect('{');
  CodeBlob* blob = new CodeBlob{ret_type};
  blob->import_params(std::move(arg_list));
  blk_fl::val res = blk_fl::init;
  bool warned = false;
  while (lex.tp() != '}') {
    if (!(res & blk_fl::end) && !warned) {
      lex.cur().loc.show_warning("unreachable code");
      warned = true;
    }
    blk_fl::combine(res, parse_stmt(lex, *blob));
  }
  if (res & blk_fl::end) {
    parse_implicit_ret_stmt(lex, *blob);
  }
  blob->close_blk(lex.cur().loc);
  lex.expect('}');
  return blob;
}

void parse_func_def(Lexer& lex) {
  SrcLocation loc{lex.cur().loc};
  sym::open_scope(lex);
  auto ret_type = parse_type(lex);
  if (lex.tp() != _Ident) {
    throw src::ParseError{lex.cur().loc, "function name identifier expected"};
  }
  Lexem func_name = lex.cur();
  lex.next();
  FormalArgList arg_list = parse_formal_args(lex);
  if (lex.tp() != ';' && lex.tp() != '{') {
    lex.expect('{', "function body block expected");
  }
  TypeExpr* func_type = TypeExpr::new_map(extract_total_arg_type(arg_list), ret_type);
  std::cerr << "function " << func_name.str << " : " << func_type << std::endl;
  SymDef* func_sym = sym::define_global_symbol(func_name.val, 0, loc);
  assert(func_sym);
  SymValFunc* func_sym_val = dynamic_cast<SymValFunc*>(func_sym->value);
  if (func_sym->value) {
    if (func_sym->value->type != SymVal::_Func || !func_sym_val) {
      lex.cur().error("was not defined as a function before");
    }
    try {
      uniformize(func_sym_val->sym_type, func_type);
    } catch (UniformizeError& ue) {
      std::ostringstream os;
      os << "previous type of function " << func_name.str << " : " << func_sym_val->get_type()
         << " cannot be unified with new type " << func_type << ": " << ue;
      lex.cur().error(os.str());
    }
  } else {
    func_sym_val = make_new_glob_func(func_sym, func_type);
  }
  if (lex.tp() == ';') {
    lex.next();
  } else {
    if (func_sym_val->code) {
      lex.cur().error(std::string{"redefinition of function `"} + func_name.str + "`");
    }
    CodeBlob* code = parse_func_body(lex, arg_list, ret_type);
    code->name = func_name.str;
    code->loc = loc;
    code->print(std::cerr);
    func_sym_val->code = code;
  }
  std::cerr << "new type of function " << func_name.str << " : " << func_type << std::endl;
  sym::close_scope(lex);
}

bool parse_source(std::istream* is, const src::FileDescr* fdescr) {
  src::SourceReader reader{is, fdescr};
  Lexer lex{reader, true};
  while (lex.tp() != _Eof) {
    parse_func_def(lex);
  }
  return true;
}

bool parse_source_file(const char* filename) {
  if (!filename || !*filename) {
    throw src::Fatal{"source file name is an empty string"};
  }
  src::FileDescr* cur_source = new src::FileDescr{filename};
  std::ifstream ifs{filename};
  if (ifs.fail()) {
    throw src::Fatal{std::string{"cannot open source file `"} + filename + "`"};
  }
  return parse_source(&ifs, cur_source);
}

bool parse_source_stdin() {
  return parse_source(&std::cin, new src::FileDescr{"stdin", true});
}

/*
 * 
 *   ASM-OP LIST FUNCTIONS
 * 
 */

void AsmOp::out(std::ostream& os) const {
  if (!op.empty()) {
    os << op;
    return;
  }
  switch (t) {
    case a_none:
      break;
    case a_xchg:
      if (!a && !(b & -2)) {
        os << (b ? "SWAP" : "NOP");
        break;
      }
      os << "s" << a << " s" << b << " XCHG";
      break;
    case a_push:
      if (!(a & -2)) {
        os << (a ? "OVER" : "DUP");
        break;
      }
      os << "s" << a << " PUSH";
      break;
    case a_pop:
      if (!(a & -2)) {
        os << (a ? "NIP" : "DROP");
        break;
      }
      os << "s" << a << " POP";
      break;
    default:
      throw src::Fatal{"unknown assembler operation"};
  }
}

void AsmOp::out_indent_nl(std::ostream& os, bool no_eol) const {
  for (int i = 0; i < indent; i++) {
    os << "  ";
  }
  out(os);
  if (!no_eol) {
    os << std::endl;
  }
}

std::string AsmOp::to_string() const {
  if (!op.empty()) {
    return op;
  } else {
    std::ostringstream os;
    out(os);
    return os.str();
  }
}

void AsmOpList::show_var(std::ostream& os, var_idx_t idx) const {
  if (!var_names_ || (unsigned)idx >= var_names_->size()) {
    os << '_' << idx;
  } else {
    var_names_->at(idx).show(os, 2);
  }
}

void AsmOpList::out(std::ostream& os, int mode) const {
  if (!(mode & 2)) {
    for (const auto& op : list_) {
      os << op;
    }
  } else {
    std::size_t n = list_.size();
    for (std::size_t i = 0; i < n; i++) {
      const auto& op = list_[i];
      if (!op.is_comment() && i + 1 < n && list_[i + 1].is_comment()) {
        op.out_indent_nl(os, true);
        os << '\t';
        do {
          i++;
        } while (i + 1 < n && list_[i + 1].is_comment());
        list_[i].out(os);
        os << std::endl;
      } else {
        op.out_indent_nl(os, false);
      }
    }
  }
}

/*
 * 
 *   DEFINE BUILT-IN FUNCTIONS
 * 
 */

int emulate_negate(int a) {
  int f = VarDescr::_Pos | VarDescr::_Neg;
  if ((a & f) && (~a & f)) {
    a ^= f;
  }
  f = VarDescr::_Bit | VarDescr::_Bool;
  if ((a & f) && (~a & f)) {
    a ^= f;
  }
  return a;
}

int emulate_add(int a, int b) {
  if (b & VarDescr::_Zero) {
    return a;
  } else if (a & VarDescr::_Zero) {
    return b;
  }
  int u = a & b, v = a | b;
  int r = VarDescr::_Int;
  int t = u & (VarDescr::_Pos | VarDescr::_Neg);
  if (v & VarDescr::_Nan) {
    return r | VarDescr::_Nan;
  }
  // non-quiet addition always returns finite results!
  r |= t | VarDescr::_Finite;
  if (t) {
    r |= v & VarDescr::_NonZero;
  }
  r |= v & VarDescr::_Nan;
  if (u & (VarDescr::_Odd | VarDescr::_Even)) {
    r |= VarDescr::_Even;
  } else if (!(~v & (VarDescr::_Odd | VarDescr::_Even))) {
    r |= VarDescr::_Odd | VarDescr::_NonZero;
  }
  return r;
}

int emulate_sub(int a, int b) {
  return emulate_add(a, emulate_negate(b));
}

int emulate_mul(int a, int b) {
  if ((b & (VarDescr::_NonZero | VarDescr::_Bit)) == (VarDescr::_NonZero | VarDescr::_Bit)) {
    return a;
  } else if ((a & (VarDescr::_NonZero | VarDescr::_Bit)) == (VarDescr::_NonZero | VarDescr::_Bit)) {
    return b;
  }
  int u = a & b, v = a | b;
  int r = VarDescr::_Int;
  if (v & VarDescr::_Nan) {
    return r | VarDescr::_Nan;
  }
  // non-quiet multiplication always yields finite results, if any
  r |= VarDescr::_Finite;
  if (v & VarDescr::_Zero) {
    // non-quiet multiplication
    // the result is zero, if any result at all
    return VarDescr::ConstZero;
  }
  if (u & (VarDescr::_Pos | VarDescr::_Neg)) {
    r |= VarDescr::_Pos;
  } else if (!(~v & (VarDescr::_Pos | VarDescr::_Neg))) {
    r |= VarDescr::_Neg;
  }
  if (u & (VarDescr::_Bit | VarDescr::_Bool)) {
    r |= VarDescr::_Bit;
  } else if (!(~v & (VarDescr::_Bit | VarDescr::_Bool))) {
    r |= VarDescr::_Bool;
  }
  r |= v & VarDescr::_Even;
  r |= u & (VarDescr::_Odd | VarDescr::_NonZero);
  return r;
}

int emulate_lshift(int a, int b) {
  if (((a | b) & VarDescr::_Nan) || !(~b & (VarDescr::_Neg | VarDescr::_NonZero))) {
    return VarDescr::_Int | VarDescr::_Nan;
  }
  if (b & VarDescr::_Zero) {
    return a;
  }
  int t = ((b & VarDescr::_NonZero) ? VarDescr::_Even : 0);
  t |= b & VarDescr::_Finite;
  return emulate_mul(a, VarDescr::_Int | VarDescr::_Pos | VarDescr::_NonZero | VarDescr::_Even | t);
}

int emulate_div(int a, int b) {
  if ((b & (VarDescr::_NonZero | VarDescr::_Bit)) == (VarDescr::_NonZero | VarDescr::_Bit)) {
    return a;
  } else if ((b & (VarDescr::_NonZero | VarDescr::_Bool)) == (VarDescr::_NonZero | VarDescr::_Bool)) {
    return emulate_negate(b);
  }
  if (b & VarDescr::_Zero) {
    return VarDescr::_Int | VarDescr::_Nan;
  }
  int u = a & b, v = a | b;
  int r = VarDescr::_Int;
  if (v & VarDescr::_Nan) {
    return r | VarDescr::_Nan;
  }
  // non-quiet division always yields finite results, if any
  r |= VarDescr::_Finite;
  if (a & VarDescr::_Zero) {
    // non-quiet division
    // the result is zero, if any result at all
    return VarDescr::ConstZero;
  }
  if (u & (VarDescr::_Pos | VarDescr::_Neg)) {
    r |= VarDescr::_Pos;
  } else if (!(~v & (VarDescr::_Pos | VarDescr::_Neg))) {
    r |= VarDescr::_Neg;
  }
  if (u & (VarDescr::_Bit | VarDescr::_Bool)) {
    r |= VarDescr::_Bit;
  } else if (!(~v & (VarDescr::_Bit | VarDescr::_Bool))) {
    r |= VarDescr::_Bool;
  }
  return r;
}

int emulate_rshift(int a, int b) {
  if (((a | b) & VarDescr::_Nan) || !(~b & (VarDescr::_Neg | VarDescr::_NonZero))) {
    return VarDescr::_Int | VarDescr::_Nan;
  }
  if (b & VarDescr::_Zero) {
    return a;
  }
  int t = ((b & VarDescr::_NonZero) ? VarDescr::_Even : 0);
  t |= b & VarDescr::_Finite;
  return emulate_div(a, VarDescr::_Int | VarDescr::_Pos | VarDescr::_NonZero | VarDescr::_Even | t);
}

int emulate_mod(int a, int b, int round_mode = -1) {
  if ((b & (VarDescr::_NonZero | VarDescr::_Bit)) == (VarDescr::_NonZero | VarDescr::_Bit)) {
    return VarDescr::ConstZero;
  } else if ((b & (VarDescr::_NonZero | VarDescr::_Bool)) == (VarDescr::_NonZero | VarDescr::_Bool)) {
    return VarDescr::ConstZero;
  }
  if (b & VarDescr::_Zero) {
    return VarDescr::_Int | VarDescr::_Nan;
  }
  int r = VarDescr::_Int;
  if ((a | b) & VarDescr::_Nan) {
    return r | VarDescr::_Nan;
  }
  // non-quiet division always yields finite results, if any
  r |= VarDescr::_Finite;
  if (a & VarDescr::_Zero) {
    // non-quiet division
    // the result is zero, if any result at all
    return VarDescr::ConstZero;
  }
  if (round_mode < 0) {
    r |= b & (VarDescr::_Pos | VarDescr::_Neg);
  } else if (round_mode > 0) {
    r |= emulate_negate(b) & (VarDescr::_Pos | VarDescr::_Neg);
  }
  if (a & (VarDescr::_Bit | VarDescr::_Bool)) {
    if (r & VarDescr::_Pos) {
      r |= VarDescr::_Bit;
    }
    if (r & VarDescr::_Neg) {
      r |= VarDescr::_Bool;
    }
  }
  if (b & VarDescr::_Even) {
    r |= a & (VarDescr::_Even | VarDescr::_Odd);
  }
  return r;
}

int is_pos_pow2(td::RefInt256 x) {
  if (sgn(x) > 0 && !sgn(x & (x - 1))) {
    return x->bit_size() - 1;
  } else {
    return -1;
  }
}

int is_neg_pow2(td::RefInt256 x) {
  return sgn(x) < 0 ? is_pos_pow2(-x) : 0;
}

AsmOp exec_op(std::string op) {
  return AsmOp::Custom(op);
}

AsmOp exec_op(std::string op, int args, int retv = 1) {
  return AsmOp::Custom(op, args, retv);
}

AsmOp exec_arg_op(std::string op, long long arg) {
  std::ostringstream os;
  os << arg << ' ' << op;
  return AsmOp::Custom(os.str());
}

AsmOp exec_arg_op(std::string op, long long arg, int args, int retv = 1) {
  std::ostringstream os;
  os << arg << ' ' << op;
  return AsmOp::Custom(os.str(), args, retv);
}

AsmOp exec_arg_op(std::string op, td::RefInt256 arg) {
  std::ostringstream os;
  os << arg << ' ' << op;
  return AsmOp::Custom(os.str());
}

AsmOp exec_arg_op(std::string op, td::RefInt256 arg, int args, int retv = 1) {
  std::ostringstream os;
  os << arg << ' ' << op;
  return AsmOp::Custom(os.str(), args, retv);
}

AsmOp AsmOp::Const(int arg, std::string push_op) {
  std::ostringstream os;
  os << arg << ' ' << push_op;
  return AsmOp::Custom(os.str());
}

AsmOp push_const(td::RefInt256 x) {
  return AsmOp::IntConst(std::move(x));
}

AsmOp AsmOp::IntConst(td::RefInt256 x) {
  if (x->signed_fits_bits(8)) {
    return AsmOp::Const(dec_string(std::move(x)) + " PUSHINT");
  }
  if (!x->is_valid()) {
    return AsmOp::Const("PUSHNAN");
  }
  int k = is_pos_pow2(x);
  if (k >= 0) {
    return AsmOp::Const(k, "PUSHPOW2");
  }
  k = is_pos_pow2(x + 1);
  if (k >= 0) {
    return AsmOp::Const(k, "PUSHPOW2DEC");
  }
  k = is_pos_pow2(-x);
  if (k >= 0) {
    return AsmOp::Const(k, "PUSHNEGPOW2");
  }
  return AsmOp::Const(dec_string(std::move(x)) + " PUSHINT");
}

AsmOp compile_add(std::vector<VarDescr>& res, std::vector<VarDescr>& args) {
  assert(res.size() == 1 && args.size() == 2);
  VarDescr &r = res[0], &x = args[0], &y = args[1];
  if (x.is_int_const() && y.is_int_const()) {
    r.set_const(x.int_const + y.int_const);
    x.unused();
    y.unused();
    return push_const(r.int_const);
  }
  r.val = emulate_add(x.val, y.val);
  if (y.is_int_const() && y.int_const->signed_fits_bits(8)) {
    y.unused();
    if (y.always_zero()) {
      return AsmOp::Nop();
    }
    if (*y.int_const == 1) {
      return exec_op("INC", 1);
    }
    if (*y.int_const == -1) {
      return exec_op("DEC", 1);
    }
    return exec_arg_op("ADDCONST", y.int_const, 1);
  }
  if (x.is_int_const() && x.int_const->signed_fits_bits(8)) {
    x.unused();
    if (x.always_zero()) {
      return AsmOp::Nop();
    }
    if (*x.int_const == 1) {
      return exec_op("INC", 1);
    }
    if (*x.int_const == -1) {
      return exec_op("DEC", 1);
    }
    return exec_arg_op("ADDCONST", x.int_const, 1);
  }
  return exec_op("ADD", 2);
}

AsmOp compile_sub(std::vector<VarDescr>& res, std::vector<VarDescr>& args) {
  assert(res.size() == 1 && args.size() == 2);
  VarDescr &r = res[0], &x = args[0], &y = args[1];
  if (x.is_int_const() && y.is_int_const()) {
    r.set_const(x.int_const - y.int_const);
    x.unused();
    y.unused();
    return push_const(r.int_const);
  }
  r.val = emulate_sub(x.val, y.val);
  if (y.is_int_const() && (-y.int_const)->signed_fits_bits(8)) {
    y.unused();
    if (y.always_zero()) {
      return {};
    }
    if (*y.int_const == 1) {
      return exec_op("DEC", 1);
    }
    if (*y.int_const == -1) {
      return exec_op("INC", 1);
    }
    return exec_arg_op("ADDCONST", -y.int_const, 1);
  }
  if (x.always_zero()) {
    x.unused();
    return exec_op("NEGATE", 1);
  }
  return exec_op("SUB", 2);
}

AsmOp compile_negate(std::vector<VarDescr>& res, std::vector<VarDescr>& args) {
  assert(res.size() == 1 && args.size() == 1);
  VarDescr &r = res[0], &x = args[0];
  if (x.is_int_const()) {
    r.set_const(-x.int_const);
    x.unused();
    return push_const(r.int_const);
  }
  r.val = emulate_negate(x.val);
  return exec_op("NEGATE", 1);
}

AsmOp compile_mul(std::vector<VarDescr>& res, std::vector<VarDescr>& args) {
  assert(res.size() == 1 && args.size() == 2);
  VarDescr &r = res[0], &x = args[0], &y = args[1];
  if (x.is_int_const() && y.is_int_const()) {
    r.set_const(x.int_const * y.int_const);
    x.unused();
    y.unused();
    return push_const(r.int_const);
  }
  r.val = emulate_mul(x.val, y.val);
  if (y.is_int_const()) {
    int k = is_pos_pow2(y.int_const);
    if (y.int_const->signed_fits_bits(8) && k < 0) {
      y.unused();
      if (y.always_zero() && x.always_finite()) {
        // dubious optimization: NaN * 0 = ?
        r.set_const(y.int_const);
        return push_const(r.int_const);
      }
      if (*y.int_const == 1 && x.always_finite()) {
        return AsmOp::Nop();
      }
      if (*y.int_const == -1) {
        return exec_op("NEGATE", 1);
      }
      return exec_arg_op("MULCONST", y.int_const, 1);
    }
    if (k >= 0) {
      y.unused();
      return exec_arg_op("LSHIFT#", k, 1);
    }
  }
  if (x.is_int_const()) {
    int k = is_pos_pow2(x.int_const);
    if (x.int_const->signed_fits_bits(8) && k < 0) {
      x.unused();
      if (x.always_zero() && y.always_finite()) {
        // dubious optimization: NaN * 0 = ?
        r.set_const(x.int_const);
        return push_const(r.int_const);
      }
      if (*x.int_const == 1 && y.always_finite()) {
        return AsmOp::Nop();
      }
      if (*x.int_const == -1) {
        return exec_op("NEGATE", 1);
      }
      return exec_arg_op("MULCONST", x.int_const, 1);
    }
    if (k >= 0) {
      x.unused();
      return exec_arg_op("LSHIFT#", k, 1);
    }
  }
  return exec_op("MUL", 2);
}

AsmOp compile_lshift(std::vector<VarDescr>& res, std::vector<VarDescr>& args) {
  assert(res.size() == 1 && args.size() == 2);
  VarDescr &r = res[0], &x = args[0], &y = args[1];
  if (y.is_int_const()) {
    auto yv = y.int_const->to_long();
    if (yv < 0 || yv > 256) {
      r.set_const_nan();
      x.unused();
      y.unused();
      return push_const(r.int_const);
    } else if (x.is_int_const()) {
      r.set_const(x.int_const << (int)yv);
      x.unused();
      y.unused();
      return push_const(r.int_const);
    }
  }
  r.val = emulate_lshift(x.val, y.val);
  if (y.is_int_const()) {
    int k = (int)(y.int_const->to_long());
    if (!k /* && x.always_finite() */) {
      // dubious optimization: what if x=NaN ?
      y.unused();
      return AsmOp::Nop();
    }
    y.unused();
    return exec_arg_op("LSHIFT#", k, 1);
  }
  if (x.is_int_const()) {
    auto xv = x.int_const->to_long();
    if (xv == 1) {
      x.unused();
      return exec_op("POW2", 1);
    }
    if (xv == -1) {
      x.unused();
      return exec_op("NEGPOW2", 1);
    }
  }
  return exec_op("LSHIFT", 2);
}

AsmOp compile_rshift(std::vector<VarDescr>& res, std::vector<VarDescr>& args, int round_mode) {
  assert(res.size() == 1 && args.size() == 2);
  VarDescr &r = res[0], &x = args[0], &y = args[1];
  if (y.is_int_const()) {
    auto yv = y.int_const->to_long();
    if (yv < 0 || yv > 256) {
      r.set_const_nan();
      x.unused();
      y.unused();
      return push_const(r.int_const);
    } else if (x.is_int_const()) {
      r.set_const(td::rshift(x.int_const, (int)yv, round_mode));
      x.unused();
      y.unused();
      return push_const(r.int_const);
    }
  }
  r.val = emulate_rshift(x.val, y.val);
  std::string rshift = (round_mode < 0 ? "RSHIFT" : (round_mode ? "RSHIFTC" : "RSHIFTR"));
  if (y.is_int_const()) {
    int k = (int)(y.int_const->to_long());
    if (!k /* && x.always_finite() */) {
      // dubious optimization: what if x=NaN ?
      y.unused();
      return AsmOp::Nop();
    }
    y.unused();
    return exec_arg_op(rshift + "#", k, 1);
  }
  return exec_op(rshift, 2);
}

AsmOp compile_div(std::vector<VarDescr>& res, std::vector<VarDescr>& args, int round_mode) {
  assert(res.size() == 1 && args.size() == 2);
  VarDescr &r = res[0], &x = args[0], &y = args[1];
  if (x.is_int_const() && y.is_int_const()) {
    r.set_const(div(x.int_const, y.int_const, round_mode));
    x.unused();
    y.unused();
    return push_const(r.int_const);
  }
  r.val = emulate_div(x.val, y.val);
  if (y.is_int_const()) {
    if (*y.int_const == 0) {
      x.unused();
      y.unused();
      r.set_const(div(y.int_const, y.int_const));
      return push_const(r.int_const);
    }
    if (*y.int_const == 1 && x.always_finite()) {
      y.unused();
      return AsmOp::Nop();
    }
    if (*y.int_const == -1) {
      y.unused();
      return exec_op("NEGATE", 1);
    }
    int k = is_pos_pow2(y.int_const);
    if (k > 0) {
      y.unused();
      std::string op = "RSHIFT";
      if (round_mode >= 0) {
        op += (round_mode > 0 ? 'C' : 'R');
      }
      return exec_arg_op(op + '#', k, 1);
    }
  }
  std::string op = "DIV";
  if (round_mode >= 0) {
    op += (round_mode > 0 ? 'C' : 'R');
  }
  return exec_op(op, 2);
}

AsmOp compile_mod(std::vector<VarDescr>& res, std::vector<VarDescr>& args, int round_mode) {
  assert(res.size() == 1 && args.size() == 2);
  VarDescr &r = res[0], &x = args[0], &y = args[1];
  if (x.is_int_const() && y.is_int_const()) {
    r.set_const(mod(x.int_const, y.int_const, round_mode));
    x.unused();
    y.unused();
    return push_const(r.int_const);
  }
  r.val = emulate_mod(x.val, y.val);
  if (y.is_int_const()) {
    if (*y.int_const == 0) {
      x.unused();
      y.unused();
      r.set_const(mod(y.int_const, y.int_const));
      return push_const(r.int_const);
    }
    if ((*y.int_const == 1 || *y.int_const == -1) && x.always_finite()) {
      x.unused();
      y.unused();
      r.set_const(td::RefInt256{true, 0});
      return push_const(r.int_const);
    }
    int k = is_pos_pow2(y.int_const);
    if (k > 0) {
      y.unused();
      std::string op = "MODPOW2";
      if (round_mode >= 0) {
        op += (round_mode > 0 ? 'C' : 'R');
      }
      return exec_arg_op(op + '#', k, 1);
    }
  }
  std::string op = "MOD";
  if (round_mode >= 0) {
    op += (round_mode > 0 ? 'C' : 'R');
  }
  return exec_op(op, 2);
}

void define_builtins() {
  using namespace std::placeholders;
  auto Int = TypeExpr::new_atomic(_Int);
  auto Int2 = TypeExpr::new_tensor({Int, Int});
  auto Int3 = TypeExpr::new_tensor({Int, Int, Int});
  auto arith_bin_op = TypeExpr::new_map(Int2, Int);
  auto arith_un_op = TypeExpr::new_map(Int, Int);
  //auto arith_null_op = TypeExpr::new_map(TypeExpr::new_unit(), Int);
  define_builtin_func("_+_", arith_bin_op, compile_add);
  define_builtin_func("_-_", arith_bin_op, compile_sub);
  define_builtin_func("-_", arith_un_op, compile_negate);
  define_builtin_func("_*_", arith_bin_op, compile_mul);
  define_builtin_func("_/_", arith_bin_op, std::bind(compile_div, _1, _2, -1));
  define_builtin_func("_/~_", arith_bin_op, std::bind(compile_div, _1, _2, 0));
  define_builtin_func("_/^_", arith_bin_op, std::bind(compile_div, _1, _2, 1));
  define_builtin_func("_%_", arith_bin_op, std::bind(compile_mod, _1, _2, -1));
  define_builtin_func("_%~_", arith_bin_op, std::bind(compile_mod, _1, _2, 0));
  define_builtin_func("_%^_", arith_bin_op, std::bind(compile_mod, _1, _2, -1));
  define_builtin_func("_/%_", TypeExpr::new_map(Int2, Int2), AsmOp::Custom("DIVMOD", 2, 2));
  define_builtin_func("_<<_", arith_bin_op, compile_lshift);
  define_builtin_func("_>>_", arith_bin_op, std::bind(compile_rshift, _1, _2, -1));
  define_builtin_func("_>>~_", arith_bin_op, std::bind(compile_rshift, _1, _2, 0));
  define_builtin_func("_>>^_", arith_bin_op, std::bind(compile_rshift, _1, _2, 1));
  define_builtin_func("_&_", arith_bin_op, AsmOp::Custom("AND", 2));
  define_builtin_func("_|_", arith_bin_op, AsmOp::Custom("OR", 2));
  define_builtin_func("_^_", arith_bin_op, AsmOp::Custom("XOR", 2));
  define_builtin_func("^_+=_", arith_bin_op, compile_add);
  define_builtin_func("^_-=_", arith_bin_op, compile_sub);
  define_builtin_func("^_*=_", arith_bin_op, compile_mul);
  define_builtin_func("^_/=_", arith_bin_op, std::bind(compile_div, _1, _2, -1));
  define_builtin_func("^_/~=_", arith_bin_op, std::bind(compile_div, _1, _2, 0));
  define_builtin_func("^_/^=_", arith_bin_op, std::bind(compile_div, _1, _2, 1));
  define_builtin_func("^_%=_", arith_bin_op, std::bind(compile_mod, _1, _2, -1));
  define_builtin_func("^_%~=_", arith_bin_op, std::bind(compile_mod, _1, _2, 0));
  define_builtin_func("^_%^=_", arith_bin_op, std::bind(compile_mod, _1, _2, 1));
  define_builtin_func("^_<<=_", arith_bin_op, compile_lshift);
  define_builtin_func("^_>>=_", arith_bin_op, std::bind(compile_rshift, _1, _2, -1));
  define_builtin_func("^_>>~=_", arith_bin_op, std::bind(compile_rshift, _1, _2, 0));
  define_builtin_func("^_>>^=_", arith_bin_op, std::bind(compile_rshift, _1, _2, 1));
  define_builtin_func("^_&=_", arith_bin_op, AsmOp::Custom("AND", 2));
  define_builtin_func("^_|=_", arith_bin_op, AsmOp::Custom("OR", 2));
  define_builtin_func("^_^=_", arith_bin_op, AsmOp::Custom("XOR", 2));
  define_builtin_func("muldivr", TypeExpr::new_map(Int3, Int), AsmOp::Custom("MULDIVR", 3));
  define_builtin_func("muldiv", TypeExpr::new_map(Int3, Int), AsmOp::Custom("MULDIV", 3));
  define_builtin_func("muldivmod", TypeExpr::new_map(Int3, Int2), AsmOp::Custom("MULDIVMOD", 3, 2));
  define_builtin_func("_==_", arith_bin_op, AsmOp::Custom("EQ", 2));
  define_builtin_func("_!=_", arith_bin_op, AsmOp::Custom("NEQ", 2));
  define_builtin_func("_<_", arith_bin_op, AsmOp::Custom("LESS", 2));
  define_builtin_func("_>_", arith_bin_op, AsmOp::Custom("GREATER", 2));
  define_builtin_func("_<=_", arith_bin_op, AsmOp::Custom("LEQ", 2));
  define_builtin_func("_>=_", arith_bin_op, AsmOp::Custom("GEQ", 2));
  define_builtin_func("true", Int, AsmOp::Const("TRUE"));
  define_builtin_func("false", Int, AsmOp::Const("FALSE"));
}

/*
 *  
 *   GENERATE OUTPUT SOURCE CODE
 * 
 */

int CodeBlob::split_vars(bool strict) {
  int n = var_cnt, changes = 0;
  for (int j = 0; j < var_cnt; j++) {
    TmpVar& var = vars[j];
    if (strict && var.v_type->minw != var.v_type->maxw) {
      throw src::ParseError{var.where.get(), "variable does not have fixed width, cannot manipulate it"};
    }
    std::vector<TypeExpr*> comp_types;
    int k = var.v_type->extract_components(comp_types);
    assert(k <= 254 && n <= 0x7fff00);
    assert((unsigned)k == comp_types.size());
    if (k != 1) {
      var.coord = ~((n << 8) + k);
      for (int i = 0; i < k; i++) {
        auto v = create_var(vars[j].cls, comp_types[i], 0, vars[j].where.get());
        assert(v == n + i);
        assert(vars[v].idx == v);
        vars[v].name = vars[j].name;
        vars[v].coord = ((int)j << 8) + i + 1;
      }
      n += k;
      ++changes;
    } else if (strict && var.v_type->minw != 1) {
      throw src::ParseError{var.where.get(),
                            "cannot work with variable or variable component of width greater than one"};
    }
  }
  if (!changes) {
    return 0;
  }
  for (auto& op : ops) {
    op.split_vars(vars);
  }
  return changes;
}

bool CodeBlob::compute_used_code_vars() {
  VarDescrList empty_var_info;
  return compute_used_code_vars(ops, empty_var_info, true);
}

bool CodeBlob::compute_used_code_vars(std::unique_ptr<Op>& ops_ptr, const VarDescrList& var_info, bool edit) const {
  assert(ops_ptr);
  if (!ops_ptr->next) {
    assert(ops_ptr->cl == Op::_Nop);
    return ops_ptr->set_var_info(var_info);
  }
  return compute_used_code_vars(ops_ptr->next, var_info, edit) | ops_ptr->compute_used_vars(*this, edit);
}

bool operator==(const VarDescrList& x, const VarDescrList& y) {
  if (x.size() != y.size()) {
    return false;
  }
  for (std::size_t i = 0; i < x.size(); i++) {
    if (x.list[i].idx != y.list[i].idx || x.list[i].flags != y.list[i].flags) {
      return false;
    }
  }
  return true;
}

bool same_values(const VarDescr& x, const VarDescr& y) {
  if (x.val != y.val || x.int_const.is_null() != y.int_const.is_null()) {
    return false;
  }
  if (x.int_const.not_null() && cmp(x.int_const, y.int_const) != 0) {
    return false;
  }
  return true;
}

bool same_values(const VarDescrList& x, const VarDescrList& y) {
  if (x.size() != y.size()) {
    return false;
  }
  for (std::size_t i = 0; i < x.size(); i++) {
    if (x.list[i].idx != y.list[i].idx || !same_values(x.list[i], y.list[i])) {
      return false;
    }
  }
  return true;
}

bool Op::set_var_info(const VarDescrList& new_var_info) {
  if (var_info == new_var_info) {
    return false;
  }
  var_info = new_var_info;
  return true;
}

bool Op::set_var_info(VarDescrList&& new_var_info) {
  if (var_info == new_var_info) {
    return false;
  }
  var_info = std::move(new_var_info);
  return true;
}

std::vector<var_idx_t> sort_unique_vars(const std::vector<var_idx_t>& var_list) {
  std::vector<var_idx_t> vars{var_list}, unique_vars;
  std::sort(vars.begin(), vars.end());
  vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
  return vars;
}

VarDescr* VarDescrList::operator[](var_idx_t idx) {
  for (auto& var : list) {
    if (var.idx == idx) {
      return &var;
    }
  }
  return nullptr;
}

const VarDescr* VarDescrList::operator[](var_idx_t idx) const {
  for (auto& var : list) {
    if (var.idx == idx) {
      return &var;
    }
  }
  return nullptr;
}

std::size_t VarDescrList::count(const std::vector<var_idx_t> idx_list) const {
  std::size_t res = 0;
  for (var_idx_t idx : idx_list) {
    if (operator[](idx)) {
      ++res;
    }
  }
  return res;
}

VarDescrList& VarDescrList::operator-=(var_idx_t idx) {
  for (auto it = list.begin(); it != list.end(); ++it) {
    if (it->idx == idx) {
      list.erase(it);
      break;
    }
  }
  return *this;
}

VarDescrList& VarDescrList::operator-=(const std::vector<var_idx_t>& idx_list) {
  for (var_idx_t idx : idx_list) {
    *this -= idx;
  }
  return *this;
}

VarDescrList& VarDescrList::operator+=(var_idx_t idx) {
  auto it = list.begin();
  for (; it != list.end(); ++it) {
    if (it->idx == idx) {
      return *this;
    } else if (it->idx > idx) {
      break;
    }
  }
  list.emplace(it, idx, VarDescr::_Last);
  return *this;
}

VarDescrList& VarDescrList::operator+=(const std::vector<var_idx_t>& idx_list) {
  for (var_idx_t idx : idx_list) {
    *this += idx;
  }
  return *this;
}

VarDescrList& VarDescrList::clear_last() {
  for (auto& var : list) {
    if (var.flags & VarDescr::_Last) {
      var.flags &= ~VarDescr::_Last;
    }
  }
  return *this;
}

VarDescrList VarDescrList::operator+(const VarDescrList& y) const {
  VarDescrList res;
  auto it1 = list.cbegin();
  auto it2 = y.list.cbegin();
  while (it1 != list.cend() && it2 != y.list.cend()) {
    if (it1->idx < it2->idx) {
      res.list.push_back(*it1++);
    } else if (it1->idx > it2->idx) {
      res.list.push_back(*it2++);
    } else {
      res.list.push_back(*it1++);
      it2++;
    }
  }
  while (it1 != list.cend()) {
    res.list.push_back(*it1++);
  }
  while (it2 != y.list.cend()) {
    res.list.push_back(*it2++);
  }
  return res;
}

VarDescrList& VarDescrList::operator+=(const VarDescrList& y) {
  return *this = *this + y;
}

VarDescrList VarDescrList::operator|(const VarDescrList& y) const {
  VarDescrList res;
  auto it1 = list.cbegin();
  auto it2 = y.list.cbegin();
  while (it1 != list.cend() && it2 != y.list.cend()) {
    if (it1->idx < it2->idx) {
      it1++;
    } else if (it1->idx > it2->idx) {
      it2++;
    } else {
      res.list.push_back(*it1++);
      res.list.back() |= *it2++;
    }
  }
  return res;
}

VarDescrList& VarDescrList::operator|=(const VarDescrList& y) {
  return *this = *this | y;
}

VarDescr& VarDescrList::add(var_idx_t idx) {
  auto it = list.begin();
  std::size_t k = 0;
  for (; it != list.end(); ++it, ++k) {
    if (it->idx == idx) {
      return *it;
    } else if (it->idx > idx) {
      break;
    }
  }
  list.emplace(it, idx);
  return list[k];
}

VarDescr& VarDescrList::add_newval(var_idx_t idx) {
  auto it = list.begin();
  std::size_t k = 0;
  for (; it != list.end(); ++it, ++k) {
    if (it->idx == idx) {
      it->clear_value();
      return *it;
    } else if (it->idx > idx) {
      break;
    }
  }
  list.emplace(it, idx);
  return list[k];
}

VarDescrList& VarDescrList::operator&=(const VarDescrList& values) {
  for (const VarDescr& vd : values.list) {
    VarDescr* item = operator[](vd.idx);
    if (item) {
      *item &= vd;
    }
  }
  return *this;
}

VarDescrList& VarDescrList::import_values(const VarDescrList& values) {
  for (const VarDescr& vd : values.list) {
    VarDescr* item = operator[](vd.idx);
    if (item) {
      item->set_value(vd);
    }
  }
  return *this;
}

bool Op::std_compute_used_vars() {
  // left = OP right
  // var_info := (var_info - left) + right
  VarDescrList new_var_info{next->var_info};
  new_var_info -= left;
  new_var_info.clear_last();
  if (args.size() == right.size()) {
    for (const VarDescr& arg : args) {
      if (!arg.is_unused()) {
        new_var_info += arg.idx;
      }
    }
  } else {
    new_var_info += right;
  }
  return set_var_info(std::move(new_var_info));
}

bool Op::compute_used_vars(const CodeBlob& code, bool edit) {
  assert(next);
  const VarDescrList& next_var_info = next->var_info;
  if (disabled() || cl == _Nop) {
    return set_var_info(next_var_info);
  }
  switch (cl) {
    case _IntConst:
    case _GlobVar:
    case _Call:
    case _CallInd: {
      // left = EXEC right;
      if (!next_var_info.count(left)) {
        // all variables in `left` are not needed
        if (edit) {
          disable();
        }
        set_var_info(next_var_info);
        return true;
      }
      return std_compute_used_vars();
    }
    case _Let: {
      // left = right
      std::size_t cnt = next_var_info.count(left);
      bool changes = false;
      if (!cnt) {
        // all variables in `left` are not needed
        if (edit) {
          disable();
        }
        set_var_info(next_var_info);
        return true;
      } else if (cnt < left.size()) {
        assert(left.size() == right.size());
        std::vector<var_idx_t> new_left, new_right;
        auto l_it = left.cbegin(), r_it = right.cbegin();
        for (; l_it < left.cend(); ++l_it, ++r_it) {
          if (std::find(l_it + 1, left.cend(), *l_it) == left.cend() && next_var_info[*l_it]) {
            new_left.push_back(*l_it);
            new_right.push_back(*r_it);
          }
        }
        if (edit) {
          left = std::move(new_left);
          right = std::move(new_right);
          changes = true;
        } else {
          VarDescrList new_var_info{next_var_info};
          new_var_info -= new_left;
          new_var_info.clear_last();
          new_var_info += new_right;
          return set_var_info(std::move(new_var_info));
        }
      }
      return std_compute_used_vars() | changes;
    }
    case _Return: {
      // return left
      if (var_info.count(left) == left.size()) {
        return false;
      }
      std::vector<var_idx_t> unique_vars = sort_unique_vars(left);
      var_info.list.clear();
      for (var_idx_t i : unique_vars) {
        var_info.list.emplace_back(i, VarDescr::_Last);
      }
      return true;
    }
    case _Import: {
      // import left
      std::vector<var_idx_t> unique_vars = sort_unique_vars(left);
      var_info.list.clear();
      for (var_idx_t i : unique_vars) {
        var_info.list.emplace_back(i, next_var_info[i] ? 0 : VarDescr::_Last);
      }
      return true;
    }
    case _If: {
      // if (left) then block0 else block1
      code.compute_used_code_vars(block0, next_var_info, edit);
      code.compute_used_code_vars(block1, next_var_info, edit);
      VarDescrList merge_info = block0->var_info + block1->var_info;
      merge_info.clear_last();
      merge_info += left;
      return set_var_info(std::move(merge_info));
    }
    case _While: {
      // while (block0 || left) block1;
      // ... { block0 left block1 } block0 left next
      VarDescrList after_cond_first{next_var_info};
      after_cond_first += left;
      code.compute_used_code_vars(block0, after_cond_first, false);
      VarDescrList new_var_info{block0->var_info};
      bool changes = false;
      do {
        code.compute_used_code_vars(block1, block0->var_info, changes);
        VarDescrList after_cond{block1->var_info};
        after_cond += left;
        code.compute_used_code_vars(block0, after_cond, changes);
        std::size_t n = new_var_info.size();
        new_var_info += block0->var_info;
        new_var_info.clear_last();
        if (changes) {
          break;
        }
        changes = (new_var_info.size() == n);
      } while (changes <= edit);
      return set_var_info(std::move(new_var_info));
    }
    case _Until: {
      // until (block0 || left);
      // .. { block0 left } block0 left next
      VarDescrList after_cond_first{next_var_info};
      after_cond_first += left;
      code.compute_used_code_vars(block0, after_cond_first, false);
      VarDescrList new_var_info{block0->var_info};
      bool changes = false;
      do {
        VarDescrList after_cond{new_var_info};
        after_cond += next_var_info;
        after_cond += left;
        code.compute_used_code_vars(block0, after_cond, changes);
        std::size_t n = new_var_info.size();
        new_var_info += block0->var_info;
        new_var_info.clear_last();
        if (changes) {
          break;
        }
        changes = (new_var_info.size() == n);
      } while (changes <= edit);
      return set_var_info(std::move(new_var_info) + next_var_info);
    }
    case _Repeat: {
      // repeat (left) block0
      // left { block0 } next
      VarDescrList new_var_info{next_var_info};
      bool changes = false;
      do {
        code.compute_used_code_vars(block0, new_var_info, changes);
        std::size_t n = new_var_info.size();
        new_var_info += block0->var_info;
        new_var_info.clear_last();
        if (changes) {
          break;
        }
        changes = (new_var_info.size() == n);
      } while (changes <= edit);
      new_var_info += left;
      return set_var_info(std::move(new_var_info));
    }
    case _Again: {
      // for(;;) block0
      // { block0 }
      VarDescrList new_var_info;
      bool changes = false;
      do {
        code.compute_used_code_vars(block0, new_var_info, changes);
        std::size_t n = new_var_info.size();
        new_var_info += block0->var_info;
        new_var_info.clear_last();
        if (changes) {
          break;
        }
        changes = (new_var_info.size() == n);
      } while (changes <= edit);
      return set_var_info(std::move(new_var_info));
    }
    default:
      std::cerr << "fatal: unknown operation <??" << cl << ">\n";
      throw src::ParseError{where, "unknown operation"};
  }
}

bool prune_unreachable(std::unique_ptr<Op>& ops) {
  if (!ops) {
    return true;
  }
  Op& op = *ops;
  if (op.disabled() || op.cl == Op::_Nop) {
    if (op.next) {
      ops = std::move(op.next);
      return prune_unreachable(ops);
    }
    return true;
  }
  bool reach;
  switch (op.cl) {
    case Op::_IntConst:
    case Op::_GlobVar:
    case Op::_Call:
    case Op::_CallInd:
    case Op::_Import:
      reach = true;
      break;
    case Op::_Let: {
      reach = true;
      break;
    }
    case Op::_Return:
      reach = false;
      break;
    case Op::_If: {
      // if left then block0 else block1; ...
      VarDescr* c_var = op.var_info[op.left[0]];
      if (c_var && c_var->always_true()) {
        op.block0->last().next = std::move(op.next);
        ops = std::move(op.block0);
        return prune_unreachable(ops);
      } else if (c_var && c_var->always_false()) {
        op.block1->last().next = std::move(op.next);
        ops = std::move(op.block1);
        return prune_unreachable(ops);
      } else {
        reach = prune_unreachable(op.block0) | prune_unreachable(op.block1);
      }
      break;
    }
    case Op::_While: {
      // while (block0 || left) block1;
      if (!prune_unreachable(op.block0)) {
        // computation of block0 never returns
        ops = std::move(op.block0);
        return prune_unreachable(ops);
      }
      VarDescr* c_var = op.block0->last().var_info[op.left[0]];
      if (c_var && c_var->always_false()) {
        // block1 never executed
        op.block0->last().next = std::move(op.next);
        ops = std::move(op.block0);
        return false;
      } else if (c_var && c_var->always_true()) {
        if (!prune_unreachable(op.block1)) {
          // block1 never returns
          op.block0->last().next = std::move(op.block1);
          ops = std::move(op.block0);
          return false;
        }
        // infinite loop
        op.cl = Op::_Again;
        op.block0->last().next = std::move(op.block1);
        op.left.clear();
        reach = false;
      } else {
        if (!prune_unreachable(op.block1)) {
          // block1 never returns, while equivalent to block0 ; if left then block1 else next
          op.cl = Op::_If;
          std::unique_ptr<Op> new_op = std::move(op.block0);
          op.block0 = std::move(op.block1);
          op.block1 = std::make_unique<Op>(op.next->where, Op::_Nop);
          new_op->last().next = std::move(ops);
          ops = std::move(new_op);
        }
        reach = true;  // block1 may be never executed
      }
      break;
    }
    case Op::_Repeat: {
      // repeat (left) block0
      VarDescr* c_var = op.var_info[op.left[0]];
      if (c_var && c_var->always_nonpos()) {
        // loop never executed
        ops = std::move(op.next);
        return prune_unreachable(ops);
      }
      if (c_var && c_var->always_pos()) {
        if (!prune_unreachable(op.block0)) {
          // block0 executed at least once, and it never returns
          // replace code with block0
          ops = std::move(op.block0);
          return false;
        }
      } else {
        prune_unreachable(op.block0);
      }
      reach = true;
      break;
    }
    case Op::_Until:
    case Op::_Again: {
      // do block0 until left; ...
      if (!prune_unreachable(op.block0)) {
        // block0 never returns, replace loop by block0
        ops = std::move(op.block0);
        return false;
      }
      reach = true;
      break;
    }
    default:
      std::cerr << "fatal: unknown operation <??" << op.cl << ">\n";
      throw src::ParseError{op.where, "unknown operation in prune_unreachable()"};
  }
  if (reach) {
    return prune_unreachable(op.next);
  } else {
    while (op.next->next) {
      op.next = std::move(op.next->next);
    }
    return false;
  }
}

void CodeBlob::prune_unreachable_code() {
  if (prune_unreachable(ops)) {
    throw src::ParseError{loc, "control reaches end of function"};
  }
}

void CodeBlob::simplify_var_types() {
  for (TmpVar& var : vars) {
    TypeExpr::remove_indirect(var.v_type);
  }
}

void CodeBlob::fwd_analyze() {
  VarDescrList values;
  assert(ops && ops->cl == Op::_Import);
  for (var_idx_t i : ops->left) {
    values += i;
    if (vars[i].v_type->is_int()) {
      values[i]->val |= VarDescr::_Int;
    }
  }
  ops->fwd_analyze(values);
}

void Op::prepare_args(VarDescrList values) {
  if (args.size() != right.size()) {
    args.clear();
    for (var_idx_t i : right) {
      args.emplace_back(i);
    }
  }
  for (std::size_t i = 0; i < right.size(); i++) {
    const VarDescr* val = values[right[i]];
    if (val) {
      args[i].set_value(*val);
      args[i].clear_unused();
    }
  }
}

VarDescrList Op::fwd_analyze(VarDescrList values) {
  var_info.import_values(values);
  switch (cl) {
    case _Nop:
    case _Import:
      break;
    case _Return:
      values.list.clear();
      break;
    case _IntConst: {
      values.add_newval(left[0]).set_const(int_const);
      break;
    }
    case _GlobVar: {
      for (var_idx_t i : left) {
        values.add_newval(i);
      }
      break;
    }
    case _Call: {
      prepare_args(values);
      auto func = dynamic_cast<const SymValBuiltinFunc*>(fun_ref->value);
      if (func) {
        std::vector<VarDescr> res;
        res.reserve(left.size());
        for (var_idx_t i : left) {
          res.emplace_back(i);
        }
        func->compile(res, args);  // abstract interpretation of res := f (args)
        int j = 0;
        for (var_idx_t i : left) {
          values.add_newval(i).set_value(res[j++]);
        }
      } else {
        for (var_idx_t i : left) {
          values.add_newval(i);
        }
      }
      break;
    }
    case _CallInd: {
      for (var_idx_t i : left) {
        values.add_newval(i);
      }
      break;
    }
    case _Let: {
      std::vector<VarDescr> old_val;
      assert(left.size() == right.size());
      for (std::size_t i = 0; i < right.size(); i++) {
        const VarDescr* ov = values[right[i]];
        assert(ov);
        old_val.push_back(*ov);
      }
      for (std::size_t i = 0; i < left.size(); i++) {
        values.add_newval(left[i]).set_value(std::move(old_val[i]));
      }
      break;
    }
    case _If: {
      VarDescrList val1 = block0->fwd_analyze(values);
      VarDescrList val2 = block1->fwd_analyze(std::move(values));
      values = val1 | val2;
      break;
    }
    case _Repeat: {
      bool atl1 = (values[left[0]] && values[left[0]]->always_pos());
      VarDescrList next_values = block0->fwd_analyze(values);
      while (true) {
        VarDescrList new_values = values | next_values;
        if (same_values(new_values, values)) {
          break;
        }
        values = std::move(new_values);
        next_values = block0->fwd_analyze(values);
      }
      if (atl1) {
        values = std::move(next_values);
      }
      break;
    }
    case _While: {
      values = block0->fwd_analyze(values);
      if (values[left[0]] && values[left[0]]->always_false()) {
        // block1 never executed
        block1->fwd_analyze(values);
        break;
      }
      while (true) {
        VarDescrList next_values = values | block0->fwd_analyze(block1->fwd_analyze(values));
        if (same_values(next_values, values)) {
          break;
        }
        values = std::move(next_values);
      }
      break;
    }
    case _Until:
    case _Again: {
      while (true) {
        VarDescrList next_values = values | block0->fwd_analyze(values);
        if (same_values(next_values, values)) {
          break;
        }
        values = std::move(next_values);
      }
      values = block0->fwd_analyze(values);
      break;
    }
    default:
      std::cerr << "fatal: unknown operation <??" << cl << ">\n";
      throw src::ParseError{where, "unknown operation in fwd_analyze()"};
  }
  if (next) {
    return next->fwd_analyze(std::move(values));
  } else {
    return values;
  }
}

bool Op::set_noreturn(bool nr) {
  if (nr) {
    flags |= _NoReturn;
  } else {
    flags &= ~_NoReturn;
  }
  return nr;
}

bool Op::mark_noreturn() {
  switch (cl) {
    case _Nop:
      if (!next) {
        return set_noreturn(false);
      }
      // fallthrough
    case _Import:
    case _IntConst:
    case _Let:
    case _GlobVar:
    case _CallInd:
    case _Call:
      return set_noreturn(next->mark_noreturn());
    case _Return:
      return set_noreturn(true);
    case _If:
      return set_noreturn((block0->mark_noreturn() & block1->mark_noreturn()) | next->mark_noreturn());
    case _Again:
      block0->mark_noreturn();
      return set_noreturn(false);
    case _Until:
      return set_noreturn(block0->mark_noreturn() | next->mark_noreturn());
    case _While:
      block1->mark_noreturn();
      return set_noreturn(block0->mark_noreturn() | next->mark_noreturn());
    case _Repeat:
      block0->mark_noreturn();
      return set_noreturn(next->mark_noreturn());
    default:
      std::cerr << "fatal: unknown operation <??" << cl << ">\n";
      throw src::ParseError{where, "unknown operation in mark_noreturn()"};
  }
}

void CodeBlob::mark_noreturn() {
  ops->mark_noreturn();
}

/*
 * 
 *   GENERATE CODE
 * 
 */

int Stack::find(var_idx_t var, int from) const {
  for (int i = from; i < depth(); i++) {
    if (at(i) == var) {
      return i;
    }
  }
  return -1;
}

int Stack::find(var_idx_t var, int from, int to) const {
  for (int i = from; i < depth() && i < to; i++) {
    if (at(i) == var) {
      return i;
    }
  }
  return -1;
}

void Stack::issue_pop(int i) {
  validate(i);
  o << AsmOp::Pop(i);
  at(i) = get(0);
  s.pop_back();
  modified();
}

void Stack::issue_push(int i) {
  validate(i);
  o << AsmOp::Push(i);
  s.push_back(get(i));
  modified();
}

void Stack::issue_xchg(int i, int j) {
  validate(i);
  validate(j);
  if (i != j && get(i) != get(j)) {
    o << AsmOp::Xchg(i, j);
    std::swap(at(i), at(j));
    modified();
  }
}

int Stack::drop_vars_except(const VarDescrList& var_info, int excl_var) {
  int dropped = 0, changes;
  do {
    changes = 0;
    int n = depth();
    for (int i = 0; i < n; i++) {
      var_idx_t idx = at(i);
      if ((!var_info[idx] && idx != excl_var) || find(idx, 0, i - 1) >= 0) {
        // unneeded
        issue_pop(i);
        changes = 1;
        break;
      }
    }
    dropped += changes;
  } while (changes);
  return dropped;
}

void Stack::show(int flags) {
  std::ostringstream os;
  for (var_idx_t i : s) {
    os << ' ';
    o.show_var(os, i);
  }
  o << AsmOp::Comment(os.str());
  mode |= _Shown;
}

void Stack::forget_var(var_idx_t idx) {
  for (auto& x : s) {
    if (x == idx) {
      x = _Garbage;
      modified();
    }
  }
}

void Stack::push_new_var(var_idx_t idx) {
  forget_var(idx);
  s.push_back(idx);
  modified();
}

void Stack::assign_var(var_idx_t new_idx, var_idx_t old_idx) {
  int i = find(old_idx);
  assert(i >= 0 && "variable not found in stack");
  if (new_idx != old_idx) {
    at(i) = new_idx;
    modified();
  }
}

void Stack::do_copy_var(var_idx_t new_idx, var_idx_t old_idx) {
  int i = find(old_idx);
  assert(i >= 0 && "variable not found in stack");
  if (find(old_idx, i + 1) < 0) {
    issue_push(i);
    assert(at(0) == old_idx);
  }
  assign_var(new_idx, old_idx);
}

void Stack::enforce_state(const StackLayout& req_stack) {
  int k = (int)req_stack.size();
  for (int i = 0; i < k; i++) {
    var_idx_t x = req_stack[i];
    if (i < depth() && s[i] == x) {
      continue;
    }
    int j = find(x);
    if (j >= depth() - i) {
      issue_push(j);
      j = 0;
    }
    issue_xchg(j, depth() - i - 1);
    assert(s[i] == x);
  }
  while (depth() > k) {
    issue_pop(0);
  }
  assert(depth() == k);
  for (int i = 0; i < k; i++) {
    assert(s[i] == req_stack[i]);
  }
}

void Stack::rearrange_top(const StackLayout& top, std::vector<bool> last) {
  while (last.size() < top.size()) {
    last.push_back(false);
  }
  int k = (int)top.size();
  for (int i = 0; i < k; i++) {
    for (int j = i + 1; j < k; j++) {
      if (top[i] == top[j]) {
        last[i] = false;
        break;
      }
    }
  }
  int ss = 0;
  for (int i = 0; i < k; i++) {
    if (last[i]) {
      ++ss;
    }
  }
  for (int i = 0; i < k; i++) {
    var_idx_t x = top[i];
    if (last[i]) {
      // rearrange x to be at ss(ss-1)
      int j = find(x);
      issue_xchg(--ss, j);
      assert(get(ss) == x);
    } else {
      // create a new copy of x
      int j = find(x);
      issue_push(j);
      issue_xchg(0, ss);
      assert(get(ss) == x);
    }
  }
  assert(!ss);
}

void Stack::rearrange_top(var_idx_t top, bool last) {
  int i = find(top);
  if (last) {
    issue_xchg(0, i);
  } else {
    issue_push(i);
  }
  assert(get(0) == top);
}

bool Op::generate_code_step(Stack& stack) {
  stack.opt_show();
  stack.drop_vars_except(var_info);
  stack.opt_show();
  switch (cl) {
    case _Nop:
    case _Import:
      return true;
    case _Return: {
      stack.enforce_state(left);
      stack.opt_show();
      return false;
    }
    case _IntConst: {
      stack.o << push_const(int_const);
      stack.push_new_var(left[0]);
      return true;
    }
    case _Let: {
      assert(left.size() == right.size());
      int i = 0;
      for (auto it = right.cbegin(); it != right.cend(); ++it) {
        var_idx_t x = *it;
        bool is_last = false;
        if (std::find(it + 1, right.cend(), x) == right.cend()) {
          auto info = var_info[x];
          if (info && info->is_last()) {
            is_last = true;
          }
        }
        if (is_last) {
          stack.assign_var(--i, x);
        } else {
          stack.do_copy_var(--i, x);
        }
      }
      i = 0;
      for (var_idx_t x : left) {
        stack.assign_var(x, --i);
      }
      return true;
    }
    case _Call:
    case _CallInd: {
      std::vector<var_idx_t> right1;
      if (args.size()) {
        for (const VarDescr& arg : args) {
          if (!arg.is_unused()) {
            right1.push_back(arg.idx);
          }
        }
      } else {
        right1 = right;
      }
      std::vector<bool> last;
      for (var_idx_t x : right1) {
        last.push_back(var_info[x] && var_info[x]->is_last());
      }
      stack.rearrange_top(right1, std::move(last));
      stack.opt_show();
      int k = (int)stack.depth() - (int)right1.size();
      assert(k >= 0);
      for (int i = 0; i < (int)right1.size(); i++) {
        assert(stack.s[k + i] == right1[i]);
      }
      if (cl == _CallInd) {
        stack.o << exec_arg_op("CALLARGS", (int)right.size() - 1, -1, (int)right.size() - 1);
      } else {
        auto func = dynamic_cast<const SymValBuiltinFunc*>(fun_ref->value);
        if (func) {
          std::vector<VarDescr> res;
          res.reserve(left.size());
          for (var_idx_t i : left) {
            res.emplace_back(i);
          }
          stack.o << func->compile(res, args);  // compile res := f (args)
        } else {
          std::string name = symbols.get_name(fun_ref->sym_idx);
          stack.o << AsmOp::Custom(name + " CALLDICT", (int)right.size());
        }
      }
      stack.s.resize(k);
      for (int i = 0; i < (int)left.size(); i++) {
        stack.push_new_var(left[i]);
      }
      return true;
    }
    case _If: {
      if (block0->is_empty() && block1->is_empty()) {
        return true;
      }
      var_idx_t x = left[0];
      stack.rearrange_top(x, var_info[x] && var_info[x]->is_last());
      assert(stack.get(0) == x);
      stack.opt_show();
      stack.s.pop_back();
      stack.modified();
      if (block1->is_empty()) {
        // if (left) block0; ...
        if (block0->noreturn()) {
          stack.o << "IFJMP:<{";
          stack.o.indent();
          Stack stack_copy{stack};
          block0->generate_code_all(stack_copy);
          stack.o.undent();
          stack.o << "}>";
          return true;
        }
        stack.o << "IF:<{";
        stack.o.indent();
        Stack stack_copy{stack};
        block0->generate_code_all(stack_copy);
        stack_copy.drop_vars_except(var_info);
        stack_copy.opt_show();
        if (stack_copy == stack) {
          stack.o.undent();
          stack.o << "}>";
          return true;
        }
        stack_copy.drop_vars_except(next->var_info);
        stack_copy.opt_show();
        if (stack_copy == stack) {
          stack.o.undent();
          stack.o << "}>";
          return true;
        }
        stack.o.undent();
        stack.o << "}>ELSE<{";
        stack.o.indent();
        stack.enforce_state(stack_copy.s);
        stack.opt_show();
        stack.o.undent();
        stack.o << "}>";
        return true;
      }
      if (block0->is_empty()) {
        // if (!left) block1; ...
        if (block1->noreturn()) {
          stack.o << "IFNOTJMP:<{";
          stack.o.indent();
          Stack stack_copy{stack};
          block1->generate_code_all(stack_copy);
          stack.o.undent();
          stack.o << "}>";
          return true;
        }
        stack.o << "IFNOT:<{";
        stack.o.indent();
        Stack stack_copy{stack};
        block1->generate_code_all(stack_copy);
        stack_copy.drop_vars_except(var_info);
        stack_copy.opt_show();
        if (stack_copy == stack) {
          stack.o.undent();
          stack.o << "}>";
          return true;
        }
        stack_copy.drop_vars_except(next->var_info);
        stack_copy.opt_show();
        if (stack_copy == stack) {
          stack.o.undent();
          stack.o << "}>";
          return true;
        }
        stack.o.undent();
        stack.o << "}>ELSE<{";
        stack.o.indent();
        stack.enforce_state(stack_copy.s);
        stack.opt_show();
        stack.o.undent();
        stack.o << "}>";
        return true;
      }
      if (block0->noreturn()) {
        stack.o << "IFJMP:<{";
        stack.o.indent();
        Stack stack_copy{stack};
        block0->generate_code_all(stack_copy);
        stack.o.undent();
        stack.o << "}>";
        block1->generate_code_all(stack);
        return true;
      }
      if (block1->noreturn()) {
        stack.o << "IFNOTJMP:<{";
        stack.o.indent();
        Stack stack_copy{stack};
        block1->generate_code_all(stack_copy);
        stack.o.undent();
        stack.o << "}>";
        block0->generate_code_all(stack);
        return true;
      }
      stack.o << "IF:<{";
      stack.o.indent();
      Stack stack_copy{stack};
      block0->generate_code_all(stack_copy);
      stack_copy.drop_vars_except(next->var_info);
      stack_copy.opt_show();
      stack.o.undent();
      stack.o << "}>ELSE<{";
      stack.o.indent();
      block1->generate_code_all(stack);
      stack.enforce_state(stack_copy.s);
      stack.opt_show();
      stack.o.undent();
      stack.o << "}>";
      return true;
    }
    case _Repeat: {
      var_idx_t x = left[0];
      //stack.drop_vars_except(block0->var_info, x);
      stack.rearrange_top(x, var_info[x] && var_info[x]->is_last());
      assert(stack.get(0) == x);
      stack.opt_show();
      stack.s.pop_back();
      stack.modified();
      if (!next->is_empty()) {
        stack.o << "REPEAT:<{";
        stack.o.indent();
        StackLayout layout1 = stack.s;
        block0->generate_code_all(stack);
        stack.enforce_state(std::move(layout1));
        stack.opt_show();
        stack.o.undent();
        stack.o << "}>";
        return true;
      } else {
        stack.o << "REPEATEND";
        StackLayout layout1 = stack.s;
        block0->generate_code_all(stack);
        stack.enforce_state(std::move(layout1));
        stack.opt_show();
        return false;
      }
    }
    case _Again: {
      stack.drop_vars_except(block0->var_info);
      stack.opt_show();
      if (!next->is_empty()) {
        stack.o << "AGAIN:<{";
        stack.o.indent();
        StackLayout layout1 = stack.s;
        block0->generate_code_all(stack);
        stack.enforce_state(std::move(layout1));
        stack.opt_show();
        stack.o.undent();
        stack.o << "}>";
        return true;
      } else {
        stack.o << "AGAINEND";
        StackLayout layout1 = stack.s;
        block0->generate_code_all(stack);
        stack.enforce_state(std::move(layout1));
        stack.opt_show();
        return false;
      }
    }
    case _Until: {
      // stack.drop_vars_except(block0->var_info);
      // stack.opt_show();
      if (!next->is_empty()) {
        stack.o << "UNTIL:<{";
        stack.o.indent();
        StackLayout layout1 = stack.s;
        block0->generate_code_all(stack);
        layout1.push_back(left[0]);
        stack.enforce_state(std::move(layout1));
        stack.opt_show();
        stack.o.undent();
        stack.o << "}>";
        stack.s.pop_back();
        stack.modified();
        return true;
      } else {
        stack.o << "UNTILEND";
        StackLayout layout1 = stack.s;
        block0->generate_code_all(stack);
        layout1.push_back(left[0]);
        stack.enforce_state(std::move(layout1));
        stack.opt_show();
        return false;
      }
    }
    case _While: {
      // while (block0 | left) block1; ...next
      var_idx_t x = left[0];
      stack.drop_vars_except(block0->var_info);
      stack.opt_show();
      StackLayout layout1 = stack.s;
      bool next_empty = next->is_empty();
      stack.o << (next_empty ? "WHILEEND:<{" : "WHILE:<{");
      stack.o.indent();
      block0->generate_code_all(stack);
      stack.rearrange_top(x, !next->var_info[x] && !block1->var_info[x]);
      stack.opt_show();
      stack.s.pop_back();
      stack.modified();
      stack.o.undent();
      Stack stack_copy{stack};
      stack.o << (next_empty ? "}>" : "}>DO<{");
      if (!next_empty) {
        stack.o.indent();
      }
      stack_copy.opt_show();
      block1->generate_code_all(stack_copy);
      stack_copy.enforce_state(std::move(layout1));
      stack_copy.opt_show();
      if (!next_empty) {
        stack.o.undent();
        stack.o << "}>";
        return true;
      } else {
        return false;
      }
    }
    default:
      std::cerr << "fatal: unknown operation <??" << cl << ">\n";
      throw src::ParseError{where, "unknown operation in generate_code()"};
  }
}

bool Op::generate_code_all(Stack& stack) {
  if (generate_code_step(stack) && next) {
    return next->generate_code_all(stack);
  } else {
    return false;
  }
}

void CodeBlob::generate_code(AsmOpList& out, int mode) {
  Stack stack{out, mode};
  assert(ops && ops->cl == Op::_Import);
  for (var_idx_t x : ops->left) {
    stack.push_new_var(x);
  }
  ops->generate_code_all(stack);
}

void CodeBlob::generate_code(std::ostream& os, int mode, int indent) {
  AsmOpList out_list(indent, &vars);
  generate_code(out_list, mode);
  out_list.out(os, mode);
}

void generate_output_func(SymDef* func_sym) {
  SymValFunc* func_val = dynamic_cast<SymValFunc*>(func_sym->value);
  assert(func_val);
  std::string name = symbols.get_name(func_sym->sym_idx);
  std::cerr << "\n\n=========================\nfunction " << name << " : " << func_val->get_type() << std::endl;
  if (!func_val->code) {
    std::cerr << "( undefined )\n";
  } else {
    CodeBlob& code = *(func_val->code);
    code.print(std::cerr, 1);
    code.simplify_var_types();
    code.prune_unreachable_code();
    code.split_vars(true);
    for (int i = 0; i < 8; i++) {
      code.compute_used_code_vars();
      code.fwd_analyze();
      code.prune_unreachable_code();
    }
    code.mark_noreturn();
    code.print(std::cerr, 7);
    std::cerr << "\n---------- resulting code for " << name << " -------------\n";
    code.generate_code(std::cout, Stack::_StkCmt | Stack::_CptStkCmt);
    std::cerr << "--------------\n";
  }
}

int generate_output() {
  int errors = 0;
  for (SymDef* func_sym : glob_func) {
    try {
      generate_output_func(func_sym);
    } catch (src::Error& err) {
      std::cerr << "cannot generate code for function `" << symbols.get_name(func_sym->sym_idx) << "`:\n"
                << err << std::endl;
      ++errors;
    }
  }
  return errors;
}

}  // namespace funC

void usage(const char* progname) {
  std::cerr << "usage: " << progname << " [-i] [-o<output-filename>] {<func-source-filename> ...}\n";
  std::exit(2);
}

std::string output_filename;

int main(int argc, char* const argv[]) {
  int i;
  bool interactive = false;
  while ((i = getopt(argc, argv, "hio:")) != -1) {
    switch (i) {
      case 'i':
        interactive = true;
        break;
      case 'o':
        output_filename = optarg;
        break;
      case 'h':
      default:
        usage(argv[0]);
    }
  }

  src::define_keywords();
  funC::define_builtins();

  int ok = 0, proc = 0;
  try {
    while (optind < argc) {
      ok += funC::parse_source_file(argv[optind++]);
      proc++;
    }
    if (interactive) {
      ok += funC::parse_source_stdin();
      proc++;
    }
    if (ok < proc) {
      throw src::Fatal{"output code generation omitted because of errors"};
    }
    if (!proc) {
      throw src::Fatal{"no source files, no output"};
    }
    funC::generate_output();
  } catch (src::Fatal& fatal) {
    std::cerr << "fatal: " << fatal << std::endl;
    std::exit(1);
  } catch (src::Error& error) {
    std::cerr << error << std::endl;
    std::exit(1);
  } catch (funC::UniformizeError& unif_err) {
    std::cerr << "fatal: ";
    unif_err.print_message(std::cerr);
    std::cerr << std::endl;
    std::exit(1);
  }
}
