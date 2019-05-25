#pragma once
#include "common/bitstring.h"
#include "vm/cells.h"
#include "vm/cellslice.h"
#include "vm/stack.hpp"
#include <functional>

namespace vm {

using td::BitSlice;

typedef std::function<bool(CellBuilder&)> store_value_func_t;

struct CombineError {};  // thrown by Dictionary::combine_with

class DictionaryBase {
 protected:
  mutable Ref<CellSlice> root;
  Ref<Cell> root_cell;
  int key_bits;
  mutable int flags;
  enum { f_valid = 1, f_root_cached = 2, f_invalid = 0x80 };

 public:
  enum class SetMode : int { Set = 3, Replace = 1, Add = 2 };
  enum { max_key_bits = 1023, max_key_bytes = (max_key_bits + 7) / 8 };
  DictionaryBase(int _n, bool validate = true);
  DictionaryBase(Ref<CellSlice> _root, int _n, bool validate = true);
  DictionaryBase(const CellSlice& root_cs, int _n, bool validate = true);
  DictionaryBase(CellSlice& root_cs, int _n, bool validate = true, bool skip = false);
  DictionaryBase(Ref<Cell> cell, int _n, bool validate = true);
  static Ref<Cell> construct_root_from(const CellSlice& root_node_cs);
  Ref<CellSlice> get_root() const;
  Ref<CellSlice> extract_root() &&;
  Ref<Cell> get_root_cell() const {
    return root_cell;
  }
  Ref<Cell> extract_root_cell() && {
    return std::move(root_cell);
  }
  bool append_dict_to_bool(CellBuilder& cb) &&;
  bool append_dict_to_bool(CellBuilder& cb) const &;
  int get_key_bits() const {
    return key_bits;
  }
  bool is_valid() const {
    return flags & f_valid;
  }
  void reset() {
    root.clear();
    root_cell.clear();
    flags = f_valid;
  }
  bool validate();
  void force_validate();
  bool is_empty() const {
    return root_cell.is_null();
  }
  static Ref<CellSlice> get_empty_dictionary();

 protected:
  bool invalidate() {
    flags |= f_invalid;
    return false;
  }
  bool compute_root() const;
  static Ref<CellSlice> new_empty_dictionary();
  static Ref<Cell> extract_value_ref(Ref<CellSlice> cs);
  void set_root_cell(Ref<Cell> cell) {
    root_cell = std::move(cell);
    flags &= ~f_root_cached;
  }
};

class Dictionary : public DictionaryBase {
 public:
  typedef std::function<bool(CellBuilder&, Ref<CellSlice>, Ref<CellSlice>)> simple_combine_func_t;
  typedef std::function<bool(CellBuilder&, Ref<CellSlice>, Ref<CellSlice>, td::ConstBitPtr, int)> combine_func_t;
  typedef std::function<bool(CellBuilder&, Ref<CellSlice>)> simple_map_func_t;
  typedef std::function<bool(CellBuilder&, Ref<CellSlice>, td::ConstBitPtr, int)> map_func_t;
  typedef std::function<bool(Ref<CellSlice>, td::ConstBitPtr, int)> foreach_func_t;
  Dictionary(int _n, bool validate = true) : DictionaryBase(_n, validate) {
  }
  Dictionary(Ref<CellSlice> _root, int _n, bool validate = true) : DictionaryBase(std::move(_root), _n, validate) {
  }
  Dictionary(const CellSlice& root_cs, int _n, bool validate = true) : DictionaryBase(root_cs, _n, validate) {
  }
  Dictionary(CellSlice& root_cs, int _n, bool validate = true, bool skip = false)
      : DictionaryBase(root_cs, _n, validate, skip) {
  }
  Dictionary(Ref<Cell> cell, int _n, bool validate = true) : DictionaryBase(std::move(cell), _n, validate) {
  }
  bool key_exists(td::ConstBitPtr key, int key_len);
  bool int_key_exists(long long key);
  bool uint_key_exists(unsigned long long key);
  Ref<CellSlice> lookup(td::ConstBitPtr key, int key_len);
  Ref<Cell> lookup_ref(td::ConstBitPtr key, int key_len);
  Ref<CellSlice> lookup_delete(td::ConstBitPtr key, int key_len);
  Ref<Cell> lookup_delete_ref(td::ConstBitPtr key, int key_len);
  bool set(td::ConstBitPtr key, int key_len, Ref<CellSlice> value, SetMode mode = SetMode::Set);
  bool set_ref(td::ConstBitPtr key, int key_len, Ref<Cell> val_ref, SetMode mode = SetMode::Set);
  bool set_builder(td::ConstBitPtr key, int key_len, Ref<CellBuilder> val_b, SetMode mode = SetMode::Set);
  bool set_builder(td::ConstBitPtr key, int key_len, const CellBuilder& val_b, SetMode mode = SetMode::Set);
  bool set_gen(td::ConstBitPtr key, int key_len, const store_value_func_t& store_val, SetMode mode = SetMode::Set);
  Ref<CellSlice> lookup_set(td::ConstBitPtr key, int key_len, Ref<CellSlice> value, SetMode mode = SetMode::Set);
  Ref<Cell> lookup_set_ref(td::ConstBitPtr key, int key_len, Ref<Cell> val_ref, SetMode mode = SetMode::Set);
  Ref<CellSlice> lookup_set_builder(td::ConstBitPtr key, int key_len, Ref<CellBuilder> val_b,
                                    SetMode mode = SetMode::Set);
  Ref<CellSlice> lookup_set_gen(td::ConstBitPtr key, int key_len, const store_value_func_t& store_val,
                                SetMode mode = SetMode::Set);
  Ref<CellSlice> get_minmax_key(td::BitPtr key_buffer, int key_len, bool fetch_max = false, bool invert_first = false);
  Ref<Cell> get_minmax_key_ref(td::BitPtr key_buffer, int key_len, bool fetch_max = false, bool invert_first = false);
  Ref<CellSlice> extract_minmax_key(td::BitPtr key_buffer, int key_len, bool fetch_max = false,
                                    bool invert_first = false);
  Ref<Cell> extract_minmax_key_ref(td::BitPtr key_buffer, int key_len, bool fetch_max = false,
                                   bool invert_first = false);
  Ref<CellSlice> lookup_nearest_key(td::BitPtr key_buffer, int key_len, bool fetch_next = false, bool allow_eq = false,
                                    bool invert_first = false);
  static BitSlice integer_key(td::RefInt256 x, unsigned n, bool sgnd = true, unsigned char buffer[128] = 0,
                              bool quiet = false);
  static bool integer_key_simple(td::RefInt256 x, unsigned n, bool sgnd, td::BitPtr buffer, bool quiet = false);
  void combine_with(Dictionary& dict2, const combine_func_t& combine_func, int mode = 0);
  void combine_with(Dictionary& dict2, const simple_combine_func_t& simple_combine_func, int mode = 0);
  void map(const map_func_t& map_func);
  void map(const simple_map_func_t& simple_map_func);
  bool check_for_each(const foreach_func_t& foreach_func, bool invert_first = false);
  template <unsigned n>
  bool key_exists(const td::BitArray<n>& key) {
    return key_exists(key.cbits(), n);
  }
  template <unsigned n>
  Ref<CellSlice> lookup(const td::BitArray<n>& key) {
    return lookup(key.cbits(), n);
  }
  template <unsigned n>
  Ref<Cell> lookup_ref(const td::BitArray<n>& key) {
    return lookup_ref(key.cbits(), n);
  }
  template <unsigned n>
  bool set(const td::BitArray<n>& key, Ref<CellSlice> value, SetMode mode = SetMode::Set) {
    return set(key.cbits(), n, std::move(value), mode);
  }
  template <unsigned n>
  bool set_ref(const td::BitArray<n>& key, Ref<Cell> val_ref, SetMode mode = SetMode::Set) {
    return set_ref(key.cbits(), n, std::move(val_ref), mode);
  }
  template <unsigned n>
  bool set_builder(const td::BitArray<n>& key, const CellBuilder& val_b, SetMode mode = SetMode::Set) {
    return set_builder(key.cbits(), n, val_b, mode);
  }
  template <unsigned n>
  bool set_builder(const td::BitArray<n>& key, Ref<vm::CellBuilder> val_ref, SetMode mode = SetMode::Set) {
    return set_builder(key.cbits(), n, std::move(val_ref), mode);
  }
};

class PrefixDictionary : public DictionaryBase {
 public:
  PrefixDictionary(int _n, bool validate = true) : DictionaryBase(_n, validate) {
  }
  PrefixDictionary(Ref<CellSlice> _root, int _n, bool validate = true)
      : DictionaryBase(std::move(_root), _n, validate) {
  }
  PrefixDictionary(Ref<Cell> cell, int _n, bool validate = true) : DictionaryBase(std::move(cell), _n, validate) {
  }
  Ref<CellSlice> lookup(td::ConstBitPtr key, int key_len);
  std::pair<Ref<CellSlice>, int> lookup_prefix(td::ConstBitPtr key, int key_len);
  Ref<CellSlice> lookup_delete(td::ConstBitPtr key, int key_len);
  bool set(td::ConstBitPtr key, int key_len, Ref<CellSlice> value, SetMode mode = SetMode::Set);
  bool set_builder(td::ConstBitPtr key, int key_len, Ref<CellBuilder> val_b, SetMode mode = SetMode::Set);
  bool set_gen(td::ConstBitPtr key, int key_len, const store_value_func_t& store_val, SetMode mode = SetMode::Set);
};

namespace dict {

struct LabelParser {
  enum { chk_none = 0, chk_min = 1, chk_size = 2, chk_all = 3 };
  Ref<CellSlice> remainder;
  int l_offs;
  int l_same;
  int l_bits;
  unsigned s_bits;
  LabelParser(Ref<CellSlice> cs, int max_label_len, int auto_validate = chk_all);
  LabelParser(Ref<Cell> cell, int max_label_len, int auto_validate = chk_all);
  int is_valid() const {
    return l_offs;
  }
  void validate() const;
  void validate_simple(int n) const;
  void validate_ext(int n) const;
  bool is_prefix_of(td::ConstBitPtr key, int len) const;
  int common_prefix_len(td::ConstBitPtr key, int len) const;
  int extract_label_to(td::BitPtr to);
  void skip_label() {
    remainder.write().advance(s_bits);
  }

 private:
  bool parse_label(CellSlice& cs, int max_label_len);
};

struct AugmentationData {
  virtual ~AugmentationData() = default;
  virtual bool skip_extra(vm::CellSlice& cs) const = 0;
  virtual bool eval_leaf(vm::CellBuilder& cb, vm::CellSlice& val_cs) const = 0;
  virtual bool eval_fork(vm::CellBuilder& cb, vm::CellSlice& left_cs, vm::CellSlice& right_cs) const = 0;
  virtual bool eval_empty(vm::CellBuilder& cb) const = 0;
  virtual bool check_leaf(vm::CellSlice& cs, vm::CellSlice& val_cs) const;
  virtual bool check_fork(vm::CellSlice& cs, vm::CellSlice& left_cs, vm::CellSlice& right_cs) const;
  virtual bool check_empty(vm::CellSlice& cs) const;
  Ref<vm::CellSlice> extract_extra(vm::CellSlice& cs) const;
  Ref<vm::CellSlice> extract_extra(Ref<vm::CellSlice> cs_ref) const;
};

static inline bool store_cell_dict(vm::CellBuilder& cb, Ref<vm::Cell> dict_root) {
  return dict_root.not_null() ? cb.store_long_bool(1, 1) && cb.store_ref_bool(std::move(dict_root))
                              : cb.store_long_bool(0, 1);
}

}  // namespace dict

using dict::AugmentationData;

class AugmentedDictionary : public DictionaryBase {
  const AugmentationData& aug;

 public:
  AugmentedDictionary(int _n, const AugmentationData& _aug, bool validate = true);
  AugmentedDictionary(Ref<CellSlice> _root, int _n, const AugmentationData& _aug, bool validate = true);
  AugmentedDictionary(Ref<Cell> cell, int _n, const AugmentationData& _aug, bool validate = true);
  Ref<CellSlice> get_empty_dictionary() const;
  Ref<CellSlice> get_root() const;
  Ref<CellSlice> extract_root() &&;
  bool append_dict_to_bool(CellBuilder& cb) &&;
  bool append_dict_to_bool(CellBuilder& cb) const &;
  Ref<CellSlice> get_root_extra() const;
  Ref<CellSlice> lookup(td::ConstBitPtr key, int key_len);
  Ref<Cell> lookup_ref(td::ConstBitPtr key, int key_len);
  Ref<CellSlice> lookup_with_extra(td::ConstBitPtr key, int key_len);
  std::pair<Ref<CellSlice>, Ref<CellSlice>> lookup_extra(td::ConstBitPtr key, int key_len);
  std::pair<Ref<Cell>, Ref<CellSlice>> lookup_ref_extra(td::ConstBitPtr key, int key_len);
  bool set(td::ConstBitPtr key, int key_len, const CellSlice& value, SetMode mode = SetMode::Set);
  bool set(td::ConstBitPtr key, int key_len, Ref<CellSlice> value, SetMode mode = SetMode::Set);
  bool set_ref(td::ConstBitPtr key, int key_len, Ref<Cell> val_ref, SetMode mode = SetMode::Set);
  bool set_builder(td::ConstBitPtr key, int key_len, const CellBuilder& value, SetMode mode = SetMode::Set);
  Ref<CellSlice> lookup_delete(td::ConstBitPtr key, int key_len);
  bool validate();
  void force_validate();
  template <unsigned n>
  Ref<CellSlice> lookup(const td::BitArray<n>& key) {
    return lookup(key.cbits(), n);
  }
  template <unsigned n>
  Ref<Cell> lookup_ref(const td::BitArray<n>& key) {
    return lookup_ref(key.cbits(), n);
  }
  template <unsigned n>
  bool set(const td::BitArray<n>& key, Ref<CellSlice> val_ref, SetMode mode = SetMode::Set) {
    return set(key.cbits(), n, std::move(val_ref), mode);
  }
  template <unsigned n>
  bool set(const td::BitArray<n>& key, const CellSlice& value, SetMode mode = SetMode::Set) {
    return set(key.cbits(), n, value, mode);
  }
  template <unsigned n>
  bool set_ref(const td::BitArray<n>& key, Ref<Cell> val_ref, SetMode mode = SetMode::Set) {
    return set_ref(key.cbits(), n, std::move(val_ref), mode);
  }
  template <unsigned n>
  bool set_builder(const td::BitArray<n>& key, const CellBuilder& val_b, SetMode mode = SetMode::Set) {
    return set_builder(key.cbits(), n, val_b, mode);
  }
  template <unsigned n>
  Ref<CellSlice> lookup_delete(const td::BitArray<n>& key) {
    return lookup_delete(key.cbits(), n);
  }

 private:
  bool compute_root() const;
  Ref<CellSlice> get_node_extra(Ref<Cell> cell_ref, int n) const;
  std::pair<Ref<Cell>, bool> dict_set(Ref<Cell> dict, td::ConstBitPtr key, int n, const CellSlice& value,
                                      SetMode mode = SetMode::Set) const;
  std::pair<Ref<CellSlice>, Ref<Cell>> dict_lookup_delete(Ref<Cell> dict, td::ConstBitPtr key, int n) const;
  Ref<Cell> finish_create_leaf(CellBuilder& cb, const CellSlice& value) const;
  Ref<Cell> finish_create_fork(CellBuilder& cb, Ref<Cell> c1, Ref<Cell> c2, int n) const;
};

}  // namespace vm
