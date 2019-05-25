#include "block-auto.h"
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
// code for type `Unit`
//

bool Unit::fetch_enum_to(vm::CellSlice& cs, char& value) const {
  value = 0;
  return true;
}

bool Unit::store_enum_from(vm::CellBuilder& cb, int value) const {
  return !value;
}

bool Unit::unpack(vm::CellSlice& cs, Unit::Record& data) const {
  return true;
}

bool Unit::unpack_unit(vm::CellSlice& cs) const {
  return true;
}

bool Unit::cell_unpack(Ref<vm::Cell> cell_ref, Unit::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Unit::cell_unpack_unit(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_unit(cs) && cs.empty_ext();
}

bool Unit::pack(vm::CellBuilder& cb, const Unit::Record& data) const {
  return true;
}

bool Unit::pack_unit(vm::CellBuilder& cb) const {
  return true;
}

bool Unit::cell_pack(Ref<vm::Cell>& cell_ref, const Unit::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Unit::cell_pack_unit(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_unit(cb) && std::move(cb).finalize_to(cell_ref);
}

bool Unit::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.cons("unit");
}

const Unit t_Unit;

//
// code for type `True`
//

bool True::fetch_enum_to(vm::CellSlice& cs, char& value) const {
  value = 0;
  return true;
}

bool True::store_enum_from(vm::CellBuilder& cb, int value) const {
  return !value;
}

bool True::unpack(vm::CellSlice& cs, True::Record& data) const {
  return true;
}

bool True::unpack_true1(vm::CellSlice& cs) const {
  return true;
}

bool True::cell_unpack(Ref<vm::Cell> cell_ref, True::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool True::cell_unpack_true1(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_true1(cs) && cs.empty_ext();
}

bool True::pack(vm::CellBuilder& cb, const True::Record& data) const {
  return true;
}

bool True::pack_true1(vm::CellBuilder& cb) const {
  return true;
}

bool True::cell_pack(Ref<vm::Cell>& cell_ref, const True::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool True::cell_pack_true1(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_true1(cb) && std::move(cb).finalize_to(cell_ref);
}

bool True::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.cons("true");
}

const True t_True;

//
// code for type `Bool`
//

bool Bool::fetch_enum_to(vm::CellSlice& cs, char& value) const {
  value = (char)cs.fetch_ulong(1);
  return value >= 0;
}

bool Bool::store_enum_from(vm::CellBuilder& cb, int value) const {
  return cb.store_long_rchk_bool(value, 1);
}

bool Bool::unpack(vm::CellSlice& cs, Bool::Record_bool_false& data) const {
  return cs.fetch_ulong(1) == 0;
}

bool Bool::unpack_bool_false(vm::CellSlice& cs) const {
  return cs.fetch_ulong(1) == 0;
}

bool Bool::cell_unpack(Ref<vm::Cell> cell_ref, Bool::Record_bool_false& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Bool::cell_unpack_bool_false(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_bool_false(cs) && cs.empty_ext();
}

bool Bool::unpack(vm::CellSlice& cs, Bool::Record_bool_true& data) const {
  return cs.fetch_ulong(1) == 1;
}

bool Bool::unpack_bool_true(vm::CellSlice& cs) const {
  return cs.fetch_ulong(1) == 1;
}

bool Bool::cell_unpack(Ref<vm::Cell> cell_ref, Bool::Record_bool_true& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Bool::cell_unpack_bool_true(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_bool_true(cs) && cs.empty_ext();
}

bool Bool::pack(vm::CellBuilder& cb, const Bool::Record_bool_false& data) const {
  return cb.store_long_bool(0, 1);
}

bool Bool::pack_bool_false(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 1);
}

bool Bool::cell_pack(Ref<vm::Cell>& cell_ref, const Bool::Record_bool_false& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Bool::cell_pack_bool_false(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_bool_false(cb) && std::move(cb).finalize_to(cell_ref);
}

bool Bool::pack(vm::CellBuilder& cb, const Bool::Record_bool_true& data) const {
  return cb.store_long_bool(1, 1);
}

bool Bool::pack_bool_true(vm::CellBuilder& cb) const {
  return cb.store_long_bool(1, 1);
}

bool Bool::cell_pack(Ref<vm::Cell>& cell_ref, const Bool::Record_bool_true& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Bool::cell_pack_bool_true(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_bool_true(cb) && std::move(cb).finalize_to(cell_ref);
}

bool Bool::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case bool_false:
    return cs.advance(1)
        && pp.cons("bool_false");
  case bool_true:
    return cs.advance(1)
        && pp.cons("bool_true");
  }
  return pp.fail("unknown constructor for Bool");
}

const Bool t_Bool;

//
// code for type `Maybe`
//

bool Maybe::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case nothing:
    return cs.advance(1);
  case just:
    return cs.advance(1)
        && X.skip(cs);
  }
  return false;
}

bool Maybe::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case nothing:
    return cs.advance(1);
  case just:
    return cs.advance(1)
        && X.validate_skip(cs);
  }
  return false;
}

bool Maybe::unpack(vm::CellSlice& cs, Maybe::Record_nothing& data) const {
  return cs.fetch_ulong(1) == 0;
}

bool Maybe::unpack_nothing(vm::CellSlice& cs) const {
  return cs.fetch_ulong(1) == 0;
}

bool Maybe::cell_unpack(Ref<vm::Cell> cell_ref, Maybe::Record_nothing& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Maybe::cell_unpack_nothing(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_nothing(cs) && cs.empty_ext();
}

bool Maybe::unpack(vm::CellSlice& cs, Maybe::Record_just& data) const {
  return cs.fetch_ulong(1) == 1
      && X.fetch_to(cs, data.value);
}

bool Maybe::unpack_just(vm::CellSlice& cs, Ref<CellSlice>& value) const {
  return cs.fetch_ulong(1) == 1
      && X.fetch_to(cs, value);
}

bool Maybe::cell_unpack(Ref<vm::Cell> cell_ref, Maybe::Record_just& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Maybe::cell_unpack_just(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_just(cs, value) && cs.empty_ext();
}

bool Maybe::pack(vm::CellBuilder& cb, const Maybe::Record_nothing& data) const {
  return cb.store_long_bool(0, 1);
}

bool Maybe::pack_nothing(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 1);
}

bool Maybe::cell_pack(Ref<vm::Cell>& cell_ref, const Maybe::Record_nothing& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Maybe::cell_pack_nothing(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_nothing(cb) && std::move(cb).finalize_to(cell_ref);
}

bool Maybe::pack(vm::CellBuilder& cb, const Maybe::Record_just& data) const {
  return cb.store_long_bool(1, 1)
      && X.store_from(cb, data.value);
}

bool Maybe::pack_just(vm::CellBuilder& cb, Ref<CellSlice> value) const {
  return cb.store_long_bool(1, 1)
      && X.store_from(cb, value);
}

bool Maybe::cell_pack(Ref<vm::Cell>& cell_ref, const Maybe::Record_just& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Maybe::cell_pack_just(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const {
  vm::CellBuilder cb;
  return pack_just(cb, std::move(value)) && std::move(cb).finalize_to(cell_ref);
}

bool Maybe::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case nothing:
    return cs.advance(1)
        && pp.cons("nothing");
  case just:
    return cs.advance(1)
        && pp.open("just")
        && pp.field("value")
        && X.print_skip(pp, cs)
        && pp.close();
  }
  return pp.fail("unknown constructor for Maybe");
}


//
// code for type `Either`
//

bool Either::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case left:
    return cs.advance(1)
        && X.skip(cs);
  case right:
    return cs.advance(1)
        && Y.skip(cs);
  }
  return false;
}

bool Either::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case left:
    return cs.advance(1)
        && X.validate_skip(cs);
  case right:
    return cs.advance(1)
        && Y.validate_skip(cs);
  }
  return false;
}

bool Either::unpack(vm::CellSlice& cs, Either::Record_left& data) const {
  return cs.fetch_ulong(1) == 0
      && X.fetch_to(cs, data.value);
}

bool Either::unpack_left(vm::CellSlice& cs, Ref<CellSlice>& value) const {
  return cs.fetch_ulong(1) == 0
      && X.fetch_to(cs, value);
}

bool Either::cell_unpack(Ref<vm::Cell> cell_ref, Either::Record_left& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Either::cell_unpack_left(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_left(cs, value) && cs.empty_ext();
}

bool Either::unpack(vm::CellSlice& cs, Either::Record_right& data) const {
  return cs.fetch_ulong(1) == 1
      && Y.fetch_to(cs, data.value);
}

bool Either::unpack_right(vm::CellSlice& cs, Ref<CellSlice>& value) const {
  return cs.fetch_ulong(1) == 1
      && Y.fetch_to(cs, value);
}

bool Either::cell_unpack(Ref<vm::Cell> cell_ref, Either::Record_right& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Either::cell_unpack_right(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_right(cs, value) && cs.empty_ext();
}

bool Either::pack(vm::CellBuilder& cb, const Either::Record_left& data) const {
  return cb.store_long_bool(0, 1)
      && X.store_from(cb, data.value);
}

bool Either::pack_left(vm::CellBuilder& cb, Ref<CellSlice> value) const {
  return cb.store_long_bool(0, 1)
      && X.store_from(cb, value);
}

bool Either::cell_pack(Ref<vm::Cell>& cell_ref, const Either::Record_left& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Either::cell_pack_left(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const {
  vm::CellBuilder cb;
  return pack_left(cb, std::move(value)) && std::move(cb).finalize_to(cell_ref);
}

bool Either::pack(vm::CellBuilder& cb, const Either::Record_right& data) const {
  return cb.store_long_bool(1, 1)
      && Y.store_from(cb, data.value);
}

bool Either::pack_right(vm::CellBuilder& cb, Ref<CellSlice> value) const {
  return cb.store_long_bool(1, 1)
      && Y.store_from(cb, value);
}

bool Either::cell_pack(Ref<vm::Cell>& cell_ref, const Either::Record_right& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Either::cell_pack_right(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const {
  vm::CellBuilder cb;
  return pack_right(cb, std::move(value)) && std::move(cb).finalize_to(cell_ref);
}

bool Either::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case left:
    return cs.advance(1)
        && pp.open("left")
        && pp.field("value")
        && X.print_skip(pp, cs)
        && pp.close();
  case right:
    return cs.advance(1)
        && pp.open("right")
        && pp.field("value")
        && Y.print_skip(pp, cs)
        && pp.close();
  }
  return pp.fail("unknown constructor for Either");
}


//
// code for type `Both`
//

bool Both::skip(vm::CellSlice& cs) const {
  return X.skip(cs)
      && Y.skip(cs);
}

bool Both::validate_skip(vm::CellSlice& cs) const {
  return X.validate_skip(cs)
      && Y.validate_skip(cs);
}

bool Both::unpack(vm::CellSlice& cs, Both::Record& data) const {
  return X.fetch_to(cs, data.first)
      && Y.fetch_to(cs, data.second);
}

bool Both::cell_unpack(Ref<vm::Cell> cell_ref, Both::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Both::pack(vm::CellBuilder& cb, const Both::Record& data) const {
  return X.store_from(cb, data.first)
      && Y.store_from(cb, data.second);
}

bool Both::cell_pack(Ref<vm::Cell>& cell_ref, const Both::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Both::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("pair")
      && pp.field("first")
      && X.print_skip(pp, cs)
      && pp.field("second")
      && Y.print_skip(pp, cs)
      && pp.close();
}


//
// code for type `Bit`
//

bool Bit::unpack(vm::CellSlice& cs, Bit::Record& data) const {
  return cs.fetch_bool_to(data.x);
}

bool Bit::unpack_bit(vm::CellSlice& cs, bool& x) const {
  return cs.fetch_bool_to(x);
}

bool Bit::cell_unpack(Ref<vm::Cell> cell_ref, Bit::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Bit::cell_unpack_bit(Ref<vm::Cell> cell_ref, bool& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_bit(cs, x) && cs.empty_ext();
}

bool Bit::pack(vm::CellBuilder& cb, const Bit::Record& data) const {
  return cb.store_ulong_rchk_bool(data.x, 1);
}

bool Bit::pack_bit(vm::CellBuilder& cb, bool x) const {
  return cb.store_ulong_rchk_bool(x, 1);
}

bool Bit::cell_pack(Ref<vm::Cell>& cell_ref, const Bit::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Bit::cell_pack_bit(Ref<vm::Cell>& cell_ref, bool x) const {
  vm::CellBuilder cb;
  return pack_bit(cb, x) && std::move(cb).finalize_to(cell_ref);
}

bool Bit::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int t1;
  return pp.open("bit")
      && cs.fetch_bool_to(t1)
      && pp.field_int(t1)
      && pp.close();
}

const Bit t_Bit;

//
// code for type `Hashmap`
//

bool Hashmap::skip(vm::CellSlice& cs) const {
  int l, m1;
  return HmLabel{m}.skip(cs, l)
      && add_r1(m1, l, m)
      && HashmapNode{m1, X}.skip(cs);
}

bool Hashmap::validate_skip(vm::CellSlice& cs) const {
  int l, m1;
  return HmLabel{m}.validate_skip(cs, l)
      && add_r1(m1, l, m)
      && HashmapNode{m1, X}.validate_skip(cs);
}

bool Hashmap::unpack(vm::CellSlice& cs, Hashmap::Record& data) const {
  return (data.n = m) >= 0
      && HmLabel{m}.fetch_to(cs, data.label, data.l)
      && add_r1(data.m, data.l, m)
      && HashmapNode{data.m, X}.fetch_to(cs, data.node);
}

bool Hashmap::cell_unpack(Ref<vm::Cell> cell_ref, Hashmap::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Hashmap::pack(vm::CellBuilder& cb, const Hashmap::Record& data) const {
  int l, m1;
  return tlb::store_from(cb, HmLabel{m}, data.label, l)
      && add_r1(m1, l, m)
      && HashmapNode{m1, X}.store_from(cb, data.node);
}

bool Hashmap::cell_pack(Ref<vm::Cell>& cell_ref, const Hashmap::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Hashmap::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int l, m1;
  return pp.open("hm_edge")
      && pp.field("label")
      && HmLabel{m}.print_skip(pp, cs, l)
      && add_r1(m1, l, m)
      && pp.field("node")
      && HashmapNode{m1, X}.print_skip(pp, cs)
      && pp.close();
}


//
// code for type `HashmapNode`
//

int HashmapNode::get_tag(const vm::CellSlice& cs) const {
  // distinguish by parameter `m` using 1 2 2 2
  return m ? hmn_fork : hmn_leaf;
}

bool HashmapNode::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case hmn_leaf:
    return m == 0
        && X.skip(cs);
  case hmn_fork: {
    int n;
    return add_r1(n, 1, m)
        && cs.advance_refs(2);
    }
  }
  return false;
}

bool HashmapNode::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case hmn_leaf:
    return m == 0
        && X.validate_skip(cs);
  case hmn_fork: {
    int n;
    return add_r1(n, 1, m)
        && Hashmap{n, X}.validate_skip_ref(cs)
        && Hashmap{n, X}.validate_skip_ref(cs);
    }
  }
  return false;
}

bool HashmapNode::unpack(vm::CellSlice& cs, HashmapNode::Record_hmn_leaf& data) const {
  return m == 0
      && X.fetch_to(cs, data.value);
}

bool HashmapNode::unpack_hmn_leaf(vm::CellSlice& cs, Ref<CellSlice>& value) const {
  return m == 0
      && X.fetch_to(cs, value);
}

bool HashmapNode::cell_unpack(Ref<vm::Cell> cell_ref, HashmapNode::Record_hmn_leaf& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HashmapNode::cell_unpack_hmn_leaf(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_hmn_leaf(cs, value) && cs.empty_ext();
}

bool HashmapNode::unpack(vm::CellSlice& cs, HashmapNode::Record_hmn_fork& data) const {
  return add_r1(data.n, 1, m)
      && cs.fetch_ref_to(data.left)
      && cs.fetch_ref_to(data.right);
}

bool HashmapNode::cell_unpack(Ref<vm::Cell> cell_ref, HashmapNode::Record_hmn_fork& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HashmapNode::pack(vm::CellBuilder& cb, const HashmapNode::Record_hmn_leaf& data) const {
  return m == 0
      && X.store_from(cb, data.value);
}

bool HashmapNode::pack_hmn_leaf(vm::CellBuilder& cb, Ref<CellSlice> value) const {
  return m == 0
      && X.store_from(cb, value);
}

bool HashmapNode::cell_pack(Ref<vm::Cell>& cell_ref, const HashmapNode::Record_hmn_leaf& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapNode::cell_pack_hmn_leaf(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const {
  vm::CellBuilder cb;
  return pack_hmn_leaf(cb, std::move(value)) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapNode::pack(vm::CellBuilder& cb, const HashmapNode::Record_hmn_fork& data) const {
  int n;
  return add_r1(n, 1, m)
      && cb.store_ref_bool(data.left)
      && cb.store_ref_bool(data.right);
}

bool HashmapNode::cell_pack(Ref<vm::Cell>& cell_ref, const HashmapNode::Record_hmn_fork& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapNode::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case hmn_leaf:
    return pp.open("hmn_leaf")
        && m == 0
        && pp.field("value")
        && X.print_skip(pp, cs)
        && pp.close();
  case hmn_fork: {
    int n;
    return pp.open("hmn_fork")
        && add_r1(n, 1, m)
        && pp.field("left")
        && Hashmap{n, X}.print_ref(pp, cs.fetch_ref())
        && pp.field("right")
        && Hashmap{n, X}.print_ref(pp, cs.fetch_ref())
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for HashmapNode");
}


//
// code for type `HmLabel`
//
constexpr char HmLabel::cons_len[3];
constexpr unsigned char HmLabel::cons_tag[3];

bool HmLabel::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case hml_short: {
    int m;
    return cs.advance(1)
        && t_Unary.skip(cs, m)
        && m <= n
        && cs.advance(m);
    }
  case hml_long: {
    int m;
    return cs.advance(2)
        && cs.fetch_uint_leq(n, m)
        && cs.advance(m);
    }
  case hml_same: {
    int m;
    return cs.advance(3)
        && cs.fetch_uint_leq(n, m);
    }
  }
  return false;
}

bool HmLabel::skip(vm::CellSlice& cs, int& m) const {
  switch (get_tag(cs)) {
  case hml_short:
    return cs.advance(1)
        && t_Unary.skip(cs, m)
        && m <= n
        && cs.advance(m);
  case hml_long:
    return cs.advance(2)
        && cs.fetch_uint_leq(n, m)
        && cs.advance(m);
  case hml_same:
    return cs.advance(3)
        && cs.fetch_uint_leq(n, m);
  }
  return false;
}

bool HmLabel::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case hml_short: {
    int m;
    return cs.advance(1)
        && t_Unary.validate_skip(cs, m)
        && m <= n
        && cs.advance(m);
    }
  case hml_long: {
    int m;
    return cs.advance(2)
        && cs.fetch_uint_leq(n, m)
        && cs.advance(m);
    }
  case hml_same: {
    int m;
    return cs.advance(3)
        && cs.fetch_uint_leq(n, m);
    }
  }
  return false;
}

bool HmLabel::validate_skip(vm::CellSlice& cs, int& m) const {
  switch (get_tag(cs)) {
  case hml_short:
    return cs.advance(1)
        && t_Unary.validate_skip(cs, m)
        && m <= n
        && cs.advance(m);
  case hml_long:
    return cs.advance(2)
        && cs.fetch_uint_leq(n, m)
        && cs.advance(m);
  case hml_same:
    return cs.advance(3)
        && cs.fetch_uint_leq(n, m);
  }
  return false;
}

bool HmLabel::fetch_to(vm::CellSlice& cs, Ref<vm::CellSlice>& res, int& m) const {
  res = Ref<vm::CellSlice>{true, cs};
  return skip(cs, m) && res.unique_write().cut_tail(cs);
}

bool HmLabel::unpack(vm::CellSlice& cs, HmLabel::Record_hml_short& data, int& m) const {
  return cs.fetch_ulong(1) == 0
      && (data.m = n) >= 0
      && t_Unary.fetch_to(cs, data.len, data.n)
      && data.n <= n
      && cs.fetch_bitstring_to(data.n, data.s)
      && (m = data.n) >= 0;
}

bool HmLabel::cell_unpack(Ref<vm::Cell> cell_ref, HmLabel::Record_hml_short& data, int& m) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data, m) && cs.empty_ext();
}

bool HmLabel::unpack(vm::CellSlice& cs, HmLabel::Record_hml_long& data, int& m) const {
  return cs.fetch_ulong(2) == 2
      && (data.m = n) >= 0
      && cs.fetch_uint_leq(n, data.n)
      && cs.fetch_bitstring_to(data.n, data.s)
      && (m = data.n) >= 0;
}

bool HmLabel::cell_unpack(Ref<vm::Cell> cell_ref, HmLabel::Record_hml_long& data, int& m) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data, m) && cs.empty_ext();
}

bool HmLabel::unpack(vm::CellSlice& cs, HmLabel::Record_hml_same& data, int& m) const {
  return cs.fetch_ulong(2) == 3
      && (data.m = n) >= 0
      && cs.fetch_bool_to(data.v)
      && cs.fetch_uint_leq(n, data.n)
      && (m = data.n) >= 0;
}

bool HmLabel::cell_unpack(Ref<vm::Cell> cell_ref, HmLabel::Record_hml_same& data, int& m) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data, m) && cs.empty_ext();
}

bool HmLabel::pack(vm::CellBuilder& cb, const HmLabel::Record_hml_short& data, int& m) const {
  return cb.store_long_bool(0, 1)
      && tlb::store_from(cb, t_Unary, data.len, m)
      && m <= n
      && cb.append_bitstring_chk(data.s, m);
}

bool HmLabel::cell_pack(Ref<vm::Cell>& cell_ref, const HmLabel::Record_hml_short& data, int& m) const {
  vm::CellBuilder cb;
  return pack(cb, data, m) && std::move(cb).finalize_to(cell_ref);
}

bool HmLabel::pack(vm::CellBuilder& cb, const HmLabel::Record_hml_long& data, int& m) const {
  return cb.store_long_bool(2, 2)
      && cb.store_uint_leq(n, data.n)
      && cb.append_bitstring_chk(data.s, data.n)
      && (m = data.n) >= 0;
}

bool HmLabel::cell_pack(Ref<vm::Cell>& cell_ref, const HmLabel::Record_hml_long& data, int& m) const {
  vm::CellBuilder cb;
  return pack(cb, data, m) && std::move(cb).finalize_to(cell_ref);
}

bool HmLabel::pack(vm::CellBuilder& cb, const HmLabel::Record_hml_same& data, int& m) const {
  return cb.store_long_bool(3, 2)
      && cb.store_ulong_rchk_bool(data.v, 1)
      && cb.store_uint_leq(n, data.n)
      && (m = data.n) >= 0;
}

bool HmLabel::cell_pack(Ref<vm::Cell>& cell_ref, const HmLabel::Record_hml_same& data, int& m) const {
  vm::CellBuilder cb;
  return pack(cb, data, m) && std::move(cb).finalize_to(cell_ref);
}

bool HmLabel::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case hml_short: {
    int m;
    return cs.advance(1)
        && pp.open("hml_short")
        && pp.field("len")
        && t_Unary.print_skip(pp, cs, m)
        && m <= n
        && pp.fetch_bits_field(cs, m, "s")
        && pp.close();
    }
  case hml_long: {
    int m;
    return cs.advance(2)
        && pp.open("hml_long")
        && cs.fetch_uint_leq(n, m)
        && pp.field_int(m, "n")
        && pp.fetch_bits_field(cs, m, "s")
        && pp.close();
    }
  case hml_same: {
    int m;
    return cs.advance(2)
        && pp.open("hml_same")
        && pp.fetch_uint_field(cs, 1, "v")
        && cs.fetch_uint_leq(n, m)
        && pp.field_int(m, "n")
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for HmLabel");
}

bool HmLabel::print_skip(PrettyPrinter&pp, vm::CellSlice& cs, int& m) const {
  switch (get_tag(cs)) {
  case hml_short:
    return cs.advance(1)
        && pp.open("hml_short")
        && pp.field("len")
        && t_Unary.print_skip(pp, cs, m)
        && m <= n
        && pp.fetch_bits_field(cs, m, "s")
        && pp.close();
  case hml_long:
    return cs.advance(2)
        && pp.open("hml_long")
        && cs.fetch_uint_leq(n, m)
        && pp.field_int(m, "n")
        && pp.fetch_bits_field(cs, m, "s")
        && pp.close();
  case hml_same:
    return cs.advance(2)
        && pp.open("hml_same")
        && pp.fetch_uint_field(cs, 1, "v")
        && cs.fetch_uint_leq(n, m)
        && pp.field_int(m, "n")
        && pp.close();
  }
  return pp.fail("unknown constructor for HmLabel");
}


//
// code for type `Unary`
//

bool Unary::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case unary_zero:
    return cs.advance(1);
  case unary_succ: {
    int n;
    return cs.advance(1)
        && skip(cs, n);
    }
  }
  return false;
}

bool Unary::skip(vm::CellSlice& cs, int& m) const {
  switch (get_tag(cs)) {
  case unary_zero:
    return (m = 0) >= 0
        && cs.advance(1);
  case unary_succ: {
    int n;
    return cs.advance(1)
        && skip(cs, n)
        && (m = n + 1) >= 0;
    }
  }
  return false;
}

bool Unary::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case unary_zero:
    return cs.advance(1);
  case unary_succ: {
    int n;
    return cs.advance(1)
        && validate_skip(cs, n);
    }
  }
  return false;
}

bool Unary::validate_skip(vm::CellSlice& cs, int& m) const {
  switch (get_tag(cs)) {
  case unary_zero:
    return (m = 0) >= 0
        && cs.advance(1);
  case unary_succ: {
    int n;
    return cs.advance(1)
        && validate_skip(cs, n)
        && (m = n + 1) >= 0;
    }
  }
  return false;
}

bool Unary::fetch_to(vm::CellSlice& cs, Ref<vm::CellSlice>& res, int& m) const {
  res = Ref<vm::CellSlice>{true, cs};
  return skip(cs, m) && res.unique_write().cut_tail(cs);
}

bool Unary::unpack(vm::CellSlice& cs, Unary::Record_unary_zero& data, int& m) const {
  return cs.fetch_ulong(1) == 0
      && (m = 0) >= 0;
}

bool Unary::unpack_unary_zero(vm::CellSlice& cs, int& m) const {
  return cs.fetch_ulong(1) == 0
      && (m = 0) >= 0;
}

bool Unary::cell_unpack(Ref<vm::Cell> cell_ref, Unary::Record_unary_zero& data, int& m) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data, m) && cs.empty_ext();
}

bool Unary::cell_unpack_unary_zero(Ref<vm::Cell> cell_ref, int& m) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_unary_zero(cs, m) && cs.empty_ext();
}

bool Unary::unpack(vm::CellSlice& cs, Unary::Record_unary_succ& data, int& m) const {
  return cs.fetch_ulong(1) == 1
      && fetch_to(cs, data.x, data.n)
      && (m = data.n + 1) >= 0;
}

bool Unary::cell_unpack(Ref<vm::Cell> cell_ref, Unary::Record_unary_succ& data, int& m) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data, m) && cs.empty_ext();
}

bool Unary::pack(vm::CellBuilder& cb, const Unary::Record_unary_zero& data, int& m) const {
  return cb.store_long_bool(0, 1)
      && (m = 0) >= 0;
}

bool Unary::pack_unary_zero(vm::CellBuilder& cb, int& m) const {
  return cb.store_long_bool(0, 1)
      && (m = 0) >= 0;
}

bool Unary::cell_pack(Ref<vm::Cell>& cell_ref, const Unary::Record_unary_zero& data, int& m) const {
  vm::CellBuilder cb;
  return pack(cb, data, m) && std::move(cb).finalize_to(cell_ref);
}

bool Unary::cell_pack_unary_zero(Ref<vm::Cell>& cell_ref, int& m) const {
  vm::CellBuilder cb;
  return pack_unary_zero(cb, m) && std::move(cb).finalize_to(cell_ref);
}

bool Unary::pack(vm::CellBuilder& cb, const Unary::Record_unary_succ& data, int& m) const {
  int n;
  return cb.store_long_bool(1, 1)
      && tlb::store_from(cb, *this, data.x, n)
      && (m = n + 1) >= 0;
}

bool Unary::cell_pack(Ref<vm::Cell>& cell_ref, const Unary::Record_unary_succ& data, int& m) const {
  vm::CellBuilder cb;
  return pack(cb, data, m) && std::move(cb).finalize_to(cell_ref);
}

bool Unary::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case unary_zero:
    return cs.advance(1)
        && pp.cons("unary_zero");
  case unary_succ: {
    int n;
    return cs.advance(1)
        && pp.open("unary_succ")
        && pp.field("x")
        && print_skip(pp, cs, n)
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for Unary");
}

bool Unary::print_skip(PrettyPrinter&pp, vm::CellSlice& cs, int& m) const {
  switch (get_tag(cs)) {
  case unary_zero:
    return cs.advance(1)
        && pp.cons("unary_zero")
        && (m = 0) >= 0;
  case unary_succ: {
    int n;
    return cs.advance(1)
        && pp.open("unary_succ")
        && pp.field("x")
        && print_skip(pp, cs, n)
        && (m = n + 1) >= 0
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for Unary");
}

const Unary t_Unary;

//
// code for type `HashmapE`
//

bool HashmapE::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case hme_empty:
    return cs.advance(1);
  case hme_root:
    return cs.advance_ext(0x10001);
  }
  return false;
}

bool HashmapE::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case hme_empty:
    return cs.advance(1);
  case hme_root:
    return cs.advance(1)
        && Hashmap{m, X}.validate_skip_ref(cs);
  }
  return false;
}

bool HashmapE::unpack(vm::CellSlice& cs, HashmapE::Record_hme_empty& data) const {
  return cs.fetch_ulong(1) == 0;
}

bool HashmapE::unpack_hme_empty(vm::CellSlice& cs) const {
  return cs.fetch_ulong(1) == 0;
}

bool HashmapE::cell_unpack(Ref<vm::Cell> cell_ref, HashmapE::Record_hme_empty& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HashmapE::cell_unpack_hme_empty(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_hme_empty(cs) && cs.empty_ext();
}

bool HashmapE::unpack(vm::CellSlice& cs, HashmapE::Record_hme_root& data) const {
  return cs.fetch_ulong(1) == 1
      && (data.n = m) >= 0
      && cs.fetch_ref_to(data.root);
}

bool HashmapE::cell_unpack(Ref<vm::Cell> cell_ref, HashmapE::Record_hme_root& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HashmapE::pack(vm::CellBuilder& cb, const HashmapE::Record_hme_empty& data) const {
  return cb.store_long_bool(0, 1);
}

bool HashmapE::pack_hme_empty(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 1);
}

bool HashmapE::cell_pack(Ref<vm::Cell>& cell_ref, const HashmapE::Record_hme_empty& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapE::cell_pack_hme_empty(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_hme_empty(cb) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapE::pack(vm::CellBuilder& cb, const HashmapE::Record_hme_root& data) const {
  return cb.store_long_bool(1, 1)
      && cb.store_ref_bool(data.root);
}

bool HashmapE::cell_pack(Ref<vm::Cell>& cell_ref, const HashmapE::Record_hme_root& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapE::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case hme_empty:
    return cs.advance(1)
        && pp.cons("hme_empty");
  case hme_root:
    return cs.advance(1)
        && pp.open("hme_root")
        && pp.field("root")
        && Hashmap{m, X}.print_ref(pp, cs.fetch_ref())
        && pp.close();
  }
  return pp.fail("unknown constructor for HashmapE");
}


//
// code for type `BitstringSet`
//

bool BitstringSet::skip(vm::CellSlice& cs) const {
  return Hashmap{m, t_True}.skip(cs);
}

bool BitstringSet::validate_skip(vm::CellSlice& cs) const {
  return Hashmap{m, t_True}.validate_skip(cs);
}

bool BitstringSet::unpack(vm::CellSlice& cs, BitstringSet::Record& data) const {
  return (data.n = m) >= 0
      && Hashmap{m, t_True}.fetch_to(cs, data.x);
}

bool BitstringSet::cell_unpack(Ref<vm::Cell> cell_ref, BitstringSet::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BitstringSet::pack(vm::CellBuilder& cb, const BitstringSet::Record& data) const {
  return Hashmap{m, t_True}.store_from(cb, data.x);
}

bool BitstringSet::cell_pack(Ref<vm::Cell>& cell_ref, const BitstringSet::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BitstringSet::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && Hashmap{m, t_True}.print_skip(pp, cs)
      && pp.close();
}


//
// code for type `VarHashmap`
//

bool VarHashmap::skip(vm::CellSlice& cs) const {
  int l, m1;
  return HmLabel{m}.skip(cs, l)
      && add_r1(m1, l, m)
      && VarHashmapNode{m1, X}.skip(cs);
}

bool VarHashmap::validate_skip(vm::CellSlice& cs) const {
  int l, m1;
  return HmLabel{m}.validate_skip(cs, l)
      && add_r1(m1, l, m)
      && VarHashmapNode{m1, X}.validate_skip(cs);
}

bool VarHashmap::unpack(vm::CellSlice& cs, VarHashmap::Record& data) const {
  return (data.n = m) >= 0
      && HmLabel{m}.fetch_to(cs, data.label, data.l)
      && add_r1(data.m, data.l, m)
      && VarHashmapNode{data.m, X}.fetch_to(cs, data.node);
}

bool VarHashmap::cell_unpack(Ref<vm::Cell> cell_ref, VarHashmap::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool VarHashmap::pack(vm::CellBuilder& cb, const VarHashmap::Record& data) const {
  int l, m1;
  return tlb::store_from(cb, HmLabel{m}, data.label, l)
      && add_r1(m1, l, m)
      && VarHashmapNode{m1, X}.store_from(cb, data.node);
}

bool VarHashmap::cell_pack(Ref<vm::Cell>& cell_ref, const VarHashmap::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool VarHashmap::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int l, m1;
  return pp.open("vhm_edge")
      && pp.field("label")
      && HmLabel{m}.print_skip(pp, cs, l)
      && add_r1(m1, l, m)
      && pp.field("node")
      && VarHashmapNode{m1, X}.print_skip(pp, cs)
      && pp.close();
}


//
// code for type `VarHashmapNode`
//
constexpr char VarHashmapNode::cons_len[3];
constexpr unsigned char VarHashmapNode::cons_tag[3];

bool VarHashmapNode::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case vhmn_leaf:
    return cs.advance(2)
        && X.skip(cs);
  case vhmn_fork: {
    int n;
    return add_r1(n, 1, m)
        && cs.advance_ext(0x20002)
        && Maybe{X}.skip(cs);
    }
  case vhmn_cont: {
    int n;
    return add_r1(n, 1, m)
        && cs.advance_ext(0x10002)
        && X.skip(cs);
    }
  }
  return false;
}

bool VarHashmapNode::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case vhmn_leaf:
    return cs.advance(2)
        && X.validate_skip(cs);
  case vhmn_fork: {
    int n;
    return add_r1(n, 1, m)
        && cs.advance(2)
        && VarHashmap{n, X}.validate_skip_ref(cs)
        && VarHashmap{n, X}.validate_skip_ref(cs)
        && Maybe{X}.validate_skip(cs);
    }
  case vhmn_cont: {
    int n;
    return add_r1(n, 1, m)
        && cs.advance(2)
        && VarHashmap{n, X}.validate_skip_ref(cs)
        && X.validate_skip(cs);
    }
  }
  return false;
}

bool VarHashmapNode::unpack(vm::CellSlice& cs, VarHashmapNode::Record_vhmn_leaf& data) const {
  return cs.fetch_ulong(2) == 0
      && X.fetch_to(cs, data.value);
}

bool VarHashmapNode::unpack_vhmn_leaf(vm::CellSlice& cs, Ref<CellSlice>& value) const {
  return cs.fetch_ulong(2) == 0
      && X.fetch_to(cs, value);
}

bool VarHashmapNode::cell_unpack(Ref<vm::Cell> cell_ref, VarHashmapNode::Record_vhmn_leaf& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool VarHashmapNode::cell_unpack_vhmn_leaf(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_vhmn_leaf(cs, value) && cs.empty_ext();
}

bool VarHashmapNode::unpack(vm::CellSlice& cs, VarHashmapNode::Record_vhmn_fork& data) const {
  return cs.fetch_ulong(2) == 1
      && add_r1(data.n, 1, m)
      && cs.fetch_ref_to(data.left)
      && cs.fetch_ref_to(data.right)
      && Maybe{X}.fetch_to(cs, data.value);
}

bool VarHashmapNode::cell_unpack(Ref<vm::Cell> cell_ref, VarHashmapNode::Record_vhmn_fork& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool VarHashmapNode::unpack(vm::CellSlice& cs, VarHashmapNode::Record_vhmn_cont& data) const {
  return cs.fetch_ulong(1) == 1
      && add_r1(data.n, 1, m)
      && cs.fetch_bool_to(data.branch)
      && cs.fetch_ref_to(data.child)
      && X.fetch_to(cs, data.value);
}

bool VarHashmapNode::cell_unpack(Ref<vm::Cell> cell_ref, VarHashmapNode::Record_vhmn_cont& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool VarHashmapNode::pack(vm::CellBuilder& cb, const VarHashmapNode::Record_vhmn_leaf& data) const {
  return cb.store_long_bool(0, 2)
      && X.store_from(cb, data.value);
}

bool VarHashmapNode::pack_vhmn_leaf(vm::CellBuilder& cb, Ref<CellSlice> value) const {
  return cb.store_long_bool(0, 2)
      && X.store_from(cb, value);
}

bool VarHashmapNode::cell_pack(Ref<vm::Cell>& cell_ref, const VarHashmapNode::Record_vhmn_leaf& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool VarHashmapNode::cell_pack_vhmn_leaf(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const {
  vm::CellBuilder cb;
  return pack_vhmn_leaf(cb, std::move(value)) && std::move(cb).finalize_to(cell_ref);
}

bool VarHashmapNode::pack(vm::CellBuilder& cb, const VarHashmapNode::Record_vhmn_fork& data) const {
  int n;
  return cb.store_long_bool(1, 2)
      && add_r1(n, 1, m)
      && cb.store_ref_bool(data.left)
      && cb.store_ref_bool(data.right)
      && Maybe{X}.store_from(cb, data.value);
}

bool VarHashmapNode::cell_pack(Ref<vm::Cell>& cell_ref, const VarHashmapNode::Record_vhmn_fork& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool VarHashmapNode::pack(vm::CellBuilder& cb, const VarHashmapNode::Record_vhmn_cont& data) const {
  int n;
  return cb.store_long_bool(1, 1)
      && add_r1(n, 1, m)
      && cb.store_ulong_rchk_bool(data.branch, 1)
      && cb.store_ref_bool(data.child)
      && X.store_from(cb, data.value);
}

bool VarHashmapNode::cell_pack(Ref<vm::Cell>& cell_ref, const VarHashmapNode::Record_vhmn_cont& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool VarHashmapNode::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case vhmn_leaf:
    return cs.advance(2)
        && pp.open("vhmn_leaf")
        && pp.field("value")
        && X.print_skip(pp, cs)
        && pp.close();
  case vhmn_fork: {
    int n;
    return cs.advance(2)
        && pp.open("vhmn_fork")
        && add_r1(n, 1, m)
        && pp.field("left")
        && VarHashmap{n, X}.print_ref(pp, cs.fetch_ref())
        && pp.field("right")
        && VarHashmap{n, X}.print_ref(pp, cs.fetch_ref())
        && pp.field("value")
        && Maybe{X}.print_skip(pp, cs)
        && pp.close();
    }
  case vhmn_cont: {
    int n;
    return cs.advance(1)
        && pp.open("vhmn_cont")
        && add_r1(n, 1, m)
        && pp.fetch_uint_field(cs, 1, "branch")
        && pp.field("child")
        && VarHashmap{n, X}.print_ref(pp, cs.fetch_ref())
        && pp.field("value")
        && X.print_skip(pp, cs)
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for VarHashmapNode");
}


//
// code for type `VarHashmapE`
//

bool VarHashmapE::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case vhme_empty:
    return cs.advance(1);
  case vhme_root:
    return cs.advance_ext(0x10001);
  }
  return false;
}

bool VarHashmapE::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case vhme_empty:
    return cs.advance(1);
  case vhme_root:
    return cs.advance(1)
        && VarHashmap{m, X}.validate_skip_ref(cs);
  }
  return false;
}

bool VarHashmapE::unpack(vm::CellSlice& cs, VarHashmapE::Record_vhme_empty& data) const {
  return cs.fetch_ulong(1) == 0;
}

bool VarHashmapE::unpack_vhme_empty(vm::CellSlice& cs) const {
  return cs.fetch_ulong(1) == 0;
}

bool VarHashmapE::cell_unpack(Ref<vm::Cell> cell_ref, VarHashmapE::Record_vhme_empty& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool VarHashmapE::cell_unpack_vhme_empty(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_vhme_empty(cs) && cs.empty_ext();
}

bool VarHashmapE::unpack(vm::CellSlice& cs, VarHashmapE::Record_vhme_root& data) const {
  return cs.fetch_ulong(1) == 1
      && (data.n = m) >= 0
      && cs.fetch_ref_to(data.root);
}

bool VarHashmapE::cell_unpack(Ref<vm::Cell> cell_ref, VarHashmapE::Record_vhme_root& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool VarHashmapE::pack(vm::CellBuilder& cb, const VarHashmapE::Record_vhme_empty& data) const {
  return cb.store_long_bool(0, 1);
}

bool VarHashmapE::pack_vhme_empty(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 1);
}

bool VarHashmapE::cell_pack(Ref<vm::Cell>& cell_ref, const VarHashmapE::Record_vhme_empty& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool VarHashmapE::cell_pack_vhme_empty(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_vhme_empty(cb) && std::move(cb).finalize_to(cell_ref);
}

bool VarHashmapE::pack(vm::CellBuilder& cb, const VarHashmapE::Record_vhme_root& data) const {
  return cb.store_long_bool(1, 1)
      && cb.store_ref_bool(data.root);
}

bool VarHashmapE::cell_pack(Ref<vm::Cell>& cell_ref, const VarHashmapE::Record_vhme_root& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool VarHashmapE::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case vhme_empty:
    return cs.advance(1)
        && pp.cons("vhme_empty");
  case vhme_root:
    return cs.advance(1)
        && pp.open("vhme_root")
        && pp.field("root")
        && VarHashmap{m, X}.print_ref(pp, cs.fetch_ref())
        && pp.close();
  }
  return pp.fail("unknown constructor for VarHashmapE");
}


//
// code for type `PfxHashmap`
//

bool PfxHashmap::skip(vm::CellSlice& cs) const {
  int l, m1;
  return HmLabel{m}.skip(cs, l)
      && add_r1(m1, l, m)
      && PfxHashmapNode{m1, X}.skip(cs);
}

bool PfxHashmap::validate_skip(vm::CellSlice& cs) const {
  int l, m1;
  return HmLabel{m}.validate_skip(cs, l)
      && add_r1(m1, l, m)
      && PfxHashmapNode{m1, X}.validate_skip(cs);
}

bool PfxHashmap::unpack(vm::CellSlice& cs, PfxHashmap::Record& data) const {
  return (data.n = m) >= 0
      && HmLabel{m}.fetch_to(cs, data.label, data.l)
      && add_r1(data.m, data.l, m)
      && PfxHashmapNode{data.m, X}.fetch_to(cs, data.node);
}

bool PfxHashmap::cell_unpack(Ref<vm::Cell> cell_ref, PfxHashmap::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool PfxHashmap::pack(vm::CellBuilder& cb, const PfxHashmap::Record& data) const {
  int l, m1;
  return tlb::store_from(cb, HmLabel{m}, data.label, l)
      && add_r1(m1, l, m)
      && PfxHashmapNode{m1, X}.store_from(cb, data.node);
}

bool PfxHashmap::cell_pack(Ref<vm::Cell>& cell_ref, const PfxHashmap::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool PfxHashmap::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int l, m1;
  return pp.open("phm_edge")
      && pp.field("label")
      && HmLabel{m}.print_skip(pp, cs, l)
      && add_r1(m1, l, m)
      && pp.field("node")
      && PfxHashmapNode{m1, X}.print_skip(pp, cs)
      && pp.close();
}


//
// code for type `PfxHashmapNode`
//

bool PfxHashmapNode::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case phmn_leaf:
    return cs.advance(1)
        && X.skip(cs);
  case phmn_fork: {
    int n;
    return add_r1(n, 1, m)
        && cs.advance_ext(0x20001);
    }
  }
  return false;
}

bool PfxHashmapNode::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case phmn_leaf:
    return cs.advance(1)
        && X.validate_skip(cs);
  case phmn_fork: {
    int n;
    return add_r1(n, 1, m)
        && cs.advance(1)
        && PfxHashmap{n, X}.validate_skip_ref(cs)
        && PfxHashmap{n, X}.validate_skip_ref(cs);
    }
  }
  return false;
}

bool PfxHashmapNode::unpack(vm::CellSlice& cs, PfxHashmapNode::Record_phmn_leaf& data) const {
  return cs.fetch_ulong(1) == 0
      && X.fetch_to(cs, data.value);
}

bool PfxHashmapNode::unpack_phmn_leaf(vm::CellSlice& cs, Ref<CellSlice>& value) const {
  return cs.fetch_ulong(1) == 0
      && X.fetch_to(cs, value);
}

bool PfxHashmapNode::cell_unpack(Ref<vm::Cell> cell_ref, PfxHashmapNode::Record_phmn_leaf& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool PfxHashmapNode::cell_unpack_phmn_leaf(Ref<vm::Cell> cell_ref, Ref<CellSlice>& value) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_phmn_leaf(cs, value) && cs.empty_ext();
}

bool PfxHashmapNode::unpack(vm::CellSlice& cs, PfxHashmapNode::Record_phmn_fork& data) const {
  return cs.fetch_ulong(1) == 1
      && add_r1(data.n, 1, m)
      && cs.fetch_ref_to(data.left)
      && cs.fetch_ref_to(data.right);
}

bool PfxHashmapNode::cell_unpack(Ref<vm::Cell> cell_ref, PfxHashmapNode::Record_phmn_fork& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool PfxHashmapNode::pack(vm::CellBuilder& cb, const PfxHashmapNode::Record_phmn_leaf& data) const {
  return cb.store_long_bool(0, 1)
      && X.store_from(cb, data.value);
}

bool PfxHashmapNode::pack_phmn_leaf(vm::CellBuilder& cb, Ref<CellSlice> value) const {
  return cb.store_long_bool(0, 1)
      && X.store_from(cb, value);
}

bool PfxHashmapNode::cell_pack(Ref<vm::Cell>& cell_ref, const PfxHashmapNode::Record_phmn_leaf& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool PfxHashmapNode::cell_pack_phmn_leaf(Ref<vm::Cell>& cell_ref, Ref<CellSlice> value) const {
  vm::CellBuilder cb;
  return pack_phmn_leaf(cb, std::move(value)) && std::move(cb).finalize_to(cell_ref);
}

bool PfxHashmapNode::pack(vm::CellBuilder& cb, const PfxHashmapNode::Record_phmn_fork& data) const {
  int n;
  return cb.store_long_bool(1, 1)
      && add_r1(n, 1, m)
      && cb.store_ref_bool(data.left)
      && cb.store_ref_bool(data.right);
}

bool PfxHashmapNode::cell_pack(Ref<vm::Cell>& cell_ref, const PfxHashmapNode::Record_phmn_fork& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool PfxHashmapNode::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case phmn_leaf:
    return cs.advance(1)
        && pp.open("phmn_leaf")
        && pp.field("value")
        && X.print_skip(pp, cs)
        && pp.close();
  case phmn_fork: {
    int n;
    return cs.advance(1)
        && pp.open("phmn_fork")
        && add_r1(n, 1, m)
        && pp.field("left")
        && PfxHashmap{n, X}.print_ref(pp, cs.fetch_ref())
        && pp.field("right")
        && PfxHashmap{n, X}.print_ref(pp, cs.fetch_ref())
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for PfxHashmapNode");
}


//
// code for type `PfxHashmapE`
//

bool PfxHashmapE::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case phme_empty:
    return cs.advance(1);
  case phme_root:
    return cs.advance_ext(0x10001);
  }
  return false;
}

bool PfxHashmapE::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case phme_empty:
    return cs.advance(1);
  case phme_root:
    return cs.advance(1)
        && PfxHashmap{m, X}.validate_skip_ref(cs);
  }
  return false;
}

bool PfxHashmapE::unpack(vm::CellSlice& cs, PfxHashmapE::Record_phme_empty& data) const {
  return cs.fetch_ulong(1) == 0;
}

bool PfxHashmapE::unpack_phme_empty(vm::CellSlice& cs) const {
  return cs.fetch_ulong(1) == 0;
}

bool PfxHashmapE::cell_unpack(Ref<vm::Cell> cell_ref, PfxHashmapE::Record_phme_empty& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool PfxHashmapE::cell_unpack_phme_empty(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_phme_empty(cs) && cs.empty_ext();
}

bool PfxHashmapE::unpack(vm::CellSlice& cs, PfxHashmapE::Record_phme_root& data) const {
  return cs.fetch_ulong(1) == 1
      && (data.n = m) >= 0
      && cs.fetch_ref_to(data.root);
}

bool PfxHashmapE::cell_unpack(Ref<vm::Cell> cell_ref, PfxHashmapE::Record_phme_root& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool PfxHashmapE::pack(vm::CellBuilder& cb, const PfxHashmapE::Record_phme_empty& data) const {
  return cb.store_long_bool(0, 1);
}

bool PfxHashmapE::pack_phme_empty(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 1);
}

bool PfxHashmapE::cell_pack(Ref<vm::Cell>& cell_ref, const PfxHashmapE::Record_phme_empty& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool PfxHashmapE::cell_pack_phme_empty(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_phme_empty(cb) && std::move(cb).finalize_to(cell_ref);
}

bool PfxHashmapE::pack(vm::CellBuilder& cb, const PfxHashmapE::Record_phme_root& data) const {
  return cb.store_long_bool(1, 1)
      && cb.store_ref_bool(data.root);
}

bool PfxHashmapE::cell_pack(Ref<vm::Cell>& cell_ref, const PfxHashmapE::Record_phme_root& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool PfxHashmapE::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case phme_empty:
    return cs.advance(1)
        && pp.cons("phme_empty");
  case phme_root:
    return cs.advance(1)
        && pp.open("phme_root")
        && pp.field("root")
        && PfxHashmap{m, X}.print_ref(pp, cs.fetch_ref())
        && pp.close();
  }
  return pp.fail("unknown constructor for PfxHashmapE");
}


//
// code for type `MsgAddressExt`
//

bool MsgAddressExt::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case addr_none:
    return cs.advance(2);
  case addr_extern: {
    int len;
    return cs.advance(2)
        && cs.fetch_uint_to(8, len)
        && cs.advance(len);
    }
  }
  return false;
}

bool MsgAddressExt::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case addr_none:
    return cs.advance(2);
  case addr_extern: {
    int len;
    return cs.fetch_ulong(2) == 1
        && cs.fetch_uint_to(8, len)
        && cs.advance(len);
    }
  }
  return false;
}

bool MsgAddressExt::unpack(vm::CellSlice& cs, MsgAddressExt::Record_addr_none& data) const {
  return cs.fetch_ulong(2) == 0;
}

bool MsgAddressExt::unpack_addr_none(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 0;
}

bool MsgAddressExt::cell_unpack(Ref<vm::Cell> cell_ref, MsgAddressExt::Record_addr_none& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MsgAddressExt::cell_unpack_addr_none(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_addr_none(cs) && cs.empty_ext();
}

bool MsgAddressExt::unpack(vm::CellSlice& cs, MsgAddressExt::Record_addr_extern& data) const {
  return cs.fetch_ulong(2) == 1
      && cs.fetch_uint_to(8, data.len)
      && cs.fetch_bitstring_to(data.len, data.external_address);
}

bool MsgAddressExt::cell_unpack(Ref<vm::Cell> cell_ref, MsgAddressExt::Record_addr_extern& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MsgAddressExt::pack(vm::CellBuilder& cb, const MsgAddressExt::Record_addr_none& data) const {
  return cb.store_long_bool(0, 2);
}

bool MsgAddressExt::pack_addr_none(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 2);
}

bool MsgAddressExt::cell_pack(Ref<vm::Cell>& cell_ref, const MsgAddressExt::Record_addr_none& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MsgAddressExt::cell_pack_addr_none(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_addr_none(cb) && std::move(cb).finalize_to(cell_ref);
}

bool MsgAddressExt::pack(vm::CellBuilder& cb, const MsgAddressExt::Record_addr_extern& data) const {
  return cb.store_long_bool(1, 2)
      && cb.store_ulong_rchk_bool(data.len, 8)
      && cb.append_bitstring_chk(data.external_address, data.len);
}

bool MsgAddressExt::cell_pack(Ref<vm::Cell>& cell_ref, const MsgAddressExt::Record_addr_extern& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MsgAddressExt::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case addr_none:
    return cs.advance(2)
        && pp.cons("addr_none");
  case addr_extern: {
    int len;
    return cs.fetch_ulong(2) == 1
        && pp.open("addr_extern")
        && cs.fetch_uint_to(8, len)
        && pp.field_int(len, "len")
        && pp.fetch_bits_field(cs, len, "external_address")
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for MsgAddressExt");
}

const MsgAddressExt t_MsgAddressExt;

//
// code for type `Anycast`
//

bool Anycast::skip(vm::CellSlice& cs) const {
  int depth;
  return cs.fetch_uint_leq(30, depth)
      && 1 <= depth
      && cs.advance(depth);
}

bool Anycast::validate_skip(vm::CellSlice& cs) const {
  int depth;
  return cs.fetch_uint_leq(30, depth)
      && 1 <= depth
      && cs.advance(depth);
}

bool Anycast::unpack(vm::CellSlice& cs, Anycast::Record& data) const {
  return cs.fetch_uint_leq(30, data.depth)
      && 1 <= data.depth
      && cs.fetch_bitstring_to(data.depth, data.rewrite_pfx);
}

bool Anycast::cell_unpack(Ref<vm::Cell> cell_ref, Anycast::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Anycast::pack(vm::CellBuilder& cb, const Anycast::Record& data) const {
  return cb.store_uint_leq(30, data.depth)
      && 1 <= data.depth
      && cb.append_bitstring_chk(data.rewrite_pfx, data.depth);
}

bool Anycast::cell_pack(Ref<vm::Cell>& cell_ref, const Anycast::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Anycast::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int depth;
  return pp.open("anycast_info")
      && cs.fetch_uint_leq(30, depth)
      && pp.field_int(depth, "depth")
      && 1 <= depth
      && pp.fetch_bits_field(cs, depth, "rewrite_pfx")
      && pp.close();
}

const Anycast t_Anycast;

//
// code for type `MsgAddressInt`
//
constexpr unsigned char MsgAddressInt::cons_tag[2];

bool MsgAddressInt::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case addr_std:
    return cs.advance(2)
        && t_Maybe_Anycast.skip(cs)
        && cs.advance(264);
  case addr_var: {
    int addr_len;
    return cs.advance(2)
        && t_Maybe_Anycast.skip(cs)
        && cs.fetch_uint_to(9, addr_len)
        && cs.advance(32)
        && cs.advance(addr_len);
    }
  }
  return false;
}

bool MsgAddressInt::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case addr_std:
    return cs.advance(2)
        && t_Maybe_Anycast.validate_skip(cs)
        && cs.advance(264);
  case addr_var: {
    int addr_len;
    return cs.advance(2)
        && t_Maybe_Anycast.validate_skip(cs)
        && cs.fetch_uint_to(9, addr_len)
        && cs.advance(32)
        && cs.advance(addr_len);
    }
  }
  return false;
}

bool MsgAddressInt::unpack(vm::CellSlice& cs, MsgAddressInt::Record_addr_std& data) const {
  return cs.fetch_ulong(2) == 2
      && t_Maybe_Anycast.fetch_to(cs, data.anycast)
      && cs.fetch_int_to(8, data.workchain_id)
      && cs.fetch_bits_to(data.address.bits(), 256);
}

bool MsgAddressInt::cell_unpack(Ref<vm::Cell> cell_ref, MsgAddressInt::Record_addr_std& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MsgAddressInt::unpack(vm::CellSlice& cs, MsgAddressInt::Record_addr_var& data) const {
  return cs.fetch_ulong(2) == 3
      && t_Maybe_Anycast.fetch_to(cs, data.anycast)
      && cs.fetch_uint_to(9, data.addr_len)
      && cs.fetch_int_to(32, data.workchain_id)
      && cs.fetch_bitstring_to(data.addr_len, data.address);
}

bool MsgAddressInt::cell_unpack(Ref<vm::Cell> cell_ref, MsgAddressInt::Record_addr_var& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MsgAddressInt::pack(vm::CellBuilder& cb, const MsgAddressInt::Record_addr_std& data) const {
  return cb.store_long_bool(2, 2)
      && t_Maybe_Anycast.store_from(cb, data.anycast)
      && cb.store_long_rchk_bool(data.workchain_id, 8)
      && cb.store_bits_bool(data.address.cbits(), 256);
}

bool MsgAddressInt::cell_pack(Ref<vm::Cell>& cell_ref, const MsgAddressInt::Record_addr_std& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MsgAddressInt::pack(vm::CellBuilder& cb, const MsgAddressInt::Record_addr_var& data) const {
  return cb.store_long_bool(3, 2)
      && t_Maybe_Anycast.store_from(cb, data.anycast)
      && cb.store_ulong_rchk_bool(data.addr_len, 9)
      && cb.store_long_rchk_bool(data.workchain_id, 32)
      && cb.append_bitstring_chk(data.address, data.addr_len);
}

bool MsgAddressInt::cell_pack(Ref<vm::Cell>& cell_ref, const MsgAddressInt::Record_addr_var& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MsgAddressInt::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case addr_std:
    return cs.advance(2)
        && pp.open("addr_std")
        && pp.field("anycast")
        && t_Maybe_Anycast.print_skip(pp, cs)
        && pp.fetch_int_field(cs, 8, "workchain_id")
        && pp.fetch_bits_field(cs, 256, "address")
        && pp.close();
  case addr_var: {
    int addr_len;
    return cs.advance(2)
        && pp.open("addr_var")
        && pp.field("anycast")
        && t_Maybe_Anycast.print_skip(pp, cs)
        && cs.fetch_uint_to(9, addr_len)
        && pp.field_int(addr_len, "addr_len")
        && pp.fetch_int_field(cs, 32, "workchain_id")
        && pp.fetch_bits_field(cs, addr_len, "address")
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for MsgAddressInt");
}

const MsgAddressInt t_MsgAddressInt;

//
// code for type `MsgAddress`
//

bool MsgAddress::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cons1:
    return t_MsgAddressInt.skip(cs);
  case cons2:
    return t_MsgAddressExt.skip(cs);
  }
  return false;
}

bool MsgAddress::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cons1:
    return t_MsgAddressInt.validate_skip(cs);
  case cons2:
    return t_MsgAddressExt.validate_skip(cs);
  }
  return false;
}

bool MsgAddress::unpack(vm::CellSlice& cs, MsgAddress::Record_cons1& data) const {
  return t_MsgAddressInt.fetch_to(cs, data.x);
}

bool MsgAddress::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_MsgAddressInt.fetch_to(cs, x);
}

bool MsgAddress::cell_unpack(Ref<vm::Cell> cell_ref, MsgAddress::Record_cons1& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MsgAddress::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool MsgAddress::unpack(vm::CellSlice& cs, MsgAddress::Record_cons2& data) const {
  return t_MsgAddressExt.fetch_to(cs, data.x);
}

bool MsgAddress::unpack_cons2(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_MsgAddressExt.fetch_to(cs, x);
}

bool MsgAddress::cell_unpack(Ref<vm::Cell> cell_ref, MsgAddress::Record_cons2& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MsgAddress::cell_unpack_cons2(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons2(cs, x) && cs.empty_ext();
}

bool MsgAddress::pack(vm::CellBuilder& cb, const MsgAddress::Record_cons1& data) const {
  return t_MsgAddressInt.store_from(cb, data.x);
}

bool MsgAddress::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_MsgAddressInt.store_from(cb, x);
}

bool MsgAddress::cell_pack(Ref<vm::Cell>& cell_ref, const MsgAddress::Record_cons1& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MsgAddress::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool MsgAddress::pack(vm::CellBuilder& cb, const MsgAddress::Record_cons2& data) const {
  return t_MsgAddressExt.store_from(cb, data.x);
}

bool MsgAddress::pack_cons2(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_MsgAddressExt.store_from(cb, x);
}

bool MsgAddress::cell_pack(Ref<vm::Cell>& cell_ref, const MsgAddress::Record_cons2& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MsgAddress::cell_pack_cons2(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons2(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool MsgAddress::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cons1:
    return pp.open()
        && pp.field()
        && t_MsgAddressInt.print_skip(pp, cs)
        && pp.close();
  case cons2:
    return pp.open()
        && pp.field()
        && t_MsgAddressExt.print_skip(pp, cs)
        && pp.close();
  }
  return pp.fail("unknown constructor for MsgAddress");
}

const MsgAddress t_MsgAddress;

//
// code for type `VarUInteger`
//

bool VarUInteger::skip(vm::CellSlice& cs) const {
  int len;
  return cs.fetch_uint_less(m, len)
      && cs.advance(8 * len);
}

bool VarUInteger::validate_skip(vm::CellSlice& cs) const {
  int len;
  return cs.fetch_uint_less(m, len)
      && cs.advance(8 * len);
}

bool VarUInteger::unpack(vm::CellSlice& cs, VarUInteger::Record& data) const {
  return (data.n = m) >= 0
      && cs.fetch_uint_less(m, data.len)
      && cs.fetch_uint256_to(8 * data.len, data.value);
}

bool VarUInteger::cell_unpack(Ref<vm::Cell> cell_ref, VarUInteger::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool VarUInteger::pack(vm::CellBuilder& cb, const VarUInteger::Record& data) const {
  return cb.store_uint_less(m, data.len)
      && cb.store_bigint256_bool(data.value, 8 * data.len, false);
}

bool VarUInteger::cell_pack(Ref<vm::Cell>& cell_ref, const VarUInteger::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool VarUInteger::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int len;
  return pp.open("var_uint")
      && cs.fetch_uint_less(m, len)
      && pp.field_int(len, "len")
      && pp.fetch_uint256_field(cs, 8 * len, "value")
      && pp.close();
}


//
// code for type `VarInteger`
//

bool VarInteger::skip(vm::CellSlice& cs) const {
  int len;
  return cs.fetch_uint_less(m, len)
      && cs.advance(8 * len);
}

bool VarInteger::validate_skip(vm::CellSlice& cs) const {
  int len;
  return cs.fetch_uint_less(m, len)
      && cs.advance(8 * len);
}

bool VarInteger::unpack(vm::CellSlice& cs, VarInteger::Record& data) const {
  return (data.n = m) >= 0
      && cs.fetch_uint_less(m, data.len)
      && cs.fetch_int256_to(8 * data.len, data.value);
}

bool VarInteger::cell_unpack(Ref<vm::Cell> cell_ref, VarInteger::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool VarInteger::pack(vm::CellBuilder& cb, const VarInteger::Record& data) const {
  return cb.store_uint_less(m, data.len)
      && cb.store_bigint256_bool(data.value, 8 * data.len);
}

bool VarInteger::cell_pack(Ref<vm::Cell>& cell_ref, const VarInteger::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool VarInteger::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int len;
  return pp.open("var_int")
      && cs.fetch_uint_less(m, len)
      && pp.field_int(len, "len")
      && pp.fetch_int256_field(cs, 8 * len, "value")
      && pp.close();
}


//
// code for type `Grams`
//

bool Grams::skip(vm::CellSlice& cs) const {
  return t_VarUInteger_16.skip(cs);
}

bool Grams::validate_skip(vm::CellSlice& cs) const {
  return t_VarUInteger_16.validate_skip(cs);
}

bool Grams::unpack(vm::CellSlice& cs, Grams::Record& data) const {
  return t_VarUInteger_16.fetch_to(cs, data.amount);
}

bool Grams::unpack_nanograms(vm::CellSlice& cs, Ref<CellSlice>& amount) const {
  return t_VarUInteger_16.fetch_to(cs, amount);
}

bool Grams::cell_unpack(Ref<vm::Cell> cell_ref, Grams::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Grams::cell_unpack_nanograms(Ref<vm::Cell> cell_ref, Ref<CellSlice>& amount) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_nanograms(cs, amount) && cs.empty_ext();
}

bool Grams::pack(vm::CellBuilder& cb, const Grams::Record& data) const {
  return t_VarUInteger_16.store_from(cb, data.amount);
}

bool Grams::pack_nanograms(vm::CellBuilder& cb, Ref<CellSlice> amount) const {
  return t_VarUInteger_16.store_from(cb, amount);
}

bool Grams::cell_pack(Ref<vm::Cell>& cell_ref, const Grams::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Grams::cell_pack_nanograms(Ref<vm::Cell>& cell_ref, Ref<CellSlice> amount) const {
  vm::CellBuilder cb;
  return pack_nanograms(cb, std::move(amount)) && std::move(cb).finalize_to(cell_ref);
}

bool Grams::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("nanograms")
      && pp.field("amount")
      && t_VarUInteger_16.print_skip(pp, cs)
      && pp.close();
}

const Grams t_Grams;

//
// code for type `ExtraCurrencyCollection`
//

bool ExtraCurrencyCollection::skip(vm::CellSlice& cs) const {
  return t_HashmapE_32_VarUInteger_32.skip(cs);
}

bool ExtraCurrencyCollection::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapE_32_VarUInteger_32.validate_skip(cs);
}

bool ExtraCurrencyCollection::unpack(vm::CellSlice& cs, ExtraCurrencyCollection::Record& data) const {
  return t_HashmapE_32_VarUInteger_32.fetch_to(cs, data.dict);
}

bool ExtraCurrencyCollection::unpack_extra_currencies(vm::CellSlice& cs, Ref<CellSlice>& dict) const {
  return t_HashmapE_32_VarUInteger_32.fetch_to(cs, dict);
}

bool ExtraCurrencyCollection::cell_unpack(Ref<vm::Cell> cell_ref, ExtraCurrencyCollection::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ExtraCurrencyCollection::cell_unpack_extra_currencies(Ref<vm::Cell> cell_ref, Ref<CellSlice>& dict) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_extra_currencies(cs, dict) && cs.empty_ext();
}

bool ExtraCurrencyCollection::pack(vm::CellBuilder& cb, const ExtraCurrencyCollection::Record& data) const {
  return t_HashmapE_32_VarUInteger_32.store_from(cb, data.dict);
}

bool ExtraCurrencyCollection::pack_extra_currencies(vm::CellBuilder& cb, Ref<CellSlice> dict) const {
  return t_HashmapE_32_VarUInteger_32.store_from(cb, dict);
}

bool ExtraCurrencyCollection::cell_pack(Ref<vm::Cell>& cell_ref, const ExtraCurrencyCollection::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ExtraCurrencyCollection::cell_pack_extra_currencies(Ref<vm::Cell>& cell_ref, Ref<CellSlice> dict) const {
  vm::CellBuilder cb;
  return pack_extra_currencies(cb, std::move(dict)) && std::move(cb).finalize_to(cell_ref);
}

bool ExtraCurrencyCollection::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("extra_currencies")
      && pp.field("dict")
      && t_HashmapE_32_VarUInteger_32.print_skip(pp, cs)
      && pp.close();
}

const ExtraCurrencyCollection t_ExtraCurrencyCollection;

//
// code for type `CurrencyCollection`
//

bool CurrencyCollection::skip(vm::CellSlice& cs) const {
  return t_Grams.skip(cs)
      && t_ExtraCurrencyCollection.skip(cs);
}

bool CurrencyCollection::validate_skip(vm::CellSlice& cs) const {
  return t_Grams.validate_skip(cs)
      && t_ExtraCurrencyCollection.validate_skip(cs);
}

bool CurrencyCollection::unpack(vm::CellSlice& cs, CurrencyCollection::Record& data) const {
  return t_Grams.fetch_to(cs, data.grams)
      && t_ExtraCurrencyCollection.fetch_to(cs, data.other);
}

bool CurrencyCollection::cell_unpack(Ref<vm::Cell> cell_ref, CurrencyCollection::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool CurrencyCollection::pack(vm::CellBuilder& cb, const CurrencyCollection::Record& data) const {
  return t_Grams.store_from(cb, data.grams)
      && t_ExtraCurrencyCollection.store_from(cb, data.other);
}

bool CurrencyCollection::cell_pack(Ref<vm::Cell>& cell_ref, const CurrencyCollection::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool CurrencyCollection::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("currencies")
      && pp.field("grams")
      && t_Grams.print_skip(pp, cs)
      && pp.field("other")
      && t_ExtraCurrencyCollection.print_skip(pp, cs)
      && pp.close();
}

const CurrencyCollection t_CurrencyCollection;

//
// code for type `CommonMsgInfo`
//
constexpr char CommonMsgInfo::cons_len[3];
constexpr unsigned char CommonMsgInfo::cons_tag[3];

bool CommonMsgInfo::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case int_msg_info:
    return cs.advance(4)
        && t_MsgAddressInt.skip(cs)
        && t_MsgAddressInt.skip(cs)
        && t_CurrencyCollection.skip(cs)
        && t_Grams.skip(cs)
        && t_Grams.skip(cs)
        && cs.advance(96);
  case ext_in_msg_info:
    return cs.advance(2)
        && t_MsgAddressExt.skip(cs)
        && t_MsgAddressInt.skip(cs)
        && t_Grams.skip(cs);
  case ext_out_msg_info:
    return cs.advance(2)
        && t_MsgAddressInt.skip(cs)
        && t_MsgAddressExt.skip(cs)
        && cs.advance(96);
  }
  return false;
}

bool CommonMsgInfo::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case int_msg_info:
    return cs.advance(4)
        && t_MsgAddressInt.validate_skip(cs)
        && t_MsgAddressInt.validate_skip(cs)
        && t_CurrencyCollection.validate_skip(cs)
        && t_Grams.validate_skip(cs)
        && t_Grams.validate_skip(cs)
        && cs.advance(96);
  case ext_in_msg_info:
    return cs.advance(2)
        && t_MsgAddressExt.validate_skip(cs)
        && t_MsgAddressInt.validate_skip(cs)
        && t_Grams.validate_skip(cs);
  case ext_out_msg_info:
    return cs.advance(2)
        && t_MsgAddressInt.validate_skip(cs)
        && t_MsgAddressExt.validate_skip(cs)
        && cs.advance(96);
  }
  return false;
}

bool CommonMsgInfo::unpack(vm::CellSlice& cs, CommonMsgInfo::Record_int_msg_info& data) const {
  return cs.fetch_ulong(1) == 0
      && cs.fetch_bool_to(data.ihr_disabled)
      && cs.fetch_bool_to(data.bounce)
      && cs.fetch_bool_to(data.bounced)
      && t_MsgAddressInt.fetch_to(cs, data.src)
      && t_MsgAddressInt.fetch_to(cs, data.dest)
      && t_CurrencyCollection.fetch_to(cs, data.value)
      && t_Grams.fetch_to(cs, data.ihr_fee)
      && t_Grams.fetch_to(cs, data.fwd_fee)
      && cs.fetch_uint_to(64, data.created_lt)
      && cs.fetch_uint_to(32, data.created_at);
}

bool CommonMsgInfo::cell_unpack(Ref<vm::Cell> cell_ref, CommonMsgInfo::Record_int_msg_info& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool CommonMsgInfo::unpack(vm::CellSlice& cs, CommonMsgInfo::Record_ext_in_msg_info& data) const {
  return cs.fetch_ulong(2) == 2
      && t_MsgAddressExt.fetch_to(cs, data.src)
      && t_MsgAddressInt.fetch_to(cs, data.dest)
      && t_Grams.fetch_to(cs, data.import_fee);
}

bool CommonMsgInfo::cell_unpack(Ref<vm::Cell> cell_ref, CommonMsgInfo::Record_ext_in_msg_info& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool CommonMsgInfo::unpack(vm::CellSlice& cs, CommonMsgInfo::Record_ext_out_msg_info& data) const {
  return cs.fetch_ulong(2) == 3
      && t_MsgAddressInt.fetch_to(cs, data.src)
      && t_MsgAddressExt.fetch_to(cs, data.dest)
      && cs.fetch_uint_to(64, data.created_lt)
      && cs.fetch_uint_to(32, data.created_at);
}

bool CommonMsgInfo::cell_unpack(Ref<vm::Cell> cell_ref, CommonMsgInfo::Record_ext_out_msg_info& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool CommonMsgInfo::pack(vm::CellBuilder& cb, const CommonMsgInfo::Record_int_msg_info& data) const {
  return cb.store_long_bool(0, 1)
      && cb.store_ulong_rchk_bool(data.ihr_disabled, 1)
      && cb.store_ulong_rchk_bool(data.bounce, 1)
      && cb.store_ulong_rchk_bool(data.bounced, 1)
      && t_MsgAddressInt.store_from(cb, data.src)
      && t_MsgAddressInt.store_from(cb, data.dest)
      && t_CurrencyCollection.store_from(cb, data.value)
      && t_Grams.store_from(cb, data.ihr_fee)
      && t_Grams.store_from(cb, data.fwd_fee)
      && cb.store_ulong_rchk_bool(data.created_lt, 64)
      && cb.store_ulong_rchk_bool(data.created_at, 32);
}

bool CommonMsgInfo::cell_pack(Ref<vm::Cell>& cell_ref, const CommonMsgInfo::Record_int_msg_info& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool CommonMsgInfo::pack(vm::CellBuilder& cb, const CommonMsgInfo::Record_ext_in_msg_info& data) const {
  return cb.store_long_bool(2, 2)
      && t_MsgAddressExt.store_from(cb, data.src)
      && t_MsgAddressInt.store_from(cb, data.dest)
      && t_Grams.store_from(cb, data.import_fee);
}

bool CommonMsgInfo::cell_pack(Ref<vm::Cell>& cell_ref, const CommonMsgInfo::Record_ext_in_msg_info& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool CommonMsgInfo::pack(vm::CellBuilder& cb, const CommonMsgInfo::Record_ext_out_msg_info& data) const {
  return cb.store_long_bool(3, 2)
      && t_MsgAddressInt.store_from(cb, data.src)
      && t_MsgAddressExt.store_from(cb, data.dest)
      && cb.store_ulong_rchk_bool(data.created_lt, 64)
      && cb.store_ulong_rchk_bool(data.created_at, 32);
}

bool CommonMsgInfo::cell_pack(Ref<vm::Cell>& cell_ref, const CommonMsgInfo::Record_ext_out_msg_info& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool CommonMsgInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case int_msg_info:
    return cs.advance(1)
        && pp.open("int_msg_info")
        && pp.fetch_uint_field(cs, 1, "ihr_disabled")
        && pp.fetch_uint_field(cs, 1, "bounce")
        && pp.fetch_uint_field(cs, 1, "bounced")
        && pp.field("src")
        && t_MsgAddressInt.print_skip(pp, cs)
        && pp.field("dest")
        && t_MsgAddressInt.print_skip(pp, cs)
        && pp.field("value")
        && t_CurrencyCollection.print_skip(pp, cs)
        && pp.field("ihr_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.field("fwd_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 64, "created_lt")
        && pp.fetch_uint_field(cs, 32, "created_at")
        && pp.close();
  case ext_in_msg_info:
    return cs.advance(2)
        && pp.open("ext_in_msg_info")
        && pp.field("src")
        && t_MsgAddressExt.print_skip(pp, cs)
        && pp.field("dest")
        && t_MsgAddressInt.print_skip(pp, cs)
        && pp.field("import_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.close();
  case ext_out_msg_info:
    return cs.advance(2)
        && pp.open("ext_out_msg_info")
        && pp.field("src")
        && t_MsgAddressInt.print_skip(pp, cs)
        && pp.field("dest")
        && t_MsgAddressExt.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 64, "created_lt")
        && pp.fetch_uint_field(cs, 32, "created_at")
        && pp.close();
  }
  return pp.fail("unknown constructor for CommonMsgInfo");
}

const CommonMsgInfo t_CommonMsgInfo;

//
// code for type `CommonMsgInfoRelaxed`
//
constexpr char CommonMsgInfoRelaxed::cons_len[2];
constexpr unsigned char CommonMsgInfoRelaxed::cons_tag[2];

bool CommonMsgInfoRelaxed::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case int_msg_info:
    return cs.advance(4)
        && t_MsgAddress.skip(cs)
        && t_MsgAddressInt.skip(cs)
        && t_CurrencyCollection.skip(cs)
        && t_Grams.skip(cs)
        && t_Grams.skip(cs)
        && cs.advance(96);
  case ext_out_msg_info:
    return cs.advance(2)
        && t_MsgAddress.skip(cs)
        && t_MsgAddressExt.skip(cs)
        && cs.advance(96);
  }
  return false;
}

bool CommonMsgInfoRelaxed::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case int_msg_info:
    return cs.advance(4)
        && t_MsgAddress.validate_skip(cs)
        && t_MsgAddressInt.validate_skip(cs)
        && t_CurrencyCollection.validate_skip(cs)
        && t_Grams.validate_skip(cs)
        && t_Grams.validate_skip(cs)
        && cs.advance(96);
  case ext_out_msg_info:
    return cs.fetch_ulong(2) == 3
        && t_MsgAddress.validate_skip(cs)
        && t_MsgAddressExt.validate_skip(cs)
        && cs.advance(96);
  }
  return false;
}

bool CommonMsgInfoRelaxed::unpack(vm::CellSlice& cs, CommonMsgInfoRelaxed::Record_int_msg_info& data) const {
  return cs.fetch_ulong(1) == 0
      && cs.fetch_bool_to(data.ihr_disabled)
      && cs.fetch_bool_to(data.bounce)
      && cs.fetch_bool_to(data.bounced)
      && t_MsgAddress.fetch_to(cs, data.src)
      && t_MsgAddressInt.fetch_to(cs, data.dest)
      && t_CurrencyCollection.fetch_to(cs, data.value)
      && t_Grams.fetch_to(cs, data.ihr_fee)
      && t_Grams.fetch_to(cs, data.fwd_fee)
      && cs.fetch_uint_to(64, data.created_lt)
      && cs.fetch_uint_to(32, data.created_at);
}

bool CommonMsgInfoRelaxed::cell_unpack(Ref<vm::Cell> cell_ref, CommonMsgInfoRelaxed::Record_int_msg_info& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool CommonMsgInfoRelaxed::unpack(vm::CellSlice& cs, CommonMsgInfoRelaxed::Record_ext_out_msg_info& data) const {
  return cs.fetch_ulong(2) == 3
      && t_MsgAddress.fetch_to(cs, data.src)
      && t_MsgAddressExt.fetch_to(cs, data.dest)
      && cs.fetch_uint_to(64, data.created_lt)
      && cs.fetch_uint_to(32, data.created_at);
}

bool CommonMsgInfoRelaxed::cell_unpack(Ref<vm::Cell> cell_ref, CommonMsgInfoRelaxed::Record_ext_out_msg_info& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool CommonMsgInfoRelaxed::pack(vm::CellBuilder& cb, const CommonMsgInfoRelaxed::Record_int_msg_info& data) const {
  return cb.store_long_bool(0, 1)
      && cb.store_ulong_rchk_bool(data.ihr_disabled, 1)
      && cb.store_ulong_rchk_bool(data.bounce, 1)
      && cb.store_ulong_rchk_bool(data.bounced, 1)
      && t_MsgAddress.store_from(cb, data.src)
      && t_MsgAddressInt.store_from(cb, data.dest)
      && t_CurrencyCollection.store_from(cb, data.value)
      && t_Grams.store_from(cb, data.ihr_fee)
      && t_Grams.store_from(cb, data.fwd_fee)
      && cb.store_ulong_rchk_bool(data.created_lt, 64)
      && cb.store_ulong_rchk_bool(data.created_at, 32);
}

bool CommonMsgInfoRelaxed::cell_pack(Ref<vm::Cell>& cell_ref, const CommonMsgInfoRelaxed::Record_int_msg_info& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool CommonMsgInfoRelaxed::pack(vm::CellBuilder& cb, const CommonMsgInfoRelaxed::Record_ext_out_msg_info& data) const {
  return cb.store_long_bool(3, 2)
      && t_MsgAddress.store_from(cb, data.src)
      && t_MsgAddressExt.store_from(cb, data.dest)
      && cb.store_ulong_rchk_bool(data.created_lt, 64)
      && cb.store_ulong_rchk_bool(data.created_at, 32);
}

bool CommonMsgInfoRelaxed::cell_pack(Ref<vm::Cell>& cell_ref, const CommonMsgInfoRelaxed::Record_ext_out_msg_info& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool CommonMsgInfoRelaxed::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case int_msg_info:
    return cs.advance(1)
        && pp.open("int_msg_info")
        && pp.fetch_uint_field(cs, 1, "ihr_disabled")
        && pp.fetch_uint_field(cs, 1, "bounce")
        && pp.fetch_uint_field(cs, 1, "bounced")
        && pp.field("src")
        && t_MsgAddress.print_skip(pp, cs)
        && pp.field("dest")
        && t_MsgAddressInt.print_skip(pp, cs)
        && pp.field("value")
        && t_CurrencyCollection.print_skip(pp, cs)
        && pp.field("ihr_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.field("fwd_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 64, "created_lt")
        && pp.fetch_uint_field(cs, 32, "created_at")
        && pp.close();
  case ext_out_msg_info:
    return cs.fetch_ulong(2) == 3
        && pp.open("ext_out_msg_info")
        && pp.field("src")
        && t_MsgAddress.print_skip(pp, cs)
        && pp.field("dest")
        && t_MsgAddressExt.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 64, "created_lt")
        && pp.fetch_uint_field(cs, 32, "created_at")
        && pp.close();
  }
  return pp.fail("unknown constructor for CommonMsgInfoRelaxed");
}

const CommonMsgInfoRelaxed t_CommonMsgInfoRelaxed;

//
// code for type `TickTock`
//

bool TickTock::unpack(vm::CellSlice& cs, TickTock::Record& data) const {
  return cs.fetch_bool_to(data.tick)
      && cs.fetch_bool_to(data.tock);
}

bool TickTock::cell_unpack(Ref<vm::Cell> cell_ref, TickTock::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TickTock::pack(vm::CellBuilder& cb, const TickTock::Record& data) const {
  return cb.store_ulong_rchk_bool(data.tick, 1)
      && cb.store_ulong_rchk_bool(data.tock, 1);
}

bool TickTock::cell_pack(Ref<vm::Cell>& cell_ref, const TickTock::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TickTock::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("tick_tock")
      && pp.fetch_uint_field(cs, 1, "tick")
      && pp.fetch_uint_field(cs, 1, "tock")
      && pp.close();
}

const TickTock t_TickTock;

//
// code for type `StateInit`
//

bool StateInit::skip(vm::CellSlice& cs) const {
  return t_Maybe_natwidth_5.skip(cs)
      && t_Maybe_TickTock.skip(cs)
      && t_Maybe_Ref_Cell.skip(cs)
      && t_Maybe_Ref_Cell.skip(cs)
      && t_HashmapE_256_SimpleLib.skip(cs);
}

bool StateInit::validate_skip(vm::CellSlice& cs) const {
  return t_Maybe_natwidth_5.validate_skip(cs)
      && t_Maybe_TickTock.validate_skip(cs)
      && t_Maybe_Ref_Cell.validate_skip(cs)
      && t_Maybe_Ref_Cell.validate_skip(cs)
      && t_HashmapE_256_SimpleLib.validate_skip(cs);
}

bool StateInit::unpack(vm::CellSlice& cs, StateInit::Record& data) const {
  return t_Maybe_natwidth_5.fetch_to(cs, data.split_depth)
      && t_Maybe_TickTock.fetch_to(cs, data.special)
      && t_Maybe_Ref_Cell.fetch_to(cs, data.code)
      && t_Maybe_Ref_Cell.fetch_to(cs, data.data)
      && t_HashmapE_256_SimpleLib.fetch_to(cs, data.library);
}

bool StateInit::cell_unpack(Ref<vm::Cell> cell_ref, StateInit::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool StateInit::pack(vm::CellBuilder& cb, const StateInit::Record& data) const {
  return t_Maybe_natwidth_5.store_from(cb, data.split_depth)
      && t_Maybe_TickTock.store_from(cb, data.special)
      && t_Maybe_Ref_Cell.store_from(cb, data.code)
      && t_Maybe_Ref_Cell.store_from(cb, data.data)
      && t_HashmapE_256_SimpleLib.store_from(cb, data.library);
}

bool StateInit::cell_pack(Ref<vm::Cell>& cell_ref, const StateInit::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool StateInit::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field("split_depth")
      && t_Maybe_natwidth_5.print_skip(pp, cs)
      && pp.field("special")
      && t_Maybe_TickTock.print_skip(pp, cs)
      && pp.field("code")
      && t_Maybe_Ref_Cell.print_skip(pp, cs)
      && pp.field("data")
      && t_Maybe_Ref_Cell.print_skip(pp, cs)
      && pp.field("library")
      && t_HashmapE_256_SimpleLib.print_skip(pp, cs)
      && pp.close();
}

const StateInit t_StateInit;

//
// code for type `SimpleLib`
//

bool SimpleLib::validate_skip(vm::CellSlice& cs) const {
  return cs.advance_ext(0x10001);
}

bool SimpleLib::unpack(vm::CellSlice& cs, SimpleLib::Record& data) const {
  return cs.fetch_bool_to(data.public1)
      && cs.fetch_ref_to(data.root);
}

bool SimpleLib::cell_unpack(Ref<vm::Cell> cell_ref, SimpleLib::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool SimpleLib::pack(vm::CellBuilder& cb, const SimpleLib::Record& data) const {
  return cb.store_ulong_rchk_bool(data.public1, 1)
      && cb.store_ref_bool(data.root);
}

bool SimpleLib::cell_pack(Ref<vm::Cell>& cell_ref, const SimpleLib::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool SimpleLib::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("simple_lib")
      && pp.fetch_uint_field(cs, 1, "public")
      && pp.field("root")
      && t_Anything.print_ref(pp, cs.fetch_ref())
      && pp.close();
}

const SimpleLib t_SimpleLib;

//
// code for type `Message`
//

bool Message::skip(vm::CellSlice& cs) const {
  return t_CommonMsgInfo.skip(cs)
      && t_Maybe_Either_StateInit_Ref_StateInit.skip(cs)
      && Either{X, RefT{X}}.skip(cs);
}

bool Message::validate_skip(vm::CellSlice& cs) const {
  return t_CommonMsgInfo.validate_skip(cs)
      && t_Maybe_Either_StateInit_Ref_StateInit.validate_skip(cs)
      && Either{X, RefT{X}}.validate_skip(cs);
}

bool Message::unpack(vm::CellSlice& cs, Message::Record& data) const {
  return t_CommonMsgInfo.fetch_to(cs, data.info)
      && t_Maybe_Either_StateInit_Ref_StateInit.fetch_to(cs, data.init)
      && Either{X, RefT{X}}.fetch_to(cs, data.body);
}

bool Message::cell_unpack(Ref<vm::Cell> cell_ref, Message::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Message::pack(vm::CellBuilder& cb, const Message::Record& data) const {
  return t_CommonMsgInfo.store_from(cb, data.info)
      && t_Maybe_Either_StateInit_Ref_StateInit.store_from(cb, data.init)
      && Either{X, RefT{X}}.store_from(cb, data.body);
}

bool Message::cell_pack(Ref<vm::Cell>& cell_ref, const Message::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Message::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("message")
      && pp.field("info")
      && t_CommonMsgInfo.print_skip(pp, cs)
      && pp.field("init")
      && t_Maybe_Either_StateInit_Ref_StateInit.print_skip(pp, cs)
      && pp.field("body")
      && Either{X, RefT{X}}.print_skip(pp, cs)
      && pp.close();
}


//
// code for type `MessageRelaxed`
//

bool MessageRelaxed::skip(vm::CellSlice& cs) const {
  return t_CommonMsgInfoRelaxed.skip(cs)
      && t_Maybe_Either_StateInit_Ref_StateInit.skip(cs)
      && Either{X, RefT{X}}.skip(cs);
}

bool MessageRelaxed::validate_skip(vm::CellSlice& cs) const {
  return t_CommonMsgInfoRelaxed.validate_skip(cs)
      && t_Maybe_Either_StateInit_Ref_StateInit.validate_skip(cs)
      && Either{X, RefT{X}}.validate_skip(cs);
}

bool MessageRelaxed::unpack(vm::CellSlice& cs, MessageRelaxed::Record& data) const {
  return t_CommonMsgInfoRelaxed.fetch_to(cs, data.info)
      && t_Maybe_Either_StateInit_Ref_StateInit.fetch_to(cs, data.init)
      && Either{X, RefT{X}}.fetch_to(cs, data.body);
}

bool MessageRelaxed::cell_unpack(Ref<vm::Cell> cell_ref, MessageRelaxed::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MessageRelaxed::pack(vm::CellBuilder& cb, const MessageRelaxed::Record& data) const {
  return t_CommonMsgInfoRelaxed.store_from(cb, data.info)
      && t_Maybe_Either_StateInit_Ref_StateInit.store_from(cb, data.init)
      && Either{X, RefT{X}}.store_from(cb, data.body);
}

bool MessageRelaxed::cell_pack(Ref<vm::Cell>& cell_ref, const MessageRelaxed::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MessageRelaxed::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("message")
      && pp.field("info")
      && t_CommonMsgInfoRelaxed.print_skip(pp, cs)
      && pp.field("init")
      && t_Maybe_Either_StateInit_Ref_StateInit.print_skip(pp, cs)
      && pp.field("body")
      && Either{X, RefT{X}}.print_skip(pp, cs)
      && pp.close();
}


//
// code for type `IntermediateAddress`
//
constexpr char IntermediateAddress::cons_len[3];
constexpr unsigned char IntermediateAddress::cons_tag[3];

bool IntermediateAddress::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case interm_addr_regular:
    return cs.advance(8);
  case interm_addr_simple:
    return cs.advance(74);
  case interm_addr_ext:
    return cs.advance(98);
  }
  return false;
}

bool IntermediateAddress::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case interm_addr_regular: {
    int use_dest_bits;
    return cs.advance(1)
        && cs.fetch_uint_leq(96, use_dest_bits);
    }
  case interm_addr_simple:
    return cs.advance(74);
  case interm_addr_ext:
    return cs.advance(98);
  }
  return false;
}

bool IntermediateAddress::unpack(vm::CellSlice& cs, IntermediateAddress::Record_interm_addr_regular& data) const {
  return cs.fetch_ulong(1) == 0
      && cs.fetch_uint_leq(96, data.use_dest_bits);
}

bool IntermediateAddress::unpack_interm_addr_regular(vm::CellSlice& cs, int& use_dest_bits) const {
  return cs.fetch_ulong(1) == 0
      && cs.fetch_uint_leq(96, use_dest_bits);
}

bool IntermediateAddress::cell_unpack(Ref<vm::Cell> cell_ref, IntermediateAddress::Record_interm_addr_regular& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool IntermediateAddress::cell_unpack_interm_addr_regular(Ref<vm::Cell> cell_ref, int& use_dest_bits) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_interm_addr_regular(cs, use_dest_bits) && cs.empty_ext();
}

bool IntermediateAddress::unpack(vm::CellSlice& cs, IntermediateAddress::Record_interm_addr_simple& data) const {
  return cs.fetch_ulong(2) == 2
      && cs.fetch_int_to(8, data.workchain_id)
      && cs.fetch_uint_to(64, data.addr_pfx);
}

bool IntermediateAddress::cell_unpack(Ref<vm::Cell> cell_ref, IntermediateAddress::Record_interm_addr_simple& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool IntermediateAddress::unpack(vm::CellSlice& cs, IntermediateAddress::Record_interm_addr_ext& data) const {
  return cs.fetch_ulong(2) == 3
      && cs.fetch_int_to(32, data.workchain_id)
      && cs.fetch_uint_to(64, data.addr_pfx);
}

bool IntermediateAddress::cell_unpack(Ref<vm::Cell> cell_ref, IntermediateAddress::Record_interm_addr_ext& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool IntermediateAddress::pack(vm::CellBuilder& cb, const IntermediateAddress::Record_interm_addr_regular& data) const {
  return cb.store_long_bool(0, 1)
      && cb.store_uint_leq(96, data.use_dest_bits);
}

bool IntermediateAddress::pack_interm_addr_regular(vm::CellBuilder& cb, int use_dest_bits) const {
  return cb.store_long_bool(0, 1)
      && cb.store_uint_leq(96, use_dest_bits);
}

bool IntermediateAddress::cell_pack(Ref<vm::Cell>& cell_ref, const IntermediateAddress::Record_interm_addr_regular& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool IntermediateAddress::cell_pack_interm_addr_regular(Ref<vm::Cell>& cell_ref, int use_dest_bits) const {
  vm::CellBuilder cb;
  return pack_interm_addr_regular(cb, use_dest_bits) && std::move(cb).finalize_to(cell_ref);
}

bool IntermediateAddress::pack(vm::CellBuilder& cb, const IntermediateAddress::Record_interm_addr_simple& data) const {
  return cb.store_long_bool(2, 2)
      && cb.store_long_rchk_bool(data.workchain_id, 8)
      && cb.store_ulong_rchk_bool(data.addr_pfx, 64);
}

bool IntermediateAddress::cell_pack(Ref<vm::Cell>& cell_ref, const IntermediateAddress::Record_interm_addr_simple& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool IntermediateAddress::pack(vm::CellBuilder& cb, const IntermediateAddress::Record_interm_addr_ext& data) const {
  return cb.store_long_bool(3, 2)
      && cb.store_long_rchk_bool(data.workchain_id, 32)
      && cb.store_ulong_rchk_bool(data.addr_pfx, 64);
}

bool IntermediateAddress::cell_pack(Ref<vm::Cell>& cell_ref, const IntermediateAddress::Record_interm_addr_ext& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool IntermediateAddress::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case interm_addr_regular: {
    int use_dest_bits;
    return cs.advance(1)
        && pp.open("interm_addr_regular")
        && cs.fetch_uint_leq(96, use_dest_bits)
        && pp.field_int(use_dest_bits, "use_dest_bits")
        && pp.close();
    }
  case interm_addr_simple:
    return cs.advance(2)
        && pp.open("interm_addr_simple")
        && pp.fetch_int_field(cs, 8, "workchain_id")
        && pp.fetch_uint_field(cs, 64, "addr_pfx")
        && pp.close();
  case interm_addr_ext:
    return cs.advance(2)
        && pp.open("interm_addr_ext")
        && pp.fetch_int_field(cs, 32, "workchain_id")
        && pp.fetch_uint_field(cs, 64, "addr_pfx")
        && pp.close();
  }
  return pp.fail("unknown constructor for IntermediateAddress");
}

const IntermediateAddress t_IntermediateAddress;

//
// code for type `MsgEnvelope`
//
constexpr unsigned char MsgEnvelope::cons_tag[1];

bool MsgEnvelope::skip(vm::CellSlice& cs) const {
  return cs.advance(4)
      && t_IntermediateAddress.skip(cs)
      && t_IntermediateAddress.skip(cs)
      && t_Grams.skip(cs)
      && cs.advance_refs(1);
}

bool MsgEnvelope::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 4
      && t_IntermediateAddress.validate_skip(cs)
      && t_IntermediateAddress.validate_skip(cs)
      && t_Grams.validate_skip(cs)
      && t_Message_Any.validate_skip_ref(cs);
}

bool MsgEnvelope::unpack(vm::CellSlice& cs, MsgEnvelope::Record& data) const {
  return cs.fetch_ulong(4) == 4
      && t_IntermediateAddress.fetch_to(cs, data.cur_addr)
      && t_IntermediateAddress.fetch_to(cs, data.next_addr)
      && t_Grams.fetch_to(cs, data.fwd_fee_remaining)
      && cs.fetch_ref_to(data.msg);
}

bool MsgEnvelope::cell_unpack(Ref<vm::Cell> cell_ref, MsgEnvelope::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MsgEnvelope::pack(vm::CellBuilder& cb, const MsgEnvelope::Record& data) const {
  return cb.store_long_bool(4, 4)
      && t_IntermediateAddress.store_from(cb, data.cur_addr)
      && t_IntermediateAddress.store_from(cb, data.next_addr)
      && t_Grams.store_from(cb, data.fwd_fee_remaining)
      && cb.store_ref_bool(data.msg);
}

bool MsgEnvelope::cell_pack(Ref<vm::Cell>& cell_ref, const MsgEnvelope::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MsgEnvelope::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 4
      && pp.open("msg_envelope")
      && pp.field("cur_addr")
      && t_IntermediateAddress.print_skip(pp, cs)
      && pp.field("next_addr")
      && t_IntermediateAddress.print_skip(pp, cs)
      && pp.field("fwd_fee_remaining")
      && t_Grams.print_skip(pp, cs)
      && pp.field("msg")
      && t_Message_Any.print_ref(pp, cs.fetch_ref())
      && pp.close();
}

const MsgEnvelope t_MsgEnvelope;

//
// code for type `InMsg`
//
constexpr unsigned char InMsg::cons_tag[7];

bool InMsg::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case msg_import_ext:
    return cs.advance_ext(0x20003);
  case msg_import_ihr:
    return cs.advance_ext(0x20003)
        && t_Grams.skip(cs)
        && cs.advance_refs(1);
  case msg_import_imm:
    return cs.advance_ext(0x20003)
        && t_Grams.skip(cs);
  case msg_import_fin:
    return cs.advance_ext(0x20003)
        && t_Grams.skip(cs);
  case msg_import_tr:
    return cs.advance_ext(0x20003)
        && t_Grams.skip(cs);
  case msg_discard_fin:
    return cs.advance_ext(0x10043)
        && t_Grams.skip(cs);
  case msg_discard_tr:
    return cs.advance_ext(0x10043)
        && t_Grams.skip(cs)
        && cs.advance_refs(1);
  }
  return false;
}

bool InMsg::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case msg_import_ext:
    return cs.fetch_ulong(3) == 0
        && t_Message_Any.validate_skip_ref(cs)
        && t_Transaction.validate_skip_ref(cs);
  case msg_import_ihr:
    return cs.advance(3)
        && t_Message_Any.validate_skip_ref(cs)
        && t_Transaction.validate_skip_ref(cs)
        && t_Grams.validate_skip(cs)
        && cs.advance_refs(1);
  case msg_import_imm:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && t_Transaction.validate_skip_ref(cs)
        && t_Grams.validate_skip(cs);
  case msg_import_fin:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && t_Transaction.validate_skip_ref(cs)
        && t_Grams.validate_skip(cs);
  case msg_import_tr:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && t_Grams.validate_skip(cs);
  case msg_discard_fin:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && cs.advance(64)
        && t_Grams.validate_skip(cs);
  case msg_discard_tr:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && cs.advance(64)
        && t_Grams.validate_skip(cs)
        && cs.advance_refs(1);
  }
  return false;
}

bool InMsg::unpack(vm::CellSlice& cs, InMsg::Record_msg_import_ext& data) const {
  return cs.fetch_ulong(3) == 0
      && cs.fetch_ref_to(data.msg)
      && cs.fetch_ref_to(data.transaction);
}

bool InMsg::cell_unpack(Ref<vm::Cell> cell_ref, InMsg::Record_msg_import_ext& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool InMsg::unpack(vm::CellSlice& cs, InMsg::Record_msg_import_ihr& data) const {
  return cs.fetch_ulong(3) == 2
      && cs.fetch_ref_to(data.msg)
      && cs.fetch_ref_to(data.transaction)
      && t_Grams.fetch_to(cs, data.ihr_fee)
      && cs.fetch_ref_to(data.proof_created);
}

bool InMsg::cell_unpack(Ref<vm::Cell> cell_ref, InMsg::Record_msg_import_ihr& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool InMsg::unpack(vm::CellSlice& cs, InMsg::Record_msg_import_imm& data) const {
  return cs.fetch_ulong(3) == 3
      && cs.fetch_ref_to(data.in_msg)
      && cs.fetch_ref_to(data.transaction)
      && t_Grams.fetch_to(cs, data.fwd_fee);
}

bool InMsg::cell_unpack(Ref<vm::Cell> cell_ref, InMsg::Record_msg_import_imm& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool InMsg::unpack(vm::CellSlice& cs, InMsg::Record_msg_import_fin& data) const {
  return cs.fetch_ulong(3) == 4
      && cs.fetch_ref_to(data.in_msg)
      && cs.fetch_ref_to(data.transaction)
      && t_Grams.fetch_to(cs, data.fwd_fee);
}

bool InMsg::cell_unpack(Ref<vm::Cell> cell_ref, InMsg::Record_msg_import_fin& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool InMsg::unpack(vm::CellSlice& cs, InMsg::Record_msg_import_tr& data) const {
  return cs.fetch_ulong(3) == 5
      && cs.fetch_ref_to(data.in_msg)
      && cs.fetch_ref_to(data.out_msg)
      && t_Grams.fetch_to(cs, data.transit_fee);
}

bool InMsg::cell_unpack(Ref<vm::Cell> cell_ref, InMsg::Record_msg_import_tr& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool InMsg::unpack(vm::CellSlice& cs, InMsg::Record_msg_discard_fin& data) const {
  return cs.fetch_ulong(3) == 6
      && cs.fetch_ref_to(data.in_msg)
      && cs.fetch_uint_to(64, data.transaction_id)
      && t_Grams.fetch_to(cs, data.fwd_fee);
}

bool InMsg::cell_unpack(Ref<vm::Cell> cell_ref, InMsg::Record_msg_discard_fin& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool InMsg::unpack(vm::CellSlice& cs, InMsg::Record_msg_discard_tr& data) const {
  return cs.fetch_ulong(3) == 7
      && cs.fetch_ref_to(data.in_msg)
      && cs.fetch_uint_to(64, data.transaction_id)
      && t_Grams.fetch_to(cs, data.fwd_fee)
      && cs.fetch_ref_to(data.proof_delivered);
}

bool InMsg::cell_unpack(Ref<vm::Cell> cell_ref, InMsg::Record_msg_discard_tr& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool InMsg::pack(vm::CellBuilder& cb, const InMsg::Record_msg_import_ext& data) const {
  return cb.store_long_bool(0, 3)
      && cb.store_ref_bool(data.msg)
      && cb.store_ref_bool(data.transaction);
}

bool InMsg::cell_pack(Ref<vm::Cell>& cell_ref, const InMsg::Record_msg_import_ext& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool InMsg::pack(vm::CellBuilder& cb, const InMsg::Record_msg_import_ihr& data) const {
  return cb.store_long_bool(2, 3)
      && cb.store_ref_bool(data.msg)
      && cb.store_ref_bool(data.transaction)
      && t_Grams.store_from(cb, data.ihr_fee)
      && cb.store_ref_bool(data.proof_created);
}

bool InMsg::cell_pack(Ref<vm::Cell>& cell_ref, const InMsg::Record_msg_import_ihr& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool InMsg::pack(vm::CellBuilder& cb, const InMsg::Record_msg_import_imm& data) const {
  return cb.store_long_bool(3, 3)
      && cb.store_ref_bool(data.in_msg)
      && cb.store_ref_bool(data.transaction)
      && t_Grams.store_from(cb, data.fwd_fee);
}

bool InMsg::cell_pack(Ref<vm::Cell>& cell_ref, const InMsg::Record_msg_import_imm& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool InMsg::pack(vm::CellBuilder& cb, const InMsg::Record_msg_import_fin& data) const {
  return cb.store_long_bool(4, 3)
      && cb.store_ref_bool(data.in_msg)
      && cb.store_ref_bool(data.transaction)
      && t_Grams.store_from(cb, data.fwd_fee);
}

bool InMsg::cell_pack(Ref<vm::Cell>& cell_ref, const InMsg::Record_msg_import_fin& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool InMsg::pack(vm::CellBuilder& cb, const InMsg::Record_msg_import_tr& data) const {
  return cb.store_long_bool(5, 3)
      && cb.store_ref_bool(data.in_msg)
      && cb.store_ref_bool(data.out_msg)
      && t_Grams.store_from(cb, data.transit_fee);
}

bool InMsg::cell_pack(Ref<vm::Cell>& cell_ref, const InMsg::Record_msg_import_tr& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool InMsg::pack(vm::CellBuilder& cb, const InMsg::Record_msg_discard_fin& data) const {
  return cb.store_long_bool(6, 3)
      && cb.store_ref_bool(data.in_msg)
      && cb.store_ulong_rchk_bool(data.transaction_id, 64)
      && t_Grams.store_from(cb, data.fwd_fee);
}

bool InMsg::cell_pack(Ref<vm::Cell>& cell_ref, const InMsg::Record_msg_discard_fin& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool InMsg::pack(vm::CellBuilder& cb, const InMsg::Record_msg_discard_tr& data) const {
  return cb.store_long_bool(7, 3)
      && cb.store_ref_bool(data.in_msg)
      && cb.store_ulong_rchk_bool(data.transaction_id, 64)
      && t_Grams.store_from(cb, data.fwd_fee)
      && cb.store_ref_bool(data.proof_delivered);
}

bool InMsg::cell_pack(Ref<vm::Cell>& cell_ref, const InMsg::Record_msg_discard_tr& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool InMsg::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case msg_import_ext:
    return cs.fetch_ulong(3) == 0
        && pp.open("msg_import_ext")
        && pp.field("msg")
        && t_Message_Any.print_ref(pp, cs.fetch_ref())
        && pp.field("transaction")
        && t_Transaction.print_ref(pp, cs.fetch_ref())
        && pp.close();
  case msg_import_ihr:
    return cs.advance(3)
        && pp.open("msg_import_ihr")
        && pp.field("msg")
        && t_Message_Any.print_ref(pp, cs.fetch_ref())
        && pp.field("transaction")
        && t_Transaction.print_ref(pp, cs.fetch_ref())
        && pp.field("ihr_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.field("proof_created")
        && t_Anything.print_ref(pp, cs.fetch_ref())
        && pp.close();
  case msg_import_imm:
    return cs.advance(3)
        && pp.open("msg_import_imm")
        && pp.field("in_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.field("transaction")
        && t_Transaction.print_ref(pp, cs.fetch_ref())
        && pp.field("fwd_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.close();
  case msg_import_fin:
    return cs.advance(3)
        && pp.open("msg_import_fin")
        && pp.field("in_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.field("transaction")
        && t_Transaction.print_ref(pp, cs.fetch_ref())
        && pp.field("fwd_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.close();
  case msg_import_tr:
    return cs.advance(3)
        && pp.open("msg_import_tr")
        && pp.field("in_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.field("out_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.field("transit_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.close();
  case msg_discard_fin:
    return cs.advance(3)
        && pp.open("msg_discard_fin")
        && pp.field("in_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.fetch_uint_field(cs, 64, "transaction_id")
        && pp.field("fwd_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.close();
  case msg_discard_tr:
    return cs.advance(3)
        && pp.open("msg_discard_tr")
        && pp.field("in_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.fetch_uint_field(cs, 64, "transaction_id")
        && pp.field("fwd_fee")
        && t_Grams.print_skip(pp, cs)
        && pp.field("proof_delivered")
        && t_Anything.print_ref(pp, cs.fetch_ref())
        && pp.close();
  }
  return pp.fail("unknown constructor for InMsg");
}

const InMsg t_InMsg;

//
// code for type `HashmapAug`
//

bool HashmapAug::skip(vm::CellSlice& cs) const {
  int l, m1;
  return HmLabel{m}.skip(cs, l)
      && add_r1(m1, l, m)
      && HashmapAugNode{m1, X, Y}.skip(cs);
}

bool HashmapAug::validate_skip(vm::CellSlice& cs) const {
  int l, m1;
  return HmLabel{m}.validate_skip(cs, l)
      && add_r1(m1, l, m)
      && HashmapAugNode{m1, X, Y}.validate_skip(cs);
}

bool HashmapAug::unpack(vm::CellSlice& cs, HashmapAug::Record& data) const {
  return (data.n = m) >= 0
      && HmLabel{m}.fetch_to(cs, data.label, data.l)
      && add_r1(data.m, data.l, m)
      && HashmapAugNode{data.m, X, Y}.fetch_to(cs, data.node);
}

bool HashmapAug::cell_unpack(Ref<vm::Cell> cell_ref, HashmapAug::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HashmapAug::pack(vm::CellBuilder& cb, const HashmapAug::Record& data) const {
  int l, m1;
  return tlb::store_from(cb, HmLabel{m}, data.label, l)
      && add_r1(m1, l, m)
      && HashmapAugNode{m1, X, Y}.store_from(cb, data.node);
}

bool HashmapAug::cell_pack(Ref<vm::Cell>& cell_ref, const HashmapAug::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapAug::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int l, m1;
  return pp.open("ahm_edge")
      && pp.field("label")
      && HmLabel{m}.print_skip(pp, cs, l)
      && add_r1(m1, l, m)
      && pp.field("node")
      && HashmapAugNode{m1, X, Y}.print_skip(pp, cs)
      && pp.close();
}


//
// code for type `HashmapAugNode`
//

int HashmapAugNode::get_tag(const vm::CellSlice& cs) const {
  // distinguish by parameter `m` using 1 2 2 2
  return m ? ahmn_fork : ahmn_leaf;
}

bool HashmapAugNode::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case ahmn_leaf:
    return m == 0
        && Y.skip(cs)
        && X.skip(cs);
  case ahmn_fork: {
    int n;
    return add_r1(n, 1, m)
        && cs.advance_refs(2)
        && Y.skip(cs);
    }
  }
  return false;
}

bool HashmapAugNode::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case ahmn_leaf:
    return m == 0
        && Y.validate_skip(cs)
        && X.validate_skip(cs);
  case ahmn_fork: {
    int n;
    return add_r1(n, 1, m)
        && HashmapAug{n, X, Y}.validate_skip_ref(cs)
        && HashmapAug{n, X, Y}.validate_skip_ref(cs)
        && Y.validate_skip(cs);
    }
  }
  return false;
}

bool HashmapAugNode::unpack(vm::CellSlice& cs, HashmapAugNode::Record_ahmn_leaf& data) const {
  return m == 0
      && Y.fetch_to(cs, data.extra)
      && X.fetch_to(cs, data.value);
}

bool HashmapAugNode::cell_unpack(Ref<vm::Cell> cell_ref, HashmapAugNode::Record_ahmn_leaf& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HashmapAugNode::unpack(vm::CellSlice& cs, HashmapAugNode::Record_ahmn_fork& data) const {
  return add_r1(data.n, 1, m)
      && cs.fetch_ref_to(data.left)
      && cs.fetch_ref_to(data.right)
      && Y.fetch_to(cs, data.extra);
}

bool HashmapAugNode::cell_unpack(Ref<vm::Cell> cell_ref, HashmapAugNode::Record_ahmn_fork& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HashmapAugNode::pack(vm::CellBuilder& cb, const HashmapAugNode::Record_ahmn_leaf& data) const {
  return m == 0
      && Y.store_from(cb, data.extra)
      && X.store_from(cb, data.value);
}

bool HashmapAugNode::cell_pack(Ref<vm::Cell>& cell_ref, const HashmapAugNode::Record_ahmn_leaf& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapAugNode::pack(vm::CellBuilder& cb, const HashmapAugNode::Record_ahmn_fork& data) const {
  int n;
  return add_r1(n, 1, m)
      && cb.store_ref_bool(data.left)
      && cb.store_ref_bool(data.right)
      && Y.store_from(cb, data.extra);
}

bool HashmapAugNode::cell_pack(Ref<vm::Cell>& cell_ref, const HashmapAugNode::Record_ahmn_fork& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapAugNode::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case ahmn_leaf:
    return pp.open("ahmn_leaf")
        && m == 0
        && pp.field("extra")
        && Y.print_skip(pp, cs)
        && pp.field("value")
        && X.print_skip(pp, cs)
        && pp.close();
  case ahmn_fork: {
    int n;
    return pp.open("ahmn_fork")
        && add_r1(n, 1, m)
        && pp.field("left")
        && HashmapAug{n, X, Y}.print_ref(pp, cs.fetch_ref())
        && pp.field("right")
        && HashmapAug{n, X, Y}.print_ref(pp, cs.fetch_ref())
        && pp.field("extra")
        && Y.print_skip(pp, cs)
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for HashmapAugNode");
}


//
// code for type `HashmapAugE`
//

bool HashmapAugE::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case ahme_empty:
    return cs.advance(1)
        && Y.skip(cs);
  case ahme_root:
    return cs.advance_ext(0x10001)
        && Y.skip(cs);
  }
  return false;
}

bool HashmapAugE::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case ahme_empty:
    return cs.advance(1)
        && Y.validate_skip(cs);
  case ahme_root:
    return cs.advance(1)
        && HashmapAug{m, X, Y}.validate_skip_ref(cs)
        && Y.validate_skip(cs);
  }
  return false;
}

bool HashmapAugE::unpack(vm::CellSlice& cs, HashmapAugE::Record_ahme_empty& data) const {
  return cs.fetch_ulong(1) == 0
      && Y.fetch_to(cs, data.extra);
}

bool HashmapAugE::unpack_ahme_empty(vm::CellSlice& cs, Ref<CellSlice>& extra) const {
  return cs.fetch_ulong(1) == 0
      && Y.fetch_to(cs, extra);
}

bool HashmapAugE::cell_unpack(Ref<vm::Cell> cell_ref, HashmapAugE::Record_ahme_empty& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HashmapAugE::cell_unpack_ahme_empty(Ref<vm::Cell> cell_ref, Ref<CellSlice>& extra) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_ahme_empty(cs, extra) && cs.empty_ext();
}

bool HashmapAugE::unpack(vm::CellSlice& cs, HashmapAugE::Record_ahme_root& data) const {
  return cs.fetch_ulong(1) == 1
      && (data.n = m) >= 0
      && cs.fetch_ref_to(data.root)
      && Y.fetch_to(cs, data.extra);
}

bool HashmapAugE::cell_unpack(Ref<vm::Cell> cell_ref, HashmapAugE::Record_ahme_root& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HashmapAugE::pack(vm::CellBuilder& cb, const HashmapAugE::Record_ahme_empty& data) const {
  return cb.store_long_bool(0, 1)
      && Y.store_from(cb, data.extra);
}

bool HashmapAugE::pack_ahme_empty(vm::CellBuilder& cb, Ref<CellSlice> extra) const {
  return cb.store_long_bool(0, 1)
      && Y.store_from(cb, extra);
}

bool HashmapAugE::cell_pack(Ref<vm::Cell>& cell_ref, const HashmapAugE::Record_ahme_empty& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapAugE::cell_pack_ahme_empty(Ref<vm::Cell>& cell_ref, Ref<CellSlice> extra) const {
  vm::CellBuilder cb;
  return pack_ahme_empty(cb, std::move(extra)) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapAugE::pack(vm::CellBuilder& cb, const HashmapAugE::Record_ahme_root& data) const {
  return cb.store_long_bool(1, 1)
      && cb.store_ref_bool(data.root)
      && Y.store_from(cb, data.extra);
}

bool HashmapAugE::cell_pack(Ref<vm::Cell>& cell_ref, const HashmapAugE::Record_ahme_root& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HashmapAugE::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case ahme_empty:
    return cs.advance(1)
        && pp.open("ahme_empty")
        && pp.field("extra")
        && Y.print_skip(pp, cs)
        && pp.close();
  case ahme_root:
    return cs.advance(1)
        && pp.open("ahme_root")
        && pp.field("root")
        && HashmapAug{m, X, Y}.print_ref(pp, cs.fetch_ref())
        && pp.field("extra")
        && Y.print_skip(pp, cs)
        && pp.close();
  }
  return pp.fail("unknown constructor for HashmapAugE");
}


//
// code for type `ImportFees`
//

bool ImportFees::skip(vm::CellSlice& cs) const {
  return t_Grams.skip(cs)
      && t_CurrencyCollection.skip(cs);
}

bool ImportFees::validate_skip(vm::CellSlice& cs) const {
  return t_Grams.validate_skip(cs)
      && t_CurrencyCollection.validate_skip(cs);
}

bool ImportFees::unpack(vm::CellSlice& cs, ImportFees::Record& data) const {
  return t_Grams.fetch_to(cs, data.fees_collected)
      && t_CurrencyCollection.fetch_to(cs, data.value_imported);
}

bool ImportFees::cell_unpack(Ref<vm::Cell> cell_ref, ImportFees::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ImportFees::pack(vm::CellBuilder& cb, const ImportFees::Record& data) const {
  return t_Grams.store_from(cb, data.fees_collected)
      && t_CurrencyCollection.store_from(cb, data.value_imported);
}

bool ImportFees::cell_pack(Ref<vm::Cell>& cell_ref, const ImportFees::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ImportFees::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("import_fees")
      && pp.field("fees_collected")
      && t_Grams.print_skip(pp, cs)
      && pp.field("value_imported")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.close();
}

const ImportFees t_ImportFees;

//
// code for type `InMsgDescr`
//

bool InMsgDescr::skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_256_InMsg_ImportFees.skip(cs);
}

bool InMsgDescr::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_256_InMsg_ImportFees.validate_skip(cs);
}

bool InMsgDescr::unpack(vm::CellSlice& cs, InMsgDescr::Record& data) const {
  return t_HashmapAugE_256_InMsg_ImportFees.fetch_to(cs, data.x);
}

bool InMsgDescr::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapAugE_256_InMsg_ImportFees.fetch_to(cs, x);
}

bool InMsgDescr::cell_unpack(Ref<vm::Cell> cell_ref, InMsgDescr::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool InMsgDescr::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool InMsgDescr::pack(vm::CellBuilder& cb, const InMsgDescr::Record& data) const {
  return t_HashmapAugE_256_InMsg_ImportFees.store_from(cb, data.x);
}

bool InMsgDescr::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapAugE_256_InMsg_ImportFees.store_from(cb, x);
}

bool InMsgDescr::cell_pack(Ref<vm::Cell>& cell_ref, const InMsgDescr::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool InMsgDescr::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool InMsgDescr::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapAugE_256_InMsg_ImportFees.print_skip(pp, cs)
      && pp.close();
}

const InMsgDescr t_InMsgDescr;

//
// code for type `OutMsg`
//
constexpr unsigned char OutMsg::cons_tag[7];

bool OutMsg::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case msg_export_ext:
    return cs.advance_ext(0x20003);
  case msg_export_imm:
    return cs.advance_ext(0x30003);
  case msg_export_new:
    return cs.advance_ext(0x20003);
  case msg_export_tr:
    return cs.advance_ext(0x20003);
  case msg_export_deq:
    return cs.advance_ext(0x10043);
  case msg_export_tr_req:
    return cs.advance_ext(0x20003);
  case msg_export_deq_imm:
    return cs.advance_ext(0x20003);
  }
  return false;
}

bool OutMsg::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case msg_export_ext:
    return cs.advance(3)
        && t_Message_Any.validate_skip_ref(cs)
        && t_Transaction.validate_skip_ref(cs);
  case msg_export_imm:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && t_Transaction.validate_skip_ref(cs)
        && t_InMsg.validate_skip_ref(cs);
  case msg_export_new:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && t_Transaction.validate_skip_ref(cs);
  case msg_export_tr:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && t_InMsg.validate_skip_ref(cs);
  case msg_export_deq:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && cs.advance(64);
  case msg_export_tr_req:
    return cs.advance(3)
        && t_MsgEnvelope.validate_skip_ref(cs)
        && t_InMsg.validate_skip_ref(cs);
  case msg_export_deq_imm:
    return cs.fetch_ulong(3) == 4
        && t_MsgEnvelope.validate_skip_ref(cs)
        && t_InMsg.validate_skip_ref(cs);
  }
  return false;
}

bool OutMsg::unpack(vm::CellSlice& cs, OutMsg::Record_msg_export_ext& data) const {
  return cs.fetch_ulong(3) == 0
      && cs.fetch_ref_to(data.msg)
      && cs.fetch_ref_to(data.transaction);
}

bool OutMsg::cell_unpack(Ref<vm::Cell> cell_ref, OutMsg::Record_msg_export_ext& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsg::unpack(vm::CellSlice& cs, OutMsg::Record_msg_export_imm& data) const {
  return cs.fetch_ulong(3) == 2
      && cs.fetch_ref_to(data.out_msg)
      && cs.fetch_ref_to(data.transaction)
      && cs.fetch_ref_to(data.reimport);
}

bool OutMsg::cell_unpack(Ref<vm::Cell> cell_ref, OutMsg::Record_msg_export_imm& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsg::unpack(vm::CellSlice& cs, OutMsg::Record_msg_export_new& data) const {
  return cs.fetch_ulong(3) == 1
      && cs.fetch_ref_to(data.out_msg)
      && cs.fetch_ref_to(data.transaction);
}

bool OutMsg::cell_unpack(Ref<vm::Cell> cell_ref, OutMsg::Record_msg_export_new& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsg::unpack(vm::CellSlice& cs, OutMsg::Record_msg_export_tr& data) const {
  return cs.fetch_ulong(3) == 3
      && cs.fetch_ref_to(data.out_msg)
      && cs.fetch_ref_to(data.imported);
}

bool OutMsg::cell_unpack(Ref<vm::Cell> cell_ref, OutMsg::Record_msg_export_tr& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsg::unpack(vm::CellSlice& cs, OutMsg::Record_msg_export_deq& data) const {
  return cs.fetch_ulong(3) == 6
      && cs.fetch_ref_to(data.out_msg)
      && cs.fetch_uint_to(64, data.import_block_lt);
}

bool OutMsg::cell_unpack(Ref<vm::Cell> cell_ref, OutMsg::Record_msg_export_deq& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsg::unpack(vm::CellSlice& cs, OutMsg::Record_msg_export_tr_req& data) const {
  return cs.fetch_ulong(3) == 7
      && cs.fetch_ref_to(data.out_msg)
      && cs.fetch_ref_to(data.imported);
}

bool OutMsg::cell_unpack(Ref<vm::Cell> cell_ref, OutMsg::Record_msg_export_tr_req& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsg::unpack(vm::CellSlice& cs, OutMsg::Record_msg_export_deq_imm& data) const {
  return cs.fetch_ulong(3) == 4
      && cs.fetch_ref_to(data.out_msg)
      && cs.fetch_ref_to(data.reimport);
}

bool OutMsg::cell_unpack(Ref<vm::Cell> cell_ref, OutMsg::Record_msg_export_deq_imm& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsg::pack(vm::CellBuilder& cb, const OutMsg::Record_msg_export_ext& data) const {
  return cb.store_long_bool(0, 3)
      && cb.store_ref_bool(data.msg)
      && cb.store_ref_bool(data.transaction);
}

bool OutMsg::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsg::Record_msg_export_ext& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsg::pack(vm::CellBuilder& cb, const OutMsg::Record_msg_export_imm& data) const {
  return cb.store_long_bool(2, 3)
      && cb.store_ref_bool(data.out_msg)
      && cb.store_ref_bool(data.transaction)
      && cb.store_ref_bool(data.reimport);
}

bool OutMsg::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsg::Record_msg_export_imm& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsg::pack(vm::CellBuilder& cb, const OutMsg::Record_msg_export_new& data) const {
  return cb.store_long_bool(1, 3)
      && cb.store_ref_bool(data.out_msg)
      && cb.store_ref_bool(data.transaction);
}

bool OutMsg::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsg::Record_msg_export_new& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsg::pack(vm::CellBuilder& cb, const OutMsg::Record_msg_export_tr& data) const {
  return cb.store_long_bool(3, 3)
      && cb.store_ref_bool(data.out_msg)
      && cb.store_ref_bool(data.imported);
}

bool OutMsg::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsg::Record_msg_export_tr& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsg::pack(vm::CellBuilder& cb, const OutMsg::Record_msg_export_deq& data) const {
  return cb.store_long_bool(6, 3)
      && cb.store_ref_bool(data.out_msg)
      && cb.store_ulong_rchk_bool(data.import_block_lt, 64);
}

bool OutMsg::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsg::Record_msg_export_deq& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsg::pack(vm::CellBuilder& cb, const OutMsg::Record_msg_export_tr_req& data) const {
  return cb.store_long_bool(7, 3)
      && cb.store_ref_bool(data.out_msg)
      && cb.store_ref_bool(data.imported);
}

bool OutMsg::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsg::Record_msg_export_tr_req& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsg::pack(vm::CellBuilder& cb, const OutMsg::Record_msg_export_deq_imm& data) const {
  return cb.store_long_bool(4, 3)
      && cb.store_ref_bool(data.out_msg)
      && cb.store_ref_bool(data.reimport);
}

bool OutMsg::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsg::Record_msg_export_deq_imm& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsg::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case msg_export_ext:
    return cs.advance(3)
        && pp.open("msg_export_ext")
        && pp.field("msg")
        && t_Message_Any.print_ref(pp, cs.fetch_ref())
        && pp.field("transaction")
        && t_Transaction.print_ref(pp, cs.fetch_ref())
        && pp.close();
  case msg_export_imm:
    return cs.advance(3)
        && pp.open("msg_export_imm")
        && pp.field("out_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.field("transaction")
        && t_Transaction.print_ref(pp, cs.fetch_ref())
        && pp.field("reimport")
        && t_InMsg.print_ref(pp, cs.fetch_ref())
        && pp.close();
  case msg_export_new:
    return cs.advance(3)
        && pp.open("msg_export_new")
        && pp.field("out_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.field("transaction")
        && t_Transaction.print_ref(pp, cs.fetch_ref())
        && pp.close();
  case msg_export_tr:
    return cs.advance(3)
        && pp.open("msg_export_tr")
        && pp.field("out_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.field("imported")
        && t_InMsg.print_ref(pp, cs.fetch_ref())
        && pp.close();
  case msg_export_deq:
    return cs.advance(3)
        && pp.open("msg_export_deq")
        && pp.field("out_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.fetch_uint_field(cs, 64, "import_block_lt")
        && pp.close();
  case msg_export_tr_req:
    return cs.advance(3)
        && pp.open("msg_export_tr_req")
        && pp.field("out_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.field("imported")
        && t_InMsg.print_ref(pp, cs.fetch_ref())
        && pp.close();
  case msg_export_deq_imm:
    return cs.fetch_ulong(3) == 4
        && pp.open("msg_export_deq_imm")
        && pp.field("out_msg")
        && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
        && pp.field("reimport")
        && t_InMsg.print_ref(pp, cs.fetch_ref())
        && pp.close();
  }
  return pp.fail("unknown constructor for OutMsg");
}

const OutMsg t_OutMsg;

//
// code for type `EnqueuedMsg`
//

bool EnqueuedMsg::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(64)
      && t_MsgEnvelope.validate_skip_ref(cs);
}

bool EnqueuedMsg::unpack(vm::CellSlice& cs, EnqueuedMsg::Record& data) const {
  return cs.fetch_uint_to(64, data.enqueued_lt)
      && cs.fetch_ref_to(data.out_msg);
}

bool EnqueuedMsg::cell_unpack(Ref<vm::Cell> cell_ref, EnqueuedMsg::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool EnqueuedMsg::pack(vm::CellBuilder& cb, const EnqueuedMsg::Record& data) const {
  return cb.store_ulong_rchk_bool(data.enqueued_lt, 64)
      && cb.store_ref_bool(data.out_msg);
}

bool EnqueuedMsg::cell_pack(Ref<vm::Cell>& cell_ref, const EnqueuedMsg::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool EnqueuedMsg::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.fetch_uint_field(cs, 64, "enqueued_lt")
      && pp.field("out_msg")
      && t_MsgEnvelope.print_ref(pp, cs.fetch_ref())
      && pp.close();
}

const EnqueuedMsg t_EnqueuedMsg;

//
// code for type `OutMsgDescr`
//

bool OutMsgDescr::skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_256_OutMsg_CurrencyCollection.skip(cs);
}

bool OutMsgDescr::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_256_OutMsg_CurrencyCollection.validate_skip(cs);
}

bool OutMsgDescr::unpack(vm::CellSlice& cs, OutMsgDescr::Record& data) const {
  return t_HashmapAugE_256_OutMsg_CurrencyCollection.fetch_to(cs, data.x);
}

bool OutMsgDescr::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapAugE_256_OutMsg_CurrencyCollection.fetch_to(cs, x);
}

bool OutMsgDescr::cell_unpack(Ref<vm::Cell> cell_ref, OutMsgDescr::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsgDescr::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool OutMsgDescr::pack(vm::CellBuilder& cb, const OutMsgDescr::Record& data) const {
  return t_HashmapAugE_256_OutMsg_CurrencyCollection.store_from(cb, data.x);
}

bool OutMsgDescr::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapAugE_256_OutMsg_CurrencyCollection.store_from(cb, x);
}

bool OutMsgDescr::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsgDescr::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsgDescr::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsgDescr::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapAugE_256_OutMsg_CurrencyCollection.print_skip(pp, cs)
      && pp.close();
}

const OutMsgDescr t_OutMsgDescr;

//
// code for type `OutMsgQueue`
//

bool OutMsgQueue::skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_352_EnqueuedMsg_uint64.skip(cs);
}

bool OutMsgQueue::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_352_EnqueuedMsg_uint64.validate_skip(cs);
}

bool OutMsgQueue::unpack(vm::CellSlice& cs, OutMsgQueue::Record& data) const {
  return t_HashmapAugE_352_EnqueuedMsg_uint64.fetch_to(cs, data.x);
}

bool OutMsgQueue::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapAugE_352_EnqueuedMsg_uint64.fetch_to(cs, x);
}

bool OutMsgQueue::cell_unpack(Ref<vm::Cell> cell_ref, OutMsgQueue::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsgQueue::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool OutMsgQueue::pack(vm::CellBuilder& cb, const OutMsgQueue::Record& data) const {
  return t_HashmapAugE_352_EnqueuedMsg_uint64.store_from(cb, data.x);
}

bool OutMsgQueue::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapAugE_352_EnqueuedMsg_uint64.store_from(cb, x);
}

bool OutMsgQueue::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsgQueue::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsgQueue::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsgQueue::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapAugE_352_EnqueuedMsg_uint64.print_skip(pp, cs)
      && pp.close();
}

const OutMsgQueue t_OutMsgQueue;

//
// code for type `ProcessedUpto`
//

bool ProcessedUpto::unpack(vm::CellSlice& cs, ProcessedUpto::Record& data) const {
  return cs.fetch_uint_to(64, data.last_msg_lt)
      && cs.fetch_bits_to(data.last_msg_hash.bits(), 256);
}

bool ProcessedUpto::cell_unpack(Ref<vm::Cell> cell_ref, ProcessedUpto::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ProcessedUpto::pack(vm::CellBuilder& cb, const ProcessedUpto::Record& data) const {
  return cb.store_ulong_rchk_bool(data.last_msg_lt, 64)
      && cb.store_bits_bool(data.last_msg_hash.cbits(), 256);
}

bool ProcessedUpto::cell_pack(Ref<vm::Cell>& cell_ref, const ProcessedUpto::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ProcessedUpto::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("processed_upto")
      && pp.fetch_uint_field(cs, 64, "last_msg_lt")
      && pp.fetch_bits_field(cs, 256, "last_msg_hash")
      && pp.close();
}

const ProcessedUpto t_ProcessedUpto;

//
// code for type `ProcessedInfo`
//

bool ProcessedInfo::skip(vm::CellSlice& cs) const {
  return t_HashmapE_96_ProcessedUpto.skip(cs);
}

bool ProcessedInfo::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapE_96_ProcessedUpto.validate_skip(cs);
}

bool ProcessedInfo::unpack(vm::CellSlice& cs, ProcessedInfo::Record& data) const {
  return t_HashmapE_96_ProcessedUpto.fetch_to(cs, data.x);
}

bool ProcessedInfo::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapE_96_ProcessedUpto.fetch_to(cs, x);
}

bool ProcessedInfo::cell_unpack(Ref<vm::Cell> cell_ref, ProcessedInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ProcessedInfo::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool ProcessedInfo::pack(vm::CellBuilder& cb, const ProcessedInfo::Record& data) const {
  return t_HashmapE_96_ProcessedUpto.store_from(cb, data.x);
}

bool ProcessedInfo::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapE_96_ProcessedUpto.store_from(cb, x);
}

bool ProcessedInfo::cell_pack(Ref<vm::Cell>& cell_ref, const ProcessedInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ProcessedInfo::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ProcessedInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapE_96_ProcessedUpto.print_skip(pp, cs)
      && pp.close();
}

const ProcessedInfo t_ProcessedInfo;

//
// code for type `IhrPendingSince`
//

bool IhrPendingSince::unpack(vm::CellSlice& cs, IhrPendingSince::Record& data) const {
  return cs.fetch_uint_to(64, data.shard)
      && cs.fetch_uint_to(64, data.import_lt);
}

bool IhrPendingSince::cell_unpack(Ref<vm::Cell> cell_ref, IhrPendingSince::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool IhrPendingSince::pack(vm::CellBuilder& cb, const IhrPendingSince::Record& data) const {
  return cb.store_ulong_rchk_bool(data.shard, 64)
      && cb.store_ulong_rchk_bool(data.import_lt, 64);
}

bool IhrPendingSince::cell_pack(Ref<vm::Cell>& cell_ref, const IhrPendingSince::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool IhrPendingSince::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("ihr_pending")
      && pp.fetch_uint_field(cs, 64, "shard")
      && pp.fetch_uint_field(cs, 64, "import_lt")
      && pp.close();
}

const IhrPendingSince t_IhrPendingSince;

//
// code for type `IhrPendingInfo`
//

bool IhrPendingInfo::skip(vm::CellSlice& cs) const {
  return t_HashmapE_256_IhrPendingSince.skip(cs);
}

bool IhrPendingInfo::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapE_256_IhrPendingSince.validate_skip(cs);
}

bool IhrPendingInfo::unpack(vm::CellSlice& cs, IhrPendingInfo::Record& data) const {
  return t_HashmapE_256_IhrPendingSince.fetch_to(cs, data.x);
}

bool IhrPendingInfo::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapE_256_IhrPendingSince.fetch_to(cs, x);
}

bool IhrPendingInfo::cell_unpack(Ref<vm::Cell> cell_ref, IhrPendingInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool IhrPendingInfo::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool IhrPendingInfo::pack(vm::CellBuilder& cb, const IhrPendingInfo::Record& data) const {
  return t_HashmapE_256_IhrPendingSince.store_from(cb, data.x);
}

bool IhrPendingInfo::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapE_256_IhrPendingSince.store_from(cb, x);
}

bool IhrPendingInfo::cell_pack(Ref<vm::Cell>& cell_ref, const IhrPendingInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool IhrPendingInfo::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool IhrPendingInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapE_256_IhrPendingSince.print_skip(pp, cs)
      && pp.close();
}

const IhrPendingInfo t_IhrPendingInfo;

//
// code for type `OutMsgQueueInfo`
//

bool OutMsgQueueInfo::skip(vm::CellSlice& cs) const {
  return t_OutMsgQueue.skip(cs)
      && t_ProcessedInfo.skip(cs)
      && t_IhrPendingInfo.skip(cs);
}

bool OutMsgQueueInfo::validate_skip(vm::CellSlice& cs) const {
  return t_OutMsgQueue.validate_skip(cs)
      && t_ProcessedInfo.validate_skip(cs)
      && t_IhrPendingInfo.validate_skip(cs);
}

bool OutMsgQueueInfo::unpack(vm::CellSlice& cs, OutMsgQueueInfo::Record& data) const {
  return t_OutMsgQueue.fetch_to(cs, data.out_queue)
      && t_ProcessedInfo.fetch_to(cs, data.proc_info)
      && t_IhrPendingInfo.fetch_to(cs, data.ihr_pending);
}

bool OutMsgQueueInfo::cell_unpack(Ref<vm::Cell> cell_ref, OutMsgQueueInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutMsgQueueInfo::pack(vm::CellBuilder& cb, const OutMsgQueueInfo::Record& data) const {
  return t_OutMsgQueue.store_from(cb, data.out_queue)
      && t_ProcessedInfo.store_from(cb, data.proc_info)
      && t_IhrPendingInfo.store_from(cb, data.ihr_pending);
}

bool OutMsgQueueInfo::cell_pack(Ref<vm::Cell>& cell_ref, const OutMsgQueueInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutMsgQueueInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field("out_queue")
      && t_OutMsgQueue.print_skip(pp, cs)
      && pp.field("proc_info")
      && t_ProcessedInfo.print_skip(pp, cs)
      && pp.field("ihr_pending")
      && t_IhrPendingInfo.print_skip(pp, cs)
      && pp.close();
}

const OutMsgQueueInfo t_OutMsgQueueInfo;

//
// code for type `StorageUsed`
//

bool StorageUsed::skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.skip(cs)
      && t_VarUInteger_7.skip(cs)
      && t_VarUInteger_7.skip(cs);
}

bool StorageUsed::validate_skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.validate_skip(cs)
      && t_VarUInteger_7.validate_skip(cs)
      && t_VarUInteger_7.validate_skip(cs);
}

bool StorageUsed::unpack(vm::CellSlice& cs, StorageUsed::Record& data) const {
  return t_VarUInteger_7.fetch_to(cs, data.cells)
      && t_VarUInteger_7.fetch_to(cs, data.bits)
      && t_VarUInteger_7.fetch_to(cs, data.public_cells);
}

bool StorageUsed::cell_unpack(Ref<vm::Cell> cell_ref, StorageUsed::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool StorageUsed::pack(vm::CellBuilder& cb, const StorageUsed::Record& data) const {
  return t_VarUInteger_7.store_from(cb, data.cells)
      && t_VarUInteger_7.store_from(cb, data.bits)
      && t_VarUInteger_7.store_from(cb, data.public_cells);
}

bool StorageUsed::cell_pack(Ref<vm::Cell>& cell_ref, const StorageUsed::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool StorageUsed::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("storage_used")
      && pp.field("cells")
      && t_VarUInteger_7.print_skip(pp, cs)
      && pp.field("bits")
      && t_VarUInteger_7.print_skip(pp, cs)
      && pp.field("public_cells")
      && t_VarUInteger_7.print_skip(pp, cs)
      && pp.close();
}

const StorageUsed t_StorageUsed;

//
// code for type `StorageUsedShort`
//

bool StorageUsedShort::skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.skip(cs)
      && t_VarUInteger_7.skip(cs);
}

bool StorageUsedShort::validate_skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.validate_skip(cs)
      && t_VarUInteger_7.validate_skip(cs);
}

bool StorageUsedShort::unpack(vm::CellSlice& cs, StorageUsedShort::Record& data) const {
  return t_VarUInteger_7.fetch_to(cs, data.cells)
      && t_VarUInteger_7.fetch_to(cs, data.bits);
}

bool StorageUsedShort::cell_unpack(Ref<vm::Cell> cell_ref, StorageUsedShort::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool StorageUsedShort::pack(vm::CellBuilder& cb, const StorageUsedShort::Record& data) const {
  return t_VarUInteger_7.store_from(cb, data.cells)
      && t_VarUInteger_7.store_from(cb, data.bits);
}

bool StorageUsedShort::cell_pack(Ref<vm::Cell>& cell_ref, const StorageUsedShort::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool StorageUsedShort::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("storage_used_short")
      && pp.field("cells")
      && t_VarUInteger_7.print_skip(pp, cs)
      && pp.field("bits")
      && t_VarUInteger_7.print_skip(pp, cs)
      && pp.close();
}

const StorageUsedShort t_StorageUsedShort;

//
// code for type `StorageInfo`
//

bool StorageInfo::skip(vm::CellSlice& cs) const {
  return t_StorageUsed.skip(cs)
      && cs.advance(32)
      && t_Maybe_Grams.skip(cs);
}

bool StorageInfo::validate_skip(vm::CellSlice& cs) const {
  return t_StorageUsed.validate_skip(cs)
      && cs.advance(32)
      && t_Maybe_Grams.validate_skip(cs);
}

bool StorageInfo::unpack(vm::CellSlice& cs, StorageInfo::Record& data) const {
  return t_StorageUsed.fetch_to(cs, data.used)
      && cs.fetch_uint_to(32, data.last_paid)
      && t_Maybe_Grams.fetch_to(cs, data.due_payment);
}

bool StorageInfo::cell_unpack(Ref<vm::Cell> cell_ref, StorageInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool StorageInfo::pack(vm::CellBuilder& cb, const StorageInfo::Record& data) const {
  return t_StorageUsed.store_from(cb, data.used)
      && cb.store_ulong_rchk_bool(data.last_paid, 32)
      && t_Maybe_Grams.store_from(cb, data.due_payment);
}

bool StorageInfo::cell_pack(Ref<vm::Cell>& cell_ref, const StorageInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool StorageInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("storage_info")
      && pp.field("used")
      && t_StorageUsed.print_skip(pp, cs)
      && pp.fetch_uint_field(cs, 32, "last_paid")
      && pp.field("due_payment")
      && t_Maybe_Grams.print_skip(pp, cs)
      && pp.close();
}

const StorageInfo t_StorageInfo;

//
// code for type `Account`
//

bool Account::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case account_none:
    return cs.advance(1);
  case account:
    return cs.advance(1)
        && t_MsgAddressInt.skip(cs)
        && t_StorageInfo.skip(cs)
        && t_AccountStorage.skip(cs);
  }
  return false;
}

bool Account::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case account_none:
    return cs.advance(1);
  case account:
    return cs.advance(1)
        && t_MsgAddressInt.validate_skip(cs)
        && t_StorageInfo.validate_skip(cs)
        && t_AccountStorage.validate_skip(cs);
  }
  return false;
}

bool Account::unpack(vm::CellSlice& cs, Account::Record_account_none& data) const {
  return cs.fetch_ulong(1) == 0;
}

bool Account::unpack_account_none(vm::CellSlice& cs) const {
  return cs.fetch_ulong(1) == 0;
}

bool Account::cell_unpack(Ref<vm::Cell> cell_ref, Account::Record_account_none& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Account::cell_unpack_account_none(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_account_none(cs) && cs.empty_ext();
}

bool Account::unpack(vm::CellSlice& cs, Account::Record_account& data) const {
  return cs.fetch_ulong(1) == 1
      && t_MsgAddressInt.fetch_to(cs, data.addr)
      && t_StorageInfo.fetch_to(cs, data.storage_stat)
      && t_AccountStorage.fetch_to(cs, data.storage);
}

bool Account::cell_unpack(Ref<vm::Cell> cell_ref, Account::Record_account& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Account::pack(vm::CellBuilder& cb, const Account::Record_account_none& data) const {
  return cb.store_long_bool(0, 1);
}

bool Account::pack_account_none(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 1);
}

bool Account::cell_pack(Ref<vm::Cell>& cell_ref, const Account::Record_account_none& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Account::cell_pack_account_none(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_account_none(cb) && std::move(cb).finalize_to(cell_ref);
}

bool Account::pack(vm::CellBuilder& cb, const Account::Record_account& data) const {
  return cb.store_long_bool(1, 1)
      && t_MsgAddressInt.store_from(cb, data.addr)
      && t_StorageInfo.store_from(cb, data.storage_stat)
      && t_AccountStorage.store_from(cb, data.storage);
}

bool Account::cell_pack(Ref<vm::Cell>& cell_ref, const Account::Record_account& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Account::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case account_none:
    return cs.advance(1)
        && pp.cons("account_none");
  case account:
    return cs.advance(1)
        && pp.open("account")
        && pp.field("addr")
        && t_MsgAddressInt.print_skip(pp, cs)
        && pp.field("storage_stat")
        && t_StorageInfo.print_skip(pp, cs)
        && pp.field("storage")
        && t_AccountStorage.print_skip(pp, cs)
        && pp.close();
  }
  return pp.fail("unknown constructor for Account");
}

const Account t_Account;

//
// code for type `AccountStorage`
//

bool AccountStorage::skip(vm::CellSlice& cs) const {
  return cs.advance(64)
      && t_CurrencyCollection.skip(cs)
      && t_AccountState.skip(cs);
}

bool AccountStorage::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(64)
      && t_CurrencyCollection.validate_skip(cs)
      && t_AccountState.validate_skip(cs);
}

bool AccountStorage::unpack(vm::CellSlice& cs, AccountStorage::Record& data) const {
  return cs.fetch_uint_to(64, data.last_trans_lt)
      && t_CurrencyCollection.fetch_to(cs, data.balance)
      && t_AccountState.fetch_to(cs, data.state);
}

bool AccountStorage::cell_unpack(Ref<vm::Cell> cell_ref, AccountStorage::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccountStorage::pack(vm::CellBuilder& cb, const AccountStorage::Record& data) const {
  return cb.store_ulong_rchk_bool(data.last_trans_lt, 64)
      && t_CurrencyCollection.store_from(cb, data.balance)
      && t_AccountState.store_from(cb, data.state);
}

bool AccountStorage::cell_pack(Ref<vm::Cell>& cell_ref, const AccountStorage::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccountStorage::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("account_storage")
      && pp.fetch_uint_field(cs, 64, "last_trans_lt")
      && pp.field("balance")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field("state")
      && t_AccountState.print_skip(pp, cs)
      && pp.close();
}

const AccountStorage t_AccountStorage;

//
// code for type `AccountState`
//
constexpr char AccountState::cons_len[3];
constexpr unsigned char AccountState::cons_tag[3];

bool AccountState::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case account_uninit:
    return cs.advance(2);
  case account_active:
    return cs.advance(1)
        && t_StateInit.skip(cs);
  case account_frozen:
    return cs.advance(258);
  }
  return false;
}

bool AccountState::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case account_uninit:
    return cs.advance(2);
  case account_active:
    return cs.advance(1)
        && t_StateInit.validate_skip(cs);
  case account_frozen:
    return cs.advance(258);
  }
  return false;
}

bool AccountState::unpack(vm::CellSlice& cs, AccountState::Record_account_uninit& data) const {
  return cs.fetch_ulong(2) == 0;
}

bool AccountState::unpack_account_uninit(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 0;
}

bool AccountState::cell_unpack(Ref<vm::Cell> cell_ref, AccountState::Record_account_uninit& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccountState::cell_unpack_account_uninit(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_account_uninit(cs) && cs.empty_ext();
}

bool AccountState::unpack(vm::CellSlice& cs, AccountState::Record_account_active& data) const {
  return cs.fetch_ulong(1) == 1
      && t_StateInit.fetch_to(cs, data.x);
}

bool AccountState::unpack_account_active(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return cs.fetch_ulong(1) == 1
      && t_StateInit.fetch_to(cs, x);
}

bool AccountState::cell_unpack(Ref<vm::Cell> cell_ref, AccountState::Record_account_active& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccountState::cell_unpack_account_active(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_account_active(cs, x) && cs.empty_ext();
}

bool AccountState::unpack(vm::CellSlice& cs, AccountState::Record_account_frozen& data) const {
  return cs.fetch_ulong(2) == 1
      && cs.fetch_bits_to(data.state_hash.bits(), 256);
}

bool AccountState::unpack_account_frozen(vm::CellSlice& cs, td::BitArray<256>& state_hash) const {
  return cs.fetch_ulong(2) == 1
      && cs.fetch_bits_to(state_hash.bits(), 256);
}

bool AccountState::cell_unpack(Ref<vm::Cell> cell_ref, AccountState::Record_account_frozen& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccountState::cell_unpack_account_frozen(Ref<vm::Cell> cell_ref, td::BitArray<256>& state_hash) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_account_frozen(cs, state_hash) && cs.empty_ext();
}

bool AccountState::pack(vm::CellBuilder& cb, const AccountState::Record_account_uninit& data) const {
  return cb.store_long_bool(0, 2);
}

bool AccountState::pack_account_uninit(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 2);
}

bool AccountState::cell_pack(Ref<vm::Cell>& cell_ref, const AccountState::Record_account_uninit& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccountState::cell_pack_account_uninit(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_account_uninit(cb) && std::move(cb).finalize_to(cell_ref);
}

bool AccountState::pack(vm::CellBuilder& cb, const AccountState::Record_account_active& data) const {
  return cb.store_long_bool(1, 1)
      && t_StateInit.store_from(cb, data.x);
}

bool AccountState::pack_account_active(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return cb.store_long_bool(1, 1)
      && t_StateInit.store_from(cb, x);
}

bool AccountState::cell_pack(Ref<vm::Cell>& cell_ref, const AccountState::Record_account_active& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccountState::cell_pack_account_active(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_account_active(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool AccountState::pack(vm::CellBuilder& cb, const AccountState::Record_account_frozen& data) const {
  return cb.store_long_bool(1, 2)
      && cb.store_bits_bool(data.state_hash.cbits(), 256);
}

bool AccountState::pack_account_frozen(vm::CellBuilder& cb, const td::BitArray<256>& state_hash) const {
  return cb.store_long_bool(1, 2)
      && cb.store_bits_bool(state_hash.cbits(), 256);
}

bool AccountState::cell_pack(Ref<vm::Cell>& cell_ref, const AccountState::Record_account_frozen& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccountState::cell_pack_account_frozen(Ref<vm::Cell>& cell_ref, const td::BitArray<256>& state_hash) const {
  vm::CellBuilder cb;
  return pack_account_frozen(cb, state_hash) && std::move(cb).finalize_to(cell_ref);
}

bool AccountState::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case account_uninit:
    return cs.advance(2)
        && pp.cons("account_uninit");
  case account_active:
    return cs.advance(1)
        && pp.open("account_active")
        && pp.field()
        && t_StateInit.print_skip(pp, cs)
        && pp.close();
  case account_frozen:
    return cs.advance(2)
        && pp.open("account_frozen")
        && pp.fetch_bits_field(cs, 256, "state_hash")
        && pp.close();
  }
  return pp.fail("unknown constructor for AccountState");
}

const AccountState t_AccountState;

//
// code for type `AccountStatus`
//

bool AccountStatus::fetch_enum_to(vm::CellSlice& cs, char& value) const {
  value = (char)cs.fetch_ulong(2);
  return value >= 0;
}

bool AccountStatus::store_enum_from(vm::CellBuilder& cb, int value) const {
  return cb.store_long_rchk_bool(value, 2);
}

bool AccountStatus::unpack(vm::CellSlice& cs, AccountStatus::Record_acc_state_uninit& data) const {
  return cs.fetch_ulong(2) == 0;
}

bool AccountStatus::unpack_acc_state_uninit(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 0;
}

bool AccountStatus::cell_unpack(Ref<vm::Cell> cell_ref, AccountStatus::Record_acc_state_uninit& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccountStatus::cell_unpack_acc_state_uninit(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_acc_state_uninit(cs) && cs.empty_ext();
}

bool AccountStatus::unpack(vm::CellSlice& cs, AccountStatus::Record_acc_state_frozen& data) const {
  return cs.fetch_ulong(2) == 1;
}

bool AccountStatus::unpack_acc_state_frozen(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 1;
}

bool AccountStatus::cell_unpack(Ref<vm::Cell> cell_ref, AccountStatus::Record_acc_state_frozen& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccountStatus::cell_unpack_acc_state_frozen(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_acc_state_frozen(cs) && cs.empty_ext();
}

bool AccountStatus::unpack(vm::CellSlice& cs, AccountStatus::Record_acc_state_active& data) const {
  return cs.fetch_ulong(2) == 2;
}

bool AccountStatus::unpack_acc_state_active(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 2;
}

bool AccountStatus::cell_unpack(Ref<vm::Cell> cell_ref, AccountStatus::Record_acc_state_active& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccountStatus::cell_unpack_acc_state_active(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_acc_state_active(cs) && cs.empty_ext();
}

bool AccountStatus::unpack(vm::CellSlice& cs, AccountStatus::Record_acc_state_nonexist& data) const {
  return cs.fetch_ulong(2) == 3;
}

bool AccountStatus::unpack_acc_state_nonexist(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 3;
}

bool AccountStatus::cell_unpack(Ref<vm::Cell> cell_ref, AccountStatus::Record_acc_state_nonexist& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccountStatus::cell_unpack_acc_state_nonexist(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_acc_state_nonexist(cs) && cs.empty_ext();
}

bool AccountStatus::pack(vm::CellBuilder& cb, const AccountStatus::Record_acc_state_uninit& data) const {
  return cb.store_long_bool(0, 2);
}

bool AccountStatus::pack_acc_state_uninit(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 2);
}

bool AccountStatus::cell_pack(Ref<vm::Cell>& cell_ref, const AccountStatus::Record_acc_state_uninit& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccountStatus::cell_pack_acc_state_uninit(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_acc_state_uninit(cb) && std::move(cb).finalize_to(cell_ref);
}

bool AccountStatus::pack(vm::CellBuilder& cb, const AccountStatus::Record_acc_state_frozen& data) const {
  return cb.store_long_bool(1, 2);
}

bool AccountStatus::pack_acc_state_frozen(vm::CellBuilder& cb) const {
  return cb.store_long_bool(1, 2);
}

bool AccountStatus::cell_pack(Ref<vm::Cell>& cell_ref, const AccountStatus::Record_acc_state_frozen& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccountStatus::cell_pack_acc_state_frozen(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_acc_state_frozen(cb) && std::move(cb).finalize_to(cell_ref);
}

bool AccountStatus::pack(vm::CellBuilder& cb, const AccountStatus::Record_acc_state_active& data) const {
  return cb.store_long_bool(2, 2);
}

bool AccountStatus::pack_acc_state_active(vm::CellBuilder& cb) const {
  return cb.store_long_bool(2, 2);
}

bool AccountStatus::cell_pack(Ref<vm::Cell>& cell_ref, const AccountStatus::Record_acc_state_active& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccountStatus::cell_pack_acc_state_active(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_acc_state_active(cb) && std::move(cb).finalize_to(cell_ref);
}

bool AccountStatus::pack(vm::CellBuilder& cb, const AccountStatus::Record_acc_state_nonexist& data) const {
  return cb.store_long_bool(3, 2);
}

bool AccountStatus::pack_acc_state_nonexist(vm::CellBuilder& cb) const {
  return cb.store_long_bool(3, 2);
}

bool AccountStatus::cell_pack(Ref<vm::Cell>& cell_ref, const AccountStatus::Record_acc_state_nonexist& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccountStatus::cell_pack_acc_state_nonexist(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_acc_state_nonexist(cb) && std::move(cb).finalize_to(cell_ref);
}

bool AccountStatus::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case acc_state_uninit:
    return cs.advance(2)
        && pp.cons("acc_state_uninit");
  case acc_state_frozen:
    return cs.advance(2)
        && pp.cons("acc_state_frozen");
  case acc_state_active:
    return cs.advance(2)
        && pp.cons("acc_state_active");
  case acc_state_nonexist:
    return cs.advance(2)
        && pp.cons("acc_state_nonexist");
  }
  return pp.fail("unknown constructor for AccountStatus");
}

const AccountStatus t_AccountStatus;

//
// code for type `ShardAccounts`
//

bool ShardAccounts::skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_256_Ref_Account_CurrencyCollection.skip(cs);
}

bool ShardAccounts::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_256_Ref_Account_CurrencyCollection.validate_skip(cs);
}

bool ShardAccounts::unpack(vm::CellSlice& cs, ShardAccounts::Record& data) const {
  return t_HashmapAugE_256_Ref_Account_CurrencyCollection.fetch_to(cs, data.x);
}

bool ShardAccounts::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapAugE_256_Ref_Account_CurrencyCollection.fetch_to(cs, x);
}

bool ShardAccounts::cell_unpack(Ref<vm::Cell> cell_ref, ShardAccounts::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardAccounts::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool ShardAccounts::pack(vm::CellBuilder& cb, const ShardAccounts::Record& data) const {
  return t_HashmapAugE_256_Ref_Account_CurrencyCollection.store_from(cb, data.x);
}

bool ShardAccounts::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapAugE_256_Ref_Account_CurrencyCollection.store_from(cb, x);
}

bool ShardAccounts::cell_pack(Ref<vm::Cell>& cell_ref, const ShardAccounts::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardAccounts::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ShardAccounts::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapAugE_256_Ref_Account_CurrencyCollection.print_skip(pp, cs)
      && pp.close();
}

const ShardAccounts t_ShardAccounts;

//
// code for type `Transaction`
//
constexpr unsigned char Transaction::cons_tag[1];

bool Transaction::skip(vm::CellSlice& cs) const {
  return cs.advance(343)
      && t_Maybe_Ref_Message_Any.skip(cs)
      && t_HashmapE_15_Ref_Message_Any.skip(cs)
      && t_Grams.skip(cs)
      && cs.advance_refs(2);
}

bool Transaction::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 6
      && cs.advance(339)
      && t_Maybe_Ref_Message_Any.validate_skip(cs)
      && t_HashmapE_15_Ref_Message_Any.validate_skip(cs)
      && t_Grams.validate_skip(cs)
      && t_HASH_UPDATE_Account.validate_skip_ref(cs)
      && t_TransactionDescr.validate_skip_ref(cs);
}

bool Transaction::unpack(vm::CellSlice& cs, Transaction::Record& data) const {
  return cs.fetch_ulong(4) == 6
      && cs.fetch_bits_to(data.account_addr.bits(), 256)
      && cs.fetch_uint_to(64, data.lt)
      && cs.fetch_uint_to(15, data.outmsg_cnt)
      && t_AccountStatus.fetch_enum_to(cs, data.orig_status)
      && t_AccountStatus.fetch_enum_to(cs, data.end_status)
      && t_Maybe_Ref_Message_Any.fetch_to(cs, data.in_msg)
      && t_HashmapE_15_Ref_Message_Any.fetch_to(cs, data.out_msgs)
      && t_Grams.fetch_to(cs, data.total_fees)
      && cs.fetch_ref_to(data.state_update)
      && cs.fetch_ref_to(data.description);
}

bool Transaction::cell_unpack(Ref<vm::Cell> cell_ref, Transaction::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Transaction::pack(vm::CellBuilder& cb, const Transaction::Record& data) const {
  return cb.store_long_bool(6, 4)
      && cb.store_bits_bool(data.account_addr.cbits(), 256)
      && cb.store_ulong_rchk_bool(data.lt, 64)
      && cb.store_ulong_rchk_bool(data.outmsg_cnt, 15)
      && t_AccountStatus.store_enum_from(cb, data.orig_status)
      && t_AccountStatus.store_enum_from(cb, data.end_status)
      && t_Maybe_Ref_Message_Any.store_from(cb, data.in_msg)
      && t_HashmapE_15_Ref_Message_Any.store_from(cb, data.out_msgs)
      && t_Grams.store_from(cb, data.total_fees)
      && cb.store_ref_bool(data.state_update)
      && cb.store_ref_bool(data.description);
}

bool Transaction::cell_pack(Ref<vm::Cell>& cell_ref, const Transaction::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Transaction::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 6
      && pp.open("transaction")
      && pp.fetch_bits_field(cs, 256, "account_addr")
      && pp.fetch_uint_field(cs, 64, "lt")
      && pp.fetch_uint_field(cs, 15, "outmsg_cnt")
      && pp.field("orig_status")
      && t_AccountStatus.print_skip(pp, cs)
      && pp.field("end_status")
      && t_AccountStatus.print_skip(pp, cs)
      && pp.field("in_msg")
      && t_Maybe_Ref_Message_Any.print_skip(pp, cs)
      && pp.field("out_msgs")
      && t_HashmapE_15_Ref_Message_Any.print_skip(pp, cs)
      && pp.field("total_fees")
      && t_Grams.print_skip(pp, cs)
      && pp.field("state_update")
      && t_HASH_UPDATE_Account.print_ref(pp, cs.fetch_ref())
      && pp.field("description")
      && t_TransactionDescr.print_ref(pp, cs.fetch_ref())
      && pp.close();
}

const Transaction t_Transaction;

//
// code for type `MERKLE_UPDATE`
//
constexpr unsigned char MERKLE_UPDATE::cons_tag[1];

bool MERKLE_UPDATE::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 2
      && cs.advance(512)
      && X.validate_skip_ref(cs)
      && X.validate_skip_ref(cs);
}

bool MERKLE_UPDATE::unpack(vm::CellSlice& cs, MERKLE_UPDATE::Record& data) const {
  return cs.fetch_ulong(8) == 2
      && cs.fetch_bits_to(data.old_hash.bits(), 256)
      && cs.fetch_bits_to(data.new_hash.bits(), 256)
      && cs.fetch_ref_to(data.old)
      && cs.fetch_ref_to(data.new1);
}

bool MERKLE_UPDATE::cell_unpack(Ref<vm::Cell> cell_ref, MERKLE_UPDATE::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MERKLE_UPDATE::pack(vm::CellBuilder& cb, const MERKLE_UPDATE::Record& data) const {
  return cb.store_long_bool(2, 8)
      && cb.store_bits_bool(data.old_hash.cbits(), 256)
      && cb.store_bits_bool(data.new_hash.cbits(), 256)
      && cb.store_ref_bool(data.old)
      && cb.store_ref_bool(data.new1);
}

bool MERKLE_UPDATE::cell_pack(Ref<vm::Cell>& cell_ref, const MERKLE_UPDATE::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MERKLE_UPDATE::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 2
      && pp.open("!merkle_update")
      && pp.fetch_bits_field(cs, 256, "old_hash")
      && pp.fetch_bits_field(cs, 256, "new_hash")
      && pp.field("old")
      && X.print_ref(pp, cs.fetch_ref())
      && pp.field("new")
      && X.print_ref(pp, cs.fetch_ref())
      && pp.close();
}


//
// code for type `HASH_UPDATE`
//
constexpr unsigned char HASH_UPDATE::cons_tag[1];

bool HASH_UPDATE::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0x72
      && cs.advance(512);
}

bool HASH_UPDATE::unpack(vm::CellSlice& cs, HASH_UPDATE::Record& data) const {
  return cs.fetch_ulong(8) == 0x72
      && cs.fetch_bits_to(data.old_hash.bits(), 256)
      && cs.fetch_bits_to(data.new_hash.bits(), 256);
}

bool HASH_UPDATE::cell_unpack(Ref<vm::Cell> cell_ref, HASH_UPDATE::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool HASH_UPDATE::pack(vm::CellBuilder& cb, const HASH_UPDATE::Record& data) const {
  return cb.store_long_bool(0x72, 8)
      && cb.store_bits_bool(data.old_hash.cbits(), 256)
      && cb.store_bits_bool(data.new_hash.cbits(), 256);
}

bool HASH_UPDATE::cell_pack(Ref<vm::Cell>& cell_ref, const HASH_UPDATE::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool HASH_UPDATE::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0x72
      && pp.open("update_hashes")
      && pp.fetch_bits_field(cs, 256, "old_hash")
      && pp.fetch_bits_field(cs, 256, "new_hash")
      && pp.close();
}


//
// code for type `AccountBlock`
//
constexpr unsigned char AccountBlock::cons_tag[1];

bool AccountBlock::skip(vm::CellSlice& cs) const {
  return cs.advance(260)
      && t_HashmapAug_64_Ref_Transaction_Grams.skip(cs)
      && cs.advance_refs(1);
}

bool AccountBlock::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 4
      && cs.advance(256)
      && t_HashmapAug_64_Ref_Transaction_Grams.validate_skip(cs)
      && t_HASH_UPDATE_Account.validate_skip_ref(cs);
}

bool AccountBlock::unpack(vm::CellSlice& cs, AccountBlock::Record& data) const {
  return cs.fetch_ulong(4) == 4
      && cs.fetch_bits_to(data.account_addr.bits(), 256)
      && t_HashmapAug_64_Ref_Transaction_Grams.fetch_to(cs, data.transactions)
      && cs.fetch_ref_to(data.state_update);
}

bool AccountBlock::cell_unpack(Ref<vm::Cell> cell_ref, AccountBlock::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccountBlock::pack(vm::CellBuilder& cb, const AccountBlock::Record& data) const {
  return cb.store_long_bool(4, 4)
      && cb.store_bits_bool(data.account_addr.cbits(), 256)
      && t_HashmapAug_64_Ref_Transaction_Grams.store_from(cb, data.transactions)
      && cb.store_ref_bool(data.state_update);
}

bool AccountBlock::cell_pack(Ref<vm::Cell>& cell_ref, const AccountBlock::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccountBlock::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 4
      && pp.open("acc_trans")
      && pp.fetch_bits_field(cs, 256, "account_addr")
      && pp.field("transactions")
      && t_HashmapAug_64_Ref_Transaction_Grams.print_skip(pp, cs)
      && pp.field("state_update")
      && t_HASH_UPDATE_Account.print_ref(pp, cs.fetch_ref())
      && pp.close();
}

const AccountBlock t_AccountBlock;

//
// code for type `ShardAccountBlocks`
//

bool ShardAccountBlocks::skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_256_AccountBlock_Grams.skip(cs);
}

bool ShardAccountBlocks::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_256_AccountBlock_Grams.validate_skip(cs);
}

bool ShardAccountBlocks::unpack(vm::CellSlice& cs, ShardAccountBlocks::Record& data) const {
  return t_HashmapAugE_256_AccountBlock_Grams.fetch_to(cs, data.x);
}

bool ShardAccountBlocks::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapAugE_256_AccountBlock_Grams.fetch_to(cs, x);
}

bool ShardAccountBlocks::cell_unpack(Ref<vm::Cell> cell_ref, ShardAccountBlocks::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardAccountBlocks::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool ShardAccountBlocks::pack(vm::CellBuilder& cb, const ShardAccountBlocks::Record& data) const {
  return t_HashmapAugE_256_AccountBlock_Grams.store_from(cb, data.x);
}

bool ShardAccountBlocks::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapAugE_256_AccountBlock_Grams.store_from(cb, x);
}

bool ShardAccountBlocks::cell_pack(Ref<vm::Cell>& cell_ref, const ShardAccountBlocks::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardAccountBlocks::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ShardAccountBlocks::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapAugE_256_AccountBlock_Grams.print_skip(pp, cs)
      && pp.close();
}

const ShardAccountBlocks t_ShardAccountBlocks;

//
// code for type `TrStoragePhase`
//

bool TrStoragePhase::skip(vm::CellSlice& cs) const {
  return t_Grams.skip(cs)
      && t_Maybe_Grams.skip(cs)
      && t_AccStatusChange.skip(cs);
}

bool TrStoragePhase::validate_skip(vm::CellSlice& cs) const {
  return t_Grams.validate_skip(cs)
      && t_Maybe_Grams.validate_skip(cs)
      && t_AccStatusChange.validate_skip(cs);
}

bool TrStoragePhase::unpack(vm::CellSlice& cs, TrStoragePhase::Record& data) const {
  return t_Grams.fetch_to(cs, data.storage_fees_collected)
      && t_Maybe_Grams.fetch_to(cs, data.storage_fees_due)
      && t_AccStatusChange.fetch_enum_to(cs, data.status_change);
}

bool TrStoragePhase::cell_unpack(Ref<vm::Cell> cell_ref, TrStoragePhase::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TrStoragePhase::pack(vm::CellBuilder& cb, const TrStoragePhase::Record& data) const {
  return t_Grams.store_from(cb, data.storage_fees_collected)
      && t_Maybe_Grams.store_from(cb, data.storage_fees_due)
      && t_AccStatusChange.store_enum_from(cb, data.status_change);
}

bool TrStoragePhase::cell_pack(Ref<vm::Cell>& cell_ref, const TrStoragePhase::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TrStoragePhase::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("tr_phase_storage")
      && pp.field("storage_fees_collected")
      && t_Grams.print_skip(pp, cs)
      && pp.field("storage_fees_due")
      && t_Maybe_Grams.print_skip(pp, cs)
      && pp.field("status_change")
      && t_AccStatusChange.print_skip(pp, cs)
      && pp.close();
}

const TrStoragePhase t_TrStoragePhase;

//
// code for type `AccStatusChange`
//
constexpr char AccStatusChange::cons_len[3];
constexpr unsigned char AccStatusChange::cons_tag[3];

bool AccStatusChange::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case acst_unchanged:
    return cs.advance(1);
  case acst_frozen:
    return cs.advance(2);
  case acst_deleted:
    return cs.advance(2);
  }
  return false;
}

bool AccStatusChange::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case acst_unchanged:
    return cs.advance(1);
  case acst_frozen:
    return cs.advance(2);
  case acst_deleted:
    return cs.advance(2);
  }
  return false;
}

bool AccStatusChange::fetch_enum_to(vm::CellSlice& cs, char& value) const {
  int t = get_tag(cs);
  value = (char)t;
  return t >= 0 && cs.advance(cons_len[t]);
}

bool AccStatusChange::store_enum_from(vm::CellBuilder& cb, int value) const {
  return (unsigned)value < 3 && cb.store_long_bool(cons_tag[value], cons_len[value]);
}

bool AccStatusChange::unpack(vm::CellSlice& cs, AccStatusChange::Record_acst_unchanged& data) const {
  return cs.fetch_ulong(1) == 0;
}

bool AccStatusChange::unpack_acst_unchanged(vm::CellSlice& cs) const {
  return cs.fetch_ulong(1) == 0;
}

bool AccStatusChange::cell_unpack(Ref<vm::Cell> cell_ref, AccStatusChange::Record_acst_unchanged& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccStatusChange::cell_unpack_acst_unchanged(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_acst_unchanged(cs) && cs.empty_ext();
}

bool AccStatusChange::unpack(vm::CellSlice& cs, AccStatusChange::Record_acst_frozen& data) const {
  return cs.fetch_ulong(2) == 2;
}

bool AccStatusChange::unpack_acst_frozen(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 2;
}

bool AccStatusChange::cell_unpack(Ref<vm::Cell> cell_ref, AccStatusChange::Record_acst_frozen& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccStatusChange::cell_unpack_acst_frozen(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_acst_frozen(cs) && cs.empty_ext();
}

bool AccStatusChange::unpack(vm::CellSlice& cs, AccStatusChange::Record_acst_deleted& data) const {
  return cs.fetch_ulong(2) == 3;
}

bool AccStatusChange::unpack_acst_deleted(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 3;
}

bool AccStatusChange::cell_unpack(Ref<vm::Cell> cell_ref, AccStatusChange::Record_acst_deleted& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool AccStatusChange::cell_unpack_acst_deleted(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_acst_deleted(cs) && cs.empty_ext();
}

bool AccStatusChange::pack(vm::CellBuilder& cb, const AccStatusChange::Record_acst_unchanged& data) const {
  return cb.store_long_bool(0, 1);
}

bool AccStatusChange::pack_acst_unchanged(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 1);
}

bool AccStatusChange::cell_pack(Ref<vm::Cell>& cell_ref, const AccStatusChange::Record_acst_unchanged& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccStatusChange::cell_pack_acst_unchanged(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_acst_unchanged(cb) && std::move(cb).finalize_to(cell_ref);
}

bool AccStatusChange::pack(vm::CellBuilder& cb, const AccStatusChange::Record_acst_frozen& data) const {
  return cb.store_long_bool(2, 2);
}

bool AccStatusChange::pack_acst_frozen(vm::CellBuilder& cb) const {
  return cb.store_long_bool(2, 2);
}

bool AccStatusChange::cell_pack(Ref<vm::Cell>& cell_ref, const AccStatusChange::Record_acst_frozen& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccStatusChange::cell_pack_acst_frozen(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_acst_frozen(cb) && std::move(cb).finalize_to(cell_ref);
}

bool AccStatusChange::pack(vm::CellBuilder& cb, const AccStatusChange::Record_acst_deleted& data) const {
  return cb.store_long_bool(3, 2);
}

bool AccStatusChange::pack_acst_deleted(vm::CellBuilder& cb) const {
  return cb.store_long_bool(3, 2);
}

bool AccStatusChange::cell_pack(Ref<vm::Cell>& cell_ref, const AccStatusChange::Record_acst_deleted& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool AccStatusChange::cell_pack_acst_deleted(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_acst_deleted(cb) && std::move(cb).finalize_to(cell_ref);
}

bool AccStatusChange::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case acst_unchanged:
    return cs.advance(1)
        && pp.cons("acst_unchanged");
  case acst_frozen:
    return cs.advance(2)
        && pp.cons("acst_frozen");
  case acst_deleted:
    return cs.advance(2)
        && pp.cons("acst_deleted");
  }
  return pp.fail("unknown constructor for AccStatusChange");
}

const AccStatusChange t_AccStatusChange;

//
// code for type `TrCreditPhase`
//

bool TrCreditPhase::skip(vm::CellSlice& cs) const {
  return t_Maybe_Grams.skip(cs)
      && t_CurrencyCollection.skip(cs);
}

bool TrCreditPhase::validate_skip(vm::CellSlice& cs) const {
  return t_Maybe_Grams.validate_skip(cs)
      && t_CurrencyCollection.validate_skip(cs);
}

bool TrCreditPhase::unpack(vm::CellSlice& cs, TrCreditPhase::Record& data) const {
  return t_Maybe_Grams.fetch_to(cs, data.due_fees_collected)
      && t_CurrencyCollection.fetch_to(cs, data.credit);
}

bool TrCreditPhase::cell_unpack(Ref<vm::Cell> cell_ref, TrCreditPhase::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TrCreditPhase::pack(vm::CellBuilder& cb, const TrCreditPhase::Record& data) const {
  return t_Maybe_Grams.store_from(cb, data.due_fees_collected)
      && t_CurrencyCollection.store_from(cb, data.credit);
}

bool TrCreditPhase::cell_pack(Ref<vm::Cell>& cell_ref, const TrCreditPhase::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TrCreditPhase::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("tr_phase_credit")
      && pp.field("due_fees_collected")
      && t_Maybe_Grams.print_skip(pp, cs)
      && pp.field("credit")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.close();
}

const TrCreditPhase t_TrCreditPhase;

//
// code for auxiliary type `TrComputePhase_aux`
//

bool TrComputePhase_aux::skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.skip(cs)
      && t_VarUInteger_7.skip(cs)
      && t_Maybe_VarUInteger_3.skip(cs)
      && cs.advance(40)
      && t_Maybe_int32.skip(cs)
      && cs.advance(544);
}

bool TrComputePhase_aux::validate_skip(vm::CellSlice& cs) const {
  return t_VarUInteger_7.validate_skip(cs)
      && t_VarUInteger_7.validate_skip(cs)
      && t_Maybe_VarUInteger_3.validate_skip(cs)
      && cs.advance(40)
      && t_Maybe_int32.validate_skip(cs)
      && cs.advance(544);
}

bool TrComputePhase_aux::unpack(vm::CellSlice& cs, TrComputePhase_aux::Record& data) const {
  return t_VarUInteger_7.fetch_to(cs, data.gas_used)
      && t_VarUInteger_7.fetch_to(cs, data.gas_limit)
      && t_Maybe_VarUInteger_3.fetch_to(cs, data.gas_credit)
      && cs.fetch_int_to(8, data.mode)
      && cs.fetch_int_to(32, data.exit_code)
      && t_Maybe_int32.fetch_to(cs, data.exit_arg)
      && cs.fetch_uint_to(32, data.vm_steps)
      && cs.fetch_bits_to(data.vm_init_state_hash.bits(), 256)
      && cs.fetch_bits_to(data.vm_final_state_hash.bits(), 256);
}

bool TrComputePhase_aux::cell_unpack(Ref<vm::Cell> cell_ref, TrComputePhase_aux::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TrComputePhase_aux::pack(vm::CellBuilder& cb, const TrComputePhase_aux::Record& data) const {
  return t_VarUInteger_7.store_from(cb, data.gas_used)
      && t_VarUInteger_7.store_from(cb, data.gas_limit)
      && t_Maybe_VarUInteger_3.store_from(cb, data.gas_credit)
      && cb.store_long_rchk_bool(data.mode, 8)
      && cb.store_long_rchk_bool(data.exit_code, 32)
      && t_Maybe_int32.store_from(cb, data.exit_arg)
      && cb.store_ulong_rchk_bool(data.vm_steps, 32)
      && cb.store_bits_bool(data.vm_init_state_hash.cbits(), 256)
      && cb.store_bits_bool(data.vm_final_state_hash.cbits(), 256);
}

bool TrComputePhase_aux::cell_pack(Ref<vm::Cell>& cell_ref, const TrComputePhase_aux::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TrComputePhase_aux::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field("gas_used")
      && t_VarUInteger_7.print_skip(pp, cs)
      && pp.field("gas_limit")
      && t_VarUInteger_7.print_skip(pp, cs)
      && pp.field("gas_credit")
      && t_Maybe_VarUInteger_3.print_skip(pp, cs)
      && pp.fetch_int_field(cs, 8, "mode")
      && pp.fetch_int_field(cs, 32, "exit_code")
      && pp.field("exit_arg")
      && t_Maybe_int32.print_skip(pp, cs)
      && pp.fetch_uint_field(cs, 32, "vm_steps")
      && pp.fetch_bits_field(cs, 256, "vm_init_state_hash")
      && pp.fetch_bits_field(cs, 256, "vm_final_state_hash")
      && pp.close();
}

const TrComputePhase_aux t_TrComputePhase_aux;

//
// code for type `TrComputePhase`
//

bool TrComputePhase::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case tr_phase_compute_skipped:
    return cs.advance(3);
  case tr_phase_compute_vm:
    return cs.advance(4)
        && t_Grams.skip(cs)
        && cs.advance_refs(1);
  }
  return false;
}

bool TrComputePhase::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case tr_phase_compute_skipped:
    return cs.advance(1)
        && t_ComputeSkipReason.validate_skip(cs);
  case tr_phase_compute_vm:
    return cs.advance(4)
        && t_Grams.validate_skip(cs)
        && t_TrComputePhase_aux.validate_skip_ref(cs);
  }
  return false;
}

bool TrComputePhase::unpack(vm::CellSlice& cs, TrComputePhase::Record_tr_phase_compute_skipped& data) const {
  return cs.fetch_ulong(1) == 0
      && t_ComputeSkipReason.fetch_enum_to(cs, data.reason);
}

bool TrComputePhase::unpack_tr_phase_compute_skipped(vm::CellSlice& cs, char& reason) const {
  return cs.fetch_ulong(1) == 0
      && t_ComputeSkipReason.fetch_enum_to(cs, reason);
}

bool TrComputePhase::cell_unpack(Ref<vm::Cell> cell_ref, TrComputePhase::Record_tr_phase_compute_skipped& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TrComputePhase::cell_unpack_tr_phase_compute_skipped(Ref<vm::Cell> cell_ref, char& reason) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_tr_phase_compute_skipped(cs, reason) && cs.empty_ext();
}

bool TrComputePhase::unpack(vm::CellSlice& cs, TrComputePhase::Record_tr_phase_compute_vm& data) const {
  return cs.fetch_ulong(1) == 1
      && cs.fetch_bool_to(data.success)
      && cs.fetch_bool_to(data.msg_state_used)
      && cs.fetch_bool_to(data.account_activated)
      && t_Grams.fetch_to(cs, data.gas_fees)
      && t_TrComputePhase_aux.cell_unpack(cs.fetch_ref(), data.r1);
}

bool TrComputePhase::cell_unpack(Ref<vm::Cell> cell_ref, TrComputePhase::Record_tr_phase_compute_vm& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TrComputePhase::pack(vm::CellBuilder& cb, const TrComputePhase::Record_tr_phase_compute_skipped& data) const {
  return cb.store_long_bool(0, 1)
      && t_ComputeSkipReason.store_enum_from(cb, data.reason);
}

bool TrComputePhase::pack_tr_phase_compute_skipped(vm::CellBuilder& cb, char reason) const {
  return cb.store_long_bool(0, 1)
      && t_ComputeSkipReason.store_enum_from(cb, reason);
}

bool TrComputePhase::cell_pack(Ref<vm::Cell>& cell_ref, const TrComputePhase::Record_tr_phase_compute_skipped& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TrComputePhase::cell_pack_tr_phase_compute_skipped(Ref<vm::Cell>& cell_ref, char reason) const {
  vm::CellBuilder cb;
  return pack_tr_phase_compute_skipped(cb, reason) && std::move(cb).finalize_to(cell_ref);
}

bool TrComputePhase::pack(vm::CellBuilder& cb, const TrComputePhase::Record_tr_phase_compute_vm& data) const {
  Ref<vm::Cell> tmp_cell;
  return cb.store_long_bool(1, 1)
      && cb.store_ulong_rchk_bool(data.success, 1)
      && cb.store_ulong_rchk_bool(data.msg_state_used, 1)
      && cb.store_ulong_rchk_bool(data.account_activated, 1)
      && t_Grams.store_from(cb, data.gas_fees)
      && t_TrComputePhase_aux.cell_pack(tmp_cell, data.r1)
      && cb.store_ref_bool(std::move(tmp_cell));
}

bool TrComputePhase::cell_pack(Ref<vm::Cell>& cell_ref, const TrComputePhase::Record_tr_phase_compute_vm& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TrComputePhase::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case tr_phase_compute_skipped:
    return cs.advance(1)
        && pp.open("tr_phase_compute_skipped")
        && pp.field("reason")
        && t_ComputeSkipReason.print_skip(pp, cs)
        && pp.close();
  case tr_phase_compute_vm:
    return cs.advance(1)
        && pp.open("tr_phase_compute_vm")
        && pp.fetch_uint_field(cs, 1, "success")
        && pp.fetch_uint_field(cs, 1, "msg_state_used")
        && pp.fetch_uint_field(cs, 1, "account_activated")
        && pp.field("gas_fees")
        && t_Grams.print_skip(pp, cs)
        && pp.field()
        && t_TrComputePhase_aux.print_ref(pp, cs.fetch_ref())
        && pp.close();
  }
  return pp.fail("unknown constructor for TrComputePhase");
}

const TrComputePhase t_TrComputePhase;

//
// code for type `ComputeSkipReason`
//

bool ComputeSkipReason::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cskip_no_state:
    return cs.advance(2);
  case cskip_bad_state:
    return cs.advance(2);
  case cskip_no_gas:
    return cs.fetch_ulong(2) == 2;
  }
  return false;
}

bool ComputeSkipReason::fetch_enum_to(vm::CellSlice& cs, char& value) const {
  int t = get_tag(cs);
  value = (char)t;
  return t >= 0 && cs.fetch_ulong(2) == (unsigned)t;
}

bool ComputeSkipReason::store_enum_from(vm::CellBuilder& cb, int value) const {
  return cb.store_uint_less(3, value);
}

bool ComputeSkipReason::unpack(vm::CellSlice& cs, ComputeSkipReason::Record_cskip_no_state& data) const {
  return cs.fetch_ulong(2) == 0;
}

bool ComputeSkipReason::unpack_cskip_no_state(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 0;
}

bool ComputeSkipReason::cell_unpack(Ref<vm::Cell> cell_ref, ComputeSkipReason::Record_cskip_no_state& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ComputeSkipReason::cell_unpack_cskip_no_state(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cskip_no_state(cs) && cs.empty_ext();
}

bool ComputeSkipReason::unpack(vm::CellSlice& cs, ComputeSkipReason::Record_cskip_bad_state& data) const {
  return cs.fetch_ulong(2) == 1;
}

bool ComputeSkipReason::unpack_cskip_bad_state(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 1;
}

bool ComputeSkipReason::cell_unpack(Ref<vm::Cell> cell_ref, ComputeSkipReason::Record_cskip_bad_state& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ComputeSkipReason::cell_unpack_cskip_bad_state(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cskip_bad_state(cs) && cs.empty_ext();
}

bool ComputeSkipReason::unpack(vm::CellSlice& cs, ComputeSkipReason::Record_cskip_no_gas& data) const {
  return cs.fetch_ulong(2) == 2;
}

bool ComputeSkipReason::unpack_cskip_no_gas(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 2;
}

bool ComputeSkipReason::cell_unpack(Ref<vm::Cell> cell_ref, ComputeSkipReason::Record_cskip_no_gas& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ComputeSkipReason::cell_unpack_cskip_no_gas(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cskip_no_gas(cs) && cs.empty_ext();
}

bool ComputeSkipReason::pack(vm::CellBuilder& cb, const ComputeSkipReason::Record_cskip_no_state& data) const {
  return cb.store_long_bool(0, 2);
}

bool ComputeSkipReason::pack_cskip_no_state(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 2);
}

bool ComputeSkipReason::cell_pack(Ref<vm::Cell>& cell_ref, const ComputeSkipReason::Record_cskip_no_state& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ComputeSkipReason::cell_pack_cskip_no_state(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_cskip_no_state(cb) && std::move(cb).finalize_to(cell_ref);
}

bool ComputeSkipReason::pack(vm::CellBuilder& cb, const ComputeSkipReason::Record_cskip_bad_state& data) const {
  return cb.store_long_bool(1, 2);
}

bool ComputeSkipReason::pack_cskip_bad_state(vm::CellBuilder& cb) const {
  return cb.store_long_bool(1, 2);
}

bool ComputeSkipReason::cell_pack(Ref<vm::Cell>& cell_ref, const ComputeSkipReason::Record_cskip_bad_state& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ComputeSkipReason::cell_pack_cskip_bad_state(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_cskip_bad_state(cb) && std::move(cb).finalize_to(cell_ref);
}

bool ComputeSkipReason::pack(vm::CellBuilder& cb, const ComputeSkipReason::Record_cskip_no_gas& data) const {
  return cb.store_long_bool(2, 2);
}

bool ComputeSkipReason::pack_cskip_no_gas(vm::CellBuilder& cb) const {
  return cb.store_long_bool(2, 2);
}

bool ComputeSkipReason::cell_pack(Ref<vm::Cell>& cell_ref, const ComputeSkipReason::Record_cskip_no_gas& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ComputeSkipReason::cell_pack_cskip_no_gas(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_cskip_no_gas(cb) && std::move(cb).finalize_to(cell_ref);
}

bool ComputeSkipReason::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cskip_no_state:
    return cs.advance(2)
        && pp.cons("cskip_no_state");
  case cskip_bad_state:
    return cs.advance(2)
        && pp.cons("cskip_bad_state");
  case cskip_no_gas:
    return cs.fetch_ulong(2) == 2
        && pp.cons("cskip_no_gas");
  }
  return pp.fail("unknown constructor for ComputeSkipReason");
}

const ComputeSkipReason t_ComputeSkipReason;

//
// code for type `TrActionPhase`
//

bool TrActionPhase::skip(vm::CellSlice& cs) const {
  return cs.advance(3)
      && t_AccStatusChange.skip(cs)
      && t_Maybe_Grams.skip(cs)
      && t_Maybe_Grams.skip(cs)
      && cs.advance(32)
      && t_Maybe_int32.skip(cs)
      && cs.advance(320)
      && t_StorageUsedShort.skip(cs);
}

bool TrActionPhase::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(3)
      && t_AccStatusChange.validate_skip(cs)
      && t_Maybe_Grams.validate_skip(cs)
      && t_Maybe_Grams.validate_skip(cs)
      && cs.advance(32)
      && t_Maybe_int32.validate_skip(cs)
      && cs.advance(320)
      && t_StorageUsedShort.validate_skip(cs);
}

bool TrActionPhase::unpack(vm::CellSlice& cs, TrActionPhase::Record& data) const {
  return cs.fetch_bool_to(data.success)
      && cs.fetch_bool_to(data.valid)
      && cs.fetch_bool_to(data.no_funds)
      && t_AccStatusChange.fetch_enum_to(cs, data.status_change)
      && t_Maybe_Grams.fetch_to(cs, data.total_fwd_fees)
      && t_Maybe_Grams.fetch_to(cs, data.total_action_fees)
      && cs.fetch_int_to(32, data.result_code)
      && t_Maybe_int32.fetch_to(cs, data.result_arg)
      && cs.fetch_uint_to(16, data.tot_actions)
      && cs.fetch_uint_to(16, data.spec_actions)
      && cs.fetch_uint_to(16, data.skipped_actions)
      && cs.fetch_uint_to(16, data.msgs_created)
      && cs.fetch_bits_to(data.action_list_hash.bits(), 256)
      && t_StorageUsedShort.fetch_to(cs, data.tot_msg_size);
}

bool TrActionPhase::cell_unpack(Ref<vm::Cell> cell_ref, TrActionPhase::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TrActionPhase::pack(vm::CellBuilder& cb, const TrActionPhase::Record& data) const {
  return cb.store_ulong_rchk_bool(data.success, 1)
      && cb.store_ulong_rchk_bool(data.valid, 1)
      && cb.store_ulong_rchk_bool(data.no_funds, 1)
      && t_AccStatusChange.store_enum_from(cb, data.status_change)
      && t_Maybe_Grams.store_from(cb, data.total_fwd_fees)
      && t_Maybe_Grams.store_from(cb, data.total_action_fees)
      && cb.store_long_rchk_bool(data.result_code, 32)
      && t_Maybe_int32.store_from(cb, data.result_arg)
      && cb.store_ulong_rchk_bool(data.tot_actions, 16)
      && cb.store_ulong_rchk_bool(data.spec_actions, 16)
      && cb.store_ulong_rchk_bool(data.skipped_actions, 16)
      && cb.store_ulong_rchk_bool(data.msgs_created, 16)
      && cb.store_bits_bool(data.action_list_hash.cbits(), 256)
      && t_StorageUsedShort.store_from(cb, data.tot_msg_size);
}

bool TrActionPhase::cell_pack(Ref<vm::Cell>& cell_ref, const TrActionPhase::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TrActionPhase::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("tr_phase_action")
      && pp.fetch_uint_field(cs, 1, "success")
      && pp.fetch_uint_field(cs, 1, "valid")
      && pp.fetch_uint_field(cs, 1, "no_funds")
      && pp.field("status_change")
      && t_AccStatusChange.print_skip(pp, cs)
      && pp.field("total_fwd_fees")
      && t_Maybe_Grams.print_skip(pp, cs)
      && pp.field("total_action_fees")
      && t_Maybe_Grams.print_skip(pp, cs)
      && pp.fetch_int_field(cs, 32, "result_code")
      && pp.field("result_arg")
      && t_Maybe_int32.print_skip(pp, cs)
      && pp.fetch_uint_field(cs, 16, "tot_actions")
      && pp.fetch_uint_field(cs, 16, "spec_actions")
      && pp.fetch_uint_field(cs, 16, "skipped_actions")
      && pp.fetch_uint_field(cs, 16, "msgs_created")
      && pp.fetch_bits_field(cs, 256, "action_list_hash")
      && pp.field("tot_msg_size")
      && t_StorageUsedShort.print_skip(pp, cs)
      && pp.close();
}

const TrActionPhase t_TrActionPhase;

//
// code for type `TrBouncePhase`
//
constexpr char TrBouncePhase::cons_len[3];
constexpr unsigned char TrBouncePhase::cons_tag[3];

bool TrBouncePhase::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case tr_phase_bounce_negfunds:
    return cs.advance(2);
  case tr_phase_bounce_nofunds:
    return cs.advance(2)
        && t_StorageUsedShort.skip(cs)
        && t_Grams.skip(cs);
  case tr_phase_bounce_ok:
    return cs.advance(1)
        && t_StorageUsedShort.skip(cs)
        && t_Grams.skip(cs)
        && t_Grams.skip(cs);
  }
  return false;
}

bool TrBouncePhase::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case tr_phase_bounce_negfunds:
    return cs.advance(2);
  case tr_phase_bounce_nofunds:
    return cs.advance(2)
        && t_StorageUsedShort.validate_skip(cs)
        && t_Grams.validate_skip(cs);
  case tr_phase_bounce_ok:
    return cs.advance(1)
        && t_StorageUsedShort.validate_skip(cs)
        && t_Grams.validate_skip(cs)
        && t_Grams.validate_skip(cs);
  }
  return false;
}

bool TrBouncePhase::unpack(vm::CellSlice& cs, TrBouncePhase::Record_tr_phase_bounce_negfunds& data) const {
  return cs.fetch_ulong(2) == 0;
}

bool TrBouncePhase::unpack_tr_phase_bounce_negfunds(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 0;
}

bool TrBouncePhase::cell_unpack(Ref<vm::Cell> cell_ref, TrBouncePhase::Record_tr_phase_bounce_negfunds& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TrBouncePhase::cell_unpack_tr_phase_bounce_negfunds(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_tr_phase_bounce_negfunds(cs) && cs.empty_ext();
}

bool TrBouncePhase::unpack(vm::CellSlice& cs, TrBouncePhase::Record_tr_phase_bounce_nofunds& data) const {
  return cs.fetch_ulong(2) == 1
      && t_StorageUsedShort.fetch_to(cs, data.msg_size)
      && t_Grams.fetch_to(cs, data.req_fwd_fees);
}

bool TrBouncePhase::cell_unpack(Ref<vm::Cell> cell_ref, TrBouncePhase::Record_tr_phase_bounce_nofunds& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TrBouncePhase::unpack(vm::CellSlice& cs, TrBouncePhase::Record_tr_phase_bounce_ok& data) const {
  return cs.fetch_ulong(1) == 1
      && t_StorageUsedShort.fetch_to(cs, data.msg_size)
      && t_Grams.fetch_to(cs, data.msg_fees)
      && t_Grams.fetch_to(cs, data.fwd_fees);
}

bool TrBouncePhase::cell_unpack(Ref<vm::Cell> cell_ref, TrBouncePhase::Record_tr_phase_bounce_ok& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TrBouncePhase::pack(vm::CellBuilder& cb, const TrBouncePhase::Record_tr_phase_bounce_negfunds& data) const {
  return cb.store_long_bool(0, 2);
}

bool TrBouncePhase::pack_tr_phase_bounce_negfunds(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 2);
}

bool TrBouncePhase::cell_pack(Ref<vm::Cell>& cell_ref, const TrBouncePhase::Record_tr_phase_bounce_negfunds& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TrBouncePhase::cell_pack_tr_phase_bounce_negfunds(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_tr_phase_bounce_negfunds(cb) && std::move(cb).finalize_to(cell_ref);
}

bool TrBouncePhase::pack(vm::CellBuilder& cb, const TrBouncePhase::Record_tr_phase_bounce_nofunds& data) const {
  return cb.store_long_bool(1, 2)
      && t_StorageUsedShort.store_from(cb, data.msg_size)
      && t_Grams.store_from(cb, data.req_fwd_fees);
}

bool TrBouncePhase::cell_pack(Ref<vm::Cell>& cell_ref, const TrBouncePhase::Record_tr_phase_bounce_nofunds& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TrBouncePhase::pack(vm::CellBuilder& cb, const TrBouncePhase::Record_tr_phase_bounce_ok& data) const {
  return cb.store_long_bool(1, 1)
      && t_StorageUsedShort.store_from(cb, data.msg_size)
      && t_Grams.store_from(cb, data.msg_fees)
      && t_Grams.store_from(cb, data.fwd_fees);
}

bool TrBouncePhase::cell_pack(Ref<vm::Cell>& cell_ref, const TrBouncePhase::Record_tr_phase_bounce_ok& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TrBouncePhase::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case tr_phase_bounce_negfunds:
    return cs.advance(2)
        && pp.cons("tr_phase_bounce_negfunds");
  case tr_phase_bounce_nofunds:
    return cs.advance(2)
        && pp.open("tr_phase_bounce_nofunds")
        && pp.field("msg_size")
        && t_StorageUsedShort.print_skip(pp, cs)
        && pp.field("req_fwd_fees")
        && t_Grams.print_skip(pp, cs)
        && pp.close();
  case tr_phase_bounce_ok:
    return cs.advance(1)
        && pp.open("tr_phase_bounce_ok")
        && pp.field("msg_size")
        && t_StorageUsedShort.print_skip(pp, cs)
        && pp.field("msg_fees")
        && t_Grams.print_skip(pp, cs)
        && pp.field("fwd_fees")
        && t_Grams.print_skip(pp, cs)
        && pp.close();
  }
  return pp.fail("unknown constructor for TrBouncePhase");
}

const TrBouncePhase t_TrBouncePhase;

//
// code for type `SplitMergeInfo`
//

bool SplitMergeInfo::unpack(vm::CellSlice& cs, SplitMergeInfo::Record& data) const {
  return cs.fetch_uint_to(6, data.cur_shard_pfx_len)
      && cs.fetch_uint_to(6, data.acc_split_depth)
      && cs.fetch_bits_to(data.this_addr.bits(), 256)
      && cs.fetch_bits_to(data.sibling_addr.bits(), 256);
}

bool SplitMergeInfo::cell_unpack(Ref<vm::Cell> cell_ref, SplitMergeInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool SplitMergeInfo::pack(vm::CellBuilder& cb, const SplitMergeInfo::Record& data) const {
  return cb.store_ulong_rchk_bool(data.cur_shard_pfx_len, 6)
      && cb.store_ulong_rchk_bool(data.acc_split_depth, 6)
      && cb.store_bits_bool(data.this_addr.cbits(), 256)
      && cb.store_bits_bool(data.sibling_addr.cbits(), 256);
}

bool SplitMergeInfo::cell_pack(Ref<vm::Cell>& cell_ref, const SplitMergeInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool SplitMergeInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int cur_shard_pfx_len, acc_split_depth;
  return pp.open("split_merge_info")
      && cs.fetch_uint_to(6, cur_shard_pfx_len)
      && pp.field_int(cur_shard_pfx_len, "cur_shard_pfx_len")
      && cs.fetch_uint_to(6, acc_split_depth)
      && pp.field_int(acc_split_depth, "acc_split_depth")
      && pp.fetch_bits_field(cs, 256, "this_addr")
      && pp.fetch_bits_field(cs, 256, "sibling_addr")
      && pp.close();
}

const SplitMergeInfo t_SplitMergeInfo;

//
// code for type `TransactionDescr`
//
constexpr char TransactionDescr::cons_len[7];
constexpr unsigned char TransactionDescr::cons_tag[7];

bool TransactionDescr::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case trans_ord:
    return cs.advance(5)
        && t_Maybe_TrStoragePhase.skip(cs)
        && t_Maybe_TrCreditPhase.skip(cs)
        && t_TrComputePhase.skip(cs)
        && t_Maybe_Ref_TrActionPhase.skip(cs)
        && cs.advance(1)
        && t_Maybe_TrBouncePhase.skip(cs)
        && cs.advance(1);
  case trans_storage:
    return cs.advance(4)
        && t_TrStoragePhase.skip(cs);
  case trans_tick_tock:
    return cs.advance(4)
        && t_TrStoragePhase.skip(cs)
        && t_TrComputePhase.skip(cs)
        && t_Maybe_Ref_TrActionPhase.skip(cs)
        && cs.advance(2);
  case trans_split_prepare:
    return cs.advance(528)
        && t_TrComputePhase.skip(cs)
        && t_Maybe_Ref_TrActionPhase.skip(cs)
        && cs.advance(2);
  case trans_split_install:
    return cs.advance_ext(0x10211);
  case trans_merge_prepare:
    return cs.advance(528)
        && t_TrStoragePhase.skip(cs)
        && cs.advance(1);
  case trans_merge_install:
    return cs.advance_ext(0x10210)
        && t_Maybe_TrCreditPhase.skip(cs)
        && t_TrComputePhase.skip(cs)
        && t_Maybe_Ref_TrActionPhase.skip(cs)
        && cs.advance(2);
  }
  return false;
}

bool TransactionDescr::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case trans_ord:
    return cs.advance(5)
        && t_Maybe_TrStoragePhase.validate_skip(cs)
        && t_Maybe_TrCreditPhase.validate_skip(cs)
        && t_TrComputePhase.validate_skip(cs)
        && t_Maybe_Ref_TrActionPhase.validate_skip(cs)
        && cs.advance(1)
        && t_Maybe_TrBouncePhase.validate_skip(cs)
        && cs.advance(1);
  case trans_storage:
    return cs.advance(4)
        && t_TrStoragePhase.validate_skip(cs);
  case trans_tick_tock:
    return cs.advance(4)
        && t_TrStoragePhase.validate_skip(cs)
        && t_TrComputePhase.validate_skip(cs)
        && t_Maybe_Ref_TrActionPhase.validate_skip(cs)
        && cs.advance(2);
  case trans_split_prepare:
    return cs.advance(528)
        && t_TrComputePhase.validate_skip(cs)
        && t_Maybe_Ref_TrActionPhase.validate_skip(cs)
        && cs.advance(2);
  case trans_split_install:
    return cs.advance(528)
        && t_Transaction.validate_skip_ref(cs)
        && cs.advance(1);
  case trans_merge_prepare:
    return cs.advance(528)
        && t_TrStoragePhase.validate_skip(cs)
        && cs.advance(1);
  case trans_merge_install:
    return cs.fetch_ulong(4) == 7
        && cs.advance(524)
        && t_Transaction.validate_skip_ref(cs)
        && t_Maybe_TrCreditPhase.validate_skip(cs)
        && t_TrComputePhase.validate_skip(cs)
        && t_Maybe_Ref_TrActionPhase.validate_skip(cs)
        && cs.advance(2);
  }
  return false;
}

bool TransactionDescr::unpack(vm::CellSlice& cs, TransactionDescr::Record_trans_ord& data) const {
  return cs.fetch_ulong(4) == 0
      && cs.fetch_bool_to(data.credit_first)
      && t_Maybe_TrStoragePhase.fetch_to(cs, data.storage_ph)
      && t_Maybe_TrCreditPhase.fetch_to(cs, data.credit_ph)
      && t_TrComputePhase.fetch_to(cs, data.compute_ph)
      && t_Maybe_Ref_TrActionPhase.fetch_to(cs, data.action)
      && cs.fetch_bool_to(data.aborted)
      && t_Maybe_TrBouncePhase.fetch_to(cs, data.bounce)
      && cs.fetch_bool_to(data.destroyed);
}

bool TransactionDescr::cell_unpack(Ref<vm::Cell> cell_ref, TransactionDescr::Record_trans_ord& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TransactionDescr::unpack(vm::CellSlice& cs, TransactionDescr::Record_trans_storage& data) const {
  return cs.fetch_ulong(4) == 1
      && t_TrStoragePhase.fetch_to(cs, data.storage_ph);
}

bool TransactionDescr::unpack_trans_storage(vm::CellSlice& cs, Ref<CellSlice>& storage_ph) const {
  return cs.fetch_ulong(4) == 1
      && t_TrStoragePhase.fetch_to(cs, storage_ph);
}

bool TransactionDescr::cell_unpack(Ref<vm::Cell> cell_ref, TransactionDescr::Record_trans_storage& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TransactionDescr::cell_unpack_trans_storage(Ref<vm::Cell> cell_ref, Ref<CellSlice>& storage_ph) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_trans_storage(cs, storage_ph) && cs.empty_ext();
}

bool TransactionDescr::unpack(vm::CellSlice& cs, TransactionDescr::Record_trans_tick_tock& data) const {
  return cs.fetch_ulong(3) == 1
      && cs.fetch_bool_to(data.is_tock)
      && t_TrStoragePhase.fetch_to(cs, data.storage)
      && t_TrComputePhase.fetch_to(cs, data.compute_ph)
      && t_Maybe_Ref_TrActionPhase.fetch_to(cs, data.action)
      && cs.fetch_bool_to(data.aborted)
      && cs.fetch_bool_to(data.destroyed);
}

bool TransactionDescr::cell_unpack(Ref<vm::Cell> cell_ref, TransactionDescr::Record_trans_tick_tock& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TransactionDescr::unpack(vm::CellSlice& cs, TransactionDescr::Record_trans_split_prepare& data) const {
  return cs.fetch_ulong(4) == 4
      && cs.fetch_subslice_to(524, data.split_info)
      && t_TrComputePhase.fetch_to(cs, data.compute_ph)
      && t_Maybe_Ref_TrActionPhase.fetch_to(cs, data.action)
      && cs.fetch_bool_to(data.aborted)
      && cs.fetch_bool_to(data.destroyed);
}

bool TransactionDescr::cell_unpack(Ref<vm::Cell> cell_ref, TransactionDescr::Record_trans_split_prepare& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TransactionDescr::unpack(vm::CellSlice& cs, TransactionDescr::Record_trans_split_install& data) const {
  return cs.fetch_ulong(4) == 5
      && cs.fetch_subslice_to(524, data.split_info)
      && cs.fetch_ref_to(data.prepare_transaction)
      && cs.fetch_bool_to(data.installed);
}

bool TransactionDescr::cell_unpack(Ref<vm::Cell> cell_ref, TransactionDescr::Record_trans_split_install& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TransactionDescr::unpack(vm::CellSlice& cs, TransactionDescr::Record_trans_merge_prepare& data) const {
  return cs.fetch_ulong(4) == 6
      && cs.fetch_subslice_to(524, data.split_info)
      && t_TrStoragePhase.fetch_to(cs, data.storage_ph)
      && cs.fetch_bool_to(data.aborted);
}

bool TransactionDescr::cell_unpack(Ref<vm::Cell> cell_ref, TransactionDescr::Record_trans_merge_prepare& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TransactionDescr::unpack(vm::CellSlice& cs, TransactionDescr::Record_trans_merge_install& data) const {
  return cs.fetch_ulong(4) == 7
      && cs.fetch_subslice_to(524, data.split_info)
      && cs.fetch_ref_to(data.prepare_transaction)
      && t_Maybe_TrCreditPhase.fetch_to(cs, data.credit_ph)
      && t_TrComputePhase.fetch_to(cs, data.compute_ph)
      && t_Maybe_Ref_TrActionPhase.fetch_to(cs, data.action)
      && cs.fetch_bool_to(data.aborted)
      && cs.fetch_bool_to(data.destroyed);
}

bool TransactionDescr::cell_unpack(Ref<vm::Cell> cell_ref, TransactionDescr::Record_trans_merge_install& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool TransactionDescr::pack(vm::CellBuilder& cb, const TransactionDescr::Record_trans_ord& data) const {
  return cb.store_long_bool(0, 4)
      && cb.store_ulong_rchk_bool(data.credit_first, 1)
      && t_Maybe_TrStoragePhase.store_from(cb, data.storage_ph)
      && t_Maybe_TrCreditPhase.store_from(cb, data.credit_ph)
      && t_TrComputePhase.store_from(cb, data.compute_ph)
      && t_Maybe_Ref_TrActionPhase.store_from(cb, data.action)
      && cb.store_ulong_rchk_bool(data.aborted, 1)
      && t_Maybe_TrBouncePhase.store_from(cb, data.bounce)
      && cb.store_ulong_rchk_bool(data.destroyed, 1);
}

bool TransactionDescr::cell_pack(Ref<vm::Cell>& cell_ref, const TransactionDescr::Record_trans_ord& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TransactionDescr::pack(vm::CellBuilder& cb, const TransactionDescr::Record_trans_storage& data) const {
  return cb.store_long_bool(1, 4)
      && t_TrStoragePhase.store_from(cb, data.storage_ph);
}

bool TransactionDescr::pack_trans_storage(vm::CellBuilder& cb, Ref<CellSlice> storage_ph) const {
  return cb.store_long_bool(1, 4)
      && t_TrStoragePhase.store_from(cb, storage_ph);
}

bool TransactionDescr::cell_pack(Ref<vm::Cell>& cell_ref, const TransactionDescr::Record_trans_storage& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TransactionDescr::cell_pack_trans_storage(Ref<vm::Cell>& cell_ref, Ref<CellSlice> storage_ph) const {
  vm::CellBuilder cb;
  return pack_trans_storage(cb, std::move(storage_ph)) && std::move(cb).finalize_to(cell_ref);
}

bool TransactionDescr::pack(vm::CellBuilder& cb, const TransactionDescr::Record_trans_tick_tock& data) const {
  return cb.store_long_bool(1, 3)
      && cb.store_ulong_rchk_bool(data.is_tock, 1)
      && t_TrStoragePhase.store_from(cb, data.storage)
      && t_TrComputePhase.store_from(cb, data.compute_ph)
      && t_Maybe_Ref_TrActionPhase.store_from(cb, data.action)
      && cb.store_ulong_rchk_bool(data.aborted, 1)
      && cb.store_ulong_rchk_bool(data.destroyed, 1);
}

bool TransactionDescr::cell_pack(Ref<vm::Cell>& cell_ref, const TransactionDescr::Record_trans_tick_tock& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TransactionDescr::pack(vm::CellBuilder& cb, const TransactionDescr::Record_trans_split_prepare& data) const {
  return cb.store_long_bool(4, 4)
      && cb.append_cellslice_chk(data.split_info, 524)
      && t_TrComputePhase.store_from(cb, data.compute_ph)
      && t_Maybe_Ref_TrActionPhase.store_from(cb, data.action)
      && cb.store_ulong_rchk_bool(data.aborted, 1)
      && cb.store_ulong_rchk_bool(data.destroyed, 1);
}

bool TransactionDescr::cell_pack(Ref<vm::Cell>& cell_ref, const TransactionDescr::Record_trans_split_prepare& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TransactionDescr::pack(vm::CellBuilder& cb, const TransactionDescr::Record_trans_split_install& data) const {
  return cb.store_long_bool(5, 4)
      && cb.append_cellslice_chk(data.split_info, 524)
      && cb.store_ref_bool(data.prepare_transaction)
      && cb.store_ulong_rchk_bool(data.installed, 1);
}

bool TransactionDescr::cell_pack(Ref<vm::Cell>& cell_ref, const TransactionDescr::Record_trans_split_install& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TransactionDescr::pack(vm::CellBuilder& cb, const TransactionDescr::Record_trans_merge_prepare& data) const {
  return cb.store_long_bool(6, 4)
      && cb.append_cellslice_chk(data.split_info, 524)
      && t_TrStoragePhase.store_from(cb, data.storage_ph)
      && cb.store_ulong_rchk_bool(data.aborted, 1);
}

bool TransactionDescr::cell_pack(Ref<vm::Cell>& cell_ref, const TransactionDescr::Record_trans_merge_prepare& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TransactionDescr::pack(vm::CellBuilder& cb, const TransactionDescr::Record_trans_merge_install& data) const {
  return cb.store_long_bool(7, 4)
      && cb.append_cellslice_chk(data.split_info, 524)
      && cb.store_ref_bool(data.prepare_transaction)
      && t_Maybe_TrCreditPhase.store_from(cb, data.credit_ph)
      && t_TrComputePhase.store_from(cb, data.compute_ph)
      && t_Maybe_Ref_TrActionPhase.store_from(cb, data.action)
      && cb.store_ulong_rchk_bool(data.aborted, 1)
      && cb.store_ulong_rchk_bool(data.destroyed, 1);
}

bool TransactionDescr::cell_pack(Ref<vm::Cell>& cell_ref, const TransactionDescr::Record_trans_merge_install& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool TransactionDescr::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case trans_ord:
    return cs.advance(4)
        && pp.open("trans_ord")
        && pp.fetch_uint_field(cs, 1, "credit_first")
        && pp.field("storage_ph")
        && t_Maybe_TrStoragePhase.print_skip(pp, cs)
        && pp.field("credit_ph")
        && t_Maybe_TrCreditPhase.print_skip(pp, cs)
        && pp.field("compute_ph")
        && t_TrComputePhase.print_skip(pp, cs)
        && pp.field("action")
        && t_Maybe_Ref_TrActionPhase.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 1, "aborted")
        && pp.field("bounce")
        && t_Maybe_TrBouncePhase.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 1, "destroyed")
        && pp.close();
  case trans_storage:
    return cs.advance(4)
        && pp.open("trans_storage")
        && pp.field("storage_ph")
        && t_TrStoragePhase.print_skip(pp, cs)
        && pp.close();
  case trans_tick_tock:
    return cs.advance(3)
        && pp.open("trans_tick_tock")
        && pp.fetch_uint_field(cs, 1, "is_tock")
        && pp.field("storage")
        && t_TrStoragePhase.print_skip(pp, cs)
        && pp.field("compute_ph")
        && t_TrComputePhase.print_skip(pp, cs)
        && pp.field("action")
        && t_Maybe_Ref_TrActionPhase.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 1, "aborted")
        && pp.fetch_uint_field(cs, 1, "destroyed")
        && pp.close();
  case trans_split_prepare:
    return cs.advance(4)
        && pp.open("trans_split_prepare")
        && pp.field("split_info")
        && t_SplitMergeInfo.print_skip(pp, cs)
        && pp.field("compute_ph")
        && t_TrComputePhase.print_skip(pp, cs)
        && pp.field("action")
        && t_Maybe_Ref_TrActionPhase.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 1, "aborted")
        && pp.fetch_uint_field(cs, 1, "destroyed")
        && pp.close();
  case trans_split_install:
    return cs.advance(4)
        && pp.open("trans_split_install")
        && pp.field("split_info")
        && t_SplitMergeInfo.print_skip(pp, cs)
        && pp.field("prepare_transaction")
        && t_Transaction.print_ref(pp, cs.fetch_ref())
        && pp.fetch_uint_field(cs, 1, "installed")
        && pp.close();
  case trans_merge_prepare:
    return cs.advance(4)
        && pp.open("trans_merge_prepare")
        && pp.field("split_info")
        && t_SplitMergeInfo.print_skip(pp, cs)
        && pp.field("storage_ph")
        && t_TrStoragePhase.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 1, "aborted")
        && pp.close();
  case trans_merge_install:
    return cs.fetch_ulong(4) == 7
        && pp.open("trans_merge_install")
        && pp.field("split_info")
        && t_SplitMergeInfo.print_skip(pp, cs)
        && pp.field("prepare_transaction")
        && t_Transaction.print_ref(pp, cs.fetch_ref())
        && pp.field("credit_ph")
        && t_Maybe_TrCreditPhase.print_skip(pp, cs)
        && pp.field("compute_ph")
        && t_TrComputePhase.print_skip(pp, cs)
        && pp.field("action")
        && t_Maybe_Ref_TrActionPhase.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 1, "aborted")
        && pp.fetch_uint_field(cs, 1, "destroyed")
        && pp.close();
  }
  return pp.fail("unknown constructor for TransactionDescr");
}

const TransactionDescr t_TransactionDescr;

//
// code for type `SmartContractInfo`
//
constexpr unsigned SmartContractInfo::cons_tag[1];

bool SmartContractInfo::skip(vm::CellSlice& cs) const {
  return cs.advance(480)
      && t_CurrencyCollection.skip(cs)
      && t_MsgAddressInt.skip(cs);
}

bool SmartContractInfo::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0x76ef1ea
      && cs.advance(448)
      && t_CurrencyCollection.validate_skip(cs)
      && t_MsgAddressInt.validate_skip(cs);
}

bool SmartContractInfo::unpack(vm::CellSlice& cs, SmartContractInfo::Record& data) const {
  return cs.fetch_ulong(32) == 0x76ef1ea
      && cs.fetch_uint_to(16, data.actions)
      && cs.fetch_uint_to(16, data.msgs_sent)
      && cs.fetch_uint_to(32, data.unixtime)
      && cs.fetch_uint_to(64, data.block_lt)
      && cs.fetch_uint_to(64, data.trans_lt)
      && cs.fetch_bits_to(data.rand_seed.bits(), 256)
      && t_CurrencyCollection.fetch_to(cs, data.balance_remaining)
      && t_MsgAddressInt.fetch_to(cs, data.myself);
}

bool SmartContractInfo::cell_unpack(Ref<vm::Cell> cell_ref, SmartContractInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool SmartContractInfo::pack(vm::CellBuilder& cb, const SmartContractInfo::Record& data) const {
  return cb.store_long_bool(0x76ef1ea, 32)
      && cb.store_ulong_rchk_bool(data.actions, 16)
      && cb.store_ulong_rchk_bool(data.msgs_sent, 16)
      && cb.store_ulong_rchk_bool(data.unixtime, 32)
      && cb.store_ulong_rchk_bool(data.block_lt, 64)
      && cb.store_ulong_rchk_bool(data.trans_lt, 64)
      && cb.store_bits_bool(data.rand_seed.cbits(), 256)
      && t_CurrencyCollection.store_from(cb, data.balance_remaining)
      && t_MsgAddressInt.store_from(cb, data.myself);
}

bool SmartContractInfo::cell_pack(Ref<vm::Cell>& cell_ref, const SmartContractInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool SmartContractInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0x76ef1ea
      && pp.open("smc_info")
      && pp.fetch_uint_field(cs, 16, "actions")
      && pp.fetch_uint_field(cs, 16, "msgs_sent")
      && pp.fetch_uint_field(cs, 32, "unixtime")
      && pp.fetch_uint_field(cs, 64, "block_lt")
      && pp.fetch_uint_field(cs, 64, "trans_lt")
      && pp.fetch_bits_field(cs, 256, "rand_seed")
      && pp.field("balance_remaining")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field("myself")
      && t_MsgAddressInt.print_skip(pp, cs)
      && pp.close();
}

const SmartContractInfo t_SmartContractInfo;

//
// code for type `OutList`
//

int OutList::get_tag(const vm::CellSlice& cs) const {
  // distinguish by parameter `m` using 1 2 2 2
  return m ? out_list : out_list_empty;
}

bool OutList::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case out_list_empty:
    return m == 0;
  case out_list: {
    int n;
    return add_r1(n, 1, m)
        && cs.advance_refs(1)
        && t_OutAction.skip(cs);
    }
  }
  return false;
}

bool OutList::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case out_list_empty:
    return m == 0;
  case out_list: {
    int n;
    return add_r1(n, 1, m)
        && OutList{n}.validate_skip_ref(cs)
        && t_OutAction.validate_skip(cs);
    }
  }
  return false;
}

bool OutList::unpack(vm::CellSlice& cs, OutList::Record_out_list_empty& data) const {
  return m == 0;
}

bool OutList::unpack_out_list_empty(vm::CellSlice& cs) const {
  return m == 0;
}

bool OutList::cell_unpack(Ref<vm::Cell> cell_ref, OutList::Record_out_list_empty& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutList::cell_unpack_out_list_empty(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_out_list_empty(cs) && cs.empty_ext();
}

bool OutList::unpack(vm::CellSlice& cs, OutList::Record_out_list& data) const {
  return add_r1(data.n, 1, m)
      && cs.fetch_ref_to(data.prev)
      && t_OutAction.fetch_to(cs, data.action);
}

bool OutList::cell_unpack(Ref<vm::Cell> cell_ref, OutList::Record_out_list& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutList::pack(vm::CellBuilder& cb, const OutList::Record_out_list_empty& data) const {
  return m == 0;
}

bool OutList::pack_out_list_empty(vm::CellBuilder& cb) const {
  return m == 0;
}

bool OutList::cell_pack(Ref<vm::Cell>& cell_ref, const OutList::Record_out_list_empty& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutList::cell_pack_out_list_empty(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_out_list_empty(cb) && std::move(cb).finalize_to(cell_ref);
}

bool OutList::pack(vm::CellBuilder& cb, const OutList::Record_out_list& data) const {
  int n;
  return add_r1(n, 1, m)
      && cb.store_ref_bool(data.prev)
      && t_OutAction.store_from(cb, data.action);
}

bool OutList::cell_pack(Ref<vm::Cell>& cell_ref, const OutList::Record_out_list& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutList::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case out_list_empty:
    return pp.cons("out_list_empty")
        && m == 0;
  case out_list: {
    int n;
    return pp.open("out_list")
        && add_r1(n, 1, m)
        && pp.field("prev")
        && OutList{n}.print_ref(pp, cs.fetch_ref())
        && pp.field("action")
        && t_OutAction.print_skip(pp, cs)
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for OutList");
}


//
// code for type `OutAction`
//
constexpr unsigned OutAction::cons_tag[3];

bool OutAction::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case action_send_msg:
    return cs.advance_ext(0x10028);
  case action_set_code:
    return cs.advance_ext(0x10020);
  case action_reserve_currency:
    return cs.advance(40)
        && t_CurrencyCollection.skip(cs);
  }
  return false;
}

bool OutAction::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case action_send_msg:
    return cs.fetch_ulong(32) == 0xec3c86d
        && cs.advance(8)
        && t_MessageRelaxed_Any.validate_skip_ref(cs);
  case action_set_code:
    return cs.fetch_ulong(32) == 0xad4de08eU
        && cs.advance_refs(1);
  case action_reserve_currency:
    return cs.fetch_ulong(32) == 0x36e6b809
        && cs.advance(8)
        && t_CurrencyCollection.validate_skip(cs);
  }
  return false;
}

bool OutAction::unpack(vm::CellSlice& cs, OutAction::Record_action_send_msg& data) const {
  return cs.fetch_ulong(32) == 0xec3c86d
      && cs.fetch_uint_to(8, data.mode)
      && cs.fetch_ref_to(data.out_msg);
}

bool OutAction::cell_unpack(Ref<vm::Cell> cell_ref, OutAction::Record_action_send_msg& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutAction::unpack(vm::CellSlice& cs, OutAction::Record_action_set_code& data) const {
  return cs.fetch_ulong(32) == 0xad4de08eU
      && cs.fetch_ref_to(data.new_code);
}

bool OutAction::unpack_action_set_code(vm::CellSlice& cs, Ref<Cell>& new_code) const {
  return cs.fetch_ulong(32) == 0xad4de08eU
      && cs.fetch_ref_to(new_code);
}

bool OutAction::cell_unpack(Ref<vm::Cell> cell_ref, OutAction::Record_action_set_code& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutAction::cell_unpack_action_set_code(Ref<vm::Cell> cell_ref, Ref<Cell>& new_code) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_action_set_code(cs, new_code) && cs.empty_ext();
}

bool OutAction::unpack(vm::CellSlice& cs, OutAction::Record_action_reserve_currency& data) const {
  return cs.fetch_ulong(32) == 0x36e6b809
      && cs.fetch_uint_to(8, data.mode)
      && t_CurrencyCollection.fetch_to(cs, data.currency);
}

bool OutAction::cell_unpack(Ref<vm::Cell> cell_ref, OutAction::Record_action_reserve_currency& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutAction::pack(vm::CellBuilder& cb, const OutAction::Record_action_send_msg& data) const {
  return cb.store_long_bool(0xec3c86d, 32)
      && cb.store_ulong_rchk_bool(data.mode, 8)
      && cb.store_ref_bool(data.out_msg);
}

bool OutAction::cell_pack(Ref<vm::Cell>& cell_ref, const OutAction::Record_action_send_msg& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutAction::pack(vm::CellBuilder& cb, const OutAction::Record_action_set_code& data) const {
  return cb.store_long_bool(0xad4de08eU, 32)
      && cb.store_ref_bool(data.new_code);
}

bool OutAction::pack_action_set_code(vm::CellBuilder& cb, Ref<Cell> new_code) const {
  return cb.store_long_bool(0xad4de08eU, 32)
      && cb.store_ref_bool(new_code);
}

bool OutAction::cell_pack(Ref<vm::Cell>& cell_ref, const OutAction::Record_action_set_code& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutAction::cell_pack_action_set_code(Ref<vm::Cell>& cell_ref, Ref<Cell> new_code) const {
  vm::CellBuilder cb;
  return pack_action_set_code(cb, std::move(new_code)) && std::move(cb).finalize_to(cell_ref);
}

bool OutAction::pack(vm::CellBuilder& cb, const OutAction::Record_action_reserve_currency& data) const {
  return cb.store_long_bool(0x36e6b809, 32)
      && cb.store_ulong_rchk_bool(data.mode, 8)
      && t_CurrencyCollection.store_from(cb, data.currency);
}

bool OutAction::cell_pack(Ref<vm::Cell>& cell_ref, const OutAction::Record_action_reserve_currency& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutAction::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case action_send_msg: {
    int mode;
    return cs.fetch_ulong(32) == 0xec3c86d
        && pp.open("action_send_msg")
        && cs.fetch_uint_to(8, mode)
        && pp.field_int(mode, "mode")
        && pp.field("out_msg")
        && t_MessageRelaxed_Any.print_ref(pp, cs.fetch_ref())
        && pp.close();
    }
  case action_set_code:
    return cs.fetch_ulong(32) == 0xad4de08eU
        && pp.open("action_set_code")
        && pp.field("new_code")
        && t_Anything.print_ref(pp, cs.fetch_ref())
        && pp.close();
  case action_reserve_currency: {
    int mode;
    return cs.fetch_ulong(32) == 0x36e6b809
        && pp.open("action_reserve_currency")
        && cs.fetch_uint_to(8, mode)
        && pp.field_int(mode, "mode")
        && pp.field("currency")
        && t_CurrencyCollection.print_skip(pp, cs)
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for OutAction");
}

const OutAction t_OutAction;

//
// code for type `OutListNode`
//

bool OutListNode::skip(vm::CellSlice& cs) const {
  return cs.advance_refs(1)
      && t_OutAction.skip(cs);
}

bool OutListNode::validate_skip(vm::CellSlice& cs) const {
  return cs.advance_refs(1)
      && t_OutAction.validate_skip(cs);
}

bool OutListNode::unpack(vm::CellSlice& cs, OutListNode::Record& data) const {
  return cs.fetch_ref_to(data.prev)
      && t_OutAction.fetch_to(cs, data.action);
}

bool OutListNode::cell_unpack(Ref<vm::Cell> cell_ref, OutListNode::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OutListNode::pack(vm::CellBuilder& cb, const OutListNode::Record& data) const {
  return cb.store_ref_bool(data.prev)
      && t_OutAction.store_from(cb, data.action);
}

bool OutListNode::cell_pack(Ref<vm::Cell>& cell_ref, const OutListNode::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OutListNode::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("out_list_node")
      && pp.field("prev")
      && t_Anything.print_ref(pp, cs.fetch_ref())
      && pp.field("action")
      && t_OutAction.print_skip(pp, cs)
      && pp.close();
}

const OutListNode t_OutListNode;

//
// code for type `ShardIdent`
//

bool ShardIdent::validate_skip(vm::CellSlice& cs) const {
  int shard_pfx_bits;
  return cs.fetch_ulong(2) == 0
      && cs.fetch_uint_leq(60, shard_pfx_bits)
      && cs.advance(96);
}

bool ShardIdent::unpack(vm::CellSlice& cs, ShardIdent::Record& data) const {
  return cs.fetch_ulong(2) == 0
      && cs.fetch_uint_leq(60, data.shard_pfx_bits)
      && cs.fetch_int_to(32, data.workchain_id)
      && cs.fetch_uint_to(64, data.shard_prefix);
}

bool ShardIdent::cell_unpack(Ref<vm::Cell> cell_ref, ShardIdent::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardIdent::pack(vm::CellBuilder& cb, const ShardIdent::Record& data) const {
  return cb.store_long_bool(0, 2)
      && cb.store_uint_leq(60, data.shard_pfx_bits)
      && cb.store_long_rchk_bool(data.workchain_id, 32)
      && cb.store_ulong_rchk_bool(data.shard_prefix, 64);
}

bool ShardIdent::cell_pack(Ref<vm::Cell>& cell_ref, const ShardIdent::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardIdent::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int shard_pfx_bits;
  return cs.fetch_ulong(2) == 0
      && pp.open("shard_ident")
      && cs.fetch_uint_leq(60, shard_pfx_bits)
      && pp.field_int(shard_pfx_bits, "shard_pfx_bits")
      && pp.fetch_int_field(cs, 32, "workchain_id")
      && pp.fetch_uint_field(cs, 64, "shard_prefix")
      && pp.close();
}

const ShardIdent t_ShardIdent;

//
// code for type `ExtBlkRef`
//

bool ExtBlkRef::unpack(vm::CellSlice& cs, ExtBlkRef::Record& data) const {
  return cs.fetch_uint_to(64, data.end_lt)
      && cs.fetch_uint_to(32, data.seq_no)
      && cs.fetch_bits_to(data.root_hash.bits(), 256)
      && cs.fetch_bits_to(data.file_hash.bits(), 256);
}

bool ExtBlkRef::cell_unpack(Ref<vm::Cell> cell_ref, ExtBlkRef::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ExtBlkRef::pack(vm::CellBuilder& cb, const ExtBlkRef::Record& data) const {
  return cb.store_ulong_rchk_bool(data.end_lt, 64)
      && cb.store_ulong_rchk_bool(data.seq_no, 32)
      && cb.store_bits_bool(data.root_hash.cbits(), 256)
      && cb.store_bits_bool(data.file_hash.cbits(), 256);
}

bool ExtBlkRef::cell_pack(Ref<vm::Cell>& cell_ref, const ExtBlkRef::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ExtBlkRef::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("ext_blk_ref")
      && pp.fetch_uint_field(cs, 64, "end_lt")
      && pp.fetch_uint_field(cs, 32, "seq_no")
      && pp.fetch_bits_field(cs, 256, "root_hash")
      && pp.fetch_bits_field(cs, 256, "file_hash")
      && pp.close();
}

const ExtBlkRef t_ExtBlkRef;

//
// code for type `BlockIdExt`
//

bool BlockIdExt::validate_skip(vm::CellSlice& cs) const {
  return t_ShardIdent.validate_skip(cs)
      && cs.advance(544);
}

bool BlockIdExt::unpack(vm::CellSlice& cs, BlockIdExt::Record& data) const {
  return cs.fetch_subslice_to(104, data.shard_id)
      && cs.fetch_uint_to(32, data.seq_no)
      && cs.fetch_bits_to(data.root_hash.bits(), 256)
      && cs.fetch_bits_to(data.file_hash.bits(), 256);
}

bool BlockIdExt::cell_unpack(Ref<vm::Cell> cell_ref, BlockIdExt::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BlockIdExt::pack(vm::CellBuilder& cb, const BlockIdExt::Record& data) const {
  return cb.append_cellslice_chk(data.shard_id, 104)
      && cb.store_ulong_rchk_bool(data.seq_no, 32)
      && cb.store_bits_bool(data.root_hash.cbits(), 256)
      && cb.store_bits_bool(data.file_hash.cbits(), 256);
}

bool BlockIdExt::cell_pack(Ref<vm::Cell>& cell_ref, const BlockIdExt::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BlockIdExt::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("block_id_ext")
      && pp.field("shard_id")
      && t_ShardIdent.print_skip(pp, cs)
      && pp.fetch_uint_field(cs, 32, "seq_no")
      && pp.fetch_bits_field(cs, 256, "root_hash")
      && pp.fetch_bits_field(cs, 256, "file_hash")
      && pp.close();
}

const BlockIdExt t_BlockIdExt;

//
// code for type `BlkMasterInfo`
//

bool BlkMasterInfo::unpack(vm::CellSlice& cs, BlkMasterInfo::Record& data) const {
  return cs.fetch_subslice_to(608, data.master);
}

bool BlkMasterInfo::unpack_master_info(vm::CellSlice& cs, Ref<CellSlice>& master) const {
  return cs.fetch_subslice_to(608, master);
}

bool BlkMasterInfo::cell_unpack(Ref<vm::Cell> cell_ref, BlkMasterInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BlkMasterInfo::cell_unpack_master_info(Ref<vm::Cell> cell_ref, Ref<CellSlice>& master) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_master_info(cs, master) && cs.empty_ext();
}

bool BlkMasterInfo::pack(vm::CellBuilder& cb, const BlkMasterInfo::Record& data) const {
  return cb.append_cellslice_chk(data.master, 608);
}

bool BlkMasterInfo::pack_master_info(vm::CellBuilder& cb, Ref<CellSlice> master) const {
  return cb.append_cellslice_chk(master, 608);
}

bool BlkMasterInfo::cell_pack(Ref<vm::Cell>& cell_ref, const BlkMasterInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BlkMasterInfo::cell_pack_master_info(Ref<vm::Cell>& cell_ref, Ref<CellSlice> master) const {
  vm::CellBuilder cb;
  return pack_master_info(cb, std::move(master)) && std::move(cb).finalize_to(cell_ref);
}

bool BlkMasterInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("master_info")
      && pp.field("master")
      && t_ExtBlkRef.print_skip(pp, cs)
      && pp.close();
}

const BlkMasterInfo t_BlkMasterInfo;

//
// code for auxiliary type `ShardStateUnsplit_aux`
//

bool ShardStateUnsplit_aux::skip(vm::CellSlice& cs) const {
  return t_CurrencyCollection.skip(cs)
      && t_CurrencyCollection.skip(cs)
      && t_HashmapE_256_LibDescr.skip(cs);
}

bool ShardStateUnsplit_aux::validate_skip(vm::CellSlice& cs) const {
  return t_CurrencyCollection.validate_skip(cs)
      && t_CurrencyCollection.validate_skip(cs)
      && t_HashmapE_256_LibDescr.validate_skip(cs);
}

bool ShardStateUnsplit_aux::unpack(vm::CellSlice& cs, ShardStateUnsplit_aux::Record& data) const {
  return t_CurrencyCollection.fetch_to(cs, data.total_balance)
      && t_CurrencyCollection.fetch_to(cs, data.total_validator_fees)
      && t_HashmapE_256_LibDescr.fetch_to(cs, data.libraries);
}

bool ShardStateUnsplit_aux::cell_unpack(Ref<vm::Cell> cell_ref, ShardStateUnsplit_aux::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardStateUnsplit_aux::pack(vm::CellBuilder& cb, const ShardStateUnsplit_aux::Record& data) const {
  return t_CurrencyCollection.store_from(cb, data.total_balance)
      && t_CurrencyCollection.store_from(cb, data.total_validator_fees)
      && t_HashmapE_256_LibDescr.store_from(cb, data.libraries);
}

bool ShardStateUnsplit_aux::cell_pack(Ref<vm::Cell>& cell_ref, const ShardStateUnsplit_aux::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardStateUnsplit_aux::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field("total_balance")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field("total_validator_fees")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field("libraries")
      && t_HashmapE_256_LibDescr.print_skip(pp, cs)
      && pp.close();
}

const ShardStateUnsplit_aux t_ShardStateUnsplit_aux;

//
// code for type `ShardStateUnsplit`
//
constexpr unsigned ShardStateUnsplit::cons_tag[1];

bool ShardStateUnsplit::skip(vm::CellSlice& cs) const {
  return cs.advance_ext(0x10149)
      && t_ShardAccounts.skip(cs)
      && cs.advance_refs(1)
      && t_Maybe_BlkMasterInfo.skip(cs)
      && t_Maybe_Ref_McStateExtra.skip(cs);
}

bool ShardStateUnsplit::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0x9023afdeU
      && cs.advance(32)
      && t_ShardIdent.validate_skip(cs)
      && cs.advance(160)
      && t_OutMsgQueueInfo.validate_skip_ref(cs)
      && cs.advance(1)
      && t_ShardAccounts.validate_skip(cs)
      && t_ShardStateUnsplit_aux.validate_skip_ref(cs)
      && t_Maybe_BlkMasterInfo.validate_skip(cs)
      && t_Maybe_Ref_McStateExtra.validate_skip(cs);
}

bool ShardStateUnsplit::unpack(vm::CellSlice& cs, ShardStateUnsplit::Record& data) const {
  return cs.fetch_ulong(32) == 0x9023afdeU
      && cs.fetch_int_to(32, data.global_id)
      && cs.fetch_subslice_to(104, data.shard_id)
      && cs.fetch_uint_to(32, data.seq_no)
      && cs.fetch_uint_to(32, data.vert_seq_no)
      && cs.fetch_uint_to(32, data.gen_utime)
      && cs.fetch_uint_to(64, data.gen_lt)
      && cs.fetch_ref_to(data.out_msg_queue_info)
      && cs.fetch_bool_to(data.before_split)
      && t_ShardAccounts.fetch_to(cs, data.accounts)
      && t_ShardStateUnsplit_aux.cell_unpack(cs.fetch_ref(), data.r1)
      && t_Maybe_BlkMasterInfo.fetch_to(cs, data.master_ref)
      && t_Maybe_Ref_McStateExtra.fetch_to(cs, data.custom);
}

bool ShardStateUnsplit::cell_unpack(Ref<vm::Cell> cell_ref, ShardStateUnsplit::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardStateUnsplit::pack(vm::CellBuilder& cb, const ShardStateUnsplit::Record& data) const {
  Ref<vm::Cell> tmp_cell;
  return cb.store_long_bool(0x9023afdeU, 32)
      && cb.store_long_rchk_bool(data.global_id, 32)
      && cb.append_cellslice_chk(data.shard_id, 104)
      && cb.store_ulong_rchk_bool(data.seq_no, 32)
      && cb.store_ulong_rchk_bool(data.vert_seq_no, 32)
      && cb.store_ulong_rchk_bool(data.gen_utime, 32)
      && cb.store_ulong_rchk_bool(data.gen_lt, 64)
      && cb.store_ref_bool(data.out_msg_queue_info)
      && cb.store_ulong_rchk_bool(data.before_split, 1)
      && t_ShardAccounts.store_from(cb, data.accounts)
      && t_ShardStateUnsplit_aux.cell_pack(tmp_cell, data.r1)
      && cb.store_ref_bool(std::move(tmp_cell))
      && t_Maybe_BlkMasterInfo.store_from(cb, data.master_ref)
      && t_Maybe_Ref_McStateExtra.store_from(cb, data.custom);
}

bool ShardStateUnsplit::cell_pack(Ref<vm::Cell>& cell_ref, const ShardStateUnsplit::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardStateUnsplit::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int vert_seq_no, before_split;
  return cs.fetch_ulong(32) == 0x9023afdeU
      && pp.open("shard_state")
      && pp.fetch_int_field(cs, 32, "global_id")
      && pp.field("shard_id")
      && t_ShardIdent.print_skip(pp, cs)
      && pp.fetch_uint_field(cs, 32, "seq_no")
      && cs.fetch_uint_to(32, vert_seq_no)
      && pp.field_int(vert_seq_no, "vert_seq_no")
      && pp.fetch_uint_field(cs, 32, "gen_utime")
      && pp.fetch_uint_field(cs, 64, "gen_lt")
      && pp.field("out_msg_queue_info")
      && t_OutMsgQueueInfo.print_ref(pp, cs.fetch_ref())
      && cs.fetch_bool_to(before_split)
      && pp.field_int(before_split, "before_split")
      && pp.field("accounts")
      && t_ShardAccounts.print_skip(pp, cs)
      && pp.field()
      && t_ShardStateUnsplit_aux.print_ref(pp, cs.fetch_ref())
      && pp.field("master_ref")
      && t_Maybe_BlkMasterInfo.print_skip(pp, cs)
      && pp.field("custom")
      && t_Maybe_Ref_McStateExtra.print_skip(pp, cs)
      && pp.close();
}

const ShardStateUnsplit t_ShardStateUnsplit;

//
// code for type `ShardState`
//
constexpr char ShardState::cons_len[2];
constexpr unsigned ShardState::cons_tag[2];

bool ShardState::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cons1:
    return t_ShardStateUnsplit.skip(cs);
  case split_state:
    return cs.advance_ext(0x20020);
  }
  return false;
}

bool ShardState::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cons1:
    return t_ShardStateUnsplit.validate_skip(cs);
  case split_state:
    return cs.fetch_ulong(32) == 0x5f327da5
        && t_ShardStateUnsplit.validate_skip_ref(cs)
        && t_ShardStateUnsplit.validate_skip_ref(cs);
  }
  return false;
}

bool ShardState::unpack(vm::CellSlice& cs, ShardState::Record_cons1& data) const {
  return t_ShardStateUnsplit.fetch_to(cs, data.x);
}

bool ShardState::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_ShardStateUnsplit.fetch_to(cs, x);
}

bool ShardState::cell_unpack(Ref<vm::Cell> cell_ref, ShardState::Record_cons1& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardState::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool ShardState::unpack(vm::CellSlice& cs, ShardState::Record_split_state& data) const {
  return cs.fetch_ulong(32) == 0x5f327da5
      && cs.fetch_ref_to(data.left)
      && cs.fetch_ref_to(data.right);
}

bool ShardState::cell_unpack(Ref<vm::Cell> cell_ref, ShardState::Record_split_state& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardState::pack(vm::CellBuilder& cb, const ShardState::Record_cons1& data) const {
  return t_ShardStateUnsplit.store_from(cb, data.x);
}

bool ShardState::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_ShardStateUnsplit.store_from(cb, x);
}

bool ShardState::cell_pack(Ref<vm::Cell>& cell_ref, const ShardState::Record_cons1& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardState::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ShardState::pack(vm::CellBuilder& cb, const ShardState::Record_split_state& data) const {
  return cb.store_long_bool(0x5f327da5, 32)
      && cb.store_ref_bool(data.left)
      && cb.store_ref_bool(data.right);
}

bool ShardState::cell_pack(Ref<vm::Cell>& cell_ref, const ShardState::Record_split_state& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardState::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cons1:
    return pp.open()
        && pp.field()
        && t_ShardStateUnsplit.print_skip(pp, cs)
        && pp.close();
  case split_state:
    return cs.fetch_ulong(32) == 0x5f327da5
        && pp.open("split_state")
        && pp.field("left")
        && t_ShardStateUnsplit.print_ref(pp, cs.fetch_ref())
        && pp.field("right")
        && t_ShardStateUnsplit.print_ref(pp, cs.fetch_ref())
        && pp.close();
  }
  return pp.fail("unknown constructor for ShardState");
}

const ShardState t_ShardState;

//
// code for type `LibDescr`
//

bool LibDescr::skip(vm::CellSlice& cs) const {
  return cs.advance_ext(0x10002)
      && t_Hashmap_256_True.skip(cs);
}

bool LibDescr::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 0
      && cs.advance_refs(1)
      && t_Hashmap_256_True.validate_skip(cs);
}

bool LibDescr::unpack(vm::CellSlice& cs, LibDescr::Record& data) const {
  return cs.fetch_ulong(2) == 0
      && cs.fetch_ref_to(data.lib)
      && t_Hashmap_256_True.fetch_to(cs, data.publishers);
}

bool LibDescr::cell_unpack(Ref<vm::Cell> cell_ref, LibDescr::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool LibDescr::pack(vm::CellBuilder& cb, const LibDescr::Record& data) const {
  return cb.store_long_bool(0, 2)
      && cb.store_ref_bool(data.lib)
      && t_Hashmap_256_True.store_from(cb, data.publishers);
}

bool LibDescr::cell_pack(Ref<vm::Cell>& cell_ref, const LibDescr::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool LibDescr::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(2) == 0
      && pp.open("shared_lib_descr")
      && pp.field("lib")
      && t_Anything.print_ref(pp, cs.fetch_ref())
      && pp.field("publishers")
      && t_Hashmap_256_True.print_skip(pp, cs)
      && pp.close();
}

const LibDescr t_LibDescr;

//
// code for type `BlockInfo`
//
constexpr unsigned BlockInfo::cons_tag[1];

bool BlockInfo::skip(vm::CellSlice& cs) const {
  int not_master, after_merge, seq_no, vert_seq_no, prev_seq_no;
  return cs.advance(64)
      && cs.fetch_bool_to(not_master)
      && cs.fetch_bool_to(after_merge)
      && cs.advance(14)
      && cs.fetch_uint_to(32, seq_no)
      && cs.fetch_uint_to(32, vert_seq_no)
      && add_r1(prev_seq_no, 1, seq_no)
      && cs.advance(328)
      && (!not_master || cs.advance_refs(1))
      && cs.advance_refs(1)
      && (!vert_seq_no || cs.advance_refs(1));
}

bool BlockInfo::validate_skip(vm::CellSlice& cs) const {
  int not_master, after_merge, seq_no, vert_seq_no, prev_seq_no;
  return cs.fetch_ulong(32) == 0x9bc7a986U
      && cs.advance(32)
      && cs.fetch_bool_to(not_master)
      && cs.fetch_bool_to(after_merge)
      && cs.advance(14)
      && cs.fetch_uint_to(32, seq_no)
      && cs.fetch_uint_to(32, vert_seq_no)
      && add_r1(prev_seq_no, 1, seq_no)
      && t_ShardIdent.validate_skip(cs)
      && cs.advance(224)
      && (!not_master || t_BlkMasterInfo.validate_skip_ref(cs))
      && BlkPrevInfo{after_merge}.validate_skip_ref(cs)
      && (!vert_seq_no || t_BlkPrevInfo_0.validate_skip_ref(cs));
}

bool BlockInfo::unpack(vm::CellSlice& cs, BlockInfo::Record& data) const {
  int prev_seq_no;
  return cs.fetch_ulong(32) == 0x9bc7a986U
      && cs.fetch_uint_to(32, data.version)
      && cs.fetch_bool_to(data.not_master)
      && cs.fetch_bool_to(data.after_merge)
      && cs.fetch_bool_to(data.before_split)
      && cs.fetch_bool_to(data.after_split)
      && cs.fetch_bool_to(data.want_split)
      && cs.fetch_bool_to(data.want_merge)
      && cs.fetch_uint_to(10, data.flags)
      && cs.fetch_uint_to(32, data.seq_no)
      && cs.fetch_uint_to(32, data.vert_seq_no)
      && add_r1(prev_seq_no, 1, data.seq_no)
      && cs.fetch_subslice_to(104, data.shard)
      && cs.fetch_uint_to(32, data.gen_utime)
      && cs.fetch_uint_to(64, data.start_lt)
      && cs.fetch_uint_to(64, data.end_lt)
      && cs.fetch_uint_to(32, data.gen_validator_list_hash_short)
      && cs.fetch_uint_to(32, data.gen_catchain_seqno)
      && (!data.not_master || cs.fetch_ref_to(data.master_ref))
      && cs.fetch_ref_to(data.prev_ref)
      && (!data.vert_seq_no || cs.fetch_ref_to(data.prev_vert_ref));
}

bool BlockInfo::cell_unpack(Ref<vm::Cell> cell_ref, BlockInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BlockInfo::pack(vm::CellBuilder& cb, const BlockInfo::Record& data) const {
  int prev_seq_no;
  return cb.store_long_bool(0x9bc7a986U, 32)
      && cb.store_ulong_rchk_bool(data.version, 32)
      && cb.store_ulong_rchk_bool(data.not_master, 1)
      && cb.store_ulong_rchk_bool(data.after_merge, 1)
      && cb.store_ulong_rchk_bool(data.before_split, 1)
      && cb.store_ulong_rchk_bool(data.after_split, 1)
      && cb.store_ulong_rchk_bool(data.want_split, 1)
      && cb.store_ulong_rchk_bool(data.want_merge, 1)
      && cb.store_ulong_rchk_bool(data.flags, 10)
      && cb.store_ulong_rchk_bool(data.seq_no, 32)
      && cb.store_ulong_rchk_bool(data.vert_seq_no, 32)
      && add_r1(prev_seq_no, 1, data.seq_no)
      && cb.append_cellslice_chk(data.shard, 104)
      && cb.store_ulong_rchk_bool(data.gen_utime, 32)
      && cb.store_ulong_rchk_bool(data.start_lt, 64)
      && cb.store_ulong_rchk_bool(data.end_lt, 64)
      && cb.store_ulong_rchk_bool(data.gen_validator_list_hash_short, 32)
      && cb.store_ulong_rchk_bool(data.gen_catchain_seqno, 32)
      && (!data.not_master || cb.store_ref_bool(data.master_ref))
      && cb.store_ref_bool(data.prev_ref)
      && (!data.vert_seq_no || cb.store_ref_bool(data.prev_vert_ref));
}

bool BlockInfo::cell_pack(Ref<vm::Cell>& cell_ref, const BlockInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BlockInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int not_master, after_merge, before_split, after_split, flags, seq_no, vert_seq_no, prev_seq_no;
  return cs.fetch_ulong(32) == 0x9bc7a986U
      && pp.open("block_info")
      && pp.fetch_uint_field(cs, 32, "version")
      && cs.fetch_bool_to(not_master)
      && pp.field_int(not_master, "not_master")
      && cs.fetch_bool_to(after_merge)
      && pp.field_int(after_merge, "after_merge")
      && cs.fetch_bool_to(before_split)
      && pp.field_int(before_split, "before_split")
      && cs.fetch_bool_to(after_split)
      && pp.field_int(after_split, "after_split")
      && pp.fetch_uint_field(cs, 1, "want_split")
      && pp.fetch_uint_field(cs, 1, "want_merge")
      && cs.fetch_uint_to(10, flags)
      && pp.field_int(flags, "flags")
      && cs.fetch_uint_to(32, seq_no)
      && pp.field_int(seq_no, "seq_no")
      && cs.fetch_uint_to(32, vert_seq_no)
      && pp.field_int(vert_seq_no, "vert_seq_no")
      && add_r1(prev_seq_no, 1, seq_no)
      && pp.field("shard")
      && t_ShardIdent.print_skip(pp, cs)
      && pp.fetch_uint_field(cs, 32, "gen_utime")
      && pp.fetch_uint_field(cs, 64, "start_lt")
      && pp.fetch_uint_field(cs, 64, "end_lt")
      && pp.fetch_uint_field(cs, 32, "gen_validator_list_hash_short")
      && pp.fetch_uint_field(cs, 32, "gen_catchain_seqno")
      && (!not_master || (pp.field("master_ref") && t_BlkMasterInfo.print_ref(pp, cs.fetch_ref())))
      && pp.field("prev_ref")
      && BlkPrevInfo{after_merge}.print_ref(pp, cs.fetch_ref())
      && (!vert_seq_no || (pp.field("prev_vert_ref") && t_BlkPrevInfo_0.print_ref(pp, cs.fetch_ref())))
      && pp.close();
}

const BlockInfo t_BlockInfo;

//
// code for type `BlkPrevInfo`
//

bool BlkPrevInfo::skip(vm::CellSlice& cs) const {
  return cs.advance(608)
      && (!m || cs.advance(608));
}

bool BlkPrevInfo::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(608)
      && (!m || cs.advance(608));
}

bool BlkPrevInfo::unpack(vm::CellSlice& cs, BlkPrevInfo::Record& data) const {
  return (data.merged = m) >= 0
      && cs.fetch_subslice_to(608, data.prev)
      && (!m || cs.fetch_subslice_to(608, data.prev_alt));
}

bool BlkPrevInfo::cell_unpack(Ref<vm::Cell> cell_ref, BlkPrevInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BlkPrevInfo::pack(vm::CellBuilder& cb, const BlkPrevInfo::Record& data) const {
  return cb.append_cellslice_chk(data.prev, 608)
      && (!m || cb.append_cellslice_chk(data.prev_alt, 608));
}

bool BlkPrevInfo::cell_pack(Ref<vm::Cell>& cell_ref, const BlkPrevInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BlkPrevInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("prev_blk_info")
      && pp.field("prev")
      && t_ExtBlkRef.print_skip(pp, cs)
      && (!m || (pp.field("prev_alt") && t_ExtBlkRef.print_skip(pp, cs)))
      && pp.close();
}


//
// code for type `Block`
//
constexpr unsigned Block::cons_tag[1];

bool Block::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0x11ef55aa
      && cs.advance(32)
      && t_BlockInfo.validate_skip_ref(cs)
      && t_ValueFlow.validate_skip_ref(cs)
      && t_MERKLE_UPDATE_ShardState.validate_skip_ref(cs)
      && t_BlockExtra.validate_skip_ref(cs);
}

bool Block::unpack(vm::CellSlice& cs, Block::Record& data) const {
  return cs.fetch_ulong(32) == 0x11ef55aa
      && cs.fetch_int_to(32, data.global_id)
      && cs.fetch_ref_to(data.info)
      && cs.fetch_ref_to(data.value_flow)
      && cs.fetch_ref_to(data.state_update)
      && cs.fetch_ref_to(data.extra);
}

bool Block::cell_unpack(Ref<vm::Cell> cell_ref, Block::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool Block::pack(vm::CellBuilder& cb, const Block::Record& data) const {
  return cb.store_long_bool(0x11ef55aa, 32)
      && cb.store_long_rchk_bool(data.global_id, 32)
      && cb.store_ref_bool(data.info)
      && cb.store_ref_bool(data.value_flow)
      && cb.store_ref_bool(data.state_update)
      && cb.store_ref_bool(data.extra);
}

bool Block::cell_pack(Ref<vm::Cell>& cell_ref, const Block::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool Block::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0x11ef55aa
      && pp.open("block")
      && pp.fetch_int_field(cs, 32, "global_id")
      && pp.field("info")
      && t_BlockInfo.print_ref(pp, cs.fetch_ref())
      && pp.field("value_flow")
      && t_ValueFlow.print_ref(pp, cs.fetch_ref())
      && pp.field("state_update")
      && t_MERKLE_UPDATE_ShardState.print_ref(pp, cs.fetch_ref())
      && pp.field("extra")
      && t_BlockExtra.print_ref(pp, cs.fetch_ref())
      && pp.close();
}

const Block t_Block;

//
// code for type `BlockExtra`
//
constexpr unsigned BlockExtra::cons_tag[1];

bool BlockExtra::skip(vm::CellSlice& cs) const {
  return cs.advance_ext(0x20020)
      && t_ShardAccountBlocks.skip(cs)
      && cs.advance(256)
      && t_Maybe_Ref_McBlockExtra.skip(cs);
}

bool BlockExtra::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0xa8929555U
      && t_InMsgDescr.validate_skip_ref(cs)
      && t_OutMsgDescr.validate_skip_ref(cs)
      && t_ShardAccountBlocks.validate_skip(cs)
      && cs.advance(256)
      && t_Maybe_Ref_McBlockExtra.validate_skip(cs);
}

bool BlockExtra::unpack(vm::CellSlice& cs, BlockExtra::Record& data) const {
  return cs.fetch_ulong(32) == 0xa8929555U
      && cs.fetch_ref_to(data.in_msg_descr)
      && cs.fetch_ref_to(data.out_msg_descr)
      && t_ShardAccountBlocks.fetch_to(cs, data.account_blocks)
      && cs.fetch_bits_to(data.rand_seed.bits(), 256)
      && t_Maybe_Ref_McBlockExtra.fetch_to(cs, data.custom);
}

bool BlockExtra::cell_unpack(Ref<vm::Cell> cell_ref, BlockExtra::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BlockExtra::pack(vm::CellBuilder& cb, const BlockExtra::Record& data) const {
  return cb.store_long_bool(0xa8929555U, 32)
      && cb.store_ref_bool(data.in_msg_descr)
      && cb.store_ref_bool(data.out_msg_descr)
      && t_ShardAccountBlocks.store_from(cb, data.account_blocks)
      && cb.store_bits_bool(data.rand_seed.cbits(), 256)
      && t_Maybe_Ref_McBlockExtra.store_from(cb, data.custom);
}

bool BlockExtra::cell_pack(Ref<vm::Cell>& cell_ref, const BlockExtra::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BlockExtra::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0xa8929555U
      && pp.open("block_extra")
      && pp.field("in_msg_descr")
      && t_InMsgDescr.print_ref(pp, cs.fetch_ref())
      && pp.field("out_msg_descr")
      && t_OutMsgDescr.print_ref(pp, cs.fetch_ref())
      && pp.field("account_blocks")
      && t_ShardAccountBlocks.print_skip(pp, cs)
      && pp.fetch_bits_field(cs, 256, "rand_seed")
      && pp.field("custom")
      && t_Maybe_Ref_McBlockExtra.print_skip(pp, cs)
      && pp.close();
}

const BlockExtra t_BlockExtra;

//
// code for auxiliary type `ValueFlow_aux`
//

bool ValueFlow_aux::skip(vm::CellSlice& cs) const {
  return t_CurrencyCollection.skip(cs)
      && t_CurrencyCollection.skip(cs)
      && t_CurrencyCollection.skip(cs)
      && t_CurrencyCollection.skip(cs);
}

bool ValueFlow_aux::validate_skip(vm::CellSlice& cs) const {
  return t_CurrencyCollection.validate_skip(cs)
      && t_CurrencyCollection.validate_skip(cs)
      && t_CurrencyCollection.validate_skip(cs)
      && t_CurrencyCollection.validate_skip(cs);
}

bool ValueFlow_aux::unpack(vm::CellSlice& cs, ValueFlow_aux::Record& data) const {
  return t_CurrencyCollection.fetch_to(cs, data.from_prev_blk)
      && t_CurrencyCollection.fetch_to(cs, data.to_next_blk)
      && t_CurrencyCollection.fetch_to(cs, data.imported)
      && t_CurrencyCollection.fetch_to(cs, data.exported);
}

bool ValueFlow_aux::cell_unpack(Ref<vm::Cell> cell_ref, ValueFlow_aux::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ValueFlow_aux::pack(vm::CellBuilder& cb, const ValueFlow_aux::Record& data) const {
  return t_CurrencyCollection.store_from(cb, data.from_prev_blk)
      && t_CurrencyCollection.store_from(cb, data.to_next_blk)
      && t_CurrencyCollection.store_from(cb, data.imported)
      && t_CurrencyCollection.store_from(cb, data.exported);
}

bool ValueFlow_aux::cell_pack(Ref<vm::Cell>& cell_ref, const ValueFlow_aux::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ValueFlow_aux::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field("from_prev_blk")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field("to_next_blk")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field("imported")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field("exported")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.close();
}

const ValueFlow_aux t_ValueFlow_aux;

//
// code for auxiliary type `ValueFlow_aux1`
//

bool ValueFlow_aux1::skip(vm::CellSlice& cs) const {
  return t_CurrencyCollection.skip(cs)
      && t_CurrencyCollection.skip(cs)
      && t_CurrencyCollection.skip(cs);
}

bool ValueFlow_aux1::validate_skip(vm::CellSlice& cs) const {
  return t_CurrencyCollection.validate_skip(cs)
      && t_CurrencyCollection.validate_skip(cs)
      && t_CurrencyCollection.validate_skip(cs);
}

bool ValueFlow_aux1::unpack(vm::CellSlice& cs, ValueFlow_aux1::Record& data) const {
  return t_CurrencyCollection.fetch_to(cs, data.fees_imported)
      && t_CurrencyCollection.fetch_to(cs, data.created)
      && t_CurrencyCollection.fetch_to(cs, data.minted);
}

bool ValueFlow_aux1::cell_unpack(Ref<vm::Cell> cell_ref, ValueFlow_aux1::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ValueFlow_aux1::pack(vm::CellBuilder& cb, const ValueFlow_aux1::Record& data) const {
  return t_CurrencyCollection.store_from(cb, data.fees_imported)
      && t_CurrencyCollection.store_from(cb, data.created)
      && t_CurrencyCollection.store_from(cb, data.minted);
}

bool ValueFlow_aux1::cell_pack(Ref<vm::Cell>& cell_ref, const ValueFlow_aux1::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ValueFlow_aux1::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field("fees_imported")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field("created")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field("minted")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.close();
}

const ValueFlow_aux1 t_ValueFlow_aux1;

//
// code for type `ValueFlow`
//
constexpr unsigned ValueFlow::cons_tag[1];

bool ValueFlow::skip(vm::CellSlice& cs) const {
  return cs.advance_ext(0x10020)
      && t_CurrencyCollection.skip(cs)
      && cs.advance_refs(1);
}

bool ValueFlow::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0x3fde65c8
      && t_ValueFlow_aux.validate_skip_ref(cs)
      && t_CurrencyCollection.validate_skip(cs)
      && t_ValueFlow_aux1.validate_skip_ref(cs);
}

bool ValueFlow::unpack(vm::CellSlice& cs, ValueFlow::Record& data) const {
  return cs.fetch_ulong(32) == 0x3fde65c8
      && t_ValueFlow_aux.cell_unpack(cs.fetch_ref(), data.r1)
      && t_CurrencyCollection.fetch_to(cs, data.fees_collected)
      && t_ValueFlow_aux1.cell_unpack(cs.fetch_ref(), data.r2);
}

bool ValueFlow::cell_unpack(Ref<vm::Cell> cell_ref, ValueFlow::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ValueFlow::pack(vm::CellBuilder& cb, const ValueFlow::Record& data) const {
  Ref<vm::Cell> tmp_cell;
  return cb.store_long_bool(0x3fde65c8, 32)
      && t_ValueFlow_aux.cell_pack(tmp_cell, data.r1)
      && cb.store_ref_bool(std::move(tmp_cell))
      && t_CurrencyCollection.store_from(cb, data.fees_collected)
      && t_ValueFlow_aux1.cell_pack(tmp_cell, data.r2)
      && cb.store_ref_bool(std::move(tmp_cell));
}

bool ValueFlow::cell_pack(Ref<vm::Cell>& cell_ref, const ValueFlow::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ValueFlow::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0x3fde65c8
      && pp.open("value_flow")
      && pp.field()
      && t_ValueFlow_aux.print_ref(pp, cs.fetch_ref())
      && pp.field("fees_collected")
      && t_CurrencyCollection.print_skip(pp, cs)
      && pp.field()
      && t_ValueFlow_aux1.print_ref(pp, cs.fetch_ref())
      && pp.close();
}

const ValueFlow t_ValueFlow;

//
// code for type `BinTree`
//

bool BinTree::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case bt_leaf:
    return cs.advance(1)
        && X.skip(cs);
  case bt_fork:
    return cs.advance_ext(0x20001);
  }
  return false;
}

bool BinTree::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case bt_leaf:
    return cs.advance(1)
        && X.validate_skip(cs);
  case bt_fork:
    return cs.advance(1)
        && validate_skip_ref(cs)
        && validate_skip_ref(cs);
  }
  return false;
}

bool BinTree::unpack(vm::CellSlice& cs, BinTree::Record_bt_leaf& data) const {
  return cs.fetch_ulong(1) == 0
      && X.fetch_to(cs, data.leaf);
}

bool BinTree::unpack_bt_leaf(vm::CellSlice& cs, Ref<CellSlice>& leaf) const {
  return cs.fetch_ulong(1) == 0
      && X.fetch_to(cs, leaf);
}

bool BinTree::cell_unpack(Ref<vm::Cell> cell_ref, BinTree::Record_bt_leaf& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BinTree::cell_unpack_bt_leaf(Ref<vm::Cell> cell_ref, Ref<CellSlice>& leaf) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_bt_leaf(cs, leaf) && cs.empty_ext();
}

bool BinTree::unpack(vm::CellSlice& cs, BinTree::Record_bt_fork& data) const {
  return cs.fetch_ulong(1) == 1
      && cs.fetch_ref_to(data.left)
      && cs.fetch_ref_to(data.right);
}

bool BinTree::cell_unpack(Ref<vm::Cell> cell_ref, BinTree::Record_bt_fork& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BinTree::pack(vm::CellBuilder& cb, const BinTree::Record_bt_leaf& data) const {
  return cb.store_long_bool(0, 1)
      && X.store_from(cb, data.leaf);
}

bool BinTree::pack_bt_leaf(vm::CellBuilder& cb, Ref<CellSlice> leaf) const {
  return cb.store_long_bool(0, 1)
      && X.store_from(cb, leaf);
}

bool BinTree::cell_pack(Ref<vm::Cell>& cell_ref, const BinTree::Record_bt_leaf& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BinTree::cell_pack_bt_leaf(Ref<vm::Cell>& cell_ref, Ref<CellSlice> leaf) const {
  vm::CellBuilder cb;
  return pack_bt_leaf(cb, std::move(leaf)) && std::move(cb).finalize_to(cell_ref);
}

bool BinTree::pack(vm::CellBuilder& cb, const BinTree::Record_bt_fork& data) const {
  return cb.store_long_bool(1, 1)
      && cb.store_ref_bool(data.left)
      && cb.store_ref_bool(data.right);
}

bool BinTree::cell_pack(Ref<vm::Cell>& cell_ref, const BinTree::Record_bt_fork& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BinTree::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case bt_leaf:
    return cs.advance(1)
        && pp.open("bt_leaf")
        && pp.field("leaf")
        && X.print_skip(pp, cs)
        && pp.close();
  case bt_fork:
    return cs.advance(1)
        && pp.open("bt_fork")
        && pp.field("left")
        && print_ref(pp, cs.fetch_ref())
        && pp.field("right")
        && print_ref(pp, cs.fetch_ref())
        && pp.close();
  }
  return pp.fail("unknown constructor for BinTree");
}


//
// code for type `FutureSplitMerge`
//
constexpr char FutureSplitMerge::cons_len[3];
constexpr unsigned char FutureSplitMerge::cons_tag[3];

bool FutureSplitMerge::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case fsm_none:
    return cs.advance(1);
  case fsm_split:
    return cs.advance(34);
  case fsm_merge:
    return cs.advance(34);
  }
  return false;
}

bool FutureSplitMerge::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case fsm_none:
    return cs.advance(1);
  case fsm_split:
    return cs.advance(34);
  case fsm_merge:
    return cs.advance(34);
  }
  return false;
}

bool FutureSplitMerge::unpack(vm::CellSlice& cs, FutureSplitMerge::Record_fsm_none& data) const {
  return cs.fetch_ulong(1) == 0;
}

bool FutureSplitMerge::unpack_fsm_none(vm::CellSlice& cs) const {
  return cs.fetch_ulong(1) == 0;
}

bool FutureSplitMerge::cell_unpack(Ref<vm::Cell> cell_ref, FutureSplitMerge::Record_fsm_none& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool FutureSplitMerge::cell_unpack_fsm_none(Ref<vm::Cell> cell_ref) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_fsm_none(cs) && cs.empty_ext();
}

bool FutureSplitMerge::unpack(vm::CellSlice& cs, FutureSplitMerge::Record_fsm_split& data) const {
  return cs.fetch_ulong(2) == 2
      && cs.fetch_uint_to(32, data.split_utime);
}

bool FutureSplitMerge::unpack_fsm_split(vm::CellSlice& cs, unsigned& split_utime) const {
  return cs.fetch_ulong(2) == 2
      && cs.fetch_uint_to(32, split_utime);
}

bool FutureSplitMerge::cell_unpack(Ref<vm::Cell> cell_ref, FutureSplitMerge::Record_fsm_split& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool FutureSplitMerge::cell_unpack_fsm_split(Ref<vm::Cell> cell_ref, unsigned& split_utime) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_fsm_split(cs, split_utime) && cs.empty_ext();
}

bool FutureSplitMerge::unpack(vm::CellSlice& cs, FutureSplitMerge::Record_fsm_merge& data) const {
  return cs.fetch_ulong(2) == 3
      && cs.fetch_uint_to(32, data.merge_utime);
}

bool FutureSplitMerge::unpack_fsm_merge(vm::CellSlice& cs, unsigned& merge_utime) const {
  return cs.fetch_ulong(2) == 3
      && cs.fetch_uint_to(32, merge_utime);
}

bool FutureSplitMerge::cell_unpack(Ref<vm::Cell> cell_ref, FutureSplitMerge::Record_fsm_merge& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool FutureSplitMerge::cell_unpack_fsm_merge(Ref<vm::Cell> cell_ref, unsigned& merge_utime) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_fsm_merge(cs, merge_utime) && cs.empty_ext();
}

bool FutureSplitMerge::pack(vm::CellBuilder& cb, const FutureSplitMerge::Record_fsm_none& data) const {
  return cb.store_long_bool(0, 1);
}

bool FutureSplitMerge::pack_fsm_none(vm::CellBuilder& cb) const {
  return cb.store_long_bool(0, 1);
}

bool FutureSplitMerge::cell_pack(Ref<vm::Cell>& cell_ref, const FutureSplitMerge::Record_fsm_none& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool FutureSplitMerge::cell_pack_fsm_none(Ref<vm::Cell>& cell_ref) const {
  vm::CellBuilder cb;
  return pack_fsm_none(cb) && std::move(cb).finalize_to(cell_ref);
}

bool FutureSplitMerge::pack(vm::CellBuilder& cb, const FutureSplitMerge::Record_fsm_split& data) const {
  return cb.store_long_bool(2, 2)
      && cb.store_ulong_rchk_bool(data.split_utime, 32);
}

bool FutureSplitMerge::pack_fsm_split(vm::CellBuilder& cb, unsigned split_utime) const {
  return cb.store_long_bool(2, 2)
      && cb.store_ulong_rchk_bool(split_utime, 32);
}

bool FutureSplitMerge::cell_pack(Ref<vm::Cell>& cell_ref, const FutureSplitMerge::Record_fsm_split& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool FutureSplitMerge::cell_pack_fsm_split(Ref<vm::Cell>& cell_ref, unsigned split_utime) const {
  vm::CellBuilder cb;
  return pack_fsm_split(cb, split_utime) && std::move(cb).finalize_to(cell_ref);
}

bool FutureSplitMerge::pack(vm::CellBuilder& cb, const FutureSplitMerge::Record_fsm_merge& data) const {
  return cb.store_long_bool(3, 2)
      && cb.store_ulong_rchk_bool(data.merge_utime, 32);
}

bool FutureSplitMerge::pack_fsm_merge(vm::CellBuilder& cb, unsigned merge_utime) const {
  return cb.store_long_bool(3, 2)
      && cb.store_ulong_rchk_bool(merge_utime, 32);
}

bool FutureSplitMerge::cell_pack(Ref<vm::Cell>& cell_ref, const FutureSplitMerge::Record_fsm_merge& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool FutureSplitMerge::cell_pack_fsm_merge(Ref<vm::Cell>& cell_ref, unsigned merge_utime) const {
  vm::CellBuilder cb;
  return pack_fsm_merge(cb, merge_utime) && std::move(cb).finalize_to(cell_ref);
}

bool FutureSplitMerge::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case fsm_none:
    return cs.advance(1)
        && pp.cons("fsm_none");
  case fsm_split:
    return cs.advance(2)
        && pp.open("fsm_split")
        && pp.fetch_uint_field(cs, 32, "split_utime")
        && pp.close();
  case fsm_merge:
    return cs.advance(2)
        && pp.open("fsm_merge")
        && pp.fetch_uint_field(cs, 32, "merge_utime")
        && pp.close();
  }
  return pp.fail("unknown constructor for FutureSplitMerge");
}

const FutureSplitMerge t_FutureSplitMerge;

//
// code for type `ShardDescr`
//

bool ShardDescr::skip(vm::CellSlice& cs) const {
  int flags;
  return cs.advance(677)
      && cs.fetch_uint_to(3, flags)
      && flags == 0
      && cs.advance(96)
      && t_FutureSplitMerge.skip(cs);
}

bool ShardDescr::validate_skip(vm::CellSlice& cs) const {
  int flags;
  return cs.advance(677)
      && cs.fetch_uint_to(3, flags)
      && flags == 0
      && cs.advance(96)
      && t_FutureSplitMerge.validate_skip(cs);
}

bool ShardDescr::unpack(vm::CellSlice& cs, ShardDescr::Record& data) const {
  return cs.fetch_uint_to(32, data.seq_no)
      && cs.fetch_uint_to(64, data.start_lt)
      && cs.fetch_uint_to(64, data.end_lt)
      && cs.fetch_bits_to(data.root_hash.bits(), 256)
      && cs.fetch_bits_to(data.file_hash.bits(), 256)
      && cs.fetch_bool_to(data.before_split)
      && cs.fetch_bool_to(data.before_merge)
      && cs.fetch_bool_to(data.want_split)
      && cs.fetch_bool_to(data.want_merge)
      && cs.fetch_bool_to(data.nx_cc_updated)
      && cs.fetch_uint_to(3, data.flags)
      && data.flags == 0
      && cs.fetch_uint_to(32, data.next_catchain_seqno)
      && cs.fetch_uint_to(64, data.next_validator_shard)
      && t_FutureSplitMerge.fetch_to(cs, data.split_merge_at);
}

bool ShardDescr::cell_unpack(Ref<vm::Cell> cell_ref, ShardDescr::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardDescr::pack(vm::CellBuilder& cb, const ShardDescr::Record& data) const {
  return cb.store_ulong_rchk_bool(data.seq_no, 32)
      && cb.store_ulong_rchk_bool(data.start_lt, 64)
      && cb.store_ulong_rchk_bool(data.end_lt, 64)
      && cb.store_bits_bool(data.root_hash.cbits(), 256)
      && cb.store_bits_bool(data.file_hash.cbits(), 256)
      && cb.store_ulong_rchk_bool(data.before_split, 1)
      && cb.store_ulong_rchk_bool(data.before_merge, 1)
      && cb.store_ulong_rchk_bool(data.want_split, 1)
      && cb.store_ulong_rchk_bool(data.want_merge, 1)
      && cb.store_ulong_rchk_bool(data.nx_cc_updated, 1)
      && cb.store_ulong_rchk_bool(data.flags, 3)
      && data.flags == 0
      && cb.store_ulong_rchk_bool(data.next_catchain_seqno, 32)
      && cb.store_ulong_rchk_bool(data.next_validator_shard, 64)
      && t_FutureSplitMerge.store_from(cb, data.split_merge_at);
}

bool ShardDescr::cell_pack(Ref<vm::Cell>& cell_ref, const ShardDescr::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardDescr::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int flags;
  return pp.open("shard_descr")
      && pp.fetch_uint_field(cs, 32, "seq_no")
      && pp.fetch_uint_field(cs, 64, "start_lt")
      && pp.fetch_uint_field(cs, 64, "end_lt")
      && pp.fetch_bits_field(cs, 256, "root_hash")
      && pp.fetch_bits_field(cs, 256, "file_hash")
      && pp.fetch_uint_field(cs, 1, "before_split")
      && pp.fetch_uint_field(cs, 1, "before_merge")
      && pp.fetch_uint_field(cs, 1, "want_split")
      && pp.fetch_uint_field(cs, 1, "want_merge")
      && pp.fetch_uint_field(cs, 1, "nx_cc_updated")
      && cs.fetch_uint_to(3, flags)
      && pp.field_int(flags, "flags")
      && flags == 0
      && pp.fetch_uint_field(cs, 32, "next_catchain_seqno")
      && pp.fetch_uint_field(cs, 64, "next_validator_shard")
      && pp.field("split_merge_at")
      && t_FutureSplitMerge.print_skip(pp, cs)
      && pp.close();
}

const ShardDescr t_ShardDescr;

//
// code for type `ShardHashes`
//

bool ShardHashes::skip(vm::CellSlice& cs) const {
  return t_HashmapE_32_Ref_BinTree_ShardDescr.skip(cs);
}

bool ShardHashes::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapE_32_Ref_BinTree_ShardDescr.validate_skip(cs);
}

bool ShardHashes::unpack(vm::CellSlice& cs, ShardHashes::Record& data) const {
  return t_HashmapE_32_Ref_BinTree_ShardDescr.fetch_to(cs, data.x);
}

bool ShardHashes::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapE_32_Ref_BinTree_ShardDescr.fetch_to(cs, x);
}

bool ShardHashes::cell_unpack(Ref<vm::Cell> cell_ref, ShardHashes::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardHashes::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool ShardHashes::pack(vm::CellBuilder& cb, const ShardHashes::Record& data) const {
  return t_HashmapE_32_Ref_BinTree_ShardDescr.store_from(cb, data.x);
}

bool ShardHashes::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapE_32_Ref_BinTree_ShardDescr.store_from(cb, x);
}

bool ShardHashes::cell_pack(Ref<vm::Cell>& cell_ref, const ShardHashes::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardHashes::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ShardHashes::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapE_32_Ref_BinTree_ShardDescr.print_skip(pp, cs)
      && pp.close();
}

const ShardHashes t_ShardHashes;

//
// code for type `BinTreeAug`
//

bool BinTreeAug::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case bta_leaf:
    return cs.advance(1)
        && X.skip(cs)
        && Y.skip(cs);
  case bta_fork:
    return cs.advance_ext(0x20001)
        && Y.skip(cs);
  }
  return false;
}

bool BinTreeAug::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case bta_leaf:
    return cs.advance(1)
        && X.validate_skip(cs)
        && Y.validate_skip(cs);
  case bta_fork:
    return cs.advance(1)
        && validate_skip_ref(cs)
        && validate_skip_ref(cs)
        && Y.validate_skip(cs);
  }
  return false;
}

bool BinTreeAug::unpack(vm::CellSlice& cs, BinTreeAug::Record_bta_leaf& data) const {
  return cs.fetch_ulong(1) == 0
      && X.fetch_to(cs, data.leaf)
      && Y.fetch_to(cs, data.extra);
}

bool BinTreeAug::cell_unpack(Ref<vm::Cell> cell_ref, BinTreeAug::Record_bta_leaf& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BinTreeAug::unpack(vm::CellSlice& cs, BinTreeAug::Record_bta_fork& data) const {
  return cs.fetch_ulong(1) == 1
      && cs.fetch_ref_to(data.left)
      && cs.fetch_ref_to(data.right)
      && Y.fetch_to(cs, data.extra);
}

bool BinTreeAug::cell_unpack(Ref<vm::Cell> cell_ref, BinTreeAug::Record_bta_fork& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BinTreeAug::pack(vm::CellBuilder& cb, const BinTreeAug::Record_bta_leaf& data) const {
  return cb.store_long_bool(0, 1)
      && X.store_from(cb, data.leaf)
      && Y.store_from(cb, data.extra);
}

bool BinTreeAug::cell_pack(Ref<vm::Cell>& cell_ref, const BinTreeAug::Record_bta_leaf& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BinTreeAug::pack(vm::CellBuilder& cb, const BinTreeAug::Record_bta_fork& data) const {
  return cb.store_long_bool(1, 1)
      && cb.store_ref_bool(data.left)
      && cb.store_ref_bool(data.right)
      && Y.store_from(cb, data.extra);
}

bool BinTreeAug::cell_pack(Ref<vm::Cell>& cell_ref, const BinTreeAug::Record_bta_fork& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BinTreeAug::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case bta_leaf:
    return cs.advance(1)
        && pp.open("bta_leaf")
        && pp.field("leaf")
        && X.print_skip(pp, cs)
        && pp.field("extra")
        && Y.print_skip(pp, cs)
        && pp.close();
  case bta_fork:
    return cs.advance(1)
        && pp.open("bta_fork")
        && pp.field("left")
        && print_ref(pp, cs.fetch_ref())
        && pp.field("right")
        && print_ref(pp, cs.fetch_ref())
        && pp.field("extra")
        && Y.print_skip(pp, cs)
        && pp.close();
  }
  return pp.fail("unknown constructor for BinTreeAug");
}


//
// code for type `ShardFees`
//

bool ShardFees::skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection.skip(cs);
}

bool ShardFees::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection.validate_skip(cs);
}

bool ShardFees::unpack(vm::CellSlice& cs, ShardFees::Record& data) const {
  return t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection.fetch_to(cs, data.x);
}

bool ShardFees::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection.fetch_to(cs, x);
}

bool ShardFees::cell_unpack(Ref<vm::Cell> cell_ref, ShardFees::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ShardFees::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool ShardFees::pack(vm::CellBuilder& cb, const ShardFees::Record& data) const {
  return t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection.store_from(cb, data.x);
}

bool ShardFees::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection.store_from(cb, x);
}

bool ShardFees::cell_pack(Ref<vm::Cell>& cell_ref, const ShardFees::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ShardFees::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ShardFees::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection.print_skip(pp, cs)
      && pp.close();
}

const ShardFees t_ShardFees;

//
// code for type `ConfigParams`
//

bool ConfigParams::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(256)
      && t_Hashmap_32_Ref_Cell.validate_skip_ref(cs);
}

bool ConfigParams::unpack(vm::CellSlice& cs, ConfigParams::Record& data) const {
  return cs.fetch_bits_to(data.config_addr.bits(), 256)
      && cs.fetch_ref_to(data.config);
}

bool ConfigParams::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParams::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParams::pack(vm::CellBuilder& cb, const ConfigParams::Record& data) const {
  return cb.store_bits_bool(data.config_addr.cbits(), 256)
      && cb.store_ref_bool(data.config);
}

bool ConfigParams::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParams::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParams::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.fetch_bits_field(cs, 256, "config_addr")
      && pp.field("config")
      && t_Hashmap_32_Ref_Cell.print_ref(pp, cs.fetch_ref())
      && pp.close();
}

const ConfigParams t_ConfigParams;

//
// code for type `ValidatorInfo`
//

bool ValidatorInfo::unpack(vm::CellSlice& cs, ValidatorInfo::Record& data) const {
  return cs.fetch_uint_to(32, data.validator_list_hash_short)
      && cs.fetch_uint_to(32, data.catchain_seqno)
      && cs.fetch_bool_to(data.nx_cc_updated);
}

bool ValidatorInfo::cell_unpack(Ref<vm::Cell> cell_ref, ValidatorInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ValidatorInfo::pack(vm::CellBuilder& cb, const ValidatorInfo::Record& data) const {
  return cb.store_ulong_rchk_bool(data.validator_list_hash_short, 32)
      && cb.store_ulong_rchk_bool(data.catchain_seqno, 32)
      && cb.store_ulong_rchk_bool(data.nx_cc_updated, 1);
}

bool ValidatorInfo::cell_pack(Ref<vm::Cell>& cell_ref, const ValidatorInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ValidatorInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("validator_info")
      && pp.fetch_uint_field(cs, 32, "validator_list_hash_short")
      && pp.fetch_uint_field(cs, 32, "catchain_seqno")
      && pp.fetch_uint_field(cs, 1, "nx_cc_updated")
      && pp.close();
}

const ValidatorInfo t_ValidatorInfo;

//
// code for type `ValidatorBaseInfo`
//

bool ValidatorBaseInfo::unpack(vm::CellSlice& cs, ValidatorBaseInfo::Record& data) const {
  return cs.fetch_uint_to(32, data.validator_list_hash_short)
      && cs.fetch_uint_to(32, data.catchain_seqno);
}

bool ValidatorBaseInfo::cell_unpack(Ref<vm::Cell> cell_ref, ValidatorBaseInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ValidatorBaseInfo::pack(vm::CellBuilder& cb, const ValidatorBaseInfo::Record& data) const {
  return cb.store_ulong_rchk_bool(data.validator_list_hash_short, 32)
      && cb.store_ulong_rchk_bool(data.catchain_seqno, 32);
}

bool ValidatorBaseInfo::cell_pack(Ref<vm::Cell>& cell_ref, const ValidatorBaseInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ValidatorBaseInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("validator_base_info")
      && pp.fetch_uint_field(cs, 32, "validator_list_hash_short")
      && pp.fetch_uint_field(cs, 32, "catchain_seqno")
      && pp.close();
}

const ValidatorBaseInfo t_ValidatorBaseInfo;

//
// code for type `OldMcBlocksInfo`
//

bool OldMcBlocksInfo::skip(vm::CellSlice& cs) const {
  return t_HashmapE_32_ExtBlkRef.skip(cs);
}

bool OldMcBlocksInfo::validate_skip(vm::CellSlice& cs) const {
  return t_HashmapE_32_ExtBlkRef.validate_skip(cs);
}

bool OldMcBlocksInfo::unpack(vm::CellSlice& cs, OldMcBlocksInfo::Record& data) const {
  return t_HashmapE_32_ExtBlkRef.fetch_to(cs, data.x);
}

bool OldMcBlocksInfo::unpack_cons1(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_HashmapE_32_ExtBlkRef.fetch_to(cs, x);
}

bool OldMcBlocksInfo::cell_unpack(Ref<vm::Cell> cell_ref, OldMcBlocksInfo::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool OldMcBlocksInfo::cell_unpack_cons1(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, x) && cs.empty_ext();
}

bool OldMcBlocksInfo::pack(vm::CellBuilder& cb, const OldMcBlocksInfo::Record& data) const {
  return t_HashmapE_32_ExtBlkRef.store_from(cb, data.x);
}

bool OldMcBlocksInfo::pack_cons1(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_HashmapE_32_ExtBlkRef.store_from(cb, x);
}

bool OldMcBlocksInfo::cell_pack(Ref<vm::Cell>& cell_ref, const OldMcBlocksInfo::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool OldMcBlocksInfo::cell_pack_cons1(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool OldMcBlocksInfo::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field()
      && t_HashmapE_32_ExtBlkRef.print_skip(pp, cs)
      && pp.close();
}

const OldMcBlocksInfo t_OldMcBlocksInfo;

//
// code for auxiliary type `McStateExtra_aux`
//

bool McStateExtra_aux::skip(vm::CellSlice& cs) const {
  return cs.advance(65)
      && t_OldMcBlocksInfo.skip(cs)
      && t_Maybe_ExtBlkRef.skip(cs);
}

bool McStateExtra_aux::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(65)
      && t_OldMcBlocksInfo.validate_skip(cs)
      && t_Maybe_ExtBlkRef.validate_skip(cs);
}

bool McStateExtra_aux::unpack(vm::CellSlice& cs, McStateExtra_aux::Record& data) const {
  return cs.fetch_subslice_to(65, data.validator_info)
      && t_OldMcBlocksInfo.fetch_to(cs, data.prev_blocks)
      && t_Maybe_ExtBlkRef.fetch_to(cs, data.last_key_block);
}

bool McStateExtra_aux::cell_unpack(Ref<vm::Cell> cell_ref, McStateExtra_aux::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool McStateExtra_aux::pack(vm::CellBuilder& cb, const McStateExtra_aux::Record& data) const {
  return cb.append_cellslice_chk(data.validator_info, 65)
      && t_OldMcBlocksInfo.store_from(cb, data.prev_blocks)
      && t_Maybe_ExtBlkRef.store_from(cb, data.last_key_block);
}

bool McStateExtra_aux::cell_pack(Ref<vm::Cell>& cell_ref, const McStateExtra_aux::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool McStateExtra_aux::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open()
      && pp.field("validator_info")
      && t_ValidatorInfo.print_skip(pp, cs)
      && pp.field("prev_blocks")
      && t_OldMcBlocksInfo.print_skip(pp, cs)
      && pp.field("last_key_block")
      && t_Maybe_ExtBlkRef.print_skip(pp, cs)
      && pp.close();
}

const McStateExtra_aux t_McStateExtra_aux;

//
// code for type `McStateExtra`
//
constexpr unsigned short McStateExtra::cons_tag[1];

bool McStateExtra::skip(vm::CellSlice& cs) const {
  return cs.advance(16)
      && t_ShardHashes.skip(cs)
      && t_ShardFees.skip(cs)
      && cs.advance_ext(0x20100);
}

bool McStateExtra::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(16) == 0xcc1f
      && t_ShardHashes.validate_skip(cs)
      && t_ShardFees.validate_skip(cs)
      && t_ConfigParams.validate_skip(cs)
      && t_McStateExtra_aux.validate_skip_ref(cs);
}

bool McStateExtra::unpack(vm::CellSlice& cs, McStateExtra::Record& data) const {
  return cs.fetch_ulong(16) == 0xcc1f
      && t_ShardHashes.fetch_to(cs, data.shard_hashes)
      && t_ShardFees.fetch_to(cs, data.shard_fees)
      && cs.fetch_subslice_ext_to(0x10100, data.config)
      && t_McStateExtra_aux.cell_unpack(cs.fetch_ref(), data.r1);
}

bool McStateExtra::cell_unpack(Ref<vm::Cell> cell_ref, McStateExtra::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool McStateExtra::pack(vm::CellBuilder& cb, const McStateExtra::Record& data) const {
  Ref<vm::Cell> tmp_cell;
  return cb.store_long_bool(0xcc1f, 16)
      && t_ShardHashes.store_from(cb, data.shard_hashes)
      && t_ShardFees.store_from(cb, data.shard_fees)
      && cb.append_cellslice_chk(data.config, 0x10100)
      && t_McStateExtra_aux.cell_pack(tmp_cell, data.r1)
      && cb.store_ref_bool(std::move(tmp_cell));
}

bool McStateExtra::cell_pack(Ref<vm::Cell>& cell_ref, const McStateExtra::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool McStateExtra::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(16) == 0xcc1f
      && pp.open("masterchain_state_extra")
      && pp.field("shard_hashes")
      && t_ShardHashes.print_skip(pp, cs)
      && pp.field("shard_fees")
      && t_ShardFees.print_skip(pp, cs)
      && pp.field("config")
      && t_ConfigParams.print_skip(pp, cs)
      && pp.field()
      && t_McStateExtra_aux.print_ref(pp, cs.fetch_ref())
      && pp.close();
}

const McStateExtra t_McStateExtra;

//
// code for type `CryptoSignature`
//
constexpr unsigned char CryptoSignature::cons_tag[1];

bool CryptoSignature::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 5
      && cs.advance(512);
}

bool CryptoSignature::unpack(vm::CellSlice& cs, CryptoSignature::Record& data) const {
  return cs.fetch_ulong(4) == 5
      && cs.fetch_bits_to(data.R.bits(), 256)
      && cs.fetch_bits_to(data.s.bits(), 256);
}

bool CryptoSignature::cell_unpack(Ref<vm::Cell> cell_ref, CryptoSignature::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool CryptoSignature::pack(vm::CellBuilder& cb, const CryptoSignature::Record& data) const {
  return cb.store_long_bool(5, 4)
      && cb.store_bits_bool(data.R.cbits(), 256)
      && cb.store_bits_bool(data.s.cbits(), 256);
}

bool CryptoSignature::cell_pack(Ref<vm::Cell>& cell_ref, const CryptoSignature::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool CryptoSignature::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(4) == 5
      && pp.open("ed25519_signature")
      && pp.fetch_bits_field(cs, 256, "R")
      && pp.fetch_bits_field(cs, 256, "s")
      && pp.close();
}

const CryptoSignature t_CryptoSignature;

//
// code for type `CryptoSignaturePair`
//

bool CryptoSignaturePair::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(256)
      && t_CryptoSignature.validate_skip(cs);
}

bool CryptoSignaturePair::unpack(vm::CellSlice& cs, CryptoSignaturePair::Record& data) const {
  return cs.fetch_bits_to(data.node_id_short.bits(), 256)
      && cs.fetch_subslice_to(516, data.sign);
}

bool CryptoSignaturePair::cell_unpack(Ref<vm::Cell> cell_ref, CryptoSignaturePair::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool CryptoSignaturePair::pack(vm::CellBuilder& cb, const CryptoSignaturePair::Record& data) const {
  return cb.store_bits_bool(data.node_id_short.cbits(), 256)
      && cb.append_cellslice_chk(data.sign, 516);
}

bool CryptoSignaturePair::cell_pack(Ref<vm::Cell>& cell_ref, const CryptoSignaturePair::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool CryptoSignaturePair::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("sig_pair")
      && pp.fetch_bits_field(cs, 256, "node_id_short")
      && pp.field("sign")
      && t_CryptoSignature.print_skip(pp, cs)
      && pp.close();
}

const CryptoSignaturePair t_CryptoSignaturePair;

//
// code for type `McBlockExtra`
//
constexpr unsigned short McBlockExtra::cons_tag[1];

bool McBlockExtra::skip(vm::CellSlice& cs) const {
  return cs.advance(17)
      && t_ShardHashes.skip(cs)
      && t_HashmapE_16_CryptoSignaturePair.skip(cs);
}

bool McBlockExtra::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(16) == 0xcc9f
      && cs.advance(1)
      && t_ShardHashes.validate_skip(cs)
      && t_HashmapE_16_CryptoSignaturePair.validate_skip(cs);
}

bool McBlockExtra::unpack(vm::CellSlice& cs, McBlockExtra::Record& data) const {
  return cs.fetch_ulong(16) == 0xcc9f
      && cs.fetch_bool_to(data.is_key_block)
      && t_ShardHashes.fetch_to(cs, data.shard_hashes)
      && t_HashmapE_16_CryptoSignaturePair.fetch_to(cs, data.prev_blk_signatures);
}

bool McBlockExtra::cell_unpack(Ref<vm::Cell> cell_ref, McBlockExtra::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool McBlockExtra::pack(vm::CellBuilder& cb, const McBlockExtra::Record& data) const {
  return cb.store_long_bool(0xcc9f, 16)
      && cb.store_ulong_rchk_bool(data.is_key_block, 1)
      && t_ShardHashes.store_from(cb, data.shard_hashes)
      && t_HashmapE_16_CryptoSignaturePair.store_from(cb, data.prev_blk_signatures);
}

bool McBlockExtra::cell_pack(Ref<vm::Cell>& cell_ref, const McBlockExtra::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool McBlockExtra::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(16) == 0xcc9f
      && pp.open("masterchain_block_extra")
      && pp.fetch_uint_field(cs, 1, "is_key_block")
      && pp.field("shard_hashes")
      && t_ShardHashes.print_skip(pp, cs)
      && pp.field("prev_blk_signatures")
      && t_HashmapE_16_CryptoSignaturePair.print_skip(pp, cs)
      && pp.close();
}

const McBlockExtra t_McBlockExtra;

//
// code for type `SigPubKey`
//
constexpr unsigned SigPubKey::cons_tag[1];

bool SigPubKey::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0x8e81278aU
      && cs.advance(256);
}

bool SigPubKey::unpack(vm::CellSlice& cs, SigPubKey::Record& data) const {
  return cs.fetch_ulong(32) == 0x8e81278aU
      && cs.fetch_bits_to(data.pubkey.bits(), 256);
}

bool SigPubKey::unpack_ed25519_pubkey(vm::CellSlice& cs, td::BitArray<256>& pubkey) const {
  return cs.fetch_ulong(32) == 0x8e81278aU
      && cs.fetch_bits_to(pubkey.bits(), 256);
}

bool SigPubKey::cell_unpack(Ref<vm::Cell> cell_ref, SigPubKey::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool SigPubKey::cell_unpack_ed25519_pubkey(Ref<vm::Cell> cell_ref, td::BitArray<256>& pubkey) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_ed25519_pubkey(cs, pubkey) && cs.empty_ext();
}

bool SigPubKey::pack(vm::CellBuilder& cb, const SigPubKey::Record& data) const {
  return cb.store_long_bool(0x8e81278aU, 32)
      && cb.store_bits_bool(data.pubkey.cbits(), 256);
}

bool SigPubKey::pack_ed25519_pubkey(vm::CellBuilder& cb, const td::BitArray<256>& pubkey) const {
  return cb.store_long_bool(0x8e81278aU, 32)
      && cb.store_bits_bool(pubkey.cbits(), 256);
}

bool SigPubKey::cell_pack(Ref<vm::Cell>& cell_ref, const SigPubKey::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool SigPubKey::cell_pack_ed25519_pubkey(Ref<vm::Cell>& cell_ref, const td::BitArray<256>& pubkey) const {
  vm::CellBuilder cb;
  return pack_ed25519_pubkey(cb, pubkey) && std::move(cb).finalize_to(cell_ref);
}

bool SigPubKey::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(32) == 0x8e81278aU
      && pp.open("ed25519_pubkey")
      && pp.fetch_bits_field(cs, 256, "pubkey")
      && pp.close();
}

const SigPubKey t_SigPubKey;

//
// code for type `ValidatorDescr`
//
constexpr unsigned char ValidatorDescr::cons_tag[1];

bool ValidatorDescr::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0x53
      && t_SigPubKey.validate_skip(cs)
      && cs.advance(64);
}

bool ValidatorDescr::unpack(vm::CellSlice& cs, ValidatorDescr::Record& data) const {
  return cs.fetch_ulong(8) == 0x53
      && cs.fetch_subslice_to(288, data.public_key)
      && cs.fetch_uint_to(64, data.weight);
}

bool ValidatorDescr::cell_unpack(Ref<vm::Cell> cell_ref, ValidatorDescr::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ValidatorDescr::pack(vm::CellBuilder& cb, const ValidatorDescr::Record& data) const {
  return cb.store_long_bool(0x53, 8)
      && cb.append_cellslice_chk(data.public_key, 288)
      && cb.store_ulong_rchk_bool(data.weight, 64);
}

bool ValidatorDescr::cell_pack(Ref<vm::Cell>& cell_ref, const ValidatorDescr::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ValidatorDescr::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0x53
      && pp.open("validator")
      && pp.field("public_key")
      && t_SigPubKey.print_skip(pp, cs)
      && pp.fetch_uint_field(cs, 64, "weight")
      && pp.close();
}

const ValidatorDescr t_ValidatorDescr;

//
// code for type `ValidatorSet`
//
constexpr unsigned char ValidatorSet::cons_tag[1];

bool ValidatorSet::skip(vm::CellSlice& cs) const {
  int total, main;
  return cs.advance(72)
      && cs.fetch_uint_to(16, total)
      && cs.fetch_uint_to(16, main)
      && main <= total
      && 1 <= main
      && t_Hashmap_16_ValidatorDescr.skip(cs);
}

bool ValidatorSet::validate_skip(vm::CellSlice& cs) const {
  int total, main;
  return cs.fetch_ulong(8) == 17
      && cs.advance(64)
      && cs.fetch_uint_to(16, total)
      && cs.fetch_uint_to(16, main)
      && main <= total
      && 1 <= main
      && t_Hashmap_16_ValidatorDescr.validate_skip(cs);
}

bool ValidatorSet::unpack(vm::CellSlice& cs, ValidatorSet::Record& data) const {
  return cs.fetch_ulong(8) == 17
      && cs.fetch_uint_to(32, data.utime_since)
      && cs.fetch_uint_to(32, data.utime_until)
      && cs.fetch_uint_to(16, data.total)
      && cs.fetch_uint_to(16, data.main)
      && data.main <= data.total
      && 1 <= data.main
      && t_Hashmap_16_ValidatorDescr.fetch_to(cs, data.list);
}

bool ValidatorSet::cell_unpack(Ref<vm::Cell> cell_ref, ValidatorSet::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ValidatorSet::pack(vm::CellBuilder& cb, const ValidatorSet::Record& data) const {
  return cb.store_long_bool(17, 8)
      && cb.store_ulong_rchk_bool(data.utime_since, 32)
      && cb.store_ulong_rchk_bool(data.utime_until, 32)
      && cb.store_ulong_rchk_bool(data.total, 16)
      && cb.store_ulong_rchk_bool(data.main, 16)
      && data.main <= data.total
      && 1 <= data.main
      && t_Hashmap_16_ValidatorDescr.store_from(cb, data.list);
}

bool ValidatorSet::cell_pack(Ref<vm::Cell>& cell_ref, const ValidatorSet::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ValidatorSet::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int total, main;
  return cs.fetch_ulong(8) == 17
      && pp.open("validators")
      && pp.fetch_uint_field(cs, 32, "utime_since")
      && pp.fetch_uint_field(cs, 32, "utime_until")
      && cs.fetch_uint_to(16, total)
      && pp.field_int(total, "total")
      && cs.fetch_uint_to(16, main)
      && pp.field_int(main, "main")
      && main <= total
      && 1 <= main
      && pp.field("list")
      && t_Hashmap_16_ValidatorDescr.print_skip(pp, cs)
      && pp.close();
}

const ValidatorSet t_ValidatorSet;

//
// code for type `WorkchainFormat`
//

bool WorkchainFormat::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case wfmt_basic:
    return cs.advance(100)
        && m == 1;
  case wfmt_ext: {
    int min_addr_len, max_addr_len, addr_len_step, workchain_type_id;
    return cs.advance(4)
        && cs.fetch_uint_to(12, min_addr_len)
        && cs.fetch_uint_to(12, max_addr_len)
        && cs.fetch_uint_to(12, addr_len_step)
        && 64 <= min_addr_len
        && min_addr_len <= max_addr_len
        && max_addr_len <= 1023
        && addr_len_step <= 1023
        && cs.fetch_uint_to(32, workchain_type_id)
        && 1 <= workchain_type_id
        && m == 0;
    }
  }
  return false;
}

bool WorkchainFormat::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case wfmt_basic:
    return cs.fetch_ulong(4) == 1
        && cs.advance(96)
        && m == 1;
  case wfmt_ext: {
    int min_addr_len, max_addr_len, addr_len_step, workchain_type_id;
    return cs.advance(4)
        && cs.fetch_uint_to(12, min_addr_len)
        && cs.fetch_uint_to(12, max_addr_len)
        && cs.fetch_uint_to(12, addr_len_step)
        && 64 <= min_addr_len
        && min_addr_len <= max_addr_len
        && max_addr_len <= 1023
        && addr_len_step <= 1023
        && cs.fetch_uint_to(32, workchain_type_id)
        && 1 <= workchain_type_id
        && m == 0;
    }
  }
  return false;
}

bool WorkchainFormat::unpack(vm::CellSlice& cs, WorkchainFormat::Record_wfmt_basic& data) const {
  return cs.fetch_ulong(4) == 1
      && cs.fetch_int_to(32, data.vm_version)
      && cs.fetch_uint_to(64, data.vm_mode)
      && m == 1;
}

bool WorkchainFormat::cell_unpack(Ref<vm::Cell> cell_ref, WorkchainFormat::Record_wfmt_basic& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool WorkchainFormat::unpack(vm::CellSlice& cs, WorkchainFormat::Record_wfmt_ext& data) const {
  return cs.fetch_ulong(4) == 0
      && cs.fetch_uint_to(12, data.min_addr_len)
      && cs.fetch_uint_to(12, data.max_addr_len)
      && cs.fetch_uint_to(12, data.addr_len_step)
      && 64 <= data.min_addr_len
      && data.min_addr_len <= data.max_addr_len
      && data.max_addr_len <= 1023
      && data.addr_len_step <= 1023
      && cs.fetch_uint_to(32, data.workchain_type_id)
      && 1 <= data.workchain_type_id
      && m == 0;
}

bool WorkchainFormat::cell_unpack(Ref<vm::Cell> cell_ref, WorkchainFormat::Record_wfmt_ext& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool WorkchainFormat::pack(vm::CellBuilder& cb, const WorkchainFormat::Record_wfmt_basic& data) const {
  return cb.store_long_bool(1, 4)
      && cb.store_long_rchk_bool(data.vm_version, 32)
      && cb.store_ulong_rchk_bool(data.vm_mode, 64)
      && m == 1;
}

bool WorkchainFormat::cell_pack(Ref<vm::Cell>& cell_ref, const WorkchainFormat::Record_wfmt_basic& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool WorkchainFormat::pack(vm::CellBuilder& cb, const WorkchainFormat::Record_wfmt_ext& data) const {
  return cb.store_long_bool(0, 4)
      && cb.store_ulong_rchk_bool(data.min_addr_len, 12)
      && cb.store_ulong_rchk_bool(data.max_addr_len, 12)
      && cb.store_ulong_rchk_bool(data.addr_len_step, 12)
      && 64 <= data.min_addr_len
      && data.min_addr_len <= data.max_addr_len
      && data.max_addr_len <= 1023
      && data.addr_len_step <= 1023
      && cb.store_ulong_rchk_bool(data.workchain_type_id, 32)
      && 1 <= data.workchain_type_id
      && m == 0;
}

bool WorkchainFormat::cell_pack(Ref<vm::Cell>& cell_ref, const WorkchainFormat::Record_wfmt_ext& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool WorkchainFormat::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case wfmt_basic:
    return cs.fetch_ulong(4) == 1
        && pp.open("wfmt_basic")
        && pp.fetch_int_field(cs, 32, "vm_version")
        && pp.fetch_uint_field(cs, 64, "vm_mode")
        && m == 1
        && pp.close();
  case wfmt_ext: {
    int min_addr_len, max_addr_len, addr_len_step, workchain_type_id;
    return cs.advance(4)
        && pp.open("wfmt_ext")
        && cs.fetch_uint_to(12, min_addr_len)
        && pp.field_int(min_addr_len, "min_addr_len")
        && cs.fetch_uint_to(12, max_addr_len)
        && pp.field_int(max_addr_len, "max_addr_len")
        && cs.fetch_uint_to(12, addr_len_step)
        && pp.field_int(addr_len_step, "addr_len_step")
        && 64 <= min_addr_len
        && min_addr_len <= max_addr_len
        && max_addr_len <= 1023
        && addr_len_step <= 1023
        && cs.fetch_uint_to(32, workchain_type_id)
        && pp.field_int(workchain_type_id, "workchain_type_id")
        && 1 <= workchain_type_id
        && m == 0
        && pp.close();
    }
  }
  return pp.fail("unknown constructor for WorkchainFormat");
}


//
// code for type `WorkchainDescr`
//
constexpr unsigned char WorkchainDescr::cons_tag[1];

bool WorkchainDescr::skip(vm::CellSlice& cs) const {
  int min_split, max_split, basic, flags;
  return cs.advance(40)
      && cs.fetch_uint_to(8, min_split)
      && cs.fetch_uint_to(8, max_split)
      && min_split <= max_split
      && max_split <= 60
      && cs.fetch_bool_to(basic)
      && cs.advance(2)
      && cs.fetch_uint_to(13, flags)
      && flags == 0
      && cs.advance(544)
      && WorkchainFormat{basic}.skip(cs);
}

bool WorkchainDescr::validate_skip(vm::CellSlice& cs) const {
  int min_split, max_split, basic, flags;
  return cs.fetch_ulong(8) == 0xa5
      && cs.advance(32)
      && cs.fetch_uint_to(8, min_split)
      && cs.fetch_uint_to(8, max_split)
      && min_split <= max_split
      && max_split <= 60
      && cs.fetch_bool_to(basic)
      && cs.advance(2)
      && cs.fetch_uint_to(13, flags)
      && flags == 0
      && cs.advance(544)
      && WorkchainFormat{basic}.validate_skip(cs);
}

bool WorkchainDescr::unpack(vm::CellSlice& cs, WorkchainDescr::Record& data) const {
  return cs.fetch_ulong(8) == 0xa5
      && cs.fetch_uint_to(32, data.enabled_since)
      && cs.fetch_uint_to(8, data.min_split)
      && cs.fetch_uint_to(8, data.max_split)
      && data.min_split <= data.max_split
      && data.max_split <= 60
      && cs.fetch_bool_to(data.basic)
      && cs.fetch_bool_to(data.active)
      && cs.fetch_bool_to(data.accept_msgs)
      && cs.fetch_uint_to(13, data.flags)
      && data.flags == 0
      && cs.fetch_bits_to(data.zerostate_root_hash.bits(), 256)
      && cs.fetch_bits_to(data.zerostate_file_hash.bits(), 256)
      && cs.fetch_uint_to(32, data.version)
      && WorkchainFormat{data.basic}.fetch_to(cs, data.format);
}

bool WorkchainDescr::cell_unpack(Ref<vm::Cell> cell_ref, WorkchainDescr::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool WorkchainDescr::pack(vm::CellBuilder& cb, const WorkchainDescr::Record& data) const {
  return cb.store_long_bool(0xa5, 8)
      && cb.store_ulong_rchk_bool(data.enabled_since, 32)
      && cb.store_ulong_rchk_bool(data.min_split, 8)
      && cb.store_ulong_rchk_bool(data.max_split, 8)
      && data.min_split <= data.max_split
      && data.max_split <= 60
      && cb.store_ulong_rchk_bool(data.basic, 1)
      && cb.store_ulong_rchk_bool(data.active, 1)
      && cb.store_ulong_rchk_bool(data.accept_msgs, 1)
      && cb.store_ulong_rchk_bool(data.flags, 13)
      && data.flags == 0
      && cb.store_bits_bool(data.zerostate_root_hash.cbits(), 256)
      && cb.store_bits_bool(data.zerostate_file_hash.cbits(), 256)
      && cb.store_ulong_rchk_bool(data.version, 32)
      && WorkchainFormat{data.basic}.store_from(cb, data.format);
}

bool WorkchainDescr::cell_pack(Ref<vm::Cell>& cell_ref, const WorkchainDescr::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool WorkchainDescr::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  int min_split, max_split, basic, flags;
  return cs.fetch_ulong(8) == 0xa5
      && pp.open("workchain")
      && pp.fetch_uint_field(cs, 32, "enabled_since")
      && cs.fetch_uint_to(8, min_split)
      && pp.field_int(min_split, "min_split")
      && cs.fetch_uint_to(8, max_split)
      && pp.field_int(max_split, "max_split")
      && min_split <= max_split
      && max_split <= 60
      && cs.fetch_bool_to(basic)
      && pp.field_int(basic, "basic")
      && pp.fetch_uint_field(cs, 1, "active")
      && pp.fetch_uint_field(cs, 1, "accept_msgs")
      && cs.fetch_uint_to(13, flags)
      && pp.field_int(flags, "flags")
      && flags == 0
      && pp.fetch_bits_field(cs, 256, "zerostate_root_hash")
      && pp.fetch_bits_field(cs, 256, "zerostate_file_hash")
      && pp.fetch_uint_field(cs, 32, "version")
      && pp.field("format")
      && WorkchainFormat{basic}.print_skip(pp, cs)
      && pp.close();
}

const WorkchainDescr t_WorkchainDescr;

//
// code for type `StoragePrices`
//
constexpr unsigned char StoragePrices::cons_tag[1];

bool StoragePrices::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xcc
      && cs.advance(288);
}

bool StoragePrices::unpack(vm::CellSlice& cs, StoragePrices::Record& data) const {
  return cs.fetch_ulong(8) == 0xcc
      && cs.fetch_uint_to(32, data.utime_since)
      && cs.fetch_uint_to(64, data.bit_price_ps)
      && cs.fetch_uint_to(64, data.cell_price_ps)
      && cs.fetch_uint_to(64, data.mc_bit_price_ps)
      && cs.fetch_uint_to(64, data.mc_cell_price_ps);
}

bool StoragePrices::cell_unpack(Ref<vm::Cell> cell_ref, StoragePrices::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool StoragePrices::pack(vm::CellBuilder& cb, const StoragePrices::Record& data) const {
  return cb.store_long_bool(0xcc, 8)
      && cb.store_ulong_rchk_bool(data.utime_since, 32)
      && cb.store_ulong_rchk_bool(data.bit_price_ps, 64)
      && cb.store_ulong_rchk_bool(data.cell_price_ps, 64)
      && cb.store_ulong_rchk_bool(data.mc_bit_price_ps, 64)
      && cb.store_ulong_rchk_bool(data.mc_cell_price_ps, 64);
}

bool StoragePrices::cell_pack(Ref<vm::Cell>& cell_ref, const StoragePrices::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool StoragePrices::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xcc
      && pp.open()
      && pp.fetch_uint_field(cs, 32, "utime_since")
      && pp.fetch_uint_field(cs, 64, "bit_price_ps")
      && pp.fetch_uint_field(cs, 64, "cell_price_ps")
      && pp.fetch_uint_field(cs, 64, "mc_bit_price_ps")
      && pp.fetch_uint_field(cs, 64, "mc_cell_price_ps")
      && pp.close();
}

const StoragePrices t_StoragePrices;

//
// code for type `GasLimitsPrices`
//
constexpr unsigned char GasLimitsPrices::cons_tag[1];

bool GasLimitsPrices::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xdd
      && cs.advance(384);
}

bool GasLimitsPrices::unpack(vm::CellSlice& cs, GasLimitsPrices::Record& data) const {
  return cs.fetch_ulong(8) == 0xdd
      && cs.fetch_uint_to(64, data.gas_price)
      && cs.fetch_uint_to(64, data.gas_limit)
      && cs.fetch_uint_to(64, data.gas_credit)
      && cs.fetch_uint_to(64, data.block_gas_limit)
      && cs.fetch_uint_to(64, data.freeze_due_limit)
      && cs.fetch_uint_to(64, data.delete_due_limit);
}

bool GasLimitsPrices::cell_unpack(Ref<vm::Cell> cell_ref, GasLimitsPrices::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool GasLimitsPrices::pack(vm::CellBuilder& cb, const GasLimitsPrices::Record& data) const {
  return cb.store_long_bool(0xdd, 8)
      && cb.store_ulong_rchk_bool(data.gas_price, 64)
      && cb.store_ulong_rchk_bool(data.gas_limit, 64)
      && cb.store_ulong_rchk_bool(data.gas_credit, 64)
      && cb.store_ulong_rchk_bool(data.block_gas_limit, 64)
      && cb.store_ulong_rchk_bool(data.freeze_due_limit, 64)
      && cb.store_ulong_rchk_bool(data.delete_due_limit, 64);
}

bool GasLimitsPrices::cell_pack(Ref<vm::Cell>& cell_ref, const GasLimitsPrices::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool GasLimitsPrices::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xdd
      && pp.open("gas_prices")
      && pp.fetch_uint_field(cs, 64, "gas_price")
      && pp.fetch_uint_field(cs, 64, "gas_limit")
      && pp.fetch_uint_field(cs, 64, "gas_credit")
      && pp.fetch_uint_field(cs, 64, "block_gas_limit")
      && pp.fetch_uint_field(cs, 64, "freeze_due_limit")
      && pp.fetch_uint_field(cs, 64, "delete_due_limit")
      && pp.close();
}

const GasLimitsPrices t_GasLimitsPrices;

//
// code for type `MsgForwardPrices`
//
constexpr unsigned char MsgForwardPrices::cons_tag[1];

bool MsgForwardPrices::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xea
      && cs.advance(256);
}

bool MsgForwardPrices::unpack(vm::CellSlice& cs, MsgForwardPrices::Record& data) const {
  return cs.fetch_ulong(8) == 0xea
      && cs.fetch_uint_to(64, data.lump_price)
      && cs.fetch_uint_to(64, data.bit_price)
      && cs.fetch_uint_to(64, data.cell_price)
      && cs.fetch_uint_to(32, data.ihr_price_factor)
      && cs.fetch_uint_to(16, data.first_frac)
      && cs.fetch_uint_to(16, data.next_frac);
}

bool MsgForwardPrices::cell_unpack(Ref<vm::Cell> cell_ref, MsgForwardPrices::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool MsgForwardPrices::pack(vm::CellBuilder& cb, const MsgForwardPrices::Record& data) const {
  return cb.store_long_bool(0xea, 8)
      && cb.store_ulong_rchk_bool(data.lump_price, 64)
      && cb.store_ulong_rchk_bool(data.bit_price, 64)
      && cb.store_ulong_rchk_bool(data.cell_price, 64)
      && cb.store_ulong_rchk_bool(data.ihr_price_factor, 32)
      && cb.store_ulong_rchk_bool(data.first_frac, 16)
      && cb.store_ulong_rchk_bool(data.next_frac, 16);
}

bool MsgForwardPrices::cell_pack(Ref<vm::Cell>& cell_ref, const MsgForwardPrices::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool MsgForwardPrices::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xea
      && pp.open("msg_forward_prices")
      && pp.fetch_uint_field(cs, 64, "lump_price")
      && pp.fetch_uint_field(cs, 64, "bit_price")
      && pp.fetch_uint_field(cs, 64, "cell_price")
      && pp.fetch_uint_field(cs, 32, "ihr_price_factor")
      && pp.fetch_uint_field(cs, 16, "first_frac")
      && pp.fetch_uint_field(cs, 16, "next_frac")
      && pp.close();
}

const MsgForwardPrices t_MsgForwardPrices;

//
// code for type `CatchainConfig`
//
constexpr unsigned char CatchainConfig::cons_tag[1];

bool CatchainConfig::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xc1
      && cs.advance(128);
}

bool CatchainConfig::unpack(vm::CellSlice& cs, CatchainConfig::Record& data) const {
  return cs.fetch_ulong(8) == 0xc1
      && cs.fetch_uint_to(32, data.mc_catchain_lifetime)
      && cs.fetch_uint_to(32, data.shard_catchain_lifetime)
      && cs.fetch_uint_to(32, data.shard_validators_lifetime)
      && cs.fetch_uint_to(32, data.shard_validators_num);
}

bool CatchainConfig::cell_unpack(Ref<vm::Cell> cell_ref, CatchainConfig::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool CatchainConfig::pack(vm::CellBuilder& cb, const CatchainConfig::Record& data) const {
  return cb.store_long_bool(0xc1, 8)
      && cb.store_ulong_rchk_bool(data.mc_catchain_lifetime, 32)
      && cb.store_ulong_rchk_bool(data.shard_catchain_lifetime, 32)
      && cb.store_ulong_rchk_bool(data.shard_validators_lifetime, 32)
      && cb.store_ulong_rchk_bool(data.shard_validators_num, 32);
}

bool CatchainConfig::cell_pack(Ref<vm::Cell>& cell_ref, const CatchainConfig::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool CatchainConfig::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xc1
      && pp.open("catchain_config")
      && pp.fetch_uint_field(cs, 32, "mc_catchain_lifetime")
      && pp.fetch_uint_field(cs, 32, "shard_catchain_lifetime")
      && pp.fetch_uint_field(cs, 32, "shard_validators_lifetime")
      && pp.fetch_uint_field(cs, 32, "shard_validators_num")
      && pp.close();
}

const CatchainConfig t_CatchainConfig;

//
// code for type `ConfigParam`
//

int ConfigParam::get_tag(const vm::CellSlice& cs) const {
  switch (m) {
  case 0:
    return cons0;
  case 1:
    return cons1;
  case 12:
    return cons12;
  case 16:
    return cons16;
  case 17:
    return cons17;
  case 18:
    return cons18;
  case 20:
    return config_mc_gas_prices;
  case 21:
    return config_gas_prices;
  case 24:
    return config_mc_fwd_prices;
  case 25:
    return config_fwd_prices;
  case 28:
    return cons28;
  case 31:
    return cons31;
  case 32:
    return cons32;
  case 34:
    return cons34;
  case 36:
    return cons36;
  default:
    return -1;
  }
}

bool ConfigParam::skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cons0:
    return cs.advance(256)
        && m == 0;
  case cons1:
    return cs.advance(256)
        && m == 1;
  case cons12:
    return t_HashmapE_32_WorkchainDescr.skip(cs)
        && m == 12;
  case cons16: {
    int max_validators, max_main_validators, min_validators;
    return cs.fetch_uint_to(16, max_validators)
        && cs.fetch_uint_to(16, max_main_validators)
        && cs.fetch_uint_to(16, min_validators)
        && max_main_validators <= max_validators
        && min_validators <= max_main_validators
        && 1 <= min_validators
        && m == 16;
    }
  case cons17:
    return t_Grams.skip(cs)
        && t_Grams.skip(cs)
        && cs.advance(32)
        && m == 17;
  case cons18:
    return t_Hashmap_32_StoragePrices.skip(cs)
        && m == 18;
  case config_mc_gas_prices:
    return cs.advance(392)
        && m == 20;
  case config_gas_prices:
    return cs.advance(392)
        && m == 21;
  case config_mc_fwd_prices:
    return cs.advance(264)
        && m == 24;
  case config_fwd_prices:
    return cs.advance(264)
        && m == 25;
  case cons28:
    return cs.advance(136)
        && m == 28;
  case cons31:
    return t_HashmapE_256_True.skip(cs)
        && m == 31;
  case cons32:
    return t_ValidatorSet.skip(cs)
        && m == 32;
  case cons34:
    return t_ValidatorSet.skip(cs)
        && m == 34;
  case cons36:
    return t_ValidatorSet.skip(cs)
        && m == 36;
  }
  return false;
}

bool ConfigParam::validate_skip(vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cons0:
    return cs.advance(256)
        && m == 0;
  case cons1:
    return cs.advance(256)
        && m == 1;
  case cons12:
    return t_HashmapE_32_WorkchainDescr.validate_skip(cs)
        && m == 12;
  case cons16: {
    int max_validators, max_main_validators, min_validators;
    return cs.fetch_uint_to(16, max_validators)
        && cs.fetch_uint_to(16, max_main_validators)
        && cs.fetch_uint_to(16, min_validators)
        && max_main_validators <= max_validators
        && min_validators <= max_main_validators
        && 1 <= min_validators
        && m == 16;
    }
  case cons17:
    return t_Grams.validate_skip(cs)
        && t_Grams.validate_skip(cs)
        && cs.advance(32)
        && m == 17;
  case cons18:
    return t_Hashmap_32_StoragePrices.validate_skip(cs)
        && m == 18;
  case config_mc_gas_prices:
    return t_GasLimitsPrices.validate_skip(cs)
        && m == 20;
  case config_gas_prices:
    return t_GasLimitsPrices.validate_skip(cs)
        && m == 21;
  case config_mc_fwd_prices:
    return t_MsgForwardPrices.validate_skip(cs)
        && m == 24;
  case config_fwd_prices:
    return t_MsgForwardPrices.validate_skip(cs)
        && m == 25;
  case cons28:
    return t_CatchainConfig.validate_skip(cs)
        && m == 28;
  case cons31:
    return t_HashmapE_256_True.validate_skip(cs)
        && m == 31;
  case cons32:
    return t_ValidatorSet.validate_skip(cs)
        && m == 32;
  case cons34:
    return t_ValidatorSet.validate_skip(cs)
        && m == 34;
  case cons36:
    return t_ValidatorSet.validate_skip(cs)
        && m == 36;
  }
  return false;
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons0& data) const {
  return cs.fetch_bits_to(data.config_addr.bits(), 256)
      && m == 0;
}

bool ConfigParam::unpack_cons0(vm::CellSlice& cs, td::BitArray<256>& config_addr) const {
  return cs.fetch_bits_to(config_addr.bits(), 256)
      && m == 0;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons0& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_cons0(Ref<vm::Cell> cell_ref, td::BitArray<256>& config_addr) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons0(cs, config_addr) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons1& data) const {
  return cs.fetch_bits_to(data.elector_addr.bits(), 256)
      && m == 1;
}

bool ConfigParam::unpack_cons1(vm::CellSlice& cs, td::BitArray<256>& elector_addr) const {
  return cs.fetch_bits_to(elector_addr.bits(), 256)
      && m == 1;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons1& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_cons1(Ref<vm::Cell> cell_ref, td::BitArray<256>& elector_addr) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons1(cs, elector_addr) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons12& data) const {
  return t_HashmapE_32_WorkchainDescr.fetch_to(cs, data.workchains)
      && m == 12;
}

bool ConfigParam::unpack_cons12(vm::CellSlice& cs, Ref<CellSlice>& workchains) const {
  return t_HashmapE_32_WorkchainDescr.fetch_to(cs, workchains)
      && m == 12;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons12& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_cons12(Ref<vm::Cell> cell_ref, Ref<CellSlice>& workchains) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons12(cs, workchains) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons16& data) const {
  return cs.fetch_uint_to(16, data.max_validators)
      && cs.fetch_uint_to(16, data.max_main_validators)
      && cs.fetch_uint_to(16, data.min_validators)
      && data.max_main_validators <= data.max_validators
      && data.min_validators <= data.max_main_validators
      && 1 <= data.min_validators
      && m == 16;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons16& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons17& data) const {
  return t_Grams.fetch_to(cs, data.min_stake)
      && t_Grams.fetch_to(cs, data.max_stake)
      && cs.fetch_uint_to(32, data.max_stake_factor)
      && m == 17;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons17& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons18& data) const {
  return t_Hashmap_32_StoragePrices.fetch_to(cs, data.x)
      && m == 18;
}

bool ConfigParam::unpack_cons18(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return t_Hashmap_32_StoragePrices.fetch_to(cs, x)
      && m == 18;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons18& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_cons18(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons18(cs, x) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_config_mc_gas_prices& data) const {
  return cs.fetch_subslice_to(392, data.x)
      && m == 20;
}

bool ConfigParam::unpack_config_mc_gas_prices(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return cs.fetch_subslice_to(392, x)
      && m == 20;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_config_mc_gas_prices& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_config_mc_gas_prices(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_config_mc_gas_prices(cs, x) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_config_gas_prices& data) const {
  return cs.fetch_subslice_to(392, data.x)
      && m == 21;
}

bool ConfigParam::unpack_config_gas_prices(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return cs.fetch_subslice_to(392, x)
      && m == 21;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_config_gas_prices& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_config_gas_prices(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_config_gas_prices(cs, x) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_config_mc_fwd_prices& data) const {
  return cs.fetch_subslice_to(264, data.x)
      && m == 24;
}

bool ConfigParam::unpack_config_mc_fwd_prices(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return cs.fetch_subslice_to(264, x)
      && m == 24;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_config_mc_fwd_prices& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_config_mc_fwd_prices(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_config_mc_fwd_prices(cs, x) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_config_fwd_prices& data) const {
  return cs.fetch_subslice_to(264, data.x)
      && m == 25;
}

bool ConfigParam::unpack_config_fwd_prices(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return cs.fetch_subslice_to(264, x)
      && m == 25;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_config_fwd_prices& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_config_fwd_prices(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_config_fwd_prices(cs, x) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons28& data) const {
  return cs.fetch_subslice_to(136, data.x)
      && m == 28;
}

bool ConfigParam::unpack_cons28(vm::CellSlice& cs, Ref<CellSlice>& x) const {
  return cs.fetch_subslice_to(136, x)
      && m == 28;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons28& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_cons28(Ref<vm::Cell> cell_ref, Ref<CellSlice>& x) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons28(cs, x) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons31& data) const {
  return t_HashmapE_256_True.fetch_to(cs, data.fundamental_smc_addr)
      && m == 31;
}

bool ConfigParam::unpack_cons31(vm::CellSlice& cs, Ref<CellSlice>& fundamental_smc_addr) const {
  return t_HashmapE_256_True.fetch_to(cs, fundamental_smc_addr)
      && m == 31;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons31& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_cons31(Ref<vm::Cell> cell_ref, Ref<CellSlice>& fundamental_smc_addr) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons31(cs, fundamental_smc_addr) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons32& data) const {
  return t_ValidatorSet.fetch_to(cs, data.prev_validators)
      && m == 32;
}

bool ConfigParam::unpack_cons32(vm::CellSlice& cs, Ref<CellSlice>& prev_validators) const {
  return t_ValidatorSet.fetch_to(cs, prev_validators)
      && m == 32;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons32& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_cons32(Ref<vm::Cell> cell_ref, Ref<CellSlice>& prev_validators) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons32(cs, prev_validators) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons34& data) const {
  return t_ValidatorSet.fetch_to(cs, data.cur_validators)
      && m == 34;
}

bool ConfigParam::unpack_cons34(vm::CellSlice& cs, Ref<CellSlice>& cur_validators) const {
  return t_ValidatorSet.fetch_to(cs, cur_validators)
      && m == 34;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons34& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_cons34(Ref<vm::Cell> cell_ref, Ref<CellSlice>& cur_validators) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons34(cs, cur_validators) && cs.empty_ext();
}

bool ConfigParam::unpack(vm::CellSlice& cs, ConfigParam::Record_cons36& data) const {
  return t_ValidatorSet.fetch_to(cs, data.next_validators)
      && m == 36;
}

bool ConfigParam::unpack_cons36(vm::CellSlice& cs, Ref<CellSlice>& next_validators) const {
  return t_ValidatorSet.fetch_to(cs, next_validators)
      && m == 36;
}

bool ConfigParam::cell_unpack(Ref<vm::Cell> cell_ref, ConfigParam::Record_cons36& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool ConfigParam::cell_unpack_cons36(Ref<vm::Cell> cell_ref, Ref<CellSlice>& next_validators) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack_cons36(cs, next_validators) && cs.empty_ext();
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons0& data) const {
  return cb.store_bits_bool(data.config_addr.cbits(), 256)
      && m == 0;
}

bool ConfigParam::pack_cons0(vm::CellBuilder& cb, const td::BitArray<256>& config_addr) const {
  return cb.store_bits_bool(config_addr.cbits(), 256)
      && m == 0;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons0& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_cons0(Ref<vm::Cell>& cell_ref, const td::BitArray<256>& config_addr) const {
  vm::CellBuilder cb;
  return pack_cons0(cb, config_addr) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons1& data) const {
  return cb.store_bits_bool(data.elector_addr.cbits(), 256)
      && m == 1;
}

bool ConfigParam::pack_cons1(vm::CellBuilder& cb, const td::BitArray<256>& elector_addr) const {
  return cb.store_bits_bool(elector_addr.cbits(), 256)
      && m == 1;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons1& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_cons1(Ref<vm::Cell>& cell_ref, const td::BitArray<256>& elector_addr) const {
  vm::CellBuilder cb;
  return pack_cons1(cb, elector_addr) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons12& data) const {
  return t_HashmapE_32_WorkchainDescr.store_from(cb, data.workchains)
      && m == 12;
}

bool ConfigParam::pack_cons12(vm::CellBuilder& cb, Ref<CellSlice> workchains) const {
  return t_HashmapE_32_WorkchainDescr.store_from(cb, workchains)
      && m == 12;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons12& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_cons12(Ref<vm::Cell>& cell_ref, Ref<CellSlice> workchains) const {
  vm::CellBuilder cb;
  return pack_cons12(cb, std::move(workchains)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons16& data) const {
  return cb.store_ulong_rchk_bool(data.max_validators, 16)
      && cb.store_ulong_rchk_bool(data.max_main_validators, 16)
      && cb.store_ulong_rchk_bool(data.min_validators, 16)
      && data.max_main_validators <= data.max_validators
      && data.min_validators <= data.max_main_validators
      && 1 <= data.min_validators
      && m == 16;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons16& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons17& data) const {
  return t_Grams.store_from(cb, data.min_stake)
      && t_Grams.store_from(cb, data.max_stake)
      && cb.store_ulong_rchk_bool(data.max_stake_factor, 32)
      && m == 17;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons17& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons18& data) const {
  return t_Hashmap_32_StoragePrices.store_from(cb, data.x)
      && m == 18;
}

bool ConfigParam::pack_cons18(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return t_Hashmap_32_StoragePrices.store_from(cb, x)
      && m == 18;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons18& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_cons18(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons18(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_config_mc_gas_prices& data) const {
  return cb.append_cellslice_chk(data.x, 392)
      && m == 20;
}

bool ConfigParam::pack_config_mc_gas_prices(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return cb.append_cellslice_chk(x, 392)
      && m == 20;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_config_mc_gas_prices& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_config_mc_gas_prices(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_config_mc_gas_prices(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_config_gas_prices& data) const {
  return cb.append_cellslice_chk(data.x, 392)
      && m == 21;
}

bool ConfigParam::pack_config_gas_prices(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return cb.append_cellslice_chk(x, 392)
      && m == 21;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_config_gas_prices& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_config_gas_prices(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_config_gas_prices(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_config_mc_fwd_prices& data) const {
  return cb.append_cellslice_chk(data.x, 264)
      && m == 24;
}

bool ConfigParam::pack_config_mc_fwd_prices(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return cb.append_cellslice_chk(x, 264)
      && m == 24;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_config_mc_fwd_prices& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_config_mc_fwd_prices(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_config_mc_fwd_prices(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_config_fwd_prices& data) const {
  return cb.append_cellslice_chk(data.x, 264)
      && m == 25;
}

bool ConfigParam::pack_config_fwd_prices(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return cb.append_cellslice_chk(x, 264)
      && m == 25;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_config_fwd_prices& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_config_fwd_prices(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_config_fwd_prices(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons28& data) const {
  return cb.append_cellslice_chk(data.x, 136)
      && m == 28;
}

bool ConfigParam::pack_cons28(vm::CellBuilder& cb, Ref<CellSlice> x) const {
  return cb.append_cellslice_chk(x, 136)
      && m == 28;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons28& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_cons28(Ref<vm::Cell>& cell_ref, Ref<CellSlice> x) const {
  vm::CellBuilder cb;
  return pack_cons28(cb, std::move(x)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons31& data) const {
  return t_HashmapE_256_True.store_from(cb, data.fundamental_smc_addr)
      && m == 31;
}

bool ConfigParam::pack_cons31(vm::CellBuilder& cb, Ref<CellSlice> fundamental_smc_addr) const {
  return t_HashmapE_256_True.store_from(cb, fundamental_smc_addr)
      && m == 31;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons31& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_cons31(Ref<vm::Cell>& cell_ref, Ref<CellSlice> fundamental_smc_addr) const {
  vm::CellBuilder cb;
  return pack_cons31(cb, std::move(fundamental_smc_addr)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons32& data) const {
  return t_ValidatorSet.store_from(cb, data.prev_validators)
      && m == 32;
}

bool ConfigParam::pack_cons32(vm::CellBuilder& cb, Ref<CellSlice> prev_validators) const {
  return t_ValidatorSet.store_from(cb, prev_validators)
      && m == 32;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons32& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_cons32(Ref<vm::Cell>& cell_ref, Ref<CellSlice> prev_validators) const {
  vm::CellBuilder cb;
  return pack_cons32(cb, std::move(prev_validators)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons34& data) const {
  return t_ValidatorSet.store_from(cb, data.cur_validators)
      && m == 34;
}

bool ConfigParam::pack_cons34(vm::CellBuilder& cb, Ref<CellSlice> cur_validators) const {
  return t_ValidatorSet.store_from(cb, cur_validators)
      && m == 34;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons34& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_cons34(Ref<vm::Cell>& cell_ref, Ref<CellSlice> cur_validators) const {
  vm::CellBuilder cb;
  return pack_cons34(cb, std::move(cur_validators)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::pack(vm::CellBuilder& cb, const ConfigParam::Record_cons36& data) const {
  return t_ValidatorSet.store_from(cb, data.next_validators)
      && m == 36;
}

bool ConfigParam::pack_cons36(vm::CellBuilder& cb, Ref<CellSlice> next_validators) const {
  return t_ValidatorSet.store_from(cb, next_validators)
      && m == 36;
}

bool ConfigParam::cell_pack(Ref<vm::Cell>& cell_ref, const ConfigParam::Record_cons36& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::cell_pack_cons36(Ref<vm::Cell>& cell_ref, Ref<CellSlice> next_validators) const {
  vm::CellBuilder cb;
  return pack_cons36(cb, std::move(next_validators)) && std::move(cb).finalize_to(cell_ref);
}

bool ConfigParam::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  switch (get_tag(cs)) {
  case cons0:
    return pp.open()
        && pp.fetch_bits_field(cs, 256, "config_addr")
        && m == 0
        && pp.close();
  case cons1:
    return pp.open()
        && pp.fetch_bits_field(cs, 256, "elector_addr")
        && m == 1
        && pp.close();
  case cons12:
    return pp.open()
        && pp.field("workchains")
        && t_HashmapE_32_WorkchainDescr.print_skip(pp, cs)
        && m == 12
        && pp.close();
  case cons16: {
    int max_validators, max_main_validators, min_validators;
    return pp.open()
        && cs.fetch_uint_to(16, max_validators)
        && pp.field_int(max_validators, "max_validators")
        && cs.fetch_uint_to(16, max_main_validators)
        && pp.field_int(max_main_validators, "max_main_validators")
        && cs.fetch_uint_to(16, min_validators)
        && pp.field_int(min_validators, "min_validators")
        && max_main_validators <= max_validators
        && min_validators <= max_main_validators
        && 1 <= min_validators
        && m == 16
        && pp.close();
    }
  case cons17:
    return pp.open()
        && pp.field("min_stake")
        && t_Grams.print_skip(pp, cs)
        && pp.field("max_stake")
        && t_Grams.print_skip(pp, cs)
        && pp.fetch_uint_field(cs, 32, "max_stake_factor")
        && m == 17
        && pp.close();
  case cons18:
    return pp.open()
        && pp.field()
        && t_Hashmap_32_StoragePrices.print_skip(pp, cs)
        && m == 18
        && pp.close();
  case config_mc_gas_prices:
    return pp.open("config_mc_gas_prices")
        && pp.field()
        && t_GasLimitsPrices.print_skip(pp, cs)
        && m == 20
        && pp.close();
  case config_gas_prices:
    return pp.open("config_gas_prices")
        && pp.field()
        && t_GasLimitsPrices.print_skip(pp, cs)
        && m == 21
        && pp.close();
  case config_mc_fwd_prices:
    return pp.open("config_mc_fwd_prices")
        && pp.field()
        && t_MsgForwardPrices.print_skip(pp, cs)
        && m == 24
        && pp.close();
  case config_fwd_prices:
    return pp.open("config_fwd_prices")
        && pp.field()
        && t_MsgForwardPrices.print_skip(pp, cs)
        && m == 25
        && pp.close();
  case cons28:
    return pp.open()
        && pp.field()
        && t_CatchainConfig.print_skip(pp, cs)
        && m == 28
        && pp.close();
  case cons31:
    return pp.open()
        && pp.field("fundamental_smc_addr")
        && t_HashmapE_256_True.print_skip(pp, cs)
        && m == 31
        && pp.close();
  case cons32:
    return pp.open()
        && pp.field("prev_validators")
        && t_ValidatorSet.print_skip(pp, cs)
        && m == 32
        && pp.close();
  case cons34:
    return pp.open()
        && pp.field("cur_validators")
        && t_ValidatorSet.print_skip(pp, cs)
        && m == 34
        && pp.close();
  case cons36:
    return pp.open()
        && pp.field("next_validators")
        && t_ValidatorSet.print_skip(pp, cs)
        && m == 36
        && pp.close();
  }
  return pp.fail("unknown constructor for ConfigParam");
}


//
// code for type `BlockSignaturesPure`
//

bool BlockSignaturesPure::skip(vm::CellSlice& cs) const {
  return cs.advance(96)
      && t_HashmapE_16_CryptoSignaturePair.skip(cs);
}

bool BlockSignaturesPure::validate_skip(vm::CellSlice& cs) const {
  return cs.advance(96)
      && t_HashmapE_16_CryptoSignaturePair.validate_skip(cs);
}

bool BlockSignaturesPure::unpack(vm::CellSlice& cs, BlockSignaturesPure::Record& data) const {
  return cs.fetch_uint_to(32, data.sig_count)
      && cs.fetch_uint_to(64, data.sig_weight)
      && t_HashmapE_16_CryptoSignaturePair.fetch_to(cs, data.signatures);
}

bool BlockSignaturesPure::cell_unpack(Ref<vm::Cell> cell_ref, BlockSignaturesPure::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BlockSignaturesPure::pack(vm::CellBuilder& cb, const BlockSignaturesPure::Record& data) const {
  return cb.store_ulong_rchk_bool(data.sig_count, 32)
      && cb.store_ulong_rchk_bool(data.sig_weight, 64)
      && t_HashmapE_16_CryptoSignaturePair.store_from(cb, data.signatures);
}

bool BlockSignaturesPure::cell_pack(Ref<vm::Cell>& cell_ref, const BlockSignaturesPure::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BlockSignaturesPure::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return pp.open("block_signatures_pure")
      && pp.fetch_uint_field(cs, 32, "sig_count")
      && pp.fetch_uint_field(cs, 64, "sig_weight")
      && pp.field("signatures")
      && t_HashmapE_16_CryptoSignaturePair.print_skip(pp, cs)
      && pp.close();
}

const BlockSignaturesPure t_BlockSignaturesPure;

//
// code for type `BlockSignatures`
//
constexpr unsigned char BlockSignatures::cons_tag[1];

bool BlockSignatures::skip(vm::CellSlice& cs) const {
  return cs.advance(72)
      && t_BlockSignaturesPure.skip(cs);
}

bool BlockSignatures::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 17
      && cs.advance(64)
      && t_BlockSignaturesPure.validate_skip(cs);
}

bool BlockSignatures::unpack(vm::CellSlice& cs, BlockSignatures::Record& data) const {
  return cs.fetch_ulong(8) == 17
      && cs.fetch_subslice_to(64, data.validator_info)
      && t_BlockSignaturesPure.fetch_to(cs, data.pure_signatures);
}

bool BlockSignatures::cell_unpack(Ref<vm::Cell> cell_ref, BlockSignatures::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BlockSignatures::pack(vm::CellBuilder& cb, const BlockSignatures::Record& data) const {
  return cb.store_long_bool(17, 8)
      && cb.append_cellslice_chk(data.validator_info, 64)
      && t_BlockSignaturesPure.store_from(cb, data.pure_signatures);
}

bool BlockSignatures::cell_pack(Ref<vm::Cell>& cell_ref, const BlockSignatures::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BlockSignatures::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 17
      && pp.open("block_signatures")
      && pp.field("validator_info")
      && t_ValidatorBaseInfo.print_skip(pp, cs)
      && pp.field("pure_signatures")
      && t_BlockSignaturesPure.print_skip(pp, cs)
      && pp.close();
}

const BlockSignatures t_BlockSignatures;

//
// code for type `BlockProof`
//
constexpr unsigned char BlockProof::cons_tag[1];

bool BlockProof::skip(vm::CellSlice& cs) const {
  return cs.advance_ext(0x10290)
      && t_Maybe_Ref_BlockSignatures.skip(cs);
}

bool BlockProof::validate_skip(vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xc3
      && t_BlockIdExt.validate_skip(cs)
      && cs.advance_refs(1)
      && t_Maybe_Ref_BlockSignatures.validate_skip(cs);
}

bool BlockProof::unpack(vm::CellSlice& cs, BlockProof::Record& data) const {
  return cs.fetch_ulong(8) == 0xc3
      && cs.fetch_subslice_to(648, data.proof_for)
      && cs.fetch_ref_to(data.root)
      && t_Maybe_Ref_BlockSignatures.fetch_to(cs, data.signatures);
}

bool BlockProof::cell_unpack(Ref<vm::Cell> cell_ref, BlockProof::Record& data) const {
  if (cell_ref.is_null()) { return false; }
  auto cs = load_cell_slice(std::move(cell_ref));
  return unpack(cs, data) && cs.empty_ext();
}

bool BlockProof::pack(vm::CellBuilder& cb, const BlockProof::Record& data) const {
  return cb.store_long_bool(0xc3, 8)
      && cb.append_cellslice_chk(data.proof_for, 648)
      && cb.store_ref_bool(data.root)
      && t_Maybe_Ref_BlockSignatures.store_from(cb, data.signatures);
}

bool BlockProof::cell_pack(Ref<vm::Cell>& cell_ref, const BlockProof::Record& data) const {
  vm::CellBuilder cb;
  return pack(cb, data) && std::move(cb).finalize_to(cell_ref);
}

bool BlockProof::print_skip(PrettyPrinter&pp, vm::CellSlice& cs) const {
  return cs.fetch_ulong(8) == 0xc3
      && pp.open("block_proof")
      && pp.field("proof_for")
      && t_BlockIdExt.print_skip(pp, cs)
      && pp.field("root")
      && t_Anything.print_ref(pp, cs.fetch_ref())
      && pp.field("signatures")
      && t_Maybe_Ref_BlockSignatures.print_skip(pp, cs)
      && pp.close();
}

const BlockProof t_BlockProof;

// definitions of constant types used

const NatWidth t_natwidth_1{1};
const NatWidth t_natwidth_8{8};
const NatLeq t_natleq_30{30};
const Maybe t_Maybe_Anycast{t_Anycast};
const Int t_int8{8};
const Bits t_bits256{256};
const NatWidth t_natwidth_9{9};
const Int t_int32{32};
const VarUInteger t_VarUInteger_16{16};
const VarUInteger t_VarUInteger_32{32};
const HashmapE t_HashmapE_32_VarUInteger_32{32, t_VarUInteger_32};
const UInt t_uint64{64};
const UInt t_uint32{32};
const NatWidth t_natwidth_5{5};
const Maybe t_Maybe_natwidth_5{t_natwidth_5};
const Maybe t_Maybe_TickTock{t_TickTock};
const Maybe t_Maybe_Ref_Cell{t_RefCell};
const HashmapE t_HashmapE_256_SimpleLib{256, t_SimpleLib};
const RefT t_Ref_StateInit{t_StateInit};
const Either t_Either_StateInit_Ref_StateInit{t_StateInit, t_Ref_StateInit};
const Maybe t_Maybe_Either_StateInit_Ref_StateInit{t_Either_StateInit_Ref_StateInit};
const NatLeq t_natleq_96{96};
const Message t_Message_Any{t_Anything};
const RefT t_Ref_Message_Any{t_Message_Any};
const RefT t_Ref_Transaction{t_Transaction};
const RefT t_Ref_MsgEnvelope{t_MsgEnvelope};
const HashmapAugE t_HashmapAugE_256_InMsg_ImportFees{256, t_InMsg, t_ImportFees};
const RefT t_Ref_InMsg{t_InMsg};
const HashmapAugE t_HashmapAugE_256_OutMsg_CurrencyCollection{256, t_OutMsg, t_CurrencyCollection};
const HashmapAugE t_HashmapAugE_352_EnqueuedMsg_uint64{352, t_EnqueuedMsg, t_uint64};
const HashmapE t_HashmapE_96_ProcessedUpto{96, t_ProcessedUpto};
const HashmapE t_HashmapE_256_IhrPendingSince{256, t_IhrPendingSince};
const VarUInteger t_VarUInteger_7{7};
const Maybe t_Maybe_Grams{t_Grams};
const RefT t_Ref_Account{t_Account};
const HashmapAugE t_HashmapAugE_256_Ref_Account_CurrencyCollection{256, t_Ref_Account, t_CurrencyCollection};
const UInt t_uint15{15};
const Maybe t_Maybe_Ref_Message_Any{t_Ref_Message_Any};
const HashmapE t_HashmapE_15_Ref_Message_Any{15, t_Ref_Message_Any};
const HASH_UPDATE t_HASH_UPDATE_Account{t_Account};
const RefT t_Ref_HASH_UPDATE_Account{t_HASH_UPDATE_Account};
const RefT t_Ref_TransactionDescr{t_TransactionDescr};
const HashmapAug t_HashmapAug_64_Ref_Transaction_Grams{64, t_Ref_Transaction, t_Grams};
const HashmapAugE t_HashmapAugE_256_AccountBlock_Grams{256, t_AccountBlock, t_Grams};
const VarUInteger t_VarUInteger_3{3};
const Maybe t_Maybe_VarUInteger_3{t_VarUInteger_3};
const Maybe t_Maybe_int32{t_int32};
const RefT t_Ref_TYPE_1619{t_TrComputePhase_aux};
const UInt t_uint16{16};
const Maybe t_Maybe_TrStoragePhase{t_TrStoragePhase};
const Maybe t_Maybe_TrCreditPhase{t_TrCreditPhase};
const RefT t_Ref_TrActionPhase{t_TrActionPhase};
const Maybe t_Maybe_Ref_TrActionPhase{t_Ref_TrActionPhase};
const Maybe t_Maybe_TrBouncePhase{t_TrBouncePhase};
const NatWidth t_natwidth_6{6};
const MessageRelaxed t_MessageRelaxed_Any{t_Anything};
const RefT t_Ref_MessageRelaxed_Any{t_MessageRelaxed_Any};
const NatLeq t_natleq_60{60};
const RefT t_Ref_OutMsgQueueInfo{t_OutMsgQueueInfo};
const HashmapE t_HashmapE_256_LibDescr{256, t_LibDescr};
const RefT t_Ref_TYPE_1632{t_ShardStateUnsplit_aux};
const Maybe t_Maybe_BlkMasterInfo{t_BlkMasterInfo};
const RefT t_Ref_McStateExtra{t_McStateExtra};
const Maybe t_Maybe_Ref_McStateExtra{t_Ref_McStateExtra};
const RefT t_Ref_ShardStateUnsplit{t_ShardStateUnsplit};
const Hashmap t_Hashmap_256_True{256, t_True};
const NatWidth t_natwidth_10{10};
const RefT t_Ref_BlkMasterInfo{t_BlkMasterInfo};
const BlkPrevInfo t_BlkPrevInfo_0{0};
const RefT t_Ref_BlkPrevInfo_0{t_BlkPrevInfo_0};
const RefT t_Ref_BlockInfo{t_BlockInfo};
const RefT t_Ref_ValueFlow{t_ValueFlow};
const MERKLE_UPDATE t_MERKLE_UPDATE_ShardState{t_ShardState};
const RefT t_Ref_MERKLE_UPDATE_ShardState{t_MERKLE_UPDATE_ShardState};
const RefT t_Ref_BlockExtra{t_BlockExtra};
const RefT t_Ref_InMsgDescr{t_InMsgDescr};
const RefT t_Ref_OutMsgDescr{t_OutMsgDescr};
const RefT t_Ref_McBlockExtra{t_McBlockExtra};
const Maybe t_Maybe_Ref_McBlockExtra{t_Ref_McBlockExtra};
const RefT t_Ref_TYPE_1642{t_ValueFlow_aux};
const RefT t_Ref_TYPE_1643{t_ValueFlow_aux1};
const NatWidth t_natwidth_3{3};
const BinTree t_BinTree_ShardDescr{t_ShardDescr};
const RefT t_Ref_BinTree_ShardDescr{t_BinTree_ShardDescr};
const HashmapE t_HashmapE_32_Ref_BinTree_ShardDescr{32, t_Ref_BinTree_ShardDescr};
const BinTreeAug t_BinTreeAug_True_CurrencyCollection{t_True, t_CurrencyCollection};
const RefT t_Ref_BinTreeAug_True_CurrencyCollection{t_BinTreeAug_True_CurrencyCollection};
const HashmapAugE t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection{32, t_Ref_BinTreeAug_True_CurrencyCollection, t_CurrencyCollection};
const Hashmap t_Hashmap_32_Ref_Cell{32, t_RefCell};
const RefT t_Ref_Hashmap_32_Ref_Cell{t_Hashmap_32_Ref_Cell};
const HashmapE t_HashmapE_32_ExtBlkRef{32, t_ExtBlkRef};
const Maybe t_Maybe_ExtBlkRef{t_ExtBlkRef};
const RefT t_Ref_TYPE_1654{t_McStateExtra_aux};
const HashmapE t_HashmapE_16_CryptoSignaturePair{16, t_CryptoSignaturePair};
const NatWidth t_natwidth_16{16};
const Hashmap t_Hashmap_16_ValidatorDescr{16, t_ValidatorDescr};
const NatWidth t_natwidth_12{12};
const NatWidth t_natwidth_32{32};
const NatWidth t_natwidth_13{13};
const HashmapE t_HashmapE_32_WorkchainDescr{32, t_WorkchainDescr};
const Hashmap t_Hashmap_32_StoragePrices{32, t_StoragePrices};
const HashmapE t_HashmapE_256_True{256, t_True};
const RefT t_Ref_BlockSignatures{t_BlockSignatures};
const Maybe t_Maybe_Ref_BlockSignatures{t_Ref_BlockSignatures};

} // namespace gen

} // namespace block
