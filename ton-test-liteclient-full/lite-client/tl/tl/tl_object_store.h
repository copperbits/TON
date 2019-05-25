#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "tl/TlObject.h"

#include "td/utils/misc.h"

namespace ton {

template <class Func, std::int32_t constructor_id>
class TlStoreBoxed {
 public:
  template <class T, class Storer>
  static void store(const T &x, Storer &s) {
    s.store_binary(constructor_id);
    Func::store(x, s);
  }
};

template <class Func>
class TlStoreBoxedUnknown {
 public:
  template <class T, class Storer>
  static void store(const T &x, Storer &s) {
    s.store_binary(x->get_id());
    Func::store(x, s);
  }
};

class TlStoreBool {
 public:
  template <class Storer>
  static void store(const bool &x, Storer &s) {
    constexpr std::int32_t ID_BOOL_FALSE = 0xbc799737;
    constexpr std::int32_t ID_BOOL_TRUE = 0x997275b5;

    s.store_binary(x ? ID_BOOL_TRUE : ID_BOOL_FALSE);
  }
};

class TlStoreTrue {
 public:
  template <class Storer>
  static void store(const bool &x, Storer &s) {
    // currently nothing to do
  }
};

class TlStoreBinary {
 public:
  template <class T, class Storer>
  static void store(const T &x, Storer &s) {
    s.store_binary(x);
  }
};

class TlStoreString {
 public:
  template <class T, class Storer>
  static void store(const T &x, Storer &s) {
    s.store_string(x);
  }
};

template <class Func>
class TlStoreVector {
 public:
  template <class T, class Storer>
  static void store(const T &vec, Storer &s) {
    s.store_binary(td::narrow_cast<td::int32>(vec.size()));
    for (auto &val : vec) {
      Func::store(val, s);
    }
  }
};

class TlStoreObject {
 public:
  template <class T, class Storer>
  static void store(const tl_object_ptr<T> &obj, Storer &s) {
    return obj->store(s);
  }
};

}  // namespace ton
