#pragma once
#include <tl/tlblib.hpp>
/*
 *
 *  AUTO-GENERATED FROM `block.tlb`
 *
 */
// uses built-in type `#`
// uses built-in type `##`
// uses built-in type `#<`
// uses built-in type `#<=`
// uses built-in type `Any`
// uses built-in type `Cell`
// uses built-in type `int`
// uses built-in type `uint`
// uses built-in type `bits`
// uses built-in type `int8`
// uses built-in type `uint15`
// uses built-in type `uint16`
// uses built-in type `int32`
// uses built-in type `uint32`
// uses built-in type `uint64`
// uses built-in type `bits256`

namespace block {

namespace gen {
using namespace tlb;
using td::Ref;
using vm::CellSlice;
using vm::Cell;
using td::RefInt256;

//
// headers for type `Unit`
//

struct Unit final : TLB_Complex {
  enum { unit };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef Unit type_class;
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 0;
  }
  bool skip(vm::CellSlice& cs) const override {
    return true;
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return true;
  }
  bool fetch_enum_to(vm::CellSlice& cs, char& value) const;
  bool store_enum_from(vm::CellBuilder& cb, int value) const;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_unit(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_unit(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_unit(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_unit(Ref<vm::Cell>& cell_ref) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "Unit";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const Unit t_Unit;

//
// headers for type `True`
//

struct True final : TLB_Complex {
  enum { true1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef True type_class;
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 0;
  }
  bool skip(vm::CellSlice& cs) const override {
    return true;
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return true;
  }
  bool fetch_enum_to(vm::CellSlice& cs, char& value) const;
  bool store_enum_from(vm::CellBuilder& cb, int value) const;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_true1(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_true1(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_true1(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_true1(Ref<vm::Cell>& cell_ref) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "True";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const True t_True;

//
// headers for type `Bool`
//

struct Bool final : TLB_Complex {
  enum { bool_false, bool_true };
  static constexpr int cons_len_exact = 1;
  struct Record_bool_false {
    typedef Bool type_class;
  };
  struct Record_bool_true {
    typedef Bool type_class;
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 1;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(1);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(1);
  }
  bool fetch_enum_to(vm::CellSlice& cs, char& value) const;
  bool store_enum_from(vm::CellBuilder& cb, int value) const;
  bool unpack(vm::CellSlice& cs, Record_bool_false& data) const;
  bool unpack_bool_false(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_bool_false& data) const;
  bool cell_unpack_bool_false(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_bool_false& data) const;
  bool pack_bool_false(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_bool_false& data) const;
  bool cell_pack_bool_false(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_bool_true& data) const;
  bool unpack_bool_true(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_bool_true& data) const;
  bool cell_unpack_bool_true(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_bool_true& data) const;
  bool pack_bool_true(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_bool_true& data) const;
  bool cell_pack_bool_true(Ref<vm::Cell>& cell_ref) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "Bool";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

extern const Bool t_Bool;

//
// headers for type `Maybe`
//

struct Maybe final : TLB_Complex {
  enum { nothing, just };
  static constexpr int cons_len_exact = 1;
  const TLB &X;
  Maybe(const TLB& _X) : X(_X) {}
  struct Record_nothing {
    typedef Maybe type_class;
  };
  struct Record_just {
    typedef Maybe type_class;
    Ref<CellSlice> value;  	// value : X
    Record_just() = default;
    Record_just(Ref<CellSlice> _value) : value(std::move(_value)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_nothing& data) const;
  bool unpack_nothing(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_nothing& data) const;
  bool cell_unpack_nothing(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_nothing& data) const;
  bool pack_nothing(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_nothing& data) const;
  bool cell_pack_nothing(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_just& data) const;
  bool unpack_just(vm::CellSlice& cs, Ref<CellSlice>& value) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_just& data) const;
  bool cell_unpack_just(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const;
  bool pack(vm::CellBuilder& cb, const Record_just& data) const;
  bool pack_just(vm::CellBuilder& cb, Ref<CellSlice> value) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_just& data) const;
  bool cell_pack_just(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(Maybe " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

//
// headers for type `Either`
//

struct Either final : TLB_Complex {
  enum { left, right };
  static constexpr int cons_len_exact = 1;
  const TLB &X, &Y;
  Either(const TLB& _X, const TLB& _Y) : X(_X), Y(_Y) {}
  struct Record_left {
    typedef Either type_class;
    Ref<CellSlice> value;  	// value : X
    Record_left() = default;
    Record_left(Ref<CellSlice> _value) : value(std::move(_value)) {}
  };
  struct Record_right {
    typedef Either type_class;
    Ref<CellSlice> value;  	// value : Y
    Record_right() = default;
    Record_right(Ref<CellSlice> _value) : value(std::move(_value)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_left& data) const;
  bool unpack_left(vm::CellSlice& cs, Ref<CellSlice>& value) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_left& data) const;
  bool cell_unpack_left(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const;
  bool pack(vm::CellBuilder& cb, const Record_left& data) const;
  bool pack_left(vm::CellBuilder& cb, Ref<CellSlice> value) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_left& data) const;
  bool cell_pack_left(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const;
  bool unpack(vm::CellSlice& cs, Record_right& data) const;
  bool unpack_right(vm::CellSlice& cs, Ref<CellSlice>& value) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_right& data) const;
  bool cell_unpack_right(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const;
  bool pack(vm::CellBuilder& cb, const Record_right& data) const;
  bool pack_right(vm::CellBuilder& cb, Ref<CellSlice> value) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_right& data) const;
  bool cell_pack_right(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(Either " << X << " " << Y << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

//
// headers for type `Both`
//

struct Both final : TLB_Complex {
  enum { pair };
  static constexpr int cons_len_exact = 0;
  const TLB &X, &Y;
  Both(const TLB& _X, const TLB& _Y) : X(_X), Y(_Y) {}
  struct Record {
    typedef Both type_class;
    Ref<CellSlice> first;  	// first : X
    Ref<CellSlice> second;  	// second : Y
    Record() = default;
    Record(Ref<CellSlice> _first, Ref<CellSlice> _second) : first(std::move(_first)), second(std::move(_second)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(Both " << X << " " << Y << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

//
// headers for type `Bit`
//

struct Bit final : TLB_Complex {
  enum { bit };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef Bit type_class;
    bool x;  	// ## 1
    Record() = default;
    Record(bool _x) : x(_x) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 1;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(1);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(1);
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_bit(vm::CellSlice& cs, bool& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_bit(Ref<vm::Cell> cell_ref, bool& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_bit(vm::CellBuilder& cb, bool x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_bit(Ref<vm::Cell>& cell_ref, bool x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "Bit";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const Bit t_Bit;

//
// headers for type `Hashmap`
//

struct Hashmap final : TLB_Complex {
  enum { hm_edge };
  static constexpr int cons_len_exact = 0;
  int m;
  const TLB &X;
  Hashmap(int _m, const TLB& _X) : m(_m), X(_X) {}
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(Hashmap " << m << " " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct Hashmap::Record {
  typedef Hashmap type_class;
  int n;  	// n : #
  int l;  	// l : #
  int m;  	// m : #
  Ref<CellSlice> label;  	// label : HmLabel ~l n
  Ref<CellSlice> node;  	// node : HashmapNode m X
  Record() = default;
  Record(Ref<CellSlice> _label, Ref<CellSlice> _node) : n(-1), l(-1), m(-1), label(std::move(_label)), node(std::move(_node)) {}
};

//
// headers for type `HashmapNode`
//

struct HashmapNode final : TLB_Complex {
  enum { hmn_leaf, hmn_fork };
  static constexpr int cons_len_exact = 0;
  int m;
  const TLB &X;
  HashmapNode(int _m, const TLB& _X) : m(_m), X(_X) {}
  struct Record_hmn_leaf {
    typedef HashmapNode type_class;
    Ref<CellSlice> value;  	// value : X
    Record_hmn_leaf() = default;
    Record_hmn_leaf(Ref<CellSlice> _value) : value(std::move(_value)) {}
  };
  struct Record_hmn_fork;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_hmn_leaf& data) const;
  bool unpack_hmn_leaf(vm::CellSlice& cs, Ref<CellSlice>& value) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_hmn_leaf& data) const;
  bool cell_unpack_hmn_leaf(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const;
  bool pack(vm::CellBuilder& cb, const Record_hmn_leaf& data) const;
  bool pack_hmn_leaf(vm::CellBuilder& cb, Ref<CellSlice> value) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_hmn_leaf& data) const;
  bool cell_pack_hmn_leaf(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const;
  bool unpack(vm::CellSlice& cs, Record_hmn_fork& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_hmn_fork& data) const;
  bool pack(vm::CellBuilder& cb, const Record_hmn_fork& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_hmn_fork& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(HashmapNode " << m << " " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override;
};

struct HashmapNode::Record_hmn_fork {
  typedef HashmapNode type_class;
  int n;  	// n : #
  Ref<Cell> left;  	// left : ^(Hashmap n X)
  Ref<Cell> right;  	// right : ^(Hashmap n X)
  Record_hmn_fork() = default;
  Record_hmn_fork(Ref<Cell> _left, Ref<Cell> _right) : n(-1), left(std::move(_left)), right(std::move(_right)) {}
};

//
// headers for type `HmLabel`
//

struct HmLabel final : TLB_Complex {
  enum { hml_short, hml_long, hml_same };
  static constexpr char cons_len[3] = { 1, 2, 2 };
  static constexpr unsigned char cons_tag[3] = { 0, 2, 3 };
  int n;
  HmLabel(int _n) : n(_n) {}
  struct Record_hml_short;
  struct Record_hml_long;
  struct Record_hml_same;
  bool skip(vm::CellSlice& cs) const override;
  bool skip(vm::CellSlice& cs, int& m) const;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs, int& m) const;
  bool fetch_to(vm::CellSlice& cs, Ref<vm::CellSlice>& res, int& m) const;
  bool unpack(vm::CellSlice& cs, Record_hml_short& data, int& m) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_hml_short& data, int& m) const;
  bool pack(vm::CellBuilder& cb, const Record_hml_short& data, int& m) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_hml_short& data, int& m) const;
  bool unpack(vm::CellSlice& cs, Record_hml_long& data, int& m) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_hml_long& data, int& m) const;
  bool pack(vm::CellBuilder& cb, const Record_hml_long& data, int& m) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_hml_long& data, int& m) const;
  bool unpack(vm::CellSlice& cs, Record_hml_same& data, int& m) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_hml_same& data, int& m) const;
  bool pack(vm::CellBuilder& cb, const Record_hml_same& data, int& m) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_hml_same& data, int& m) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs, int& m) const;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(HmLabel ~m " << n << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(2, 13);
  }
};

struct HmLabel::Record_hml_short {
  typedef HmLabel type_class;
  int m;  	// m : #
  int n;  	// n : #
  Ref<CellSlice> len;  	// len : Unary ~n
  Ref<td::BitString> s;  	// s : n * Bit
  Record_hml_short() = default;
  Record_hml_short(Ref<CellSlice> _len, Ref<td::BitString> _s) : m(-1), n(-1), len(std::move(_len)), s(std::move(_s)) {}
};

struct HmLabel::Record_hml_long {
  typedef HmLabel type_class;
  int m;  	// m : #
  int n;  	// n : #<= m
  Ref<td::BitString> s;  	// s : n * Bit
  Record_hml_long() = default;
  Record_hml_long(int _n, Ref<td::BitString> _s) : m(-1), n(_n), s(std::move(_s)) {}
};

struct HmLabel::Record_hml_same {
  typedef HmLabel type_class;
  int m;  	// m : #
  bool v;  	// v : Bit
  int n;  	// n : #<= m
  Record_hml_same() = default;
  Record_hml_same(bool _v, int _n) : m(-1), v(_v), n(_n) {}
};

//
// headers for type `Unary`
//

struct Unary final : TLB_Complex {
  enum { unary_zero, unary_succ };
  static constexpr int cons_len_exact = 1;
  struct Record_unary_zero {
    typedef Unary type_class;
  };
  struct Record_unary_succ {
    typedef Unary type_class;
    int n;  	// n : #
    Ref<CellSlice> x;  	// x : Unary ~n
    Record_unary_succ() = default;
    Record_unary_succ(Ref<CellSlice> _x) : n(-1), x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool skip(vm::CellSlice& cs, int& m) const;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs, int& m) const;
  bool fetch_to(vm::CellSlice& cs, Ref<vm::CellSlice>& res, int& m) const;
  bool unpack(vm::CellSlice& cs, Record_unary_zero& data, int& m) const;
  bool unpack_unary_zero(vm::CellSlice& cs, int& m) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_unary_zero& data, int& m) const;
  bool cell_unpack_unary_zero(Ref<vm::Cell> cell_ref, int& m) const;
  bool pack(vm::CellBuilder& cb, const Record_unary_zero& data, int& m) const;
  bool pack_unary_zero(vm::CellBuilder& cb, int& m) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_unary_zero& data, int& m) const;
  bool cell_pack_unary_zero(Ref<vm::Cell>& cell_ref, int& m) const;
  bool unpack(vm::CellSlice& cs, Record_unary_succ& data, int& m) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_unary_succ& data, int& m) const;
  bool pack(vm::CellBuilder& cb, const Record_unary_succ& data, int& m) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_unary_succ& data, int& m) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs, int& m) const;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(Unary ~m)";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

extern const Unary t_Unary;

//
// headers for type `HashmapE`
//

struct HashmapE final : TLB_Complex {
  enum { hme_empty, hme_root };
  static constexpr int cons_len_exact = 1;
  int m;
  const TLB &X;
  HashmapE(int _m, const TLB& _X) : m(_m), X(_X) {}
  struct Record_hme_empty {
    typedef HashmapE type_class;
  };
  struct Record_hme_root {
    typedef HashmapE type_class;
    int n;  	// n : #
    Ref<Cell> root;  	// root : ^(Hashmap n X)
    Record_hme_root() = default;
    Record_hme_root(Ref<Cell> _root) : n(-1), root(std::move(_root)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_hme_empty& data) const;
  bool unpack_hme_empty(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_hme_empty& data) const;
  bool cell_unpack_hme_empty(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_hme_empty& data) const;
  bool pack_hme_empty(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_hme_empty& data) const;
  bool cell_pack_hme_empty(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_hme_root& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_hme_root& data) const;
  bool pack(vm::CellBuilder& cb, const Record_hme_root& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_hme_root& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(HashmapE " << m << " " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

//
// headers for type `BitstringSet`
//

struct BitstringSet final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  int m;
  BitstringSet(int _m) : m(_m) {}
  struct Record {
    typedef BitstringSet type_class;
    int n;  	// n : #
    Ref<CellSlice> x;  	// Hashmap n True
    Record() = default;
    Record(Ref<CellSlice> _x) : n(-1), x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(BitstringSet " << m << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

//
// headers for type `VarHashmap`
//

struct VarHashmap final : TLB_Complex {
  enum { vhm_edge };
  static constexpr int cons_len_exact = 0;
  int m;
  const TLB &X;
  VarHashmap(int _m, const TLB& _X) : m(_m), X(_X) {}
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(VarHashmap " << m << " " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct VarHashmap::Record {
  typedef VarHashmap type_class;
  int n;  	// n : #
  int l;  	// l : #
  int m;  	// m : #
  Ref<CellSlice> label;  	// label : HmLabel ~l n
  Ref<CellSlice> node;  	// node : VarHashmapNode m X
  Record() = default;
  Record(Ref<CellSlice> _label, Ref<CellSlice> _node) : n(-1), l(-1), m(-1), label(std::move(_label)), node(std::move(_node)) {}
};

//
// headers for type `VarHashmapNode`
//

struct VarHashmapNode final : TLB_Complex {
  enum { vhmn_leaf, vhmn_fork, vhmn_cont };
  static constexpr char cons_len[3] = { 2, 2, 1 };
  static constexpr unsigned char cons_tag[3] = { 0, 1, 1 };
  int m;
  const TLB &X;
  VarHashmapNode(int _m, const TLB& _X) : m(_m), X(_X) {}
  struct Record_vhmn_leaf {
    typedef VarHashmapNode type_class;
    Ref<CellSlice> value;  	// value : X
    Record_vhmn_leaf() = default;
    Record_vhmn_leaf(Ref<CellSlice> _value) : value(std::move(_value)) {}
  };
  struct Record_vhmn_fork;
  struct Record_vhmn_cont;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_vhmn_leaf& data) const;
  bool unpack_vhmn_leaf(vm::CellSlice& cs, Ref<CellSlice>& value) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_vhmn_leaf& data) const;
  bool cell_unpack_vhmn_leaf(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const;
  bool pack(vm::CellBuilder& cb, const Record_vhmn_leaf& data) const;
  bool pack_vhmn_leaf(vm::CellBuilder& cb, Ref<CellSlice> value) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_vhmn_leaf& data) const;
  bool cell_pack_vhmn_leaf(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const;
  bool unpack(vm::CellSlice& cs, Record_vhmn_fork& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_vhmn_fork& data) const;
  bool pack(vm::CellBuilder& cb, const Record_vhmn_fork& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_vhmn_fork& data) const;
  bool unpack(vm::CellSlice& cs, Record_vhmn_cont& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_vhmn_cont& data) const;
  bool pack(vm::CellBuilder& cb, const Record_vhmn_cont& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_vhmn_cont& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(VarHashmapNode " << m << " " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(2, 7);
  }
};

struct VarHashmapNode::Record_vhmn_fork {
  typedef VarHashmapNode type_class;
  int n;  	// n : #
  Ref<Cell> left;  	// left : ^(VarHashmap n X)
  Ref<Cell> right;  	// right : ^(VarHashmap n X)
  Ref<CellSlice> value;  	// value : Maybe X
  Record_vhmn_fork() = default;
  Record_vhmn_fork(Ref<Cell> _left, Ref<Cell> _right, Ref<CellSlice> _value) : n(-1), left(std::move(_left)), right(std::move(_right)), value(std::move(_value)) {}
};

struct VarHashmapNode::Record_vhmn_cont {
  typedef VarHashmapNode type_class;
  int n;  	// n : #
  bool branch;  	// branch : Bit
  Ref<Cell> child;  	// child : ^(VarHashmap n X)
  Ref<CellSlice> value;  	// value : X
  Record_vhmn_cont() = default;
  Record_vhmn_cont(bool _branch, Ref<Cell> _child, Ref<CellSlice> _value) : n(-1), branch(_branch), child(std::move(_child)), value(std::move(_value)) {}
};

//
// headers for type `VarHashmapE`
//

struct VarHashmapE final : TLB_Complex {
  enum { vhme_empty, vhme_root };
  static constexpr int cons_len_exact = 1;
  int m;
  const TLB &X;
  VarHashmapE(int _m, const TLB& _X) : m(_m), X(_X) {}
  struct Record_vhme_empty {
    typedef VarHashmapE type_class;
  };
  struct Record_vhme_root {
    typedef VarHashmapE type_class;
    int n;  	// n : #
    Ref<Cell> root;  	// root : ^(VarHashmap n X)
    Record_vhme_root() = default;
    Record_vhme_root(Ref<Cell> _root) : n(-1), root(std::move(_root)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_vhme_empty& data) const;
  bool unpack_vhme_empty(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_vhme_empty& data) const;
  bool cell_unpack_vhme_empty(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_vhme_empty& data) const;
  bool pack_vhme_empty(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_vhme_empty& data) const;
  bool cell_pack_vhme_empty(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_vhme_root& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_vhme_root& data) const;
  bool pack(vm::CellBuilder& cb, const Record_vhme_root& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_vhme_root& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(VarHashmapE " << m << " " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

//
// headers for type `PfxHashmap`
//

struct PfxHashmap final : TLB_Complex {
  enum { phm_edge };
  static constexpr int cons_len_exact = 0;
  int m;
  const TLB &X;
  PfxHashmap(int _m, const TLB& _X) : m(_m), X(_X) {}
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(PfxHashmap " << m << " " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct PfxHashmap::Record {
  typedef PfxHashmap type_class;
  int n;  	// n : #
  int l;  	// l : #
  int m;  	// m : #
  Ref<CellSlice> label;  	// label : HmLabel ~l n
  Ref<CellSlice> node;  	// node : PfxHashmapNode m X
  Record() = default;
  Record(Ref<CellSlice> _label, Ref<CellSlice> _node) : n(-1), l(-1), m(-1), label(std::move(_label)), node(std::move(_node)) {}
};

//
// headers for type `PfxHashmapNode`
//

struct PfxHashmapNode final : TLB_Complex {
  enum { phmn_leaf, phmn_fork };
  static constexpr int cons_len_exact = 1;
  int m;
  const TLB &X;
  PfxHashmapNode(int _m, const TLB& _X) : m(_m), X(_X) {}
  struct Record_phmn_leaf {
    typedef PfxHashmapNode type_class;
    Ref<CellSlice> value;  	// value : X
    Record_phmn_leaf() = default;
    Record_phmn_leaf(Ref<CellSlice> _value) : value(std::move(_value)) {}
  };
  struct Record_phmn_fork;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_phmn_leaf& data) const;
  bool unpack_phmn_leaf(vm::CellSlice& cs, Ref<CellSlice>& value) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_phmn_leaf& data) const;
  bool cell_unpack_phmn_leaf(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const;
  bool pack(vm::CellBuilder& cb, const Record_phmn_leaf& data) const;
  bool pack_phmn_leaf(vm::CellBuilder& cb, Ref<CellSlice> value) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_phmn_leaf& data) const;
  bool cell_pack_phmn_leaf(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const;
  bool unpack(vm::CellSlice& cs, Record_phmn_fork& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_phmn_fork& data) const;
  bool pack(vm::CellBuilder& cb, const Record_phmn_fork& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_phmn_fork& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(PfxHashmapNode " << m << " " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

struct PfxHashmapNode::Record_phmn_fork {
  typedef PfxHashmapNode type_class;
  int n;  	// n : #
  Ref<Cell> left;  	// left : ^(PfxHashmap n X)
  Ref<Cell> right;  	// right : ^(PfxHashmap n X)
  Record_phmn_fork() = default;
  Record_phmn_fork(Ref<Cell> _left, Ref<Cell> _right) : n(-1), left(std::move(_left)), right(std::move(_right)) {}
};

//
// headers for type `PfxHashmapE`
//

struct PfxHashmapE final : TLB_Complex {
  enum { phme_empty, phme_root };
  static constexpr int cons_len_exact = 1;
  int m;
  const TLB &X;
  PfxHashmapE(int _m, const TLB& _X) : m(_m), X(_X) {}
  struct Record_phme_empty {
    typedef PfxHashmapE type_class;
  };
  struct Record_phme_root {
    typedef PfxHashmapE type_class;
    int n;  	// n : #
    Ref<Cell> root;  	// root : ^(PfxHashmap n X)
    Record_phme_root() = default;
    Record_phme_root(Ref<Cell> _root) : n(-1), root(std::move(_root)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_phme_empty& data) const;
  bool unpack_phme_empty(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_phme_empty& data) const;
  bool cell_unpack_phme_empty(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_phme_empty& data) const;
  bool pack_phme_empty(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_phme_empty& data) const;
  bool cell_pack_phme_empty(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_phme_root& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_phme_root& data) const;
  bool pack(vm::CellBuilder& cb, const Record_phme_root& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_phme_root& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(PfxHashmapE " << m << " " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

//
// headers for type `MsgAddressExt`
//

struct MsgAddressExt final : TLB_Complex {
  enum { addr_none, addr_extern };
  static constexpr int cons_len_exact = 2;
  struct Record_addr_none {
    typedef MsgAddressExt type_class;
  };
  struct Record_addr_extern {
    typedef MsgAddressExt type_class;
    int len;  	// len : ## 8
    Ref<td::BitString> external_address;  	// external_address : bits len
    Record_addr_extern() = default;
    Record_addr_extern(int _len, Ref<td::BitString> _external_address) : len(_len), external_address(std::move(_external_address)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_addr_none& data) const;
  bool unpack_addr_none(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_addr_none& data) const;
  bool cell_unpack_addr_none(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_addr_none& data) const;
  bool pack_addr_none(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_addr_none& data) const;
  bool cell_pack_addr_none(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_addr_extern& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_addr_extern& data) const;
  bool pack(vm::CellBuilder& cb, const Record_addr_extern& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_addr_extern& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "MsgAddressExt";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(2, 3);
  }
};

extern const MsgAddressExt t_MsgAddressExt;

//
// headers for type `Anycast`
//

struct Anycast final : TLB_Complex {
  enum { anycast_info };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef Anycast type_class;
    int depth;  	// depth : #<= 30
    Ref<td::BitString> rewrite_pfx;  	// rewrite_pfx : bits depth
    Record() = default;
    Record(int _depth, Ref<td::BitString> _rewrite_pfx) : depth(_depth), rewrite_pfx(std::move(_rewrite_pfx)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "Anycast";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const Anycast t_Anycast;

//
// headers for type `MsgAddressInt`
//

struct MsgAddressInt final : TLB_Complex {
  enum { addr_std, addr_var };
  static constexpr int cons_len_exact = 2;
  static constexpr unsigned char cons_tag[2] = { 2, 3 };
  struct Record_addr_std;
  struct Record_addr_var;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_addr_std& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_addr_std& data) const;
  bool pack(vm::CellBuilder& cb, const Record_addr_std& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_addr_std& data) const;
  bool unpack(vm::CellSlice& cs, Record_addr_var& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_addr_var& data) const;
  bool pack(vm::CellBuilder& cb, const Record_addr_var& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_addr_var& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "MsgAddressInt";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(2, 12);
  }
};

struct MsgAddressInt::Record_addr_std {
  typedef MsgAddressInt type_class;
  Ref<CellSlice> anycast;  	// anycast : Maybe Anycast
  int workchain_id;  	// workchain_id : int8
  td::BitArray<256> address;  	// address : bits256
  Record_addr_std() = default;
  Record_addr_std(Ref<CellSlice> _anycast, int _workchain_id, const td::BitArray<256>& _address) : anycast(std::move(_anycast)), workchain_id(_workchain_id), address(_address) {}
};

struct MsgAddressInt::Record_addr_var {
  typedef MsgAddressInt type_class;
  Ref<CellSlice> anycast;  	// anycast : Maybe Anycast
  int addr_len;  	// addr_len : ## 9
  int workchain_id;  	// workchain_id : int32
  Ref<td::BitString> address;  	// address : bits addr_len
  Record_addr_var() = default;
  Record_addr_var(Ref<CellSlice> _anycast, int _addr_len, int _workchain_id, Ref<td::BitString> _address) : anycast(std::move(_anycast)), addr_len(_addr_len), workchain_id(_workchain_id), address(std::move(_address)) {}
};

extern const MsgAddressInt t_MsgAddressInt;

//
// headers for type `MsgAddress`
//

struct MsgAddress final : TLB_Complex {
  enum { cons2, cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record_cons1 {
    typedef MsgAddress type_class;
    Ref<CellSlice> x;  	// MsgAddressInt
    Record_cons1() = default;
    Record_cons1(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  struct Record_cons2 {
    typedef MsgAddress type_class;
    Ref<CellSlice> x;  	// MsgAddressExt
    Record_cons2() = default;
    Record_cons2(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_cons1& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons1& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_cons1& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons1& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool unpack(vm::CellSlice& cs, Record_cons2& data) const;
  bool unpack_cons2(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons2& data) const;
  bool cell_unpack_cons2(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_cons2& data) const;
  bool pack_cons2(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons2& data) const;
  bool cell_pack_cons2(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "MsgAddress";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

extern const MsgAddress t_MsgAddress;

//
// headers for type `VarUInteger`
//

struct VarUInteger final : TLB_Complex {
  enum { var_uint };
  static constexpr int cons_len_exact = 0;
  int m;
  VarUInteger(int _m) : m(_m) {}
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(VarUInteger " << m << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct VarUInteger::Record {
  typedef VarUInteger type_class;
  int n;  	// n : #
  int len;  	// len : #< n
  RefInt256 value;  	// value : uint (8 * len)
  Record() = default;
  Record(int _len, RefInt256 _value) : n(-1), len(_len), value(std::move(_value)) {}
};

//
// headers for type `VarInteger`
//

struct VarInteger final : TLB_Complex {
  enum { var_int };
  static constexpr int cons_len_exact = 0;
  int m;
  VarInteger(int _m) : m(_m) {}
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(VarInteger " << m << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct VarInteger::Record {
  typedef VarInteger type_class;
  int n;  	// n : #
  int len;  	// len : #< n
  RefInt256 value;  	// value : int (8 * len)
  Record() = default;
  Record(int _len, RefInt256 _value) : n(-1), len(_len), value(std::move(_value)) {}
};

//
// headers for type `Grams`
//

struct Grams final : TLB_Complex {
  enum { nanograms };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef Grams type_class;
    Ref<CellSlice> amount;  	// amount : VarUInteger 16
    Record() = default;
    Record(Ref<CellSlice> _amount) : amount(std::move(_amount)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_nanograms(vm::CellSlice& cs, Ref<CellSlice>& amount) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_nanograms(Ref<vm::Cell> cell_ref, Ref<CellSlice>& amount) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_nanograms(vm::CellBuilder& cb, Ref<CellSlice> amount) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_nanograms(Ref<vm::Cell>& cell_ref, Ref<CellSlice> amount) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "Grams";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const Grams t_Grams;

//
// headers for type `ExtraCurrencyCollection`
//

struct ExtraCurrencyCollection final : TLB_Complex {
  enum { extra_currencies };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ExtraCurrencyCollection type_class;
    Ref<CellSlice> dict;  	// dict : HashmapE 32 (VarUInteger 32)
    Record() = default;
    Record(Ref<CellSlice> _dict) : dict(std::move(_dict)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_extra_currencies(vm::CellSlice& cs, Ref<CellSlice>& dict) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_extra_currencies(Ref<vm::Cell> cell_ref, Ref<CellSlice>& dict) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_extra_currencies(vm::CellBuilder& cb, Ref<CellSlice> dict) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_extra_currencies(Ref<vm::Cell>& cell_ref, Ref<CellSlice> dict) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ExtraCurrencyCollection";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ExtraCurrencyCollection t_ExtraCurrencyCollection;

//
// headers for type `CurrencyCollection`
//

struct CurrencyCollection final : TLB_Complex {
  enum { currencies };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef CurrencyCollection type_class;
    Ref<CellSlice> grams;  	// grams : Grams
    Ref<CellSlice> other;  	// other : ExtraCurrencyCollection
    Record() = default;
    Record(Ref<CellSlice> _grams, Ref<CellSlice> _other) : grams(std::move(_grams)), other(std::move(_other)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "CurrencyCollection";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const CurrencyCollection t_CurrencyCollection;

//
// headers for type `CommonMsgInfo`
//

struct CommonMsgInfo final : TLB_Complex {
  enum { int_msg_info, ext_in_msg_info, ext_out_msg_info };
  static constexpr char cons_len[3] = { 1, 2, 2 };
  static constexpr unsigned char cons_tag[3] = { 0, 2, 3 };
  struct Record_int_msg_info;
  struct Record_ext_in_msg_info;
  struct Record_ext_out_msg_info;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_int_msg_info& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_int_msg_info& data) const;
  bool pack(vm::CellBuilder& cb, const Record_int_msg_info& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_int_msg_info& data) const;
  bool unpack(vm::CellSlice& cs, Record_ext_in_msg_info& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_ext_in_msg_info& data) const;
  bool pack(vm::CellBuilder& cb, const Record_ext_in_msg_info& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_ext_in_msg_info& data) const;
  bool unpack(vm::CellSlice& cs, Record_ext_out_msg_info& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_ext_out_msg_info& data) const;
  bool pack(vm::CellBuilder& cb, const Record_ext_out_msg_info& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_ext_out_msg_info& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "CommonMsgInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(2, 13);
  }
};

struct CommonMsgInfo::Record_int_msg_info {
  typedef CommonMsgInfo type_class;
  bool ihr_disabled;  	// ihr_disabled : Bool
  bool bounce;  	// bounce : Bool
  bool bounced;  	// bounced : Bool
  Ref<CellSlice> src;  	// src : MsgAddressInt
  Ref<CellSlice> dest;  	// dest : MsgAddressInt
  Ref<CellSlice> value;  	// value : CurrencyCollection
  Ref<CellSlice> ihr_fee;  	// ihr_fee : Grams
  Ref<CellSlice> fwd_fee;  	// fwd_fee : Grams
  unsigned long long created_lt;  	// created_lt : uint64
  unsigned created_at;  	// created_at : uint32
  Record_int_msg_info() = default;
  Record_int_msg_info(bool _ihr_disabled, bool _bounce, bool _bounced, Ref<CellSlice> _src, Ref<CellSlice> _dest, Ref<CellSlice> _value, Ref<CellSlice> _ihr_fee, Ref<CellSlice> _fwd_fee, unsigned long long _created_lt, unsigned _created_at) : ihr_disabled(_ihr_disabled), bounce(_bounce), bounced(_bounced), src(std::move(_src)), dest(std::move(_dest)), value(std::move(_value)), ihr_fee(std::move(_ihr_fee)), fwd_fee(std::move(_fwd_fee)), created_lt(_created_lt), created_at(_created_at) {}
};

struct CommonMsgInfo::Record_ext_in_msg_info {
  typedef CommonMsgInfo type_class;
  Ref<CellSlice> src;  	// src : MsgAddressExt
  Ref<CellSlice> dest;  	// dest : MsgAddressInt
  Ref<CellSlice> import_fee;  	// import_fee : Grams
  Record_ext_in_msg_info() = default;
  Record_ext_in_msg_info(Ref<CellSlice> _src, Ref<CellSlice> _dest, Ref<CellSlice> _import_fee) : src(std::move(_src)), dest(std::move(_dest)), import_fee(std::move(_import_fee)) {}
};

struct CommonMsgInfo::Record_ext_out_msg_info {
  typedef CommonMsgInfo type_class;
  Ref<CellSlice> src;  	// src : MsgAddressInt
  Ref<CellSlice> dest;  	// dest : MsgAddressExt
  unsigned long long created_lt;  	// created_lt : uint64
  unsigned created_at;  	// created_at : uint32
  Record_ext_out_msg_info() = default;
  Record_ext_out_msg_info(Ref<CellSlice> _src, Ref<CellSlice> _dest, unsigned long long _created_lt, unsigned _created_at) : src(std::move(_src)), dest(std::move(_dest)), created_lt(_created_lt), created_at(_created_at) {}
};

extern const CommonMsgInfo t_CommonMsgInfo;

//
// headers for type `CommonMsgInfoRelaxed`
//

struct CommonMsgInfoRelaxed final : TLB_Complex {
  enum { int_msg_info, ext_out_msg_info };
  static constexpr char cons_len[2] = { 1, 2 };
  static constexpr unsigned char cons_tag[2] = { 0, 3 };
  struct Record_int_msg_info;
  struct Record_ext_out_msg_info;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_int_msg_info& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_int_msg_info& data) const;
  bool pack(vm::CellBuilder& cb, const Record_int_msg_info& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_int_msg_info& data) const;
  bool unpack(vm::CellSlice& cs, Record_ext_out_msg_info& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_ext_out_msg_info& data) const;
  bool pack(vm::CellBuilder& cb, const Record_ext_out_msg_info& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_ext_out_msg_info& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "CommonMsgInfoRelaxed";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

struct CommonMsgInfoRelaxed::Record_int_msg_info {
  typedef CommonMsgInfoRelaxed type_class;
  bool ihr_disabled;  	// ihr_disabled : Bool
  bool bounce;  	// bounce : Bool
  bool bounced;  	// bounced : Bool
  Ref<CellSlice> src;  	// src : MsgAddress
  Ref<CellSlice> dest;  	// dest : MsgAddressInt
  Ref<CellSlice> value;  	// value : CurrencyCollection
  Ref<CellSlice> ihr_fee;  	// ihr_fee : Grams
  Ref<CellSlice> fwd_fee;  	// fwd_fee : Grams
  unsigned long long created_lt;  	// created_lt : uint64
  unsigned created_at;  	// created_at : uint32
  Record_int_msg_info() = default;
  Record_int_msg_info(bool _ihr_disabled, bool _bounce, bool _bounced, Ref<CellSlice> _src, Ref<CellSlice> _dest, Ref<CellSlice> _value, Ref<CellSlice> _ihr_fee, Ref<CellSlice> _fwd_fee, unsigned long long _created_lt, unsigned _created_at) : ihr_disabled(_ihr_disabled), bounce(_bounce), bounced(_bounced), src(std::move(_src)), dest(std::move(_dest)), value(std::move(_value)), ihr_fee(std::move(_ihr_fee)), fwd_fee(std::move(_fwd_fee)), created_lt(_created_lt), created_at(_created_at) {}
};

struct CommonMsgInfoRelaxed::Record_ext_out_msg_info {
  typedef CommonMsgInfoRelaxed type_class;
  Ref<CellSlice> src;  	// src : MsgAddress
  Ref<CellSlice> dest;  	// dest : MsgAddressExt
  unsigned long long created_lt;  	// created_lt : uint64
  unsigned created_at;  	// created_at : uint32
  Record_ext_out_msg_info() = default;
  Record_ext_out_msg_info(Ref<CellSlice> _src, Ref<CellSlice> _dest, unsigned long long _created_lt, unsigned _created_at) : src(std::move(_src)), dest(std::move(_dest)), created_lt(_created_lt), created_at(_created_at) {}
};

extern const CommonMsgInfoRelaxed t_CommonMsgInfoRelaxed;

//
// headers for type `TickTock`
//

struct TickTock final : TLB_Complex {
  enum { tick_tock };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef TickTock type_class;
    bool tick;  	// tick : Bool
    bool tock;  	// tock : Bool
    Record() = default;
    Record(bool _tick, bool _tock) : tick(_tick), tock(_tock) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 2;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(2);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(2);
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "TickTock";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const TickTock t_TickTock;

//
// headers for type `StateInit`
//

struct StateInit final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "StateInit";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct StateInit::Record {
  typedef StateInit type_class;
  Ref<CellSlice> split_depth;  	// split_depth : Maybe (## 5)
  Ref<CellSlice> special;  	// special : Maybe TickTock
  Ref<CellSlice> code;  	// code : Maybe ^Cell
  Ref<CellSlice> data;  	// data : Maybe ^Cell
  Ref<CellSlice> library;  	// library : HashmapE 256 SimpleLib
  Record() = default;
  Record(Ref<CellSlice> _split_depth, Ref<CellSlice> _special, Ref<CellSlice> _code, Ref<CellSlice> _data, Ref<CellSlice> _library) : split_depth(std::move(_split_depth)), special(std::move(_special)), code(std::move(_code)), data(std::move(_data)), library(std::move(_library)) {}
};

extern const StateInit t_StateInit;

//
// headers for type `SimpleLib`
//

struct SimpleLib final : TLB_Complex {
  enum { simple_lib };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef SimpleLib type_class;
    bool public1;  	// public : Bool
    Ref<Cell> root;  	// root : ^Cell
    Record() = default;
    Record(bool _public1, Ref<Cell> _root) : public1(_public1), root(std::move(_root)) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 0x10001;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance_ext(0x10001);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "SimpleLib";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const SimpleLib t_SimpleLib;

//
// headers for type `Message`
//

struct Message final : TLB_Complex {
  enum { message };
  static constexpr int cons_len_exact = 0;
  const TLB &X;
  Message(const TLB& _X) : X(_X) {}
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(Message " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct Message::Record {
  typedef Message type_class;
  Ref<CellSlice> info;  	// info : CommonMsgInfo
  Ref<CellSlice> init;  	// init : Maybe (Either StateInit ^StateInit)
  Ref<CellSlice> body;  	// body : Either X ^X
  Record() = default;
  Record(Ref<CellSlice> _info, Ref<CellSlice> _init, Ref<CellSlice> _body) : info(std::move(_info)), init(std::move(_init)), body(std::move(_body)) {}
};

//
// headers for type `MessageRelaxed`
//

struct MessageRelaxed final : TLB_Complex {
  enum { message };
  static constexpr int cons_len_exact = 0;
  const TLB &X;
  MessageRelaxed(const TLB& _X) : X(_X) {}
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(MessageRelaxed " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct MessageRelaxed::Record {
  typedef MessageRelaxed type_class;
  Ref<CellSlice> info;  	// info : CommonMsgInfoRelaxed
  Ref<CellSlice> init;  	// init : Maybe (Either StateInit ^StateInit)
  Ref<CellSlice> body;  	// body : Either X ^X
  Record() = default;
  Record(Ref<CellSlice> _info, Ref<CellSlice> _init, Ref<CellSlice> _body) : info(std::move(_info)), init(std::move(_init)), body(std::move(_body)) {}
};

//
// headers for type `IntermediateAddress`
//

struct IntermediateAddress final : TLB_Complex {
  enum { interm_addr_regular, interm_addr_simple, interm_addr_ext };
  static constexpr char cons_len[3] = { 1, 2, 2 };
  static constexpr unsigned char cons_tag[3] = { 0, 2, 3 };
  struct Record_interm_addr_regular {
    typedef IntermediateAddress type_class;
    int use_dest_bits;  	// use_dest_bits : #<= 96
    Record_interm_addr_regular() = default;
    Record_interm_addr_regular(int _use_dest_bits) : use_dest_bits(_use_dest_bits) {}
  };
  struct Record_interm_addr_simple {
    typedef IntermediateAddress type_class;
    int workchain_id;  	// workchain_id : int8
    unsigned long long addr_pfx;  	// addr_pfx : uint64
    Record_interm_addr_simple() = default;
    Record_interm_addr_simple(int _workchain_id, unsigned long long _addr_pfx) : workchain_id(_workchain_id), addr_pfx(_addr_pfx) {}
  };
  struct Record_interm_addr_ext {
    typedef IntermediateAddress type_class;
    int workchain_id;  	// workchain_id : int32
    unsigned long long addr_pfx;  	// addr_pfx : uint64
    Record_interm_addr_ext() = default;
    Record_interm_addr_ext(int _workchain_id, unsigned long long _addr_pfx) : workchain_id(_workchain_id), addr_pfx(_addr_pfx) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_interm_addr_regular& data) const;
  bool unpack_interm_addr_regular(vm::CellSlice& cs, int& use_dest_bits) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_interm_addr_regular& data) const;
  bool cell_unpack_interm_addr_regular(Ref<vm::Cell> cell_ref, int& use_dest_bits) const;
  bool pack(vm::CellBuilder& cb, const Record_interm_addr_regular& data) const;
  bool pack_interm_addr_regular(vm::CellBuilder& cb, int use_dest_bits) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_interm_addr_regular& data) const;
  bool cell_pack_interm_addr_regular(Ref<vm::Cell>& cell_ref, int use_dest_bits) const;
  bool unpack(vm::CellSlice& cs, Record_interm_addr_simple& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_interm_addr_simple& data) const;
  bool pack(vm::CellBuilder& cb, const Record_interm_addr_simple& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_interm_addr_simple& data) const;
  bool unpack(vm::CellSlice& cs, Record_interm_addr_ext& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_interm_addr_ext& data) const;
  bool pack(vm::CellBuilder& cb, const Record_interm_addr_ext& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_interm_addr_ext& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "IntermediateAddress";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(2, 13);
  }
};

extern const IntermediateAddress t_IntermediateAddress;

//
// headers for type `MsgEnvelope`
//

struct MsgEnvelope final : TLB_Complex {
  enum { msg_envelope };
  static constexpr int cons_len_exact = 4;
  static constexpr unsigned char cons_tag[1] = { 4 };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "MsgEnvelope";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct MsgEnvelope::Record {
  typedef MsgEnvelope type_class;
  Ref<CellSlice> cur_addr;  	// cur_addr : IntermediateAddress
  Ref<CellSlice> next_addr;  	// next_addr : IntermediateAddress
  Ref<CellSlice> fwd_fee_remaining;  	// fwd_fee_remaining : Grams
  Ref<Cell> msg;  	// msg : ^(Message Any)
  Record() = default;
  Record(Ref<CellSlice> _cur_addr, Ref<CellSlice> _next_addr, Ref<CellSlice> _fwd_fee_remaining, Ref<Cell> _msg) : cur_addr(std::move(_cur_addr)), next_addr(std::move(_next_addr)), fwd_fee_remaining(std::move(_fwd_fee_remaining)), msg(std::move(_msg)) {}
};

extern const MsgEnvelope t_MsgEnvelope;

//
// headers for type `InMsg`
//

struct InMsg final : TLB_Complex {
  enum { msg_import_ext, msg_import_ihr, msg_import_imm, msg_import_fin, msg_import_tr, msg_discard_fin, msg_discard_tr };
  static constexpr int cons_len_exact = 3;
  static constexpr unsigned char cons_tag[7] = { 0, 2, 3, 4, 5, 6, 7 };
  struct Record_msg_import_ext {
    typedef InMsg type_class;
    Ref<Cell> msg;  	// msg : ^(Message Any)
    Ref<Cell> transaction;  	// transaction : ^Transaction
    Record_msg_import_ext() = default;
    Record_msg_import_ext(Ref<Cell> _msg, Ref<Cell> _transaction) : msg(std::move(_msg)), transaction(std::move(_transaction)) {}
  };
  struct Record_msg_import_ihr;
  struct Record_msg_import_imm;
  struct Record_msg_import_fin;
  struct Record_msg_import_tr;
  struct Record_msg_discard_fin;
  struct Record_msg_discard_tr;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_msg_import_ext& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_import_ext& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_import_ext& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_import_ext& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_import_ihr& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_import_ihr& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_import_ihr& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_import_ihr& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_import_imm& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_import_imm& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_import_imm& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_import_imm& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_import_fin& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_import_fin& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_import_fin& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_import_fin& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_import_tr& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_import_tr& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_import_tr& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_import_tr& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_discard_fin& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_discard_fin& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_discard_fin& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_discard_fin& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_discard_tr& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_discard_tr& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_discard_tr& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_discard_tr& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "InMsg";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(3, 0xfd);
  }
};

struct InMsg::Record_msg_import_ihr {
  typedef InMsg type_class;
  Ref<Cell> msg;  	// msg : ^(Message Any)
  Ref<Cell> transaction;  	// transaction : ^Transaction
  Ref<CellSlice> ihr_fee;  	// ihr_fee : Grams
  Ref<Cell> proof_created;  	// proof_created : ^Cell
  Record_msg_import_ihr() = default;
  Record_msg_import_ihr(Ref<Cell> _msg, Ref<Cell> _transaction, Ref<CellSlice> _ihr_fee, Ref<Cell> _proof_created) : msg(std::move(_msg)), transaction(std::move(_transaction)), ihr_fee(std::move(_ihr_fee)), proof_created(std::move(_proof_created)) {}
};

struct InMsg::Record_msg_import_imm {
  typedef InMsg type_class;
  Ref<Cell> in_msg;  	// in_msg : ^MsgEnvelope
  Ref<Cell> transaction;  	// transaction : ^Transaction
  Ref<CellSlice> fwd_fee;  	// fwd_fee : Grams
  Record_msg_import_imm() = default;
  Record_msg_import_imm(Ref<Cell> _in_msg, Ref<Cell> _transaction, Ref<CellSlice> _fwd_fee) : in_msg(std::move(_in_msg)), transaction(std::move(_transaction)), fwd_fee(std::move(_fwd_fee)) {}
};

struct InMsg::Record_msg_import_fin {
  typedef InMsg type_class;
  Ref<Cell> in_msg;  	// in_msg : ^MsgEnvelope
  Ref<Cell> transaction;  	// transaction : ^Transaction
  Ref<CellSlice> fwd_fee;  	// fwd_fee : Grams
  Record_msg_import_fin() = default;
  Record_msg_import_fin(Ref<Cell> _in_msg, Ref<Cell> _transaction, Ref<CellSlice> _fwd_fee) : in_msg(std::move(_in_msg)), transaction(std::move(_transaction)), fwd_fee(std::move(_fwd_fee)) {}
};

struct InMsg::Record_msg_import_tr {
  typedef InMsg type_class;
  Ref<Cell> in_msg;  	// in_msg : ^MsgEnvelope
  Ref<Cell> out_msg;  	// out_msg : ^MsgEnvelope
  Ref<CellSlice> transit_fee;  	// transit_fee : Grams
  Record_msg_import_tr() = default;
  Record_msg_import_tr(Ref<Cell> _in_msg, Ref<Cell> _out_msg, Ref<CellSlice> _transit_fee) : in_msg(std::move(_in_msg)), out_msg(std::move(_out_msg)), transit_fee(std::move(_transit_fee)) {}
};

struct InMsg::Record_msg_discard_fin {
  typedef InMsg type_class;
  Ref<Cell> in_msg;  	// in_msg : ^MsgEnvelope
  unsigned long long transaction_id;  	// transaction_id : uint64
  Ref<CellSlice> fwd_fee;  	// fwd_fee : Grams
  Record_msg_discard_fin() = default;
  Record_msg_discard_fin(Ref<Cell> _in_msg, unsigned long long _transaction_id, Ref<CellSlice> _fwd_fee) : in_msg(std::move(_in_msg)), transaction_id(_transaction_id), fwd_fee(std::move(_fwd_fee)) {}
};

struct InMsg::Record_msg_discard_tr {
  typedef InMsg type_class;
  Ref<Cell> in_msg;  	// in_msg : ^MsgEnvelope
  unsigned long long transaction_id;  	// transaction_id : uint64
  Ref<CellSlice> fwd_fee;  	// fwd_fee : Grams
  Ref<Cell> proof_delivered;  	// proof_delivered : ^Cell
  Record_msg_discard_tr() = default;
  Record_msg_discard_tr(Ref<Cell> _in_msg, unsigned long long _transaction_id, Ref<CellSlice> _fwd_fee, Ref<Cell> _proof_delivered) : in_msg(std::move(_in_msg)), transaction_id(_transaction_id), fwd_fee(std::move(_fwd_fee)), proof_delivered(std::move(_proof_delivered)) {}
};

extern const InMsg t_InMsg;

//
// headers for type `HashmapAug`
//

struct HashmapAug final : TLB_Complex {
  enum { ahm_edge };
  static constexpr int cons_len_exact = 0;
  int m;
  const TLB &X, &Y;
  HashmapAug(int _m, const TLB& _X, const TLB& _Y) : m(_m), X(_X), Y(_Y) {}
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(HashmapAug " << m << " " << X << " " << Y << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct HashmapAug::Record {
  typedef HashmapAug type_class;
  int n;  	// n : #
  int l;  	// l : #
  int m;  	// m : #
  Ref<CellSlice> label;  	// label : HmLabel ~l n
  Ref<CellSlice> node;  	// node : HashmapAugNode m X Y
  Record() = default;
  Record(Ref<CellSlice> _label, Ref<CellSlice> _node) : n(-1), l(-1), m(-1), label(std::move(_label)), node(std::move(_node)) {}
};

//
// headers for type `HashmapAugNode`
//

struct HashmapAugNode final : TLB_Complex {
  enum { ahmn_leaf, ahmn_fork };
  static constexpr int cons_len_exact = 0;
  int m;
  const TLB &X, &Y;
  HashmapAugNode(int _m, const TLB& _X, const TLB& _Y) : m(_m), X(_X), Y(_Y) {}
  struct Record_ahmn_leaf {
    typedef HashmapAugNode type_class;
    Ref<CellSlice> extra;  	// extra : Y
    Ref<CellSlice> value;  	// value : X
    Record_ahmn_leaf() = default;
    Record_ahmn_leaf(Ref<CellSlice> _extra, Ref<CellSlice> _value) : extra(std::move(_extra)), value(std::move(_value)) {}
  };
  struct Record_ahmn_fork;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_ahmn_leaf& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_ahmn_leaf& data) const;
  bool pack(vm::CellBuilder& cb, const Record_ahmn_leaf& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_ahmn_leaf& data) const;
  bool unpack(vm::CellSlice& cs, Record_ahmn_fork& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_ahmn_fork& data) const;
  bool pack(vm::CellBuilder& cb, const Record_ahmn_fork& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_ahmn_fork& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(HashmapAugNode " << m << " " << X << " " << Y << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override;
};

struct HashmapAugNode::Record_ahmn_fork {
  typedef HashmapAugNode type_class;
  int n;  	// n : #
  Ref<Cell> left;  	// left : ^(HashmapAug n X Y)
  Ref<Cell> right;  	// right : ^(HashmapAug n X Y)
  Ref<CellSlice> extra;  	// extra : Y
  Record_ahmn_fork() = default;
  Record_ahmn_fork(Ref<Cell> _left, Ref<Cell> _right, Ref<CellSlice> _extra) : n(-1), left(std::move(_left)), right(std::move(_right)), extra(std::move(_extra)) {}
};

//
// headers for type `HashmapAugE`
//

struct HashmapAugE final : TLB_Complex {
  enum { ahme_empty, ahme_root };
  static constexpr int cons_len_exact = 1;
  int m;
  const TLB &X, &Y;
  HashmapAugE(int _m, const TLB& _X, const TLB& _Y) : m(_m), X(_X), Y(_Y) {}
  struct Record_ahme_empty {
    typedef HashmapAugE type_class;
    Ref<CellSlice> extra;  	// extra : Y
    Record_ahme_empty() = default;
    Record_ahme_empty(Ref<CellSlice> _extra) : extra(std::move(_extra)) {}
  };
  struct Record_ahme_root;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_ahme_empty& data) const;
  bool unpack_ahme_empty(vm::CellSlice& cs, Ref<CellSlice>& extra) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_ahme_empty& data) const;
  bool cell_unpack_ahme_empty(Ref<vm::Cell> cell_ref, Ref<CellSlice>& extra) const;
  bool pack(vm::CellBuilder& cb, const Record_ahme_empty& data) const;
  bool pack_ahme_empty(vm::CellBuilder& cb, Ref<CellSlice> extra) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_ahme_empty& data) const;
  bool cell_pack_ahme_empty(Ref<vm::Cell>& cell_ref, Ref<CellSlice> extra) const;
  bool unpack(vm::CellSlice& cs, Record_ahme_root& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_ahme_root& data) const;
  bool pack(vm::CellBuilder& cb, const Record_ahme_root& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_ahme_root& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(HashmapAugE " << m << " " << X << " " << Y << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

struct HashmapAugE::Record_ahme_root {
  typedef HashmapAugE type_class;
  int n;  	// n : #
  Ref<Cell> root;  	// root : ^(HashmapAug n X Y)
  Ref<CellSlice> extra;  	// extra : Y
  Record_ahme_root() = default;
  Record_ahme_root(Ref<Cell> _root, Ref<CellSlice> _extra) : n(-1), root(std::move(_root)), extra(std::move(_extra)) {}
};

//
// headers for type `ImportFees`
//

struct ImportFees final : TLB_Complex {
  enum { import_fees };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ImportFees type_class;
    Ref<CellSlice> fees_collected;  	// fees_collected : Grams
    Ref<CellSlice> value_imported;  	// value_imported : CurrencyCollection
    Record() = default;
    Record(Ref<CellSlice> _fees_collected, Ref<CellSlice> _value_imported) : fees_collected(std::move(_fees_collected)), value_imported(std::move(_value_imported)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ImportFees";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ImportFees t_ImportFees;

//
// headers for type `InMsgDescr`
//

struct InMsgDescr final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef InMsgDescr type_class;
    Ref<CellSlice> x;  	// HashmapAugE 256 InMsg ImportFees
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "InMsgDescr";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const InMsgDescr t_InMsgDescr;

//
// headers for type `OutMsg`
//

struct OutMsg final : TLB_Complex {
  enum { msg_export_ext, msg_export_new, msg_export_imm, msg_export_tr, msg_export_deq_imm, msg_export_deq, msg_export_tr_req };
  static constexpr int cons_len_exact = 3;
  static constexpr unsigned char cons_tag[7] = { 0, 1, 2, 3, 4, 6, 7 };
  struct Record_msg_export_ext {
    typedef OutMsg type_class;
    Ref<Cell> msg;  	// msg : ^(Message Any)
    Ref<Cell> transaction;  	// transaction : ^Transaction
    Record_msg_export_ext() = default;
    Record_msg_export_ext(Ref<Cell> _msg, Ref<Cell> _transaction) : msg(std::move(_msg)), transaction(std::move(_transaction)) {}
  };
  struct Record_msg_export_imm;
  struct Record_msg_export_new {
    typedef OutMsg type_class;
    Ref<Cell> out_msg;  	// out_msg : ^MsgEnvelope
    Ref<Cell> transaction;  	// transaction : ^Transaction
    Record_msg_export_new() = default;
    Record_msg_export_new(Ref<Cell> _out_msg, Ref<Cell> _transaction) : out_msg(std::move(_out_msg)), transaction(std::move(_transaction)) {}
  };
  struct Record_msg_export_tr {
    typedef OutMsg type_class;
    Ref<Cell> out_msg;  	// out_msg : ^MsgEnvelope
    Ref<Cell> imported;  	// imported : ^InMsg
    Record_msg_export_tr() = default;
    Record_msg_export_tr(Ref<Cell> _out_msg, Ref<Cell> _imported) : out_msg(std::move(_out_msg)), imported(std::move(_imported)) {}
  };
  struct Record_msg_export_deq {
    typedef OutMsg type_class;
    Ref<Cell> out_msg;  	// out_msg : ^MsgEnvelope
    unsigned long long import_block_lt;  	// import_block_lt : uint64
    Record_msg_export_deq() = default;
    Record_msg_export_deq(Ref<Cell> _out_msg, unsigned long long _import_block_lt) : out_msg(std::move(_out_msg)), import_block_lt(_import_block_lt) {}
  };
  struct Record_msg_export_tr_req {
    typedef OutMsg type_class;
    Ref<Cell> out_msg;  	// out_msg : ^MsgEnvelope
    Ref<Cell> imported;  	// imported : ^InMsg
    Record_msg_export_tr_req() = default;
    Record_msg_export_tr_req(Ref<Cell> _out_msg, Ref<Cell> _imported) : out_msg(std::move(_out_msg)), imported(std::move(_imported)) {}
  };
  struct Record_msg_export_deq_imm {
    typedef OutMsg type_class;
    Ref<Cell> out_msg;  	// out_msg : ^MsgEnvelope
    Ref<Cell> reimport;  	// reimport : ^InMsg
    Record_msg_export_deq_imm() = default;
    Record_msg_export_deq_imm(Ref<Cell> _out_msg, Ref<Cell> _reimport) : out_msg(std::move(_out_msg)), reimport(std::move(_reimport)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_msg_export_ext& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_export_ext& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_export_ext& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_export_ext& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_export_imm& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_export_imm& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_export_imm& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_export_imm& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_export_new& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_export_new& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_export_new& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_export_new& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_export_tr& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_export_tr& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_export_tr& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_export_tr& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_export_deq& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_export_deq& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_export_deq& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_export_deq& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_export_tr_req& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_export_tr_req& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_export_tr_req& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_export_tr_req& data) const;
  bool unpack(vm::CellSlice& cs, Record_msg_export_deq_imm& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_msg_export_deq_imm& data) const;
  bool pack(vm::CellBuilder& cb, const Record_msg_export_deq_imm& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_msg_export_deq_imm& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "OutMsg";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(3, 0xdf);
  }
};

struct OutMsg::Record_msg_export_imm {
  typedef OutMsg type_class;
  Ref<Cell> out_msg;  	// out_msg : ^MsgEnvelope
  Ref<Cell> transaction;  	// transaction : ^Transaction
  Ref<Cell> reimport;  	// reimport : ^InMsg
  Record_msg_export_imm() = default;
  Record_msg_export_imm(Ref<Cell> _out_msg, Ref<Cell> _transaction, Ref<Cell> _reimport) : out_msg(std::move(_out_msg)), transaction(std::move(_transaction)), reimport(std::move(_reimport)) {}
};

extern const OutMsg t_OutMsg;

//
// headers for type `EnqueuedMsg`
//

struct EnqueuedMsg final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef EnqueuedMsg type_class;
    unsigned long long enqueued_lt;  	// enqueued_lt : uint64
    Ref<Cell> out_msg;  	// out_msg : ^MsgEnvelope
    Record() = default;
    Record(unsigned long long _enqueued_lt, Ref<Cell> _out_msg) : enqueued_lt(_enqueued_lt), out_msg(std::move(_out_msg)) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 0x10040;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance_ext(0x10040);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "EnqueuedMsg";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const EnqueuedMsg t_EnqueuedMsg;

//
// headers for type `OutMsgDescr`
//

struct OutMsgDescr final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef OutMsgDescr type_class;
    Ref<CellSlice> x;  	// HashmapAugE 256 OutMsg CurrencyCollection
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "OutMsgDescr";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const OutMsgDescr t_OutMsgDescr;

//
// headers for type `OutMsgQueue`
//

struct OutMsgQueue final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef OutMsgQueue type_class;
    Ref<CellSlice> x;  	// HashmapAugE 352 EnqueuedMsg uint64
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "OutMsgQueue";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const OutMsgQueue t_OutMsgQueue;

//
// headers for type `ProcessedUpto`
//

struct ProcessedUpto final : TLB_Complex {
  enum { processed_upto };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ProcessedUpto type_class;
    unsigned long long last_msg_lt;  	// last_msg_lt : uint64
    td::BitArray<256> last_msg_hash;  	// last_msg_hash : bits256
    Record() = default;
    Record(unsigned long long _last_msg_lt, const td::BitArray<256>& _last_msg_hash) : last_msg_lt(_last_msg_lt), last_msg_hash(_last_msg_hash) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 320;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(320);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(320);
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ProcessedUpto";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ProcessedUpto t_ProcessedUpto;

//
// headers for type `ProcessedInfo`
//

struct ProcessedInfo final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ProcessedInfo type_class;
    Ref<CellSlice> x;  	// HashmapE 96 ProcessedUpto
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ProcessedInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ProcessedInfo t_ProcessedInfo;

//
// headers for type `IhrPendingSince`
//

struct IhrPendingSince final : TLB_Complex {
  enum { ihr_pending };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef IhrPendingSince type_class;
    unsigned long long shard;  	// shard : uint64
    unsigned long long import_lt;  	// import_lt : uint64
    Record() = default;
    Record(unsigned long long _shard, unsigned long long _import_lt) : shard(_shard), import_lt(_import_lt) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 128;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(128);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(128);
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "IhrPendingSince";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const IhrPendingSince t_IhrPendingSince;

//
// headers for type `IhrPendingInfo`
//

struct IhrPendingInfo final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef IhrPendingInfo type_class;
    Ref<CellSlice> x;  	// HashmapE 256 IhrPendingSince
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "IhrPendingInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const IhrPendingInfo t_IhrPendingInfo;

//
// headers for type `OutMsgQueueInfo`
//

struct OutMsgQueueInfo final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "OutMsgQueueInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct OutMsgQueueInfo::Record {
  typedef OutMsgQueueInfo type_class;
  Ref<CellSlice> out_queue;  	// out_queue : OutMsgQueue
  Ref<CellSlice> proc_info;  	// proc_info : ProcessedInfo
  Ref<CellSlice> ihr_pending;  	// ihr_pending : IhrPendingInfo
  Record() = default;
  Record(Ref<CellSlice> _out_queue, Ref<CellSlice> _proc_info, Ref<CellSlice> _ihr_pending) : out_queue(std::move(_out_queue)), proc_info(std::move(_proc_info)), ihr_pending(std::move(_ihr_pending)) {}
};

extern const OutMsgQueueInfo t_OutMsgQueueInfo;

//
// headers for type `StorageUsed`
//

struct StorageUsed final : TLB_Complex {
  enum { storage_used };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "StorageUsed";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct StorageUsed::Record {
  typedef StorageUsed type_class;
  Ref<CellSlice> cells;  	// cells : VarUInteger 7
  Ref<CellSlice> bits;  	// bits : VarUInteger 7
  Ref<CellSlice> public_cells;  	// public_cells : VarUInteger 7
  Record() = default;
  Record(Ref<CellSlice> _cells, Ref<CellSlice> _bits, Ref<CellSlice> _public_cells) : cells(std::move(_cells)), bits(std::move(_bits)), public_cells(std::move(_public_cells)) {}
};

extern const StorageUsed t_StorageUsed;

//
// headers for type `StorageUsedShort`
//

struct StorageUsedShort final : TLB_Complex {
  enum { storage_used_short };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef StorageUsedShort type_class;
    Ref<CellSlice> cells;  	// cells : VarUInteger 7
    Ref<CellSlice> bits;  	// bits : VarUInteger 7
    Record() = default;
    Record(Ref<CellSlice> _cells, Ref<CellSlice> _bits) : cells(std::move(_cells)), bits(std::move(_bits)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "StorageUsedShort";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const StorageUsedShort t_StorageUsedShort;

//
// headers for type `StorageInfo`
//

struct StorageInfo final : TLB_Complex {
  enum { storage_info };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "StorageInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct StorageInfo::Record {
  typedef StorageInfo type_class;
  Ref<CellSlice> used;  	// used : StorageUsed
  unsigned last_paid;  	// last_paid : uint32
  Ref<CellSlice> due_payment;  	// due_payment : Maybe Grams
  Record() = default;
  Record(Ref<CellSlice> _used, unsigned _last_paid, Ref<CellSlice> _due_payment) : used(std::move(_used)), last_paid(_last_paid), due_payment(std::move(_due_payment)) {}
};

extern const StorageInfo t_StorageInfo;

//
// headers for type `Account`
//

struct Account final : TLB_Complex {
  enum { account_none, account };
  static constexpr int cons_len_exact = 1;
  struct Record_account_none {
    typedef Account type_class;
  };
  struct Record_account;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_account_none& data) const;
  bool unpack_account_none(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_account_none& data) const;
  bool cell_unpack_account_none(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_account_none& data) const;
  bool pack_account_none(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_account_none& data) const;
  bool cell_pack_account_none(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_account& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_account& data) const;
  bool pack(vm::CellBuilder& cb, const Record_account& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_account& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "Account";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

struct Account::Record_account {
  typedef Account type_class;
  Ref<CellSlice> addr;  	// addr : MsgAddressInt
  Ref<CellSlice> storage_stat;  	// storage_stat : StorageInfo
  Ref<CellSlice> storage;  	// storage : AccountStorage
  Record_account() = default;
  Record_account(Ref<CellSlice> _addr, Ref<CellSlice> _storage_stat, Ref<CellSlice> _storage) : addr(std::move(_addr)), storage_stat(std::move(_storage_stat)), storage(std::move(_storage)) {}
};

extern const Account t_Account;

//
// headers for type `AccountStorage`
//

struct AccountStorage final : TLB_Complex {
  enum { account_storage };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "AccountStorage";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct AccountStorage::Record {
  typedef AccountStorage type_class;
  unsigned long long last_trans_lt;  	// last_trans_lt : uint64
  Ref<CellSlice> balance;  	// balance : CurrencyCollection
  Ref<CellSlice> state;  	// state : AccountState
  Record() = default;
  Record(unsigned long long _last_trans_lt, Ref<CellSlice> _balance, Ref<CellSlice> _state) : last_trans_lt(_last_trans_lt), balance(std::move(_balance)), state(std::move(_state)) {}
};

extern const AccountStorage t_AccountStorage;

//
// headers for type `AccountState`
//

struct AccountState final : TLB_Complex {
  enum { account_uninit, account_frozen, account_active };
  static constexpr char cons_len[3] = { 2, 2, 1 };
  static constexpr unsigned char cons_tag[3] = { 0, 1, 1 };
  struct Record_account_uninit {
    typedef AccountState type_class;
  };
  struct Record_account_active {
    typedef AccountState type_class;
    Ref<CellSlice> x;  	// StateInit
    Record_account_active() = default;
    Record_account_active(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  struct Record_account_frozen {
    typedef AccountState type_class;
    td::BitArray<256> state_hash;  	// state_hash : bits256
    Record_account_frozen() = default;
    Record_account_frozen(const td::BitArray<256>& _state_hash) : state_hash(_state_hash) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_account_uninit& data) const;
  bool unpack_account_uninit(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_account_uninit& data) const;
  bool cell_unpack_account_uninit(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_account_uninit& data) const;
  bool pack_account_uninit(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_account_uninit& data) const;
  bool cell_pack_account_uninit(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_account_active& data) const;
  bool unpack_account_active(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_account_active& data) const;
  bool cell_unpack_account_active(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_account_active& data) const;
  bool pack_account_active(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_account_active& data) const;
  bool cell_pack_account_active(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool unpack(vm::CellSlice& cs, Record_account_frozen& data) const;
  bool unpack_account_frozen(vm::CellSlice& cs, td::BitArray<256>& state_hash) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_account_frozen& data) const;
  bool cell_unpack_account_frozen(Ref<vm::Cell> cell_ref, td::BitArray<256>& state_hash) const;
  bool pack(vm::CellBuilder& cb, const Record_account_frozen& data) const;
  bool pack_account_frozen(vm::CellBuilder& cb, const td::BitArray<256>& state_hash) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_account_frozen& data) const;
  bool cell_pack_account_frozen(Ref<vm::Cell>& cell_ref, const td::BitArray<256>& state_hash) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "AccountState";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(2, 7);
  }
};

extern const AccountState t_AccountState;

//
// headers for type `AccountStatus`
//

struct AccountStatus final : TLB_Complex {
  enum { acc_state_uninit, acc_state_frozen, acc_state_active, acc_state_nonexist };
  static constexpr int cons_len_exact = 2;
  struct Record_acc_state_uninit {
    typedef AccountStatus type_class;
  };
  struct Record_acc_state_frozen {
    typedef AccountStatus type_class;
  };
  struct Record_acc_state_active {
    typedef AccountStatus type_class;
  };
  struct Record_acc_state_nonexist {
    typedef AccountStatus type_class;
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 2;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(2);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(2);
  }
  bool fetch_enum_to(vm::CellSlice& cs, char& value) const;
  bool store_enum_from(vm::CellBuilder& cb, int value) const;
  bool unpack(vm::CellSlice& cs, Record_acc_state_uninit& data) const;
  bool unpack_acc_state_uninit(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_acc_state_uninit& data) const;
  bool cell_unpack_acc_state_uninit(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_acc_state_uninit& data) const;
  bool pack_acc_state_uninit(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_acc_state_uninit& data) const;
  bool cell_pack_acc_state_uninit(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_acc_state_frozen& data) const;
  bool unpack_acc_state_frozen(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_acc_state_frozen& data) const;
  bool cell_unpack_acc_state_frozen(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_acc_state_frozen& data) const;
  bool pack_acc_state_frozen(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_acc_state_frozen& data) const;
  bool cell_pack_acc_state_frozen(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_acc_state_active& data) const;
  bool unpack_acc_state_active(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_acc_state_active& data) const;
  bool cell_unpack_acc_state_active(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_acc_state_active& data) const;
  bool pack_acc_state_active(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_acc_state_active& data) const;
  bool cell_pack_acc_state_active(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_acc_state_nonexist& data) const;
  bool unpack_acc_state_nonexist(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_acc_state_nonexist& data) const;
  bool cell_unpack_acc_state_nonexist(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_acc_state_nonexist& data) const;
  bool pack_acc_state_nonexist(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_acc_state_nonexist& data) const;
  bool cell_pack_acc_state_nonexist(Ref<vm::Cell>& cell_ref) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "AccountStatus";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(2);
  }
};

extern const AccountStatus t_AccountStatus;

//
// headers for type `ShardAccounts`
//

struct ShardAccounts final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ShardAccounts type_class;
    Ref<CellSlice> x;  	// HashmapAugE 256 ^Account CurrencyCollection
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ShardAccounts";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ShardAccounts t_ShardAccounts;

//
// headers for type `Transaction`
//

struct Transaction final : TLB_Complex {
  enum { transaction };
  static constexpr int cons_len_exact = 4;
  static constexpr unsigned char cons_tag[1] = { 6 };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "Transaction";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct Transaction::Record {
  typedef Transaction type_class;
  td::BitArray<256> account_addr;  	// account_addr : bits256
  unsigned long long lt;  	// lt : uint64
  int outmsg_cnt;  	// outmsg_cnt : uint15
  char orig_status;  	// orig_status : AccountStatus
  char end_status;  	// end_status : AccountStatus
  Ref<CellSlice> in_msg;  	// in_msg : Maybe ^(Message Any)
  Ref<CellSlice> out_msgs;  	// out_msgs : HashmapE 15 ^(Message Any)
  Ref<CellSlice> total_fees;  	// total_fees : Grams
  Ref<Cell> state_update;  	// state_update : ^(HASH_UPDATE Account)
  Ref<Cell> description;  	// description : ^TransactionDescr
  Record() = default;
  Record(const td::BitArray<256>& _account_addr, unsigned long long _lt, int _outmsg_cnt, char _orig_status, char _end_status, Ref<CellSlice> _in_msg, Ref<CellSlice> _out_msgs, Ref<CellSlice> _total_fees, Ref<Cell> _state_update, Ref<Cell> _description) : account_addr(_account_addr), lt(_lt), outmsg_cnt(_outmsg_cnt), orig_status(_orig_status), end_status(_end_status), in_msg(std::move(_in_msg)), out_msgs(std::move(_out_msgs)), total_fees(std::move(_total_fees)), state_update(std::move(_state_update)), description(std::move(_description)) {}
};

extern const Transaction t_Transaction;

//
// headers for type `MERKLE_UPDATE`
//

struct MERKLE_UPDATE final : TLB_Complex {
  enum { _merkle_update };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 2 };
  const TLB &X;
  MERKLE_UPDATE(const TLB& _X) : X(_X) {}
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 0x20208;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance_ext(0x20208);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(MERKLE_UPDATE " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct MERKLE_UPDATE::Record {
  typedef MERKLE_UPDATE type_class;
  td::BitArray<256> old_hash;  	// old_hash : bits256
  td::BitArray<256> new_hash;  	// new_hash : bits256
  Ref<Cell> old;  	// old : ^X
  Ref<Cell> new1;  	// new : ^X
  Record() = default;
  Record(const td::BitArray<256>& _old_hash, const td::BitArray<256>& _new_hash, Ref<Cell> _old, Ref<Cell> _new1) : old_hash(_old_hash), new_hash(_new_hash), old(std::move(_old)), new1(std::move(_new1)) {}
};

//
// headers for type `HASH_UPDATE`
//

struct HASH_UPDATE final : TLB_Complex {
  enum { update_hashes };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 0x72 };
  const TLB &X;
  HASH_UPDATE(const TLB& _X) : X(_X) {}
  struct Record {
    typedef HASH_UPDATE type_class;
    td::BitArray<256> old_hash;  	// old_hash : bits256
    td::BitArray<256> new_hash;  	// new_hash : bits256
    Record() = default;
    Record(const td::BitArray<256>& _old_hash, const td::BitArray<256>& _new_hash) : old_hash(_old_hash), new_hash(_new_hash) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 520;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(520);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(HASH_UPDATE " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

//
// headers for type `AccountBlock`
//

struct AccountBlock final : TLB_Complex {
  enum { acc_trans };
  static constexpr int cons_len_exact = 4;
  static constexpr unsigned char cons_tag[1] = { 4 };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "AccountBlock";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct AccountBlock::Record {
  typedef AccountBlock type_class;
  td::BitArray<256> account_addr;  	// account_addr : bits256
  Ref<CellSlice> transactions;  	// transactions : HashmapAug 64 ^Transaction Grams
  Ref<Cell> state_update;  	// state_update : ^(HASH_UPDATE Account)
  Record() = default;
  Record(const td::BitArray<256>& _account_addr, Ref<CellSlice> _transactions, Ref<Cell> _state_update) : account_addr(_account_addr), transactions(std::move(_transactions)), state_update(std::move(_state_update)) {}
};

extern const AccountBlock t_AccountBlock;

//
// headers for type `ShardAccountBlocks`
//

struct ShardAccountBlocks final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ShardAccountBlocks type_class;
    Ref<CellSlice> x;  	// HashmapAugE 256 AccountBlock Grams
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ShardAccountBlocks";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ShardAccountBlocks t_ShardAccountBlocks;

//
// headers for type `TrStoragePhase`
//

struct TrStoragePhase final : TLB_Complex {
  enum { tr_phase_storage };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "TrStoragePhase";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct TrStoragePhase::Record {
  typedef TrStoragePhase type_class;
  Ref<CellSlice> storage_fees_collected;  	// storage_fees_collected : Grams
  Ref<CellSlice> storage_fees_due;  	// storage_fees_due : Maybe Grams
  char status_change;  	// status_change : AccStatusChange
  Record() = default;
  Record(Ref<CellSlice> _storage_fees_collected, Ref<CellSlice> _storage_fees_due, char _status_change) : storage_fees_collected(std::move(_storage_fees_collected)), storage_fees_due(std::move(_storage_fees_due)), status_change(_status_change) {}
};

extern const TrStoragePhase t_TrStoragePhase;

//
// headers for type `AccStatusChange`
//

struct AccStatusChange final : TLB_Complex {
  enum { acst_unchanged, acst_frozen, acst_deleted };
  static constexpr char cons_len[3] = { 1, 2, 2 };
  static constexpr unsigned char cons_tag[3] = { 0, 2, 3 };
  struct Record_acst_unchanged {
    typedef AccStatusChange type_class;
  };
  struct Record_acst_frozen {
    typedef AccStatusChange type_class;
  };
  struct Record_acst_deleted {
    typedef AccStatusChange type_class;
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool fetch_enum_to(vm::CellSlice& cs, char& value) const;
  bool store_enum_from(vm::CellBuilder& cb, int value) const;
  bool unpack(vm::CellSlice& cs, Record_acst_unchanged& data) const;
  bool unpack_acst_unchanged(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_acst_unchanged& data) const;
  bool cell_unpack_acst_unchanged(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_acst_unchanged& data) const;
  bool pack_acst_unchanged(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_acst_unchanged& data) const;
  bool cell_pack_acst_unchanged(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_acst_frozen& data) const;
  bool unpack_acst_frozen(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_acst_frozen& data) const;
  bool cell_unpack_acst_frozen(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_acst_frozen& data) const;
  bool pack_acst_frozen(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_acst_frozen& data) const;
  bool cell_pack_acst_frozen(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_acst_deleted& data) const;
  bool unpack_acst_deleted(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_acst_deleted& data) const;
  bool cell_unpack_acst_deleted(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_acst_deleted& data) const;
  bool pack_acst_deleted(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_acst_deleted& data) const;
  bool cell_pack_acst_deleted(Ref<vm::Cell>& cell_ref) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "AccStatusChange";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect_ext(2, 13);
  }
};

extern const AccStatusChange t_AccStatusChange;

//
// headers for type `TrCreditPhase`
//

struct TrCreditPhase final : TLB_Complex {
  enum { tr_phase_credit };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef TrCreditPhase type_class;
    Ref<CellSlice> due_fees_collected;  	// due_fees_collected : Maybe Grams
    Ref<CellSlice> credit;  	// credit : CurrencyCollection
    Record() = default;
    Record(Ref<CellSlice> _due_fees_collected, Ref<CellSlice> _credit) : due_fees_collected(std::move(_due_fees_collected)), credit(std::move(_credit)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "TrCreditPhase";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const TrCreditPhase t_TrCreditPhase;

//
// headers for auxiliary type `TrComputePhase_aux`
//

struct TrComputePhase_aux final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "TrComputePhase_aux";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct TrComputePhase_aux::Record {
  typedef TrComputePhase_aux type_class;
  Ref<CellSlice> gas_used;  	// gas_used : VarUInteger 7
  Ref<CellSlice> gas_limit;  	// gas_limit : VarUInteger 7
  Ref<CellSlice> gas_credit;  	// gas_credit : Maybe (VarUInteger 3)
  int mode;  	// mode : int8
  int exit_code;  	// exit_code : int32
  Ref<CellSlice> exit_arg;  	// exit_arg : Maybe int32
  unsigned vm_steps;  	// vm_steps : uint32
  td::BitArray<256> vm_init_state_hash;  	// vm_init_state_hash : bits256
  td::BitArray<256> vm_final_state_hash;  	// vm_final_state_hash : bits256
  Record() = default;
  Record(Ref<CellSlice> _gas_used, Ref<CellSlice> _gas_limit, Ref<CellSlice> _gas_credit, int _mode, int _exit_code, Ref<CellSlice> _exit_arg, unsigned _vm_steps, const td::BitArray<256>& _vm_init_state_hash, const td::BitArray<256>& _vm_final_state_hash) : gas_used(std::move(_gas_used)), gas_limit(std::move(_gas_limit)), gas_credit(std::move(_gas_credit)), mode(_mode), exit_code(_exit_code), exit_arg(std::move(_exit_arg)), vm_steps(_vm_steps), vm_init_state_hash(_vm_init_state_hash), vm_final_state_hash(_vm_final_state_hash) {}
};

extern const TrComputePhase_aux t_TrComputePhase_aux;

//
// headers for type `TrComputePhase`
//

struct TrComputePhase final : TLB_Complex {
  enum { tr_phase_compute_skipped, tr_phase_compute_vm };
  static constexpr int cons_len_exact = 1;
  struct Record_tr_phase_compute_skipped {
    typedef TrComputePhase type_class;
    char reason;  	// reason : ComputeSkipReason
    Record_tr_phase_compute_skipped() = default;
    Record_tr_phase_compute_skipped(char _reason) : reason(_reason) {}
  };
  struct Record_tr_phase_compute_vm;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_tr_phase_compute_skipped& data) const;
  bool unpack_tr_phase_compute_skipped(vm::CellSlice& cs, char& reason) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_tr_phase_compute_skipped& data) const;
  bool cell_unpack_tr_phase_compute_skipped(Ref<vm::Cell> cell_ref, char& reason) const;
  bool pack(vm::CellBuilder& cb, const Record_tr_phase_compute_skipped& data) const;
  bool pack_tr_phase_compute_skipped(vm::CellBuilder& cb, char reason) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_tr_phase_compute_skipped& data) const;
  bool cell_pack_tr_phase_compute_skipped(Ref<vm::Cell>& cell_ref, char reason) const;
  bool unpack(vm::CellSlice& cs, Record_tr_phase_compute_vm& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_tr_phase_compute_vm& data) const;
  bool pack(vm::CellBuilder& cb, const Record_tr_phase_compute_vm& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_tr_phase_compute_vm& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "TrComputePhase";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

struct TrComputePhase::Record_tr_phase_compute_vm {
  typedef TrComputePhase type_class;
  bool success;  	// success : Bool
  bool msg_state_used;  	// msg_state_used : Bool
  bool account_activated;  	// account_activated : Bool
  Ref<CellSlice> gas_fees;  	// gas_fees : Grams
  TrComputePhase_aux::Record r1;  	// ^[$_ gas_used:(VarUInteger 7) gas_limit:(VarUInteger 7) gas_credit:(Maybe (VarUInteger 3)) mode:int8 exit_code:int32 exit_arg:(Maybe int32) vm_steps:uint32 vm_init_state_hash:bits256 vm_final_state_hash:bits256 ]
  Record_tr_phase_compute_vm() = default;
  Record_tr_phase_compute_vm(bool _success, bool _msg_state_used, bool _account_activated, Ref<CellSlice> _gas_fees, const TrComputePhase_aux::Record& _r1) : success(_success), msg_state_used(_msg_state_used), account_activated(_account_activated), gas_fees(std::move(_gas_fees)), r1(_r1) {}
};

extern const TrComputePhase t_TrComputePhase;

//
// headers for type `ComputeSkipReason`
//

struct ComputeSkipReason final : TLB_Complex {
  enum { cskip_no_state, cskip_bad_state, cskip_no_gas };
  static constexpr int cons_len_exact = 2;
  struct Record_cskip_no_state {
    typedef ComputeSkipReason type_class;
  };
  struct Record_cskip_bad_state {
    typedef ComputeSkipReason type_class;
  };
  struct Record_cskip_no_gas {
    typedef ComputeSkipReason type_class;
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 2;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(2);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool fetch_enum_to(vm::CellSlice& cs, char& value) const;
  bool store_enum_from(vm::CellBuilder& cb, int value) const;
  bool unpack(vm::CellSlice& cs, Record_cskip_no_state& data) const;
  bool unpack_cskip_no_state(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cskip_no_state& data) const;
  bool cell_unpack_cskip_no_state(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_cskip_no_state& data) const;
  bool pack_cskip_no_state(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cskip_no_state& data) const;
  bool cell_pack_cskip_no_state(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_cskip_bad_state& data) const;
  bool unpack_cskip_bad_state(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cskip_bad_state& data) const;
  bool cell_unpack_cskip_bad_state(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_cskip_bad_state& data) const;
  bool pack_cskip_bad_state(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cskip_bad_state& data) const;
  bool cell_pack_cskip_bad_state(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_cskip_no_gas& data) const;
  bool unpack_cskip_no_gas(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cskip_no_gas& data) const;
  bool cell_unpack_cskip_no_gas(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_cskip_no_gas& data) const;
  bool pack_cskip_no_gas(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cskip_no_gas& data) const;
  bool cell_pack_cskip_no_gas(Ref<vm::Cell>& cell_ref) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ComputeSkipReason";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(2, 7);
  }
};

extern const ComputeSkipReason t_ComputeSkipReason;

//
// headers for type `TrActionPhase`
//

struct TrActionPhase final : TLB_Complex {
  enum { tr_phase_action };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "TrActionPhase";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct TrActionPhase::Record {
  typedef TrActionPhase type_class;
  bool success;  	// success : Bool
  bool valid;  	// valid : Bool
  bool no_funds;  	// no_funds : Bool
  char status_change;  	// status_change : AccStatusChange
  Ref<CellSlice> total_fwd_fees;  	// total_fwd_fees : Maybe Grams
  Ref<CellSlice> total_action_fees;  	// total_action_fees : Maybe Grams
  int result_code;  	// result_code : int32
  Ref<CellSlice> result_arg;  	// result_arg : Maybe int32
  int tot_actions;  	// tot_actions : uint16
  int spec_actions;  	// spec_actions : uint16
  int skipped_actions;  	// skipped_actions : uint16
  int msgs_created;  	// msgs_created : uint16
  td::BitArray<256> action_list_hash;  	// action_list_hash : bits256
  Ref<CellSlice> tot_msg_size;  	// tot_msg_size : StorageUsedShort
  Record() = default;
  Record(bool _success, bool _valid, bool _no_funds, char _status_change, Ref<CellSlice> _total_fwd_fees, Ref<CellSlice> _total_action_fees, int _result_code, Ref<CellSlice> _result_arg, int _tot_actions, int _spec_actions, int _skipped_actions, int _msgs_created, const td::BitArray<256>& _action_list_hash, Ref<CellSlice> _tot_msg_size) : success(_success), valid(_valid), no_funds(_no_funds), status_change(_status_change), total_fwd_fees(std::move(_total_fwd_fees)), total_action_fees(std::move(_total_action_fees)), result_code(_result_code), result_arg(std::move(_result_arg)), tot_actions(_tot_actions), spec_actions(_spec_actions), skipped_actions(_skipped_actions), msgs_created(_msgs_created), action_list_hash(_action_list_hash), tot_msg_size(std::move(_tot_msg_size)) {}
};

extern const TrActionPhase t_TrActionPhase;

//
// headers for type `TrBouncePhase`
//

struct TrBouncePhase final : TLB_Complex {
  enum { tr_phase_bounce_negfunds, tr_phase_bounce_nofunds, tr_phase_bounce_ok };
  static constexpr char cons_len[3] = { 2, 2, 1 };
  static constexpr unsigned char cons_tag[3] = { 0, 1, 1 };
  struct Record_tr_phase_bounce_negfunds {
    typedef TrBouncePhase type_class;
  };
  struct Record_tr_phase_bounce_nofunds {
    typedef TrBouncePhase type_class;
    Ref<CellSlice> msg_size;  	// msg_size : StorageUsedShort
    Ref<CellSlice> req_fwd_fees;  	// req_fwd_fees : Grams
    Record_tr_phase_bounce_nofunds() = default;
    Record_tr_phase_bounce_nofunds(Ref<CellSlice> _msg_size, Ref<CellSlice> _req_fwd_fees) : msg_size(std::move(_msg_size)), req_fwd_fees(std::move(_req_fwd_fees)) {}
  };
  struct Record_tr_phase_bounce_ok;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_tr_phase_bounce_negfunds& data) const;
  bool unpack_tr_phase_bounce_negfunds(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_tr_phase_bounce_negfunds& data) const;
  bool cell_unpack_tr_phase_bounce_negfunds(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_tr_phase_bounce_negfunds& data) const;
  bool pack_tr_phase_bounce_negfunds(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_tr_phase_bounce_negfunds& data) const;
  bool cell_pack_tr_phase_bounce_negfunds(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_tr_phase_bounce_nofunds& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_tr_phase_bounce_nofunds& data) const;
  bool pack(vm::CellBuilder& cb, const Record_tr_phase_bounce_nofunds& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_tr_phase_bounce_nofunds& data) const;
  bool unpack(vm::CellSlice& cs, Record_tr_phase_bounce_ok& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_tr_phase_bounce_ok& data) const;
  bool pack(vm::CellBuilder& cb, const Record_tr_phase_bounce_ok& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_tr_phase_bounce_ok& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "TrBouncePhase";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect_ext(2, 7);
  }
};

struct TrBouncePhase::Record_tr_phase_bounce_ok {
  typedef TrBouncePhase type_class;
  Ref<CellSlice> msg_size;  	// msg_size : StorageUsedShort
  Ref<CellSlice> msg_fees;  	// msg_fees : Grams
  Ref<CellSlice> fwd_fees;  	// fwd_fees : Grams
  Record_tr_phase_bounce_ok() = default;
  Record_tr_phase_bounce_ok(Ref<CellSlice> _msg_size, Ref<CellSlice> _msg_fees, Ref<CellSlice> _fwd_fees) : msg_size(std::move(_msg_size)), msg_fees(std::move(_msg_fees)), fwd_fees(std::move(_fwd_fees)) {}
};

extern const TrBouncePhase t_TrBouncePhase;

//
// headers for type `SplitMergeInfo`
//

struct SplitMergeInfo final : TLB_Complex {
  enum { split_merge_info };
  static constexpr int cons_len_exact = 0;
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 524;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(524);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(524);
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "SplitMergeInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct SplitMergeInfo::Record {
  typedef SplitMergeInfo type_class;
  int cur_shard_pfx_len;  	// cur_shard_pfx_len : ## 6
  int acc_split_depth;  	// acc_split_depth : ## 6
  td::BitArray<256> this_addr;  	// this_addr : bits256
  td::BitArray<256> sibling_addr;  	// sibling_addr : bits256
  Record() = default;
  Record(int _cur_shard_pfx_len, int _acc_split_depth, const td::BitArray<256>& _this_addr, const td::BitArray<256>& _sibling_addr) : cur_shard_pfx_len(_cur_shard_pfx_len), acc_split_depth(_acc_split_depth), this_addr(_this_addr), sibling_addr(_sibling_addr) {}
};

extern const SplitMergeInfo t_SplitMergeInfo;

//
// headers for type `TransactionDescr`
//

struct TransactionDescr final : TLB_Complex {
  enum { trans_ord, trans_storage, trans_tick_tock, trans_split_prepare, trans_split_install, trans_merge_prepare, trans_merge_install };
  static constexpr char cons_len[7] = { 4, 4, 3, 4, 4, 4, 4 };
  static constexpr unsigned char cons_tag[7] = { 0, 1, 1, 4, 5, 6, 7 };
  struct Record_trans_ord;
  struct Record_trans_storage {
    typedef TransactionDescr type_class;
    Ref<CellSlice> storage_ph;  	// storage_ph : TrStoragePhase
    Record_trans_storage() = default;
    Record_trans_storage(Ref<CellSlice> _storage_ph) : storage_ph(std::move(_storage_ph)) {}
  };
  struct Record_trans_tick_tock;
  struct Record_trans_split_prepare;
  struct Record_trans_split_install;
  struct Record_trans_merge_prepare;
  struct Record_trans_merge_install;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_trans_ord& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_trans_ord& data) const;
  bool pack(vm::CellBuilder& cb, const Record_trans_ord& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_trans_ord& data) const;
  bool unpack(vm::CellSlice& cs, Record_trans_storage& data) const;
  bool unpack_trans_storage(vm::CellSlice& cs, Ref<CellSlice>& storage_ph) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_trans_storage& data) const;
  bool cell_unpack_trans_storage(Ref<vm::Cell> cell_ref, Ref<CellSlice>& storage_ph) const;
  bool pack(vm::CellBuilder& cb, const Record_trans_storage& data) const;
  bool pack_trans_storage(vm::CellBuilder& cb, Ref<CellSlice> storage_ph) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_trans_storage& data) const;
  bool cell_pack_trans_storage(Ref<vm::Cell>& cell_ref, Ref<CellSlice> storage_ph) const;
  bool unpack(vm::CellSlice& cs, Record_trans_tick_tock& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_trans_tick_tock& data) const;
  bool pack(vm::CellBuilder& cb, const Record_trans_tick_tock& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_trans_tick_tock& data) const;
  bool unpack(vm::CellSlice& cs, Record_trans_split_prepare& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_trans_split_prepare& data) const;
  bool pack(vm::CellBuilder& cb, const Record_trans_split_prepare& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_trans_split_prepare& data) const;
  bool unpack(vm::CellSlice& cs, Record_trans_split_install& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_trans_split_install& data) const;
  bool pack(vm::CellBuilder& cb, const Record_trans_split_install& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_trans_split_install& data) const;
  bool unpack(vm::CellSlice& cs, Record_trans_merge_prepare& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_trans_merge_prepare& data) const;
  bool pack(vm::CellBuilder& cb, const Record_trans_merge_prepare& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_trans_merge_prepare& data) const;
  bool unpack(vm::CellSlice& cs, Record_trans_merge_install& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_trans_merge_install& data) const;
  bool pack(vm::CellBuilder& cb, const Record_trans_merge_install& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_trans_merge_install& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "TransactionDescr";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(4, 0xf7);
  }
};

struct TransactionDescr::Record_trans_ord {
  typedef TransactionDescr type_class;
  bool credit_first;  	// credit_first : Bool
  Ref<CellSlice> storage_ph;  	// storage_ph : Maybe TrStoragePhase
  Ref<CellSlice> credit_ph;  	// credit_ph : Maybe TrCreditPhase
  Ref<CellSlice> compute_ph;  	// compute_ph : TrComputePhase
  Ref<CellSlice> action;  	// action : Maybe ^TrActionPhase
  bool aborted;  	// aborted : Bool
  Ref<CellSlice> bounce;  	// bounce : Maybe TrBouncePhase
  bool destroyed;  	// destroyed : Bool
  Record_trans_ord() = default;
  Record_trans_ord(bool _credit_first, Ref<CellSlice> _storage_ph, Ref<CellSlice> _credit_ph, Ref<CellSlice> _compute_ph, Ref<CellSlice> _action, bool _aborted, Ref<CellSlice> _bounce, bool _destroyed) : credit_first(_credit_first), storage_ph(std::move(_storage_ph)), credit_ph(std::move(_credit_ph)), compute_ph(std::move(_compute_ph)), action(std::move(_action)), aborted(_aborted), bounce(std::move(_bounce)), destroyed(_destroyed) {}
};

struct TransactionDescr::Record_trans_tick_tock {
  typedef TransactionDescr type_class;
  bool is_tock;  	// is_tock : Bool
  Ref<CellSlice> storage;  	// storage : TrStoragePhase
  Ref<CellSlice> compute_ph;  	// compute_ph : TrComputePhase
  Ref<CellSlice> action;  	// action : Maybe ^TrActionPhase
  bool aborted;  	// aborted : Bool
  bool destroyed;  	// destroyed : Bool
  Record_trans_tick_tock() = default;
  Record_trans_tick_tock(bool _is_tock, Ref<CellSlice> _storage, Ref<CellSlice> _compute_ph, Ref<CellSlice> _action, bool _aborted, bool _destroyed) : is_tock(_is_tock), storage(std::move(_storage)), compute_ph(std::move(_compute_ph)), action(std::move(_action)), aborted(_aborted), destroyed(_destroyed) {}
};

struct TransactionDescr::Record_trans_split_prepare {
  typedef TransactionDescr type_class;
  Ref<CellSlice> split_info;  	// split_info : SplitMergeInfo
  Ref<CellSlice> compute_ph;  	// compute_ph : TrComputePhase
  Ref<CellSlice> action;  	// action : Maybe ^TrActionPhase
  bool aborted;  	// aborted : Bool
  bool destroyed;  	// destroyed : Bool
  Record_trans_split_prepare() = default;
  Record_trans_split_prepare(Ref<CellSlice> _split_info, Ref<CellSlice> _compute_ph, Ref<CellSlice> _action, bool _aborted, bool _destroyed) : split_info(std::move(_split_info)), compute_ph(std::move(_compute_ph)), action(std::move(_action)), aborted(_aborted), destroyed(_destroyed) {}
};

struct TransactionDescr::Record_trans_split_install {
  typedef TransactionDescr type_class;
  Ref<CellSlice> split_info;  	// split_info : SplitMergeInfo
  Ref<Cell> prepare_transaction;  	// prepare_transaction : ^Transaction
  bool installed;  	// installed : Bool
  Record_trans_split_install() = default;
  Record_trans_split_install(Ref<CellSlice> _split_info, Ref<Cell> _prepare_transaction, bool _installed) : split_info(std::move(_split_info)), prepare_transaction(std::move(_prepare_transaction)), installed(_installed) {}
};

struct TransactionDescr::Record_trans_merge_prepare {
  typedef TransactionDescr type_class;
  Ref<CellSlice> split_info;  	// split_info : SplitMergeInfo
  Ref<CellSlice> storage_ph;  	// storage_ph : TrStoragePhase
  bool aborted;  	// aborted : Bool
  Record_trans_merge_prepare() = default;
  Record_trans_merge_prepare(Ref<CellSlice> _split_info, Ref<CellSlice> _storage_ph, bool _aborted) : split_info(std::move(_split_info)), storage_ph(std::move(_storage_ph)), aborted(_aborted) {}
};

struct TransactionDescr::Record_trans_merge_install {
  typedef TransactionDescr type_class;
  Ref<CellSlice> split_info;  	// split_info : SplitMergeInfo
  Ref<Cell> prepare_transaction;  	// prepare_transaction : ^Transaction
  Ref<CellSlice> credit_ph;  	// credit_ph : Maybe TrCreditPhase
  Ref<CellSlice> compute_ph;  	// compute_ph : TrComputePhase
  Ref<CellSlice> action;  	// action : Maybe ^TrActionPhase
  bool aborted;  	// aborted : Bool
  bool destroyed;  	// destroyed : Bool
  Record_trans_merge_install() = default;
  Record_trans_merge_install(Ref<CellSlice> _split_info, Ref<Cell> _prepare_transaction, Ref<CellSlice> _credit_ph, Ref<CellSlice> _compute_ph, Ref<CellSlice> _action, bool _aborted, bool _destroyed) : split_info(std::move(_split_info)), prepare_transaction(std::move(_prepare_transaction)), credit_ph(std::move(_credit_ph)), compute_ph(std::move(_compute_ph)), action(std::move(_action)), aborted(_aborted), destroyed(_destroyed) {}
};

extern const TransactionDescr t_TransactionDescr;

//
// headers for type `SmartContractInfo`
//

struct SmartContractInfo final : TLB_Complex {
  enum { smc_info };
  static constexpr int cons_len_exact = 32;
  static constexpr unsigned cons_tag[1] = { 0x76ef1ea };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "SmartContractInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct SmartContractInfo::Record {
  typedef SmartContractInfo type_class;
  int actions;  	// actions : uint16
  int msgs_sent;  	// msgs_sent : uint16
  unsigned unixtime;  	// unixtime : uint32
  unsigned long long block_lt;  	// block_lt : uint64
  unsigned long long trans_lt;  	// trans_lt : uint64
  td::BitArray<256> rand_seed;  	// rand_seed : bits256
  Ref<CellSlice> balance_remaining;  	// balance_remaining : CurrencyCollection
  Ref<CellSlice> myself;  	// myself : MsgAddressInt
  Record() = default;
  Record(int _actions, int _msgs_sent, unsigned _unixtime, unsigned long long _block_lt, unsigned long long _trans_lt, const td::BitArray<256>& _rand_seed, Ref<CellSlice> _balance_remaining, Ref<CellSlice> _myself) : actions(_actions), msgs_sent(_msgs_sent), unixtime(_unixtime), block_lt(_block_lt), trans_lt(_trans_lt), rand_seed(_rand_seed), balance_remaining(std::move(_balance_remaining)), myself(std::move(_myself)) {}
};

extern const SmartContractInfo t_SmartContractInfo;

//
// headers for type `OutList`
//

struct OutList final : TLB_Complex {
  enum { out_list, out_list_empty };
  static constexpr int cons_len_exact = 0;
  int m;
  OutList(int _m) : m(_m) {}
  struct Record_out_list_empty {
    typedef OutList type_class;
  };
  struct Record_out_list;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_out_list_empty& data) const;
  bool unpack_out_list_empty(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_out_list_empty& data) const;
  bool cell_unpack_out_list_empty(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_out_list_empty& data) const;
  bool pack_out_list_empty(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_out_list_empty& data) const;
  bool cell_pack_out_list_empty(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_out_list& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_out_list& data) const;
  bool pack(vm::CellBuilder& cb, const Record_out_list& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_out_list& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(OutList " << m << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override;
};

struct OutList::Record_out_list {
  typedef OutList type_class;
  int n;  	// n : #
  Ref<Cell> prev;  	// prev : ^(OutList n)
  Ref<CellSlice> action;  	// action : OutAction
  Record_out_list() = default;
  Record_out_list(Ref<Cell> _prev, Ref<CellSlice> _action) : n(-1), prev(std::move(_prev)), action(std::move(_action)) {}
};

//
// headers for type `OutAction`
//

struct OutAction final : TLB_Complex {
  enum { action_send_msg, action_reserve_currency, action_set_code };
  static constexpr int cons_len_exact = 32;
  static constexpr unsigned cons_tag[3] = { 0xec3c86d, 0x36e6b809, 0xad4de08eU };
  struct Record_action_send_msg {
    typedef OutAction type_class;
    int mode;  	// mode : ## 8
    Ref<Cell> out_msg;  	// out_msg : ^(MessageRelaxed Any)
    Record_action_send_msg() = default;
    Record_action_send_msg(int _mode, Ref<Cell> _out_msg) : mode(_mode), out_msg(std::move(_out_msg)) {}
  };
  struct Record_action_set_code {
    typedef OutAction type_class;
    Ref<Cell> new_code;  	// new_code : ^Cell
    Record_action_set_code() = default;
    Record_action_set_code(Ref<Cell> _new_code) : new_code(std::move(_new_code)) {}
  };
  struct Record_action_reserve_currency {
    typedef OutAction type_class;
    int mode;  	// mode : ## 8
    Ref<CellSlice> currency;  	// currency : CurrencyCollection
    Record_action_reserve_currency() = default;
    Record_action_reserve_currency(int _mode, Ref<CellSlice> _currency) : mode(_mode), currency(std::move(_currency)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_action_send_msg& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_action_send_msg& data) const;
  bool pack(vm::CellBuilder& cb, const Record_action_send_msg& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_action_send_msg& data) const;
  bool unpack(vm::CellSlice& cs, Record_action_set_code& data) const;
  bool unpack_action_set_code(vm::CellSlice& cs, Ref<Cell>& new_code) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_action_set_code& data) const;
  bool cell_unpack_action_set_code(Ref<vm::Cell> cell_ref, Ref<Cell>& new_code) const;
  bool pack(vm::CellBuilder& cb, const Record_action_set_code& data) const;
  bool pack_action_set_code(vm::CellBuilder& cb, Ref<Cell> new_code) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_action_set_code& data) const;
  bool cell_pack_action_set_code(Ref<vm::Cell>& cell_ref, Ref<Cell> new_code) const;
  bool unpack(vm::CellSlice& cs, Record_action_reserve_currency& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_action_reserve_currency& data) const;
  bool pack(vm::CellBuilder& cb, const Record_action_reserve_currency& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_action_reserve_currency& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "OutAction";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(3, 0x23);
  }
};

extern const OutAction t_OutAction;

//
// headers for type `OutListNode`
//

struct OutListNode final : TLB_Complex {
  enum { out_list_node };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef OutListNode type_class;
    Ref<Cell> prev;  	// prev : ^Cell
    Ref<CellSlice> action;  	// action : OutAction
    Record() = default;
    Record(Ref<Cell> _prev, Ref<CellSlice> _action) : prev(std::move(_prev)), action(std::move(_action)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "OutListNode";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const OutListNode t_OutListNode;

//
// headers for type `ShardIdent`
//

struct ShardIdent final : TLB_Complex {
  enum { shard_ident };
  static constexpr int cons_len_exact = 2;
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 104;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(104);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ShardIdent";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ShardIdent::Record {
  typedef ShardIdent type_class;
  int shard_pfx_bits;  	// shard_pfx_bits : #<= 60
  int workchain_id;  	// workchain_id : int32
  unsigned long long shard_prefix;  	// shard_prefix : uint64
  Record() = default;
  Record(int _shard_pfx_bits, int _workchain_id, unsigned long long _shard_prefix) : shard_pfx_bits(_shard_pfx_bits), workchain_id(_workchain_id), shard_prefix(_shard_prefix) {}
};

extern const ShardIdent t_ShardIdent;

//
// headers for type `ExtBlkRef`
//

struct ExtBlkRef final : TLB_Complex {
  enum { ext_blk_ref };
  static constexpr int cons_len_exact = 0;
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 608;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(608);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(608);
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ExtBlkRef";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ExtBlkRef::Record {
  typedef ExtBlkRef type_class;
  unsigned long long end_lt;  	// end_lt : uint64
  unsigned seq_no;  	// seq_no : uint32
  td::BitArray<256> root_hash;  	// root_hash : bits256
  td::BitArray<256> file_hash;  	// file_hash : bits256
  Record() = default;
  Record(unsigned long long _end_lt, unsigned _seq_no, const td::BitArray<256>& _root_hash, const td::BitArray<256>& _file_hash) : end_lt(_end_lt), seq_no(_seq_no), root_hash(_root_hash), file_hash(_file_hash) {}
};

extern const ExtBlkRef t_ExtBlkRef;

//
// headers for type `BlockIdExt`
//

struct BlockIdExt final : TLB_Complex {
  enum { block_id_ext };
  static constexpr int cons_len_exact = 0;
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 648;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(648);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "BlockIdExt";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct BlockIdExt::Record {
  typedef BlockIdExt type_class;
  Ref<CellSlice> shard_id;  	// shard_id : ShardIdent
  unsigned seq_no;  	// seq_no : uint32
  td::BitArray<256> root_hash;  	// root_hash : bits256
  td::BitArray<256> file_hash;  	// file_hash : bits256
  Record() = default;
  Record(Ref<CellSlice> _shard_id, unsigned _seq_no, const td::BitArray<256>& _root_hash, const td::BitArray<256>& _file_hash) : shard_id(std::move(_shard_id)), seq_no(_seq_no), root_hash(_root_hash), file_hash(_file_hash) {}
};

extern const BlockIdExt t_BlockIdExt;

//
// headers for type `BlkMasterInfo`
//

struct BlkMasterInfo final : TLB_Complex {
  enum { master_info };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef BlkMasterInfo type_class;
    Ref<CellSlice> master;  	// master : ExtBlkRef
    Record() = default;
    Record(Ref<CellSlice> _master) : master(std::move(_master)) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 608;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(608);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(608);
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_master_info(vm::CellSlice& cs, Ref<CellSlice>& master) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_master_info(Ref<vm::Cell> cell_ref, Ref<CellSlice>& master) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_master_info(vm::CellBuilder& cb, Ref<CellSlice> master) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_master_info(Ref<vm::Cell>& cell_ref, Ref<CellSlice> master) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "BlkMasterInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const BlkMasterInfo t_BlkMasterInfo;

//
// headers for auxiliary type `ShardStateUnsplit_aux`
//

struct ShardStateUnsplit_aux final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ShardStateUnsplit_aux";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ShardStateUnsplit_aux::Record {
  typedef ShardStateUnsplit_aux type_class;
  Ref<CellSlice> total_balance;  	// total_balance : CurrencyCollection
  Ref<CellSlice> total_validator_fees;  	// total_validator_fees : CurrencyCollection
  Ref<CellSlice> libraries;  	// libraries : HashmapE 256 LibDescr
  Record() = default;
  Record(Ref<CellSlice> _total_balance, Ref<CellSlice> _total_validator_fees, Ref<CellSlice> _libraries) : total_balance(std::move(_total_balance)), total_validator_fees(std::move(_total_validator_fees)), libraries(std::move(_libraries)) {}
};

extern const ShardStateUnsplit_aux t_ShardStateUnsplit_aux;

//
// headers for type `ShardStateUnsplit`
//

struct ShardStateUnsplit final : TLB_Complex {
  enum { shard_state };
  static constexpr int cons_len_exact = 32;
  static constexpr unsigned cons_tag[1] = { 0x9023afdeU };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ShardStateUnsplit";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ShardStateUnsplit::Record {
  typedef ShardStateUnsplit type_class;
  int global_id;  	// global_id : int32
  Ref<CellSlice> shard_id;  	// shard_id : ShardIdent
  unsigned seq_no;  	// seq_no : uint32
  int vert_seq_no;  	// vert_seq_no : #
  unsigned gen_utime;  	// gen_utime : uint32
  unsigned long long gen_lt;  	// gen_lt : uint64
  Ref<Cell> out_msg_queue_info;  	// out_msg_queue_info : ^OutMsgQueueInfo
  bool before_split;  	// before_split : ## 1
  Ref<CellSlice> accounts;  	// accounts : ShardAccounts
  ShardStateUnsplit_aux::Record r1;  	// ^[$_ total_balance:CurrencyCollection total_validator_fees:CurrencyCollection libraries:(HashmapE 256 LibDescr) ]
  Ref<CellSlice> master_ref;  	// master_ref : Maybe BlkMasterInfo
  Ref<CellSlice> custom;  	// custom : Maybe ^McStateExtra
  Record() = default;
  Record(int _global_id, Ref<CellSlice> _shard_id, unsigned _seq_no, int _vert_seq_no, unsigned _gen_utime, unsigned long long _gen_lt, Ref<Cell> _out_msg_queue_info, bool _before_split, Ref<CellSlice> _accounts, const ShardStateUnsplit_aux::Record& _r1, Ref<CellSlice> _master_ref, Ref<CellSlice> _custom) : global_id(_global_id), shard_id(std::move(_shard_id)), seq_no(_seq_no), vert_seq_no(_vert_seq_no), gen_utime(_gen_utime), gen_lt(_gen_lt), out_msg_queue_info(std::move(_out_msg_queue_info)), before_split(_before_split), accounts(std::move(_accounts)), r1(_r1), master_ref(std::move(_master_ref)), custom(std::move(_custom)) {}
};

extern const ShardStateUnsplit t_ShardStateUnsplit;

//
// headers for type `ShardState`
//

struct ShardState final : TLB_Complex {
  enum { split_state, cons1 };
  static constexpr char cons_len[2] = { 32, 0 };
  static constexpr unsigned cons_tag[2] = { 0x5f327da5, 0 };
  struct Record_cons1 {
    typedef ShardState type_class;
    Ref<CellSlice> x;  	// ShardStateUnsplit
    Record_cons1() = default;
    Record_cons1(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  struct Record_split_state {
    typedef ShardState type_class;
    Ref<Cell> left;  	// left : ^ShardStateUnsplit
    Ref<Cell> right;  	// right : ^ShardStateUnsplit
    Record_split_state() = default;
    Record_split_state(Ref<Cell> _left, Ref<Cell> _right) : left(std::move(_left)), right(std::move(_right)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_cons1& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons1& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_cons1& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons1& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool unpack(vm::CellSlice& cs, Record_split_state& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_split_state& data) const;
  bool pack(vm::CellBuilder& cb, const Record_split_state& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_split_state& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ShardState";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

extern const ShardState t_ShardState;

//
// headers for type `LibDescr`
//

struct LibDescr final : TLB_Complex {
  enum { shared_lib_descr };
  static constexpr int cons_len_exact = 2;
  struct Record {
    typedef LibDescr type_class;
    Ref<Cell> lib;  	// lib : ^Cell
    Ref<CellSlice> publishers;  	// publishers : Hashmap 256 True
    Record() = default;
    Record(Ref<Cell> _lib, Ref<CellSlice> _publishers) : lib(std::move(_lib)), publishers(std::move(_publishers)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "LibDescr";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const LibDescr t_LibDescr;

//
// headers for type `BlockInfo`
//

struct BlockInfo final : TLB_Complex {
  enum { block_info };
  static constexpr int cons_len_exact = 32;
  static constexpr unsigned cons_tag[1] = { 0x9bc7a986U };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "BlockInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct BlockInfo::Record {
  typedef BlockInfo type_class;
  unsigned version;  	// version : uint32
  bool not_master;  	// not_master : ## 1
  bool after_merge;  	// after_merge : ## 1
  bool before_split;  	// before_split : ## 1
  bool after_split;  	// after_split : ## 1
  bool want_split;  	// want_split : Bool
  bool want_merge;  	// want_merge : Bool
  int flags;  	// flags : ## 10
  int seq_no;  	// seq_no : #
  int vert_seq_no;  	// vert_seq_no : #
  Ref<CellSlice> shard;  	// shard : ShardIdent
  unsigned gen_utime;  	// gen_utime : uint32
  unsigned long long start_lt;  	// start_lt : uint64
  unsigned long long end_lt;  	// end_lt : uint64
  unsigned gen_validator_list_hash_short;  	// gen_validator_list_hash_short : uint32
  unsigned gen_catchain_seqno;  	// gen_catchain_seqno : uint32
  Ref<Cell> master_ref;  	// master_ref : not_master?^BlkMasterInfo
  Ref<Cell> prev_ref;  	// prev_ref : ^(BlkPrevInfo after_merge)
  Ref<Cell> prev_vert_ref;  	// prev_vert_ref : vert_seq_no?^(BlkPrevInfo 0)
  Record() = default;
  Record(unsigned _version, bool _not_master, bool _after_merge, bool _before_split, bool _after_split, bool _want_split, bool _want_merge, int _flags, int _seq_no, int _vert_seq_no, Ref<CellSlice> _shard, unsigned _gen_utime, unsigned long long _start_lt, unsigned long long _end_lt, unsigned _gen_validator_list_hash_short, unsigned _gen_catchain_seqno, Ref<Cell> _master_ref, Ref<Cell> _prev_ref, Ref<Cell> _prev_vert_ref) : version(_version), not_master(_not_master), after_merge(_after_merge), before_split(_before_split), after_split(_after_split), want_split(_want_split), want_merge(_want_merge), flags(_flags), seq_no(_seq_no), vert_seq_no(_vert_seq_no), shard(std::move(_shard)), gen_utime(_gen_utime), start_lt(_start_lt), end_lt(_end_lt), gen_validator_list_hash_short(_gen_validator_list_hash_short), gen_catchain_seqno(_gen_catchain_seqno), master_ref(std::move(_master_ref)), prev_ref(std::move(_prev_ref)), prev_vert_ref(std::move(_prev_vert_ref)) {}
};

extern const BlockInfo t_BlockInfo;

//
// headers for type `BlkPrevInfo`
//

struct BlkPrevInfo final : TLB_Complex {
  enum { prev_blk_info };
  static constexpr int cons_len_exact = 0;
  int m;
  BlkPrevInfo(int _m) : m(_m) {}
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(BlkPrevInfo " << m << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct BlkPrevInfo::Record {
  typedef BlkPrevInfo type_class;
  int merged;  	// merged : #
  Ref<CellSlice> prev;  	// prev : ExtBlkRef
  Ref<CellSlice> prev_alt;  	// prev_alt : merged?ExtBlkRef
  Record() = default;
  Record(Ref<CellSlice> _prev, Ref<CellSlice> _prev_alt) : merged(-1), prev(std::move(_prev)), prev_alt(std::move(_prev_alt)) {}
};

//
// headers for type `Block`
//

struct Block final : TLB_Complex {
  enum { block };
  static constexpr int cons_len_exact = 32;
  static constexpr unsigned cons_tag[1] = { 0x11ef55aa };
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 0x40040;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance_ext(0x40040);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "Block";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct Block::Record {
  typedef Block type_class;
  int global_id;  	// global_id : int32
  Ref<Cell> info;  	// info : ^BlockInfo
  Ref<Cell> value_flow;  	// value_flow : ^ValueFlow
  Ref<Cell> state_update;  	// state_update : ^(MERKLE_UPDATE ShardState)
  Ref<Cell> extra;  	// extra : ^BlockExtra
  Record() = default;
  Record(int _global_id, Ref<Cell> _info, Ref<Cell> _value_flow, Ref<Cell> _state_update, Ref<Cell> _extra) : global_id(_global_id), info(std::move(_info)), value_flow(std::move(_value_flow)), state_update(std::move(_state_update)), extra(std::move(_extra)) {}
};

extern const Block t_Block;

//
// headers for type `BlockExtra`
//

struct BlockExtra final : TLB_Complex {
  enum { block_extra };
  static constexpr int cons_len_exact = 32;
  static constexpr unsigned cons_tag[1] = { 0xa8929555U };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "BlockExtra";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct BlockExtra::Record {
  typedef BlockExtra type_class;
  Ref<Cell> in_msg_descr;  	// in_msg_descr : ^InMsgDescr
  Ref<Cell> out_msg_descr;  	// out_msg_descr : ^OutMsgDescr
  Ref<CellSlice> account_blocks;  	// account_blocks : ShardAccountBlocks
  td::BitArray<256> rand_seed;  	// rand_seed : bits256
  Ref<CellSlice> custom;  	// custom : Maybe ^McBlockExtra
  Record() = default;
  Record(Ref<Cell> _in_msg_descr, Ref<Cell> _out_msg_descr, Ref<CellSlice> _account_blocks, const td::BitArray<256>& _rand_seed, Ref<CellSlice> _custom) : in_msg_descr(std::move(_in_msg_descr)), out_msg_descr(std::move(_out_msg_descr)), account_blocks(std::move(_account_blocks)), rand_seed(_rand_seed), custom(std::move(_custom)) {}
};

extern const BlockExtra t_BlockExtra;

//
// headers for auxiliary type `ValueFlow_aux`
//

struct ValueFlow_aux final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ValueFlow_aux";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ValueFlow_aux::Record {
  typedef ValueFlow_aux type_class;
  Ref<CellSlice> from_prev_blk;  	// from_prev_blk : CurrencyCollection
  Ref<CellSlice> to_next_blk;  	// to_next_blk : CurrencyCollection
  Ref<CellSlice> imported;  	// imported : CurrencyCollection
  Ref<CellSlice> exported;  	// exported : CurrencyCollection
  Record() = default;
  Record(Ref<CellSlice> _from_prev_blk, Ref<CellSlice> _to_next_blk, Ref<CellSlice> _imported, Ref<CellSlice> _exported) : from_prev_blk(std::move(_from_prev_blk)), to_next_blk(std::move(_to_next_blk)), imported(std::move(_imported)), exported(std::move(_exported)) {}
};

extern const ValueFlow_aux t_ValueFlow_aux;

//
// headers for auxiliary type `ValueFlow_aux1`
//

struct ValueFlow_aux1 final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ValueFlow_aux1";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ValueFlow_aux1::Record {
  typedef ValueFlow_aux1 type_class;
  Ref<CellSlice> fees_imported;  	// fees_imported : CurrencyCollection
  Ref<CellSlice> created;  	// created : CurrencyCollection
  Ref<CellSlice> minted;  	// minted : CurrencyCollection
  Record() = default;
  Record(Ref<CellSlice> _fees_imported, Ref<CellSlice> _created, Ref<CellSlice> _minted) : fees_imported(std::move(_fees_imported)), created(std::move(_created)), minted(std::move(_minted)) {}
};

extern const ValueFlow_aux1 t_ValueFlow_aux1;

//
// headers for type `ValueFlow`
//

struct ValueFlow final : TLB_Complex {
  enum { value_flow };
  static constexpr int cons_len_exact = 32;
  static constexpr unsigned cons_tag[1] = { 0x3fde65c8 };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ValueFlow";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ValueFlow::Record {
  typedef ValueFlow type_class;
  ValueFlow_aux::Record r1;  	// ^[$_ from_prev_blk:CurrencyCollection to_next_blk:CurrencyCollection imported:CurrencyCollection exported:CurrencyCollection ]
  Ref<CellSlice> fees_collected;  	// fees_collected : CurrencyCollection
  ValueFlow_aux1::Record r2;  	// ^[$_ fees_imported:CurrencyCollection created:CurrencyCollection minted:CurrencyCollection ]
  Record() = default;
  Record(const ValueFlow_aux::Record& _r1, Ref<CellSlice> _fees_collected, const ValueFlow_aux1::Record& _r2) : r1(_r1), fees_collected(std::move(_fees_collected)), r2(_r2) {}
};

extern const ValueFlow t_ValueFlow;

//
// headers for type `BinTree`
//

struct BinTree final : TLB_Complex {
  enum { bt_leaf, bt_fork };
  static constexpr int cons_len_exact = 1;
  const TLB &X;
  BinTree(const TLB& _X) : X(_X) {}
  struct Record_bt_leaf {
    typedef BinTree type_class;
    Ref<CellSlice> leaf;  	// leaf : X
    Record_bt_leaf() = default;
    Record_bt_leaf(Ref<CellSlice> _leaf) : leaf(std::move(_leaf)) {}
  };
  struct Record_bt_fork {
    typedef BinTree type_class;
    Ref<Cell> left;  	// left : ^(BinTree X)
    Ref<Cell> right;  	// right : ^(BinTree X)
    Record_bt_fork() = default;
    Record_bt_fork(Ref<Cell> _left, Ref<Cell> _right) : left(std::move(_left)), right(std::move(_right)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_bt_leaf& data) const;
  bool unpack_bt_leaf(vm::CellSlice& cs, Ref<CellSlice>& leaf) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_bt_leaf& data) const;
  bool cell_unpack_bt_leaf(Ref<vm::Cell> cell_ref, Ref<CellSlice>& leaf) const;
  bool pack(vm::CellBuilder& cb, const Record_bt_leaf& data) const;
  bool pack_bt_leaf(vm::CellBuilder& cb, Ref<CellSlice> leaf) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_bt_leaf& data) const;
  bool cell_pack_bt_leaf(Ref<vm::Cell>& cell_ref, Ref<CellSlice> leaf) const;
  bool unpack(vm::CellSlice& cs, Record_bt_fork& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_bt_fork& data) const;
  bool pack(vm::CellBuilder& cb, const Record_bt_fork& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_bt_fork& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(BinTree " << X << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

//
// headers for type `FutureSplitMerge`
//

struct FutureSplitMerge final : TLB_Complex {
  enum { fsm_none, fsm_split, fsm_merge };
  static constexpr char cons_len[3] = { 1, 2, 2 };
  static constexpr unsigned char cons_tag[3] = { 0, 2, 3 };
  struct Record_fsm_none {
    typedef FutureSplitMerge type_class;
  };
  struct Record_fsm_split {
    typedef FutureSplitMerge type_class;
    unsigned split_utime;  	// split_utime : uint32
    Record_fsm_split() = default;
    Record_fsm_split(unsigned _split_utime) : split_utime(_split_utime) {}
  };
  struct Record_fsm_merge {
    typedef FutureSplitMerge type_class;
    unsigned merge_utime;  	// merge_utime : uint32
    Record_fsm_merge() = default;
    Record_fsm_merge(unsigned _merge_utime) : merge_utime(_merge_utime) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_fsm_none& data) const;
  bool unpack_fsm_none(vm::CellSlice& cs) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_fsm_none& data) const;
  bool cell_unpack_fsm_none(Ref<vm::Cell> cell_ref) const;
  bool pack(vm::CellBuilder& cb, const Record_fsm_none& data) const;
  bool pack_fsm_none(vm::CellBuilder& cb) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_fsm_none& data) const;
  bool cell_pack_fsm_none(Ref<vm::Cell>& cell_ref) const;
  bool unpack(vm::CellSlice& cs, Record_fsm_split& data) const;
  bool unpack_fsm_split(vm::CellSlice& cs, unsigned& split_utime) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_fsm_split& data) const;
  bool cell_unpack_fsm_split(Ref<vm::Cell> cell_ref, unsigned& split_utime) const;
  bool pack(vm::CellBuilder& cb, const Record_fsm_split& data) const;
  bool pack_fsm_split(vm::CellBuilder& cb, unsigned split_utime) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_fsm_split& data) const;
  bool cell_pack_fsm_split(Ref<vm::Cell>& cell_ref, unsigned split_utime) const;
  bool unpack(vm::CellSlice& cs, Record_fsm_merge& data) const;
  bool unpack_fsm_merge(vm::CellSlice& cs, unsigned& merge_utime) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_fsm_merge& data) const;
  bool cell_unpack_fsm_merge(Ref<vm::Cell> cell_ref, unsigned& merge_utime) const;
  bool pack(vm::CellBuilder& cb, const Record_fsm_merge& data) const;
  bool pack_fsm_merge(vm::CellBuilder& cb, unsigned merge_utime) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_fsm_merge& data) const;
  bool cell_pack_fsm_merge(Ref<vm::Cell>& cell_ref, unsigned merge_utime) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "FutureSplitMerge";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect_ext(2, 13);
  }
};

extern const FutureSplitMerge t_FutureSplitMerge;

//
// headers for type `ShardDescr`
//

struct ShardDescr final : TLB_Complex {
  enum { shard_descr };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ShardDescr";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ShardDescr::Record {
  typedef ShardDescr type_class;
  unsigned seq_no;  	// seq_no : uint32
  unsigned long long start_lt;  	// start_lt : uint64
  unsigned long long end_lt;  	// end_lt : uint64
  td::BitArray<256> root_hash;  	// root_hash : bits256
  td::BitArray<256> file_hash;  	// file_hash : bits256
  bool before_split;  	// before_split : Bool
  bool before_merge;  	// before_merge : Bool
  bool want_split;  	// want_split : Bool
  bool want_merge;  	// want_merge : Bool
  bool nx_cc_updated;  	// nx_cc_updated : Bool
  int flags;  	// flags : ## 3
  unsigned next_catchain_seqno;  	// next_catchain_seqno : uint32
  unsigned long long next_validator_shard;  	// next_validator_shard : uint64
  Ref<CellSlice> split_merge_at;  	// split_merge_at : FutureSplitMerge
  Record() = default;
  Record(unsigned _seq_no, unsigned long long _start_lt, unsigned long long _end_lt, const td::BitArray<256>& _root_hash, const td::BitArray<256>& _file_hash, bool _before_split, bool _before_merge, bool _want_split, bool _want_merge, bool _nx_cc_updated, int _flags, unsigned _next_catchain_seqno, unsigned long long _next_validator_shard, Ref<CellSlice> _split_merge_at) : seq_no(_seq_no), start_lt(_start_lt), end_lt(_end_lt), root_hash(_root_hash), file_hash(_file_hash), before_split(_before_split), before_merge(_before_merge), want_split(_want_split), want_merge(_want_merge), nx_cc_updated(_nx_cc_updated), flags(_flags), next_catchain_seqno(_next_catchain_seqno), next_validator_shard(_next_validator_shard), split_merge_at(std::move(_split_merge_at)) {}
};

extern const ShardDescr t_ShardDescr;

//
// headers for type `ShardHashes`
//

struct ShardHashes final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ShardHashes type_class;
    Ref<CellSlice> x;  	// HashmapE 32 ^(BinTree ShardDescr)
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ShardHashes";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ShardHashes t_ShardHashes;

//
// headers for type `BinTreeAug`
//

struct BinTreeAug final : TLB_Complex {
  enum { bta_leaf, bta_fork };
  static constexpr int cons_len_exact = 1;
  const TLB &X, &Y;
  BinTreeAug(const TLB& _X, const TLB& _Y) : X(_X), Y(_Y) {}
  struct Record_bta_leaf {
    typedef BinTreeAug type_class;
    Ref<CellSlice> leaf;  	// leaf : X
    Ref<CellSlice> extra;  	// extra : Y
    Record_bta_leaf() = default;
    Record_bta_leaf(Ref<CellSlice> _leaf, Ref<CellSlice> _extra) : leaf(std::move(_leaf)), extra(std::move(_extra)) {}
  };
  struct Record_bta_fork;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_bta_leaf& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_bta_leaf& data) const;
  bool pack(vm::CellBuilder& cb, const Record_bta_leaf& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_bta_leaf& data) const;
  bool unpack(vm::CellSlice& cs, Record_bta_fork& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_bta_fork& data) const;
  bool pack(vm::CellBuilder& cb, const Record_bta_fork& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_bta_fork& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(BinTreeAug " << X << " " << Y << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return (int)cs.prefetch_ulong(1);
  }
};

struct BinTreeAug::Record_bta_fork {
  typedef BinTreeAug type_class;
  Ref<Cell> left;  	// left : ^(BinTreeAug X Y)
  Ref<Cell> right;  	// right : ^(BinTreeAug X Y)
  Ref<CellSlice> extra;  	// extra : Y
  Record_bta_fork() = default;
  Record_bta_fork(Ref<Cell> _left, Ref<Cell> _right, Ref<CellSlice> _extra) : left(std::move(_left)), right(std::move(_right)), extra(std::move(_extra)) {}
};

//
// headers for type `ShardFees`
//

struct ShardFees final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ShardFees type_class;
    Ref<CellSlice> x;  	// HashmapAugE 32 ^(BinTreeAug True CurrencyCollection) CurrencyCollection
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ShardFees";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ShardFees t_ShardFees;

//
// headers for type `ConfigParams`
//

struct ConfigParams final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ConfigParams type_class;
    td::BitArray<256> config_addr;  	// config_addr : bits256
    Ref<Cell> config;  	// config : ^(Hashmap 32 ^Cell)
    Record() = default;
    Record(const td::BitArray<256>& _config_addr, Ref<Cell> _config) : config_addr(_config_addr), config(std::move(_config)) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 0x10100;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance_ext(0x10100);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ConfigParams";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ConfigParams t_ConfigParams;

//
// headers for type `ValidatorInfo`
//

struct ValidatorInfo final : TLB_Complex {
  enum { validator_info };
  static constexpr int cons_len_exact = 0;
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 65;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(65);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(65);
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ValidatorInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ValidatorInfo::Record {
  typedef ValidatorInfo type_class;
  unsigned validator_list_hash_short;  	// validator_list_hash_short : uint32
  unsigned catchain_seqno;  	// catchain_seqno : uint32
  bool nx_cc_updated;  	// nx_cc_updated : Bool
  Record() = default;
  Record(unsigned _validator_list_hash_short, unsigned _catchain_seqno, bool _nx_cc_updated) : validator_list_hash_short(_validator_list_hash_short), catchain_seqno(_catchain_seqno), nx_cc_updated(_nx_cc_updated) {}
};

extern const ValidatorInfo t_ValidatorInfo;

//
// headers for type `ValidatorBaseInfo`
//

struct ValidatorBaseInfo final : TLB_Complex {
  enum { validator_base_info };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef ValidatorBaseInfo type_class;
    unsigned validator_list_hash_short;  	// validator_list_hash_short : uint32
    unsigned catchain_seqno;  	// catchain_seqno : uint32
    Record() = default;
    Record(unsigned _validator_list_hash_short, unsigned _catchain_seqno) : validator_list_hash_short(_validator_list_hash_short), catchain_seqno(_catchain_seqno) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 64;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(64);
  }
  bool validate_skip(vm::CellSlice& cs) const override {
    return cs.advance(64);
  }
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ValidatorBaseInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ValidatorBaseInfo t_ValidatorBaseInfo;

//
// headers for type `OldMcBlocksInfo`
//

struct OldMcBlocksInfo final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef OldMcBlocksInfo type_class;
    Ref<CellSlice> x;  	// HashmapE 32 ExtBlkRef
    Record() = default;
    Record(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "OldMcBlocksInfo";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const OldMcBlocksInfo t_OldMcBlocksInfo;

//
// headers for auxiliary type `McStateExtra_aux`
//

struct McStateExtra_aux final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "McStateExtra_aux";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct McStateExtra_aux::Record {
  typedef McStateExtra_aux type_class;
  Ref<CellSlice> validator_info;  	// validator_info : ValidatorInfo
  Ref<CellSlice> prev_blocks;  	// prev_blocks : OldMcBlocksInfo
  Ref<CellSlice> last_key_block;  	// last_key_block : Maybe ExtBlkRef
  Record() = default;
  Record(Ref<CellSlice> _validator_info, Ref<CellSlice> _prev_blocks, Ref<CellSlice> _last_key_block) : validator_info(std::move(_validator_info)), prev_blocks(std::move(_prev_blocks)), last_key_block(std::move(_last_key_block)) {}
};

extern const McStateExtra_aux t_McStateExtra_aux;

//
// headers for type `McStateExtra`
//

struct McStateExtra final : TLB_Complex {
  enum { masterchain_state_extra };
  static constexpr int cons_len_exact = 16;
  static constexpr unsigned short cons_tag[1] = { 0xcc1f };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "McStateExtra";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct McStateExtra::Record {
  typedef McStateExtra type_class;
  Ref<CellSlice> shard_hashes;  	// shard_hashes : ShardHashes
  Ref<CellSlice> shard_fees;  	// shard_fees : ShardFees
  Ref<CellSlice> config;  	// config : ConfigParams
  McStateExtra_aux::Record r1;  	// ^[$_ validator_info:ValidatorInfo prev_blocks:OldMcBlocksInfo last_key_block:(Maybe ExtBlkRef) ]
  Record() = default;
  Record(Ref<CellSlice> _shard_hashes, Ref<CellSlice> _shard_fees, Ref<CellSlice> _config, const McStateExtra_aux::Record& _r1) : shard_hashes(std::move(_shard_hashes)), shard_fees(std::move(_shard_fees)), config(std::move(_config)), r1(_r1) {}
};

extern const McStateExtra t_McStateExtra;

//
// headers for type `CryptoSignature`
//

struct CryptoSignature final : TLB_Complex {
  enum { ed25519_signature };
  static constexpr int cons_len_exact = 4;
  static constexpr unsigned char cons_tag[1] = { 5 };
  struct Record {
    typedef CryptoSignature type_class;
    td::BitArray<256> R;  	// R : bits256
    td::BitArray<256> s;  	// s : bits256
    Record() = default;
    Record(const td::BitArray<256>& _R, const td::BitArray<256>& _s) : R(_R), s(_s) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 516;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(516);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "CryptoSignature";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const CryptoSignature t_CryptoSignature;

//
// headers for type `CryptoSignaturePair`
//

struct CryptoSignaturePair final : TLB_Complex {
  enum { sig_pair };
  static constexpr int cons_len_exact = 0;
  struct Record {
    typedef CryptoSignaturePair type_class;
    td::BitArray<256> node_id_short;  	// node_id_short : bits256
    Ref<CellSlice> sign;  	// sign : CryptoSignature
    Record() = default;
    Record(const td::BitArray<256>& _node_id_short, Ref<CellSlice> _sign) : node_id_short(_node_id_short), sign(std::move(_sign)) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 772;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(772);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "CryptoSignaturePair";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const CryptoSignaturePair t_CryptoSignaturePair;

//
// headers for type `McBlockExtra`
//

struct McBlockExtra final : TLB_Complex {
  enum { masterchain_block_extra };
  static constexpr int cons_len_exact = 16;
  static constexpr unsigned short cons_tag[1] = { 0xcc9f };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "McBlockExtra";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct McBlockExtra::Record {
  typedef McBlockExtra type_class;
  bool is_key_block;  	// is_key_block : Bool
  Ref<CellSlice> shard_hashes;  	// shard_hashes : ShardHashes
  Ref<CellSlice> prev_blk_signatures;  	// prev_blk_signatures : HashmapE 16 CryptoSignaturePair
  Record() = default;
  Record(bool _is_key_block, Ref<CellSlice> _shard_hashes, Ref<CellSlice> _prev_blk_signatures) : is_key_block(_is_key_block), shard_hashes(std::move(_shard_hashes)), prev_blk_signatures(std::move(_prev_blk_signatures)) {}
};

extern const McBlockExtra t_McBlockExtra;

//
// headers for type `SigPubKey`
//

struct SigPubKey final : TLB_Complex {
  enum { ed25519_pubkey };
  static constexpr int cons_len_exact = 32;
  static constexpr unsigned cons_tag[1] = { 0x8e81278aU };
  struct Record {
    typedef SigPubKey type_class;
    td::BitArray<256> pubkey;  	// pubkey : bits256
    Record() = default;
    Record(const td::BitArray<256>& _pubkey) : pubkey(_pubkey) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 288;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(288);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool unpack_ed25519_pubkey(vm::CellSlice& cs, td::BitArray<256>& pubkey) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool cell_unpack_ed25519_pubkey(Ref<vm::Cell> cell_ref, td::BitArray<256>& pubkey) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool pack_ed25519_pubkey(vm::CellBuilder& cb, const td::BitArray<256>& pubkey) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool cell_pack_ed25519_pubkey(Ref<vm::Cell>& cell_ref, const td::BitArray<256>& pubkey) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "SigPubKey";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const SigPubKey t_SigPubKey;

//
// headers for type `ValidatorDescr`
//

struct ValidatorDescr final : TLB_Complex {
  enum { validator };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 0x53 };
  struct Record {
    typedef ValidatorDescr type_class;
    Ref<CellSlice> public_key;  	// public_key : SigPubKey
    unsigned long long weight;  	// weight : uint64
    Record() = default;
    Record(Ref<CellSlice> _public_key, unsigned long long _weight) : public_key(std::move(_public_key)), weight(_weight) {}
  };
  int get_size(const vm::CellSlice& cs) const override {
    return 360;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(360);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ValidatorDescr";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const ValidatorDescr t_ValidatorDescr;

//
// headers for type `ValidatorSet`
//

struct ValidatorSet final : TLB_Complex {
  enum { validators };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 17 };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "ValidatorSet";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct ValidatorSet::Record {
  typedef ValidatorSet type_class;
  unsigned utime_since;  	// utime_since : uint32
  unsigned utime_until;  	// utime_until : uint32
  int total;  	// total : ## 16
  int main;  	// main : ## 16
  Ref<CellSlice> list;  	// list : Hashmap 16 ValidatorDescr
  Record() = default;
  Record(unsigned _utime_since, unsigned _utime_until, int _total, int _main, Ref<CellSlice> _list) : utime_since(_utime_since), utime_until(_utime_until), total(_total), main(_main), list(std::move(_list)) {}
};

extern const ValidatorSet t_ValidatorSet;

//
// headers for type `WorkchainFormat`
//

struct WorkchainFormat final : TLB_Complex {
  enum { wfmt_ext, wfmt_basic };
  static constexpr int cons_len_exact = 4;
  int m;
  WorkchainFormat(int _m) : m(_m) {}
  struct Record_wfmt_basic {
    typedef WorkchainFormat type_class;
    int vm_version;  	// vm_version : int32
    unsigned long long vm_mode;  	// vm_mode : uint64
    Record_wfmt_basic() = default;
    Record_wfmt_basic(int _vm_version, unsigned long long _vm_mode) : vm_version(_vm_version), vm_mode(_vm_mode) {}
  };
  struct Record_wfmt_ext;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_wfmt_basic& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_wfmt_basic& data) const;
  bool pack(vm::CellBuilder& cb, const Record_wfmt_basic& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_wfmt_basic& data) const;
  bool unpack(vm::CellSlice& cs, Record_wfmt_ext& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_wfmt_ext& data) const;
  bool pack(vm::CellBuilder& cb, const Record_wfmt_ext& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_wfmt_ext& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(WorkchainFormat " << m << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return cs.bselect(4, 3);
  }
};

struct WorkchainFormat::Record_wfmt_ext {
  typedef WorkchainFormat type_class;
  int min_addr_len;  	// min_addr_len : ## 12
  int max_addr_len;  	// max_addr_len : ## 12
  int addr_len_step;  	// addr_len_step : ## 12
  int workchain_type_id;  	// workchain_type_id : ## 32
  Record_wfmt_ext() = default;
  Record_wfmt_ext(int _min_addr_len, int _max_addr_len, int _addr_len_step, int _workchain_type_id) : min_addr_len(_min_addr_len), max_addr_len(_max_addr_len), addr_len_step(_addr_len_step), workchain_type_id(_workchain_type_id) {}
};

//
// headers for type `WorkchainDescr`
//

struct WorkchainDescr final : TLB_Complex {
  enum { workchain };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 0xa5 };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "WorkchainDescr";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct WorkchainDescr::Record {
  typedef WorkchainDescr type_class;
  unsigned enabled_since;  	// enabled_since : uint32
  int min_split;  	// min_split : ## 8
  int max_split;  	// max_split : ## 8
  bool basic;  	// basic : ## 1
  bool active;  	// active : Bool
  bool accept_msgs;  	// accept_msgs : Bool
  int flags;  	// flags : ## 13
  td::BitArray<256> zerostate_root_hash;  	// zerostate_root_hash : bits256
  td::BitArray<256> zerostate_file_hash;  	// zerostate_file_hash : bits256
  unsigned version;  	// version : uint32
  Ref<CellSlice> format;  	// format : WorkchainFormat basic
  Record() = default;
  Record(unsigned _enabled_since, int _min_split, int _max_split, bool _basic, bool _active, bool _accept_msgs, int _flags, const td::BitArray<256>& _zerostate_root_hash, const td::BitArray<256>& _zerostate_file_hash, unsigned _version, Ref<CellSlice> _format) : enabled_since(_enabled_since), min_split(_min_split), max_split(_max_split), basic(_basic), active(_active), accept_msgs(_accept_msgs), flags(_flags), zerostate_root_hash(_zerostate_root_hash), zerostate_file_hash(_zerostate_file_hash), version(_version), format(std::move(_format)) {}
};

extern const WorkchainDescr t_WorkchainDescr;

//
// headers for type `StoragePrices`
//

struct StoragePrices final : TLB_Complex {
  enum { cons1 };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 0xcc };
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 296;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(296);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "StoragePrices";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct StoragePrices::Record {
  typedef StoragePrices type_class;
  unsigned utime_since;  	// utime_since : uint32
  unsigned long long bit_price_ps;  	// bit_price_ps : uint64
  unsigned long long cell_price_ps;  	// cell_price_ps : uint64
  unsigned long long mc_bit_price_ps;  	// mc_bit_price_ps : uint64
  unsigned long long mc_cell_price_ps;  	// mc_cell_price_ps : uint64
  Record() = default;
  Record(unsigned _utime_since, unsigned long long _bit_price_ps, unsigned long long _cell_price_ps, unsigned long long _mc_bit_price_ps, unsigned long long _mc_cell_price_ps) : utime_since(_utime_since), bit_price_ps(_bit_price_ps), cell_price_ps(_cell_price_ps), mc_bit_price_ps(_mc_bit_price_ps), mc_cell_price_ps(_mc_cell_price_ps) {}
};

extern const StoragePrices t_StoragePrices;

//
// headers for type `GasLimitsPrices`
//

struct GasLimitsPrices final : TLB_Complex {
  enum { gas_prices };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 0xdd };
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 392;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(392);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "GasLimitsPrices";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct GasLimitsPrices::Record {
  typedef GasLimitsPrices type_class;
  unsigned long long gas_price;  	// gas_price : uint64
  unsigned long long gas_limit;  	// gas_limit : uint64
  unsigned long long gas_credit;  	// gas_credit : uint64
  unsigned long long block_gas_limit;  	// block_gas_limit : uint64
  unsigned long long freeze_due_limit;  	// freeze_due_limit : uint64
  unsigned long long delete_due_limit;  	// delete_due_limit : uint64
  Record() = default;
  Record(unsigned long long _gas_price, unsigned long long _gas_limit, unsigned long long _gas_credit, unsigned long long _block_gas_limit, unsigned long long _freeze_due_limit, unsigned long long _delete_due_limit) : gas_price(_gas_price), gas_limit(_gas_limit), gas_credit(_gas_credit), block_gas_limit(_block_gas_limit), freeze_due_limit(_freeze_due_limit), delete_due_limit(_delete_due_limit) {}
};

extern const GasLimitsPrices t_GasLimitsPrices;

//
// headers for type `MsgForwardPrices`
//

struct MsgForwardPrices final : TLB_Complex {
  enum { msg_forward_prices };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 0xea };
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 264;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(264);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "MsgForwardPrices";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct MsgForwardPrices::Record {
  typedef MsgForwardPrices type_class;
  unsigned long long lump_price;  	// lump_price : uint64
  unsigned long long bit_price;  	// bit_price : uint64
  unsigned long long cell_price;  	// cell_price : uint64
  unsigned ihr_price_factor;  	// ihr_price_factor : uint32
  int first_frac;  	// first_frac : uint16
  int next_frac;  	// next_frac : uint16
  Record() = default;
  Record(unsigned long long _lump_price, unsigned long long _bit_price, unsigned long long _cell_price, unsigned _ihr_price_factor, int _first_frac, int _next_frac) : lump_price(_lump_price), bit_price(_bit_price), cell_price(_cell_price), ihr_price_factor(_ihr_price_factor), first_frac(_first_frac), next_frac(_next_frac) {}
};

extern const MsgForwardPrices t_MsgForwardPrices;

//
// headers for type `CatchainConfig`
//

struct CatchainConfig final : TLB_Complex {
  enum { catchain_config };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 0xc1 };
  struct Record;
  int get_size(const vm::CellSlice& cs) const override {
    return 136;
  }
  bool skip(vm::CellSlice& cs) const override {
    return cs.advance(136);
  }
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "CatchainConfig";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct CatchainConfig::Record {
  typedef CatchainConfig type_class;
  unsigned mc_catchain_lifetime;  	// mc_catchain_lifetime : uint32
  unsigned shard_catchain_lifetime;  	// shard_catchain_lifetime : uint32
  unsigned shard_validators_lifetime;  	// shard_validators_lifetime : uint32
  unsigned shard_validators_num;  	// shard_validators_num : uint32
  Record() = default;
  Record(unsigned _mc_catchain_lifetime, unsigned _shard_catchain_lifetime, unsigned _shard_validators_lifetime, unsigned _shard_validators_num) : mc_catchain_lifetime(_mc_catchain_lifetime), shard_catchain_lifetime(_shard_catchain_lifetime), shard_validators_lifetime(_shard_validators_lifetime), shard_validators_num(_shard_validators_num) {}
};

extern const CatchainConfig t_CatchainConfig;

//
// headers for type `ConfigParam`
//

struct ConfigParam final : TLB_Complex {
  enum { cons32, cons34, cons36, cons0, cons1, cons12, cons16, cons17, cons18, cons31, cons28, config_mc_gas_prices, config_gas_prices, config_mc_fwd_prices, config_fwd_prices };
  static constexpr int cons_len_exact = 0;
  int m;
  ConfigParam(int _m) : m(_m) {}
  struct Record_cons0 {
    typedef ConfigParam type_class;
    td::BitArray<256> config_addr;  	// config_addr : bits256
    Record_cons0() = default;
    Record_cons0(const td::BitArray<256>& _config_addr) : config_addr(_config_addr) {}
  };
  struct Record_cons1 {
    typedef ConfigParam type_class;
    td::BitArray<256> elector_addr;  	// elector_addr : bits256
    Record_cons1() = default;
    Record_cons1(const td::BitArray<256>& _elector_addr) : elector_addr(_elector_addr) {}
  };
  struct Record_cons12 {
    typedef ConfigParam type_class;
    Ref<CellSlice> workchains;  	// workchains : HashmapE 32 WorkchainDescr
    Record_cons12() = default;
    Record_cons12(Ref<CellSlice> _workchains) : workchains(std::move(_workchains)) {}
  };
  struct Record_cons16;
  struct Record_cons17;
  struct Record_cons18 {
    typedef ConfigParam type_class;
    Ref<CellSlice> x;  	// Hashmap 32 StoragePrices
    Record_cons18() = default;
    Record_cons18(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  struct Record_config_mc_gas_prices {
    typedef ConfigParam type_class;
    Ref<CellSlice> x;  	// GasLimitsPrices
    Record_config_mc_gas_prices() = default;
    Record_config_mc_gas_prices(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  struct Record_config_gas_prices {
    typedef ConfigParam type_class;
    Ref<CellSlice> x;  	// GasLimitsPrices
    Record_config_gas_prices() = default;
    Record_config_gas_prices(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  struct Record_config_mc_fwd_prices {
    typedef ConfigParam type_class;
    Ref<CellSlice> x;  	// MsgForwardPrices
    Record_config_mc_fwd_prices() = default;
    Record_config_mc_fwd_prices(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  struct Record_config_fwd_prices {
    typedef ConfigParam type_class;
    Ref<CellSlice> x;  	// MsgForwardPrices
    Record_config_fwd_prices() = default;
    Record_config_fwd_prices(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  struct Record_cons28 {
    typedef ConfigParam type_class;
    Ref<CellSlice> x;  	// CatchainConfig
    Record_cons28() = default;
    Record_cons28(Ref<CellSlice> _x) : x(std::move(_x)) {}
  };
  struct Record_cons31 {
    typedef ConfigParam type_class;
    Ref<CellSlice> fundamental_smc_addr;  	// fundamental_smc_addr : HashmapE 256 True
    Record_cons31() = default;
    Record_cons31(Ref<CellSlice> _fundamental_smc_addr) : fundamental_smc_addr(std::move(_fundamental_smc_addr)) {}
  };
  struct Record_cons32 {
    typedef ConfigParam type_class;
    Ref<CellSlice> prev_validators;  	// prev_validators : ValidatorSet
    Record_cons32() = default;
    Record_cons32(Ref<CellSlice> _prev_validators) : prev_validators(std::move(_prev_validators)) {}
  };
  struct Record_cons34 {
    typedef ConfigParam type_class;
    Ref<CellSlice> cur_validators;  	// cur_validators : ValidatorSet
    Record_cons34() = default;
    Record_cons34(Ref<CellSlice> _cur_validators) : cur_validators(std::move(_cur_validators)) {}
  };
  struct Record_cons36 {
    typedef ConfigParam type_class;
    Ref<CellSlice> next_validators;  	// next_validators : ValidatorSet
    Record_cons36() = default;
    Record_cons36(Ref<CellSlice> _next_validators) : next_validators(std::move(_next_validators)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record_cons0& data) const;
  bool unpack_cons0(vm::CellSlice& cs, td::BitArray<256>& config_addr) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons0& data) const;
  bool cell_unpack_cons0(Ref<vm::Cell> cell_ref, td::BitArray<256>& config_addr) const;
  bool pack(vm::CellBuilder& cb, const Record_cons0& data) const;
  bool pack_cons0(vm::CellBuilder& cb, const td::BitArray<256>& config_addr) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons0& data) const;
  bool cell_pack_cons0(Ref<vm::Cell>& cell_ref, const td::BitArray<256>& config_addr) const;
  bool unpack(vm::CellSlice& cs, Record_cons1& data) const;
  bool unpack_cons1(vm::CellSlice& cs, td::BitArray<256>& elector_addr) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons1& data) const;
  bool cell_unpack_cons1(Ref<vm::Cell> cell_ref, td::BitArray<256>& elector_addr) const;
  bool pack(vm::CellBuilder& cb, const Record_cons1& data) const;
  bool pack_cons1(vm::CellBuilder& cb, const td::BitArray<256>& elector_addr) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons1& data) const;
  bool cell_pack_cons1(Ref<vm::Cell>& cell_ref, const td::BitArray<256>& elector_addr) const;
  bool unpack(vm::CellSlice& cs, Record_cons12& data) const;
  bool unpack_cons12(vm::CellSlice& cs, Ref<CellSlice>& workchains) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons12& data) const;
  bool cell_unpack_cons12(Ref<vm::Cell> cell_ref, Ref<CellSlice>& workchains) const;
  bool pack(vm::CellBuilder& cb, const Record_cons12& data) const;
  bool pack_cons12(vm::CellBuilder& cb, Ref<CellSlice> workchains) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons12& data) const;
  bool cell_pack_cons12(Ref<vm::Cell>& cell_ref, Ref<CellSlice> workchains) const;
  bool unpack(vm::CellSlice& cs, Record_cons16& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons16& data) const;
  bool pack(vm::CellBuilder& cb, const Record_cons16& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons16& data) const;
  bool unpack(vm::CellSlice& cs, Record_cons17& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons17& data) const;
  bool pack(vm::CellBuilder& cb, const Record_cons17& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons17& data) const;
  bool unpack(vm::CellSlice& cs, Record_cons18& data) const;
  bool unpack_cons18(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons18& data) const;
  bool cell_unpack_cons18(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_cons18& data) const;
  bool pack_cons18(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons18& data) const;
  bool cell_pack_cons18(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool unpack(vm::CellSlice& cs, Record_config_mc_gas_prices& data) const;
  bool unpack_config_mc_gas_prices(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_config_mc_gas_prices& data) const;
  bool cell_unpack_config_mc_gas_prices(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_config_mc_gas_prices& data) const;
  bool pack_config_mc_gas_prices(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_config_mc_gas_prices& data) const;
  bool cell_pack_config_mc_gas_prices(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool unpack(vm::CellSlice& cs, Record_config_gas_prices& data) const;
  bool unpack_config_gas_prices(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_config_gas_prices& data) const;
  bool cell_unpack_config_gas_prices(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_config_gas_prices& data) const;
  bool pack_config_gas_prices(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_config_gas_prices& data) const;
  bool cell_pack_config_gas_prices(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool unpack(vm::CellSlice& cs, Record_config_mc_fwd_prices& data) const;
  bool unpack_config_mc_fwd_prices(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_config_mc_fwd_prices& data) const;
  bool cell_unpack_config_mc_fwd_prices(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_config_mc_fwd_prices& data) const;
  bool pack_config_mc_fwd_prices(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_config_mc_fwd_prices& data) const;
  bool cell_pack_config_mc_fwd_prices(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool unpack(vm::CellSlice& cs, Record_config_fwd_prices& data) const;
  bool unpack_config_fwd_prices(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_config_fwd_prices& data) const;
  bool cell_unpack_config_fwd_prices(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_config_fwd_prices& data) const;
  bool pack_config_fwd_prices(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_config_fwd_prices& data) const;
  bool cell_pack_config_fwd_prices(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool unpack(vm::CellSlice& cs, Record_cons28& data) const;
  bool unpack_cons28(vm::CellSlice& cs, Ref<CellSlice>& x) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons28& data) const;
  bool cell_unpack_cons28(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const;
  bool pack(vm::CellBuilder& cb, const Record_cons28& data) const;
  bool pack_cons28(vm::CellBuilder& cb, Ref<CellSlice> x) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons28& data) const;
  bool cell_pack_cons28(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const;
  bool unpack(vm::CellSlice& cs, Record_cons31& data) const;
  bool unpack_cons31(vm::CellSlice& cs, Ref<CellSlice>& fundamental_smc_addr) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons31& data) const;
  bool cell_unpack_cons31(Ref<vm::Cell> cell_ref, Ref<CellSlice>& fundamental_smc_addr) const;
  bool pack(vm::CellBuilder& cb, const Record_cons31& data) const;
  bool pack_cons31(vm::CellBuilder& cb, Ref<CellSlice> fundamental_smc_addr) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons31& data) const;
  bool cell_pack_cons31(Ref<vm::Cell>& cell_ref, Ref<CellSlice> fundamental_smc_addr) const;
  bool unpack(vm::CellSlice& cs, Record_cons32& data) const;
  bool unpack_cons32(vm::CellSlice& cs, Ref<CellSlice>& prev_validators) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons32& data) const;
  bool cell_unpack_cons32(Ref<vm::Cell> cell_ref, Ref<CellSlice>& prev_validators) const;
  bool pack(vm::CellBuilder& cb, const Record_cons32& data) const;
  bool pack_cons32(vm::CellBuilder& cb, Ref<CellSlice> prev_validators) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons32& data) const;
  bool cell_pack_cons32(Ref<vm::Cell>& cell_ref, Ref<CellSlice> prev_validators) const;
  bool unpack(vm::CellSlice& cs, Record_cons34& data) const;
  bool unpack_cons34(vm::CellSlice& cs, Ref<CellSlice>& cur_validators) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons34& data) const;
  bool cell_unpack_cons34(Ref<vm::Cell> cell_ref, Ref<CellSlice>& cur_validators) const;
  bool pack(vm::CellBuilder& cb, const Record_cons34& data) const;
  bool pack_cons34(vm::CellBuilder& cb, Ref<CellSlice> cur_validators) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons34& data) const;
  bool cell_pack_cons34(Ref<vm::Cell>& cell_ref, Ref<CellSlice> cur_validators) const;
  bool unpack(vm::CellSlice& cs, Record_cons36& data) const;
  bool unpack_cons36(vm::CellSlice& cs, Ref<CellSlice>& next_validators) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record_cons36& data) const;
  bool cell_unpack_cons36(Ref<vm::Cell> cell_ref, Ref<CellSlice>& next_validators) const;
  bool pack(vm::CellBuilder& cb, const Record_cons36& data) const;
  bool pack_cons36(vm::CellBuilder& cb, Ref<CellSlice> next_validators) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record_cons36& data) const;
  bool cell_pack_cons36(Ref<vm::Cell>& cell_ref, Ref<CellSlice> next_validators) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "(ConfigParam " << m << ")";
  }
  int get_tag(const vm::CellSlice& cs) const override;
};

struct ConfigParam::Record_cons16 {
  typedef ConfigParam type_class;
  int max_validators;  	// max_validators : ## 16
  int max_main_validators;  	// max_main_validators : ## 16
  int min_validators;  	// min_validators : ## 16
  Record_cons16() = default;
  Record_cons16(int _max_validators, int _max_main_validators, int _min_validators) : max_validators(_max_validators), max_main_validators(_max_main_validators), min_validators(_min_validators) {}
};

struct ConfigParam::Record_cons17 {
  typedef ConfigParam type_class;
  Ref<CellSlice> min_stake;  	// min_stake : Grams
  Ref<CellSlice> max_stake;  	// max_stake : Grams
  unsigned max_stake_factor;  	// max_stake_factor : uint32
  Record_cons17() = default;
  Record_cons17(Ref<CellSlice> _min_stake, Ref<CellSlice> _max_stake, unsigned _max_stake_factor) : min_stake(std::move(_min_stake)), max_stake(std::move(_max_stake)), max_stake_factor(_max_stake_factor) {}
};

//
// headers for type `BlockSignaturesPure`
//

struct BlockSignaturesPure final : TLB_Complex {
  enum { block_signatures_pure };
  static constexpr int cons_len_exact = 0;
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "BlockSignaturesPure";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct BlockSignaturesPure::Record {
  typedef BlockSignaturesPure type_class;
  unsigned sig_count;  	// sig_count : uint32
  unsigned long long sig_weight;  	// sig_weight : uint64
  Ref<CellSlice> signatures;  	// signatures : HashmapE 16 CryptoSignaturePair
  Record() = default;
  Record(unsigned _sig_count, unsigned long long _sig_weight, Ref<CellSlice> _signatures) : sig_count(_sig_count), sig_weight(_sig_weight), signatures(std::move(_signatures)) {}
};

extern const BlockSignaturesPure t_BlockSignaturesPure;

//
// headers for type `BlockSignatures`
//

struct BlockSignatures final : TLB_Complex {
  enum { block_signatures };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 17 };
  struct Record {
    typedef BlockSignatures type_class;
    Ref<CellSlice> validator_info;  	// validator_info : ValidatorBaseInfo
    Ref<CellSlice> pure_signatures;  	// pure_signatures : BlockSignaturesPure
    Record() = default;
    Record(Ref<CellSlice> _validator_info, Ref<CellSlice> _pure_signatures) : validator_info(std::move(_validator_info)), pure_signatures(std::move(_pure_signatures)) {}
  };
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "BlockSignatures";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

extern const BlockSignatures t_BlockSignatures;

//
// headers for type `BlockProof`
//

struct BlockProof final : TLB_Complex {
  enum { block_proof };
  static constexpr int cons_len_exact = 8;
  static constexpr unsigned char cons_tag[1] = { 0xc3 };
  struct Record;
  bool skip(vm::CellSlice& cs) const override;
  bool validate_skip(vm::CellSlice& cs) const override;
  bool unpack(vm::CellSlice& cs, Record& data) const;
  bool cell_unpack(Ref<vm::Cell> cell_ref, Record& data) const;
  bool pack(vm::CellBuilder& cb, const Record& data) const;
  bool cell_pack(Ref<vm::Cell>& cell_ref, const Record& data) const;
  bool print_skip(PrettyPrinter& pp, vm::CellSlice& cs) const override;
  std::ostream& print_type(std::ostream& os) const override {
    return os << "BlockProof";
  }
  int get_tag(const vm::CellSlice& cs) const override {
    return 0;
  }
};

struct BlockProof::Record {
  typedef BlockProof type_class;
  Ref<CellSlice> proof_for;  	// proof_for : BlockIdExt
  Ref<Cell> root;  	// root : ^Cell
  Ref<CellSlice> signatures;  	// signatures : Maybe ^BlockSignatures
  Record() = default;
  Record(Ref<CellSlice> _proof_for, Ref<Cell> _root, Ref<CellSlice> _signatures) : proof_for(std::move(_proof_for)), root(std::move(_root)), signatures(std::move(_signatures)) {}
};

extern const BlockProof t_BlockProof;

// declarations of constant types used

// ## 1
extern const NatWidth t_natwidth_1;
// ## 8
extern const NatWidth t_natwidth_8;
// #<= 30
extern const NatLeq t_natleq_30;
// Maybe Anycast
extern const Maybe t_Maybe_Anycast;
// int8
extern const Int t_int8;
// bits256
extern const Bits t_bits256;
// ## 9
extern const NatWidth t_natwidth_9;
// int32
extern const Int t_int32;
// VarUInteger 16
extern const VarUInteger t_VarUInteger_16;
// VarUInteger 32
extern const VarUInteger t_VarUInteger_32;
// HashmapE 32 (VarUInteger 32)
extern const HashmapE t_HashmapE_32_VarUInteger_32;
// uint64
extern const UInt t_uint64;
// uint32
extern const UInt t_uint32;
// ## 5
extern const NatWidth t_natwidth_5;
// Maybe (## 5)
extern const Maybe t_Maybe_natwidth_5;
// Maybe TickTock
extern const Maybe t_Maybe_TickTock;
// Maybe ^Cell
extern const Maybe t_Maybe_Ref_Cell;
// HashmapE 256 SimpleLib
extern const HashmapE t_HashmapE_256_SimpleLib;
// ^StateInit
extern const RefT t_Ref_StateInit;
// Either StateInit ^StateInit
extern const Either t_Either_StateInit_Ref_StateInit;
// Maybe (Either StateInit ^StateInit)
extern const Maybe t_Maybe_Either_StateInit_Ref_StateInit;
// #<= 96
extern const NatLeq t_natleq_96;
// Message Any
extern const Message t_Message_Any;
// ^(Message Any)
extern const RefT t_Ref_Message_Any;
// ^Transaction
extern const RefT t_Ref_Transaction;
// ^MsgEnvelope
extern const RefT t_Ref_MsgEnvelope;
// HashmapAugE 256 InMsg ImportFees
extern const HashmapAugE t_HashmapAugE_256_InMsg_ImportFees;
// ^InMsg
extern const RefT t_Ref_InMsg;
// HashmapAugE 256 OutMsg CurrencyCollection
extern const HashmapAugE t_HashmapAugE_256_OutMsg_CurrencyCollection;
// HashmapAugE 352 EnqueuedMsg uint64
extern const HashmapAugE t_HashmapAugE_352_EnqueuedMsg_uint64;
// HashmapE 96 ProcessedUpto
extern const HashmapE t_HashmapE_96_ProcessedUpto;
// HashmapE 256 IhrPendingSince
extern const HashmapE t_HashmapE_256_IhrPendingSince;
// VarUInteger 7
extern const VarUInteger t_VarUInteger_7;
// Maybe Grams
extern const Maybe t_Maybe_Grams;
// ^Account
extern const RefT t_Ref_Account;
// HashmapAugE 256 ^Account CurrencyCollection
extern const HashmapAugE t_HashmapAugE_256_Ref_Account_CurrencyCollection;
// uint15
extern const UInt t_uint15;
// Maybe ^(Message Any)
extern const Maybe t_Maybe_Ref_Message_Any;
// HashmapE 15 ^(Message Any)
extern const HashmapE t_HashmapE_15_Ref_Message_Any;
// HASH_UPDATE Account
extern const HASH_UPDATE t_HASH_UPDATE_Account;
// ^(HASH_UPDATE Account)
extern const RefT t_Ref_HASH_UPDATE_Account;
// ^TransactionDescr
extern const RefT t_Ref_TransactionDescr;
// HashmapAug 64 ^Transaction Grams
extern const HashmapAug t_HashmapAug_64_Ref_Transaction_Grams;
// HashmapAugE 256 AccountBlock Grams
extern const HashmapAugE t_HashmapAugE_256_AccountBlock_Grams;
// VarUInteger 3
extern const VarUInteger t_VarUInteger_3;
// Maybe (VarUInteger 3)
extern const Maybe t_Maybe_VarUInteger_3;
// Maybe int32
extern const Maybe t_Maybe_int32;
// ^[$_ gas_used:(VarUInteger 7) gas_limit:(VarUInteger 7) gas_credit:(Maybe (VarUInteger 3)) mode:int8 exit_code:int32 exit_arg:(Maybe int32) vm_steps:uint32 vm_init_state_hash:bits256 vm_final_state_hash:bits256 ]
extern const RefT t_Ref_TYPE_1619;
// uint16
extern const UInt t_uint16;
// Maybe TrStoragePhase
extern const Maybe t_Maybe_TrStoragePhase;
// Maybe TrCreditPhase
extern const Maybe t_Maybe_TrCreditPhase;
// ^TrActionPhase
extern const RefT t_Ref_TrActionPhase;
// Maybe ^TrActionPhase
extern const Maybe t_Maybe_Ref_TrActionPhase;
// Maybe TrBouncePhase
extern const Maybe t_Maybe_TrBouncePhase;
// ## 6
extern const NatWidth t_natwidth_6;
// MessageRelaxed Any
extern const MessageRelaxed t_MessageRelaxed_Any;
// ^(MessageRelaxed Any)
extern const RefT t_Ref_MessageRelaxed_Any;
// #<= 60
extern const NatLeq t_natleq_60;
// ^OutMsgQueueInfo
extern const RefT t_Ref_OutMsgQueueInfo;
// HashmapE 256 LibDescr
extern const HashmapE t_HashmapE_256_LibDescr;
// ^[$_ total_balance:CurrencyCollection total_validator_fees:CurrencyCollection libraries:(HashmapE 256 LibDescr) ]
extern const RefT t_Ref_TYPE_1632;
// Maybe BlkMasterInfo
extern const Maybe t_Maybe_BlkMasterInfo;
// ^McStateExtra
extern const RefT t_Ref_McStateExtra;
// Maybe ^McStateExtra
extern const Maybe t_Maybe_Ref_McStateExtra;
// ^ShardStateUnsplit
extern const RefT t_Ref_ShardStateUnsplit;
// Hashmap 256 True
extern const Hashmap t_Hashmap_256_True;
// ## 10
extern const NatWidth t_natwidth_10;
// ^BlkMasterInfo
extern const RefT t_Ref_BlkMasterInfo;
// BlkPrevInfo 0
extern const BlkPrevInfo t_BlkPrevInfo_0;
// ^(BlkPrevInfo 0)
extern const RefT t_Ref_BlkPrevInfo_0;
// ^BlockInfo
extern const RefT t_Ref_BlockInfo;
// ^ValueFlow
extern const RefT t_Ref_ValueFlow;
// MERKLE_UPDATE ShardState
extern const MERKLE_UPDATE t_MERKLE_UPDATE_ShardState;
// ^(MERKLE_UPDATE ShardState)
extern const RefT t_Ref_MERKLE_UPDATE_ShardState;
// ^BlockExtra
extern const RefT t_Ref_BlockExtra;
// ^InMsgDescr
extern const RefT t_Ref_InMsgDescr;
// ^OutMsgDescr
extern const RefT t_Ref_OutMsgDescr;
// ^McBlockExtra
extern const RefT t_Ref_McBlockExtra;
// Maybe ^McBlockExtra
extern const Maybe t_Maybe_Ref_McBlockExtra;
// ^[$_ from_prev_blk:CurrencyCollection to_next_blk:CurrencyCollection imported:CurrencyCollection exported:CurrencyCollection ]
extern const RefT t_Ref_TYPE_1642;
// ^[$_ fees_imported:CurrencyCollection created:CurrencyCollection minted:CurrencyCollection ]
extern const RefT t_Ref_TYPE_1643;
// ## 3
extern const NatWidth t_natwidth_3;
// BinTree ShardDescr
extern const BinTree t_BinTree_ShardDescr;
// ^(BinTree ShardDescr)
extern const RefT t_Ref_BinTree_ShardDescr;
// HashmapE 32 ^(BinTree ShardDescr)
extern const HashmapE t_HashmapE_32_Ref_BinTree_ShardDescr;
// BinTreeAug True CurrencyCollection
extern const BinTreeAug t_BinTreeAug_True_CurrencyCollection;
// ^(BinTreeAug True CurrencyCollection)
extern const RefT t_Ref_BinTreeAug_True_CurrencyCollection;
// HashmapAugE 32 ^(BinTreeAug True CurrencyCollection) CurrencyCollection
extern const HashmapAugE t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection;
// Hashmap 32 ^Cell
extern const Hashmap t_Hashmap_32_Ref_Cell;
// ^(Hashmap 32 ^Cell)
extern const RefT t_Ref_Hashmap_32_Ref_Cell;
// HashmapE 32 ExtBlkRef
extern const HashmapE t_HashmapE_32_ExtBlkRef;
// Maybe ExtBlkRef
extern const Maybe t_Maybe_ExtBlkRef;
// ^[$_ validator_info:ValidatorInfo prev_blocks:OldMcBlocksInfo last_key_block:(Maybe ExtBlkRef) ]
extern const RefT t_Ref_TYPE_1654;
// HashmapE 16 CryptoSignaturePair
extern const HashmapE t_HashmapE_16_CryptoSignaturePair;
// ## 16
extern const NatWidth t_natwidth_16;
// Hashmap 16 ValidatorDescr
extern const Hashmap t_Hashmap_16_ValidatorDescr;
// ## 12
extern const NatWidth t_natwidth_12;
// ## 32
extern const NatWidth t_natwidth_32;
// ## 13
extern const NatWidth t_natwidth_13;
// HashmapE 32 WorkchainDescr
extern const HashmapE t_HashmapE_32_WorkchainDescr;
// Hashmap 32 StoragePrices
extern const Hashmap t_Hashmap_32_StoragePrices;
// HashmapE 256 True
extern const HashmapE t_HashmapE_256_True;
// ^BlockSignatures
extern const RefT t_Ref_BlockSignatures;
// Maybe ^BlockSignatures
extern const Maybe t_Maybe_Ref_BlockSignatures;

} // namespace gen

} // namespace block
