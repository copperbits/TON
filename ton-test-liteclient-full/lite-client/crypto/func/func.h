#pragma once
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include "common/refcnt.hpp"
#include "common/bigint.hpp"
#include "common/refint.h"

namespace funC {

enum Keyword {
  _Eof = -1,
  _Ident = 0,
  _Number,
  _Return = 0x80,
  _Var,
  _Repeat,
  _Do,
  _While,
  _Until,
  _If,
  _Then,
  _Else,
  _Elseif,
  _Eq,
  _Neq,
  _Leq,
  _Geq,
  _Lshift,
  _Rshift,
  _RshiftR,
  _RshiftC,
  _DivR,
  _DivC,
  _DivMod,
  _PlusLet,
  _MinusLet,
  _TimesLet,
  _DivLet,
  _DivRLet,
  _DivCLet,
  _ModLet,
  _LshiftLet,
  _RshiftLet,
  _RshiftRLet,
  _RshiftCLet,
  _Int,
  _Cell,
  _Slice,
  _Builder,
  _Cont,
  _Type,
  _Mapsto,
  _Extern,
  _Operator,
  _Infix,
  _Infixl,
  _Infixr
};

}  // namespace funC

namespace funC {

/*
 * 
 *   TYPE EXPRESSIONS
 * 
 */

struct TypeExpr {
  enum te_type { te_Unknown, te_Indirect, te_Atomic, te_Tensor, te_Map, te_Type } constr;
  enum {
    _Int = Keyword::_Int,
    _Cell = Keyword::_Cell,
    _Slice = Keyword::_Slice,
    _Builder = Keyword::_Builder,
    _Cont = Keyword::_Cont,
    _Type = Keyword::_Type
  };
  int value;
  int minw, maxw;
  static constexpr int w_inf = 1023;
  std::vector<TypeExpr*> args;
  TypeExpr(te_type _constr, int _val = 0) : constr(_constr), value(_val), minw(0), maxw(w_inf) {
  }
  TypeExpr(te_type _constr, int _val, int width) : constr(_constr), value(_val), minw(width), maxw(width) {
  }
  TypeExpr(te_type _constr, std::vector<TypeExpr*> list)
      : constr(_constr), value((int)list.size()), args(std::move(list)) {
    compute_width();
  }
  TypeExpr(te_type _constr, std::initializer_list<TypeExpr*> list)
      : constr(_constr), value((int)list.size()), args(std::move(list)) {
    compute_width();
  }
  bool is_atomic() const {
    return constr == te_Atomic;
  }
  bool is_atomic(int v) const {
    return constr == te_Atomic && value == v;
  }
  bool is_int() const {
    return is_atomic(_Int);
  }
  void compute_width();
  bool recompute_width();
  void show_width(std::ostream& os);
  std::ostream& print(std::ostream& os, int prio = 0);
  void replace_with(TypeExpr* te2);
  int extract_components(std::vector<TypeExpr*>& comp_list);
  static int holes;
  static TypeExpr* new_hole() {
    return new TypeExpr{te_Unknown, ++holes};
  }
  static TypeExpr* new_unit() {
    return new TypeExpr{te_Tensor, 0, 0};
  }
  static TypeExpr* new_atomic(int value) {
    return new TypeExpr{te_Atomic, value, 1};
  }
  static TypeExpr* new_map(TypeExpr* from, TypeExpr* to);
  static TypeExpr* new_func() {
    return new_map(new_hole(), new_hole());
  }
  static TypeExpr* new_tensor(std::vector<TypeExpr*> list, bool red = true) {
    return red && list.size() == 1 ? list[0] : new TypeExpr{te_Tensor, std::move(list)};
  }
  static TypeExpr* new_tensor(std::initializer_list<TypeExpr*> list) {
    return new TypeExpr{te_Tensor, std::move(list)};
  }
  static bool remove_indirect(TypeExpr*& te, TypeExpr* forbidden = nullptr);
};

// extern int TypeExpr::holes;

/*
 * 
 *   ABSTRACT CODE
 * 
 */

using src::Lexem;
using src::SrcLocation;
using src::sym_idx_t;
using sym::SymDef;
using sym::var_idx_t;

struct TmpVar {
  TypeExpr* v_type;
  var_idx_t idx;
  enum { _In = 1, _Named = 2, _Tmp = 4, _UniqueName = 0x20 };
  int cls;
  sym_idx_t name;
  int coord;
  std::unique_ptr<SrcLocation> where;
  TmpVar(var_idx_t _idx, int _cls, TypeExpr* _type = 0, SymDef* sym = 0, const SrcLocation* loc = 0);
  void show(std::ostream& os, int omit_idx = 0) const;
  void dump(std::ostream& os) const;
  void set_location(const SrcLocation& loc);
};

struct VarDescr {
  var_idx_t idx;
  enum { _Last = 1, _Unused = 2 };
  int flags;
  enum {
    _Const = 16,
    _Int = 32,
    _Zero = 64,
    _NonZero = 128,
    _Pos = 256,
    _Neg = 512,
    _Bool = 1024,
    _Bit = 2048,
    _Finite = 4096,
    _Nan = 8192,
    _Even = 16384,
    _Odd = 32768
  };
  static constexpr int ConstZero = _Int | _Zero | _Pos | _Neg | _Bool | _Bit | _Finite | _Even;
  static constexpr int ConstOne = _Int | _NonZero | _Pos | _Bit | _Finite | _Odd;
  static constexpr int ConstTrue = _Int | _NonZero | _Neg | _Bool | _Finite | _Odd;
  int val;
  td::RefInt256 int_const;
  VarDescr(var_idx_t _idx = -1, int _flags = 0, int _val = 0) : idx(_idx), flags(_flags), val(_val) {
  }
  bool is_unused() const {
    return flags & _Unused;
  }
  bool is_last() const {
    return flags & _Last;
  }
  bool always_true() const {
    return val & _NonZero;
  }
  bool always_false() const {
    return val & _Zero;
  }
  bool always_nonzero() const {
    return val & _NonZero;
  }
  bool always_zero() const {
    return val & _Zero;
  }
  bool is_const() const {
    return val & _Const;
  }
  bool is_int_const() const {
    return (val & (_Int | _Const)) == (_Int | _Const);
  }
  bool always_nonpos() const {
    return val & _Neg;
  }
  bool always_nonneg() const {
    return val & _Pos;
  }
  bool always_pos() const {
    return (val & (_Pos | _NonZero)) == (_Pos | _NonZero);
  }
  bool always_neg() const {
    return (val & (_Neg | _NonZero)) == (_Neg | _NonZero);
  }
  bool always_finite() const {
    return val & _Finite;
  }
  void unused() {
    flags |= _Unused;
  }
  void clear_unused() {
    flags &= ~_Unused;
  }
  void set_const(td::RefInt256 value);
  void set_const_nan();
  void operator|=(const VarDescr& y);
  void operator&=(const VarDescr& y);
  void set_value(const VarDescr& y);
  void set_value(VarDescr&& y);
  void clear_value();
  void show_value(std::ostream& os) const;
};

struct VarDescrList {
  std::vector<VarDescr> list;
  VarDescrList() : list() {
  }
  VarDescrList(const std::vector<VarDescr>& _list) : list(_list) {
  }
  VarDescrList(std::vector<VarDescr>&& _list) : list(std::move(_list)) {
  }
  std::size_t size() const {
    return list.size();
  }
  VarDescr* operator[](var_idx_t idx);
  const VarDescr* operator[](var_idx_t idx) const;
  VarDescrList operator+(const VarDescrList& y) const;
  VarDescrList& operator+=(const VarDescrList& y);
  VarDescrList& clear_last();
  VarDescrList& operator+=(const std::vector<var_idx_t>& idx_list);
  VarDescrList& operator+=(var_idx_t idx);
  VarDescrList& operator-=(const std::vector<var_idx_t>& idx_list);
  VarDescrList& operator-=(var_idx_t idx);
  std::size_t count(const std::vector<var_idx_t> idx_list) const;
  VarDescr& add(var_idx_t idx);
  VarDescr& add_newval(var_idx_t idx);
  VarDescrList& operator&=(const VarDescrList& values);
  VarDescrList& import_values(const VarDescrList& values);
  VarDescrList operator|(const VarDescrList& y) const;
  VarDescrList& operator|=(const VarDescrList& values);
};

struct CodeBlob;

template <typename T>
class ListIterator {
  T* ptr;

 public:
  ListIterator() : ptr(nullptr) {
  }
  ListIterator(T* _ptr) : ptr(_ptr) {
  }
  ListIterator& operator++() {
    ptr = ptr->next.get();
    return *this;
  }
  ListIterator& operator++(int) {
    T* z = ptr;
    ptr = ptr->next.get();
    return ListIterator{z};
  }
  T& operator*() const {
    return *ptr;
  }
  T* operator->() const {
    return ptr;
  }
  bool operator==(const ListIterator& y) const {
    return ptr == y.ptr;
  }
  bool operator!=(const ListIterator& y) const {
    return ptr != y.ptr;
  }
};

struct Stack;

struct Op {
  enum {
    _Undef,
    _Nop,
    _Call,
    _CallInd,
    _Let,
    _IntConst,
    _GlobVar,
    _Import,
    _Return,
    _If,
    _While,
    _Until,
    _Repeat,
    _Again
  };
  int cl;
  enum { _Disabled = 1, _Reachable = 2, _NoReturn = 4 };
  int flags;
  std::unique_ptr<Op> next;
  SymDef* fun_ref;
  SrcLocation where;
  VarDescrList var_info;
  std::vector<VarDescr> args;
  std::vector<var_idx_t> left, right;
  std::unique_ptr<Op> block0, block1;
  td::RefInt256 int_const;
  Op(const SrcLocation& _where = {}, int _cl = _Undef) : cl(_cl), flags(0), fun_ref(nullptr), where(_where) {
  }
  Op(const SrcLocation& _where, int _cl, const std::vector<var_idx_t>& _left)
      : cl(_cl), flags(0), fun_ref(nullptr), where(_where), left(_left) {
  }
  Op(const SrcLocation& _where, int _cl, std::vector<var_idx_t>&& _left)
      : cl(_cl), flags(0), fun_ref(nullptr), where(_where), left(std::move(_left)) {
  }
  Op(const SrcLocation& _where, int _cl, const std::vector<var_idx_t>& _left, td::RefInt256 _const)
      : cl(_cl), flags(0), fun_ref(nullptr), where(_where), left(_left), int_const(_const) {
  }
  Op(const SrcLocation& _where, int _cl, const std::vector<var_idx_t>& _left, const std::vector<var_idx_t>& _right,
     SymDef* _fun = nullptr)
      : cl(_cl), flags(0), fun_ref(_fun), where(_where), left(_left), right(_right) {
  }
  Op(const SrcLocation& _where, int _cl, std::vector<var_idx_t>&& _left, std::vector<var_idx_t>&& _right,
     SymDef* _fun = nullptr)
      : cl(_cl), flags(0), fun_ref(_fun), where(_where), left(std::move(_left)), right(std::move(_right)) {
  }
  bool disabled() const {
    return flags & _Disabled;
  }
  bool enabled() const {
    return !disabled();
  }
  void disable() {
    flags |= _Disabled;
  }
  bool unreachable() {
    return !(flags & _Reachable);
  }
  void flags_set_clear(int set, int clear);
  void show(std::ostream& os, const std::vector<TmpVar>& vars, std::string pfx = "", int mode = 0) const;
  void show_var_list(std::ostream& os, const std::vector<var_idx_t>& idx_list, const std::vector<TmpVar>& vars) const;
  void show_var_list(std::ostream& os, const std::vector<VarDescr>& list, const std::vector<TmpVar>& vars) const;
  static void show_block(std::ostream& os, const Op* block, const std::vector<TmpVar>& vars, std::string pfx = "",
                         int mode = 0);
  void split_vars(const std::vector<TmpVar>& vars);
  static void split_var_list(std::vector<var_idx_t>& var_list, const std::vector<TmpVar>& vars);
  bool compute_used_vars(const CodeBlob& code, bool edit);
  bool std_compute_used_vars();
  bool set_var_info(const VarDescrList& new_var_info);
  bool set_var_info(VarDescrList&& new_var_info);
  void prepare_args(VarDescrList values);
  VarDescrList fwd_analyze(VarDescrList values);
  bool set_noreturn(bool nr);
  bool mark_noreturn();
  bool noreturn() const {
    return flags & _NoReturn;
  }
  bool is_empty() const {
    return cl == _Nop && !next;
  }
  bool generate_code_step(Stack& stack);
  bool generate_code_all(Stack& stack);
  Op& last() {
    return next ? next->last() : *this;
  }
  const Op& last() const {
    return next ? next->last() : *this;
  }
  ListIterator<Op> begin() {
    return ListIterator<Op>{this};
  }
  ListIterator<Op> end() const {
    return ListIterator<Op>{};
  }
  ListIterator<const Op> cbegin() {
    return ListIterator<const Op>{this};
  }
  ListIterator<const Op> cend() const {
    return ListIterator<const Op>{};
  }
};

typedef std::tuple<TypeExpr*, SymDef*, SrcLocation> FormalArg;
typedef std::vector<FormalArg> FormalArgList;

class AsmOpList;

struct CodeBlob {
  int var_cnt, in_var_cnt, op_cnt;
  TypeExpr* ret_type;
  std::string name;
  SrcLocation loc;
  std::vector<TmpVar> vars;
  std::unique_ptr<Op> ops;
  std::unique_ptr<Op>* cur_ops;
  std::stack<std::unique_ptr<Op>*> cur_ops_stack;
  CodeBlob(TypeExpr* ret = nullptr) : var_cnt(0), in_var_cnt(0), op_cnt(0), ret_type(ret), cur_ops(&ops) {
  }
  template <typename... Args>
  Op& emplace_back(const Args&... args) {
    Op& res = *(*cur_ops = std::make_unique<Op>(args...));
    cur_ops = &(res.next);
    return res;
  }
  bool import_params(FormalArgList arg_list);
  var_idx_t create_var(int cls, TypeExpr* var_type = 0, SymDef* sym = 0, const SrcLocation* loc = 0);
  int split_vars(bool strict = false);
  bool compute_used_code_vars();
  bool compute_used_code_vars(std::unique_ptr<Op>& ops, const VarDescrList& var_info, bool edit) const;
  void print(std::ostream& os, int flags = 0) const;
  void push_set_cur(std::unique_ptr<Op>& new_cur_ops) {
    cur_ops_stack.push(cur_ops);
    cur_ops = &new_cur_ops;
  }
  void close_blk(const SrcLocation& location) {
    *cur_ops = std::make_unique<Op>(location, Op::_Nop);
  }
  void pop_cur() {
    cur_ops = cur_ops_stack.top();
    cur_ops_stack.pop();
  }
  void close_pop_cur(const SrcLocation& location) {
    close_blk(location);
    pop_cur();
  }
  void simplify_var_types();
  void flags_set_clear(int set, int clear);
  void prune_unreachable_code();
  void fwd_analyze();
  void mark_noreturn();
  void generate_code(AsmOpList& out_list, int mode = 0);
  void generate_code(std::ostream& os, int mode = 0, int indent = 0);
};

/*
 *
 *   SYMBOL VALUES
 * 
 */

struct SymVal : sym::SymValBase {
  TypeExpr* sym_type;
  SymVal(int _type, int _idx, TypeExpr* _stype = nullptr) : sym::SymValBase(_type, _idx), sym_type(_stype) {
  }
  TypeExpr* get_type() const {
    return sym_type;
  }
};

struct SymValFunc : SymVal {
  CodeBlob* code;
  ~SymValFunc() override = default;
  SymValFunc(int val, TypeExpr* _ft) : SymVal(_Func, val, _ft), code(nullptr) {
  }
};

extern int glob_func_cnt, undef_func_cnt;
extern std::vector<SymDef*> glob_func;

/*
 * 
 *   EXPRESSIONS
 * 
 */

struct Expr {
  enum { _None, _Apply, _VarApply, _TypeApply, _Tuple, _Const, _Var, _Glob, _Letop, _Hole, _Type };
  int cls;
  int val;
  enum { _IsType = 1, _IsRvalue = 2, _IsLvalue = 4, _IsHole = 8, _IsNewVar = 16 };
  int flags;
  SrcLocation here;
  td::RefInt256 intval;
  SymDef* sym;
  TypeExpr* e_type;
  std::vector<Expr*> args;
  Expr(int c = _None) : cls(c), val(0), flags(0), here(), sym(nullptr), e_type(nullptr) {
  }
  Expr(int c, const SrcLocation& loc) : cls(c), val(0), flags(0), here(loc), sym(nullptr), e_type(nullptr) {
  }
  Expr(int c, std::vector<Expr*> _args)
      : cls(c), val(0), flags(0), here(), sym(nullptr), e_type(nullptr), args(std::move(_args)) {
  }
  Expr(int c, std::initializer_list<Expr*> _arglist)
      : cls(c), val(0), flags(0), here(), sym(nullptr), e_type(nullptr), args(std::move(_arglist)) {
  }
  Expr(int c, sym_idx_t name_idx, std::initializer_list<Expr*> _arglist);
  ~Expr() {
    for (auto& arg_ptr : args) {
      delete arg_ptr;
    }
  }
  Expr* copy() const;
  void pb_arg(Expr* expr) {
    args.push_back(expr);
  }
  void set_val(int _val) {
    val = _val;
  }
  bool is_rvalue() const {
    return flags & _IsRvalue;
  }
  bool is_lvalue() const {
    return flags & _IsLvalue;
  }
  bool is_type() const {
    return flags & _IsType;
  }
  void chk_rvalue(const Lexem& lem) const;
  void chk_lvalue(const Lexem& lem) const;
  void chk_type(const Lexem& lem) const;
  bool deduce_type(const Lexem& lem);
  void set_location(const SrcLocation& loc) {
    here = loc;
  }
  const SrcLocation& get_location() const {
    return here;
  }
  int define_new_vars(CodeBlob& code);
  int predefine_vars();
  std::vector<var_idx_t> pre_compile(CodeBlob& code) const;
};

/*
 * 
 *   GENERATE CODE
 * 
 */

typedef std::vector<var_idx_t> StackLayout;

struct AsmOp {
  enum Type { a_none, a_xchg, a_push, a_pop, a_const, a_custom, a_magic };
  int t{a_none};
  int indent{0};
  int a, b, c;
  std::string op;
  AsmOp() = default;
  AsmOp(int _t) : t(_t) {
  }
  AsmOp(int _t, std::string _op) : t(_t), op(std::move(_op)) {
  }
  AsmOp(int _t, int _a) : t(_t), a(_a) {
  }
  AsmOp(int _t, int _a, std::string _op) : t(_t), a(_a), op(std::move(_op)) {
  }
  AsmOp(int _t, int _a, int _b) : t(_t), a(_a), b(_b) {
  }
  AsmOp(int _t, int _a, int _b, std::string _op) : t(_t), a(_a), b(_b), op(std::move(_op)) {
  }
  AsmOp(int _t, int _a, int _b, int _c) : t(_t), a(_a), b(_b), c(_c) {
  }
  AsmOp(int _t, int _a, int _b, int _c, std::string _op) : t(_t), a(_a), b(_b), c(_c), op(std::move(_op)) {
  }
  void out(std::ostream& os) const;
  void out_indent_nl(std::ostream& os, bool no_nl = false) const;
  std::string to_string() const;
  bool is_nop() const {
    return t == a_none && op.empty();
  }
  bool is_comment() const {
    return t == a_none && !op.empty();
  }
  static AsmOp Nop() {
    return AsmOp(a_none);
  }
  static AsmOp Xchg(int a, int b) {
    return a == b ? AsmOp(a_none) : (a < b ? AsmOp(a_xchg, a, b) : AsmOp(a_xchg, b, a));
  }
  static AsmOp Push(int a) {
    return AsmOp(a_push, a);
  }
  static AsmOp Pop(int a) {
    return AsmOp(a_pop, a);
  }
  static AsmOp IntConst(td::RefInt256 value);
  static AsmOp Const(std::string push_op) {
    return AsmOp(a_const, 0, 1, std::move(push_op));
  }
  static AsmOp Const(int arg, std::string push_op);
  static AsmOp Comment(std::string comment) {
    return AsmOp(a_none, std::string{"// "} + comment);
  }
  static AsmOp Custom(std::string custom_op) {
    return AsmOp(a_custom, 255, 255, custom_op);
  }
  static AsmOp Custom(std::string custom_op, int args, int retv = 1) {
    return AsmOp(a_custom, args, retv, custom_op);
  }
};

inline std::ostream& operator<<(std::ostream& os, const AsmOp& op) {
  op.out_indent_nl(os);
  return os;
}

struct AsmOpList {
  std::vector<AsmOp> list_;
  int indent_{0};
  const std::vector<TmpVar>* var_names_{nullptr};
  void out(std::ostream& os, int mode = 0) const;
  AsmOpList(int indent = 0, const std::vector<TmpVar>* var_names = nullptr) : indent_(indent), var_names_(var_names) {
  }
  template <typename... Args>
  AsmOpList& add(Args&&... args) {
    list_.emplace_back(std::forward<Args>(args)...);
    adjust_last();
    return *this;
  }
  AsmOpList& operator<<(const AsmOp& op) {
    return add(op);
  }
  AsmOpList& operator<<(AsmOp&& op) {
    return add(std::move(op));
  }
  AsmOpList& operator<<(std::string str) {
    return add(AsmOp::Type::a_custom, 255, 255, str);
  }
  void show_var(std::ostream& os, var_idx_t idx) const;
  void adjust_last() {
    if (list_.back().is_nop()) {
      list_.pop_back();
    } else {
      list_.back().indent = indent_;
    }
  }
  void indent() {
    ++indent_;
  }
  void undent() {
    --indent_;
  }
  void set_indent(int new_indent) {
    indent_ = new_indent;
  }
};

inline std::ostream& operator<<(std::ostream& os, const AsmOpList& op_list) {
  op_list.out(os);
  return os;
}

class IndentGuard {
  AsmOpList& aol_;

 public:
  IndentGuard(AsmOpList& aol) : aol_(aol) {
    aol.indent();
  }
  ~IndentGuard() {
    aol_.undent();
  }
};

struct Stack {
  StackLayout s;
  AsmOpList& o;
  enum { _StkCmt = 1, _CptStkCmt = 2, _Shown = 256, _Garbage = -0x10000 };
  int mode;
  Stack(AsmOpList& _o, int _mode = 0) : o(_o), mode(_mode) {
  }
  Stack(AsmOpList& _o, const StackLayout& _s, int _mode = 0) : s(_s), o(_o), mode(_mode) {
  }
  Stack(AsmOpList& _o, StackLayout&& _s, int _mode = 0) : s(std::move(_s)), o(_o), mode(_mode) {
  }
  int depth() const {
    return (int)s.size();
  }
  var_idx_t& operator[](int i) {
    return s[depth() - i - 1];
  }
  var_idx_t operator[](int i) const {
    return s[depth() - i - 1];
  }
  var_idx_t& at(int i) {
    validate(i);
    return operator[](i);
  }
  var_idx_t at(int i) const {
    validate(i);
    return operator[](i);
  }
  var_idx_t get(int i) const {
    validate(i);
    return operator[](i);
  }
  int find(var_idx_t var, int from = 0) const;
  int find(var_idx_t var, int from, int to) const;
  void validate(int i) const {
    assert(i >= 0 && i < depth());
  }
  void modified() {
    mode &= ~_Shown;
  }
  void issue_pop(int i);
  void issue_push(int i);
  void issue_xchg(int i, int j);
  int drop_vars_except(const VarDescrList& var_info, int excl_var = 0x80000000);
  void forget_var(var_idx_t idx);
  void push_new_var(var_idx_t idx);
  void assign_var(var_idx_t new_idx, var_idx_t old_idx);
  void do_copy_var(var_idx_t new_idx, var_idx_t old_idx);
  void enforce_state(const StackLayout& req_stack);
  void rearrange_top(const StackLayout& top, std::vector<bool> last);
  void rearrange_top(var_idx_t top, bool last);
  void show(int _mode);
  void show() {
    show(mode);
  }
  void opt_show() {
    if ((mode & (_StkCmt | _Shown)) == _StkCmt) {
      show(mode);
    }
  }
  bool operator==(const Stack& y) const & {
    return s == y.s;
  }
};

/*
 *
 *   SPECIFIC SYMBOL VALUES
 * 
 */

typedef std::function<AsmOp(std::vector<VarDescr>&, std::vector<VarDescr>&)> simple_compile_func_t;
typedef std::function<bool(AsmOpList&, std::vector<VarDescr>&, std::vector<VarDescr>&)> compile_func_t;

inline simple_compile_func_t simple_compile(AsmOp op) {
  return [op](std::vector<VarDescr>& out, std::vector<VarDescr>& in) -> AsmOp { return op; };
}

struct SymValBuiltinFunc : SymVal {
  simple_compile_func_t compile;
  ~SymValBuiltinFunc() override = default;
  SymValBuiltinFunc(TypeExpr* _ft, const AsmOp& _macro) : SymVal(_Func, -1, _ft), compile(simple_compile(_macro)) {
  }
  SymValBuiltinFunc(TypeExpr* _ft, const simple_compile_func_t& _compile) : SymVal(_Func, -1, _ft), compile(_compile) {
  }
};

}  // namespace funC
