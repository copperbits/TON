#include "func.h"

namespace funC {

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

}  // namespace funC
