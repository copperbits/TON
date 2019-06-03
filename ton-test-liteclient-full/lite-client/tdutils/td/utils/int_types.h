#pragma once

#include "td/utils/port/platform.h"

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace td {

#if !TD_WINDOWS
using size_t = std::size_t;
#endif

using int8 = std::int8_t;
using int16 = std::int16_t;
using uint16 = std::uint16_t;
using int32 = std::int32_t;
using uint32 = std::uint32_t;
using int64 = std::int64_t;
using uint64 = std::uint64_t;

static_assert(sizeof(std::uint8_t) == sizeof(unsigned char), "Unsigned char expected to be 8-bit");
using uint8 = unsigned char;

#if TD_MSVC
#pragma warning(push)
#pragma warning(disable : 4309)
#endif

static_assert(static_cast<char>(128) == -128 || static_cast<char>(128) == 128,
              "Unexpected cast to char implementation-defined behaviour");
static_assert(static_cast<char>(256) == 0, "Unexpected cast to char implementation-defined behaviour");
static_assert(static_cast<char>(-256) == 0, "Unexpected cast to char implementation-defined behaviour");

#if TD_MSVC
#pragma warning(pop)
#endif

class Slice;
class MutableSlice;
template <size_t size>
struct UInt {
  static_assert(size % 8 == 0, "size should be divisible by 8");
  uint8 raw[size / 8];
  Slice as_slice() const;
  MutableSlice as_slice();

  bool is_zero() const {
    for (size_t i = 0; i * 8 < size; i++) {
      if (raw[i] != 0) {
        return false;
      }
    }
    return true;
  }
  void set_zero() {
    for (size_t i = 0; i * 8 < size; i++) {
      raw[i] = 0;
    }
  }
  void set_zero_s() {
    volatile uint8 *p = raw;
    auto n = size / 8;
    while (n--) {
      *p++ = 0;
    }
  }
  static UInt zero() {
    UInt v;
    v.set_zero();
    return v;
  }
};

template <size_t size>
bool operator==(const UInt<size> &a, const UInt<size> &b) {
  return std::memcmp(a.raw, b.raw, sizeof(a.raw)) == 0;
}

template <size_t size>
bool operator!=(const UInt<size> &a, const UInt<size> &b) {
  return !(a == b);
}

template <size_t size>
td::UInt<size> operator^(const UInt<size> &a, const UInt<size> &b) {
  td::UInt<size> res;
  for (size_t i = 0; i < size / 8; i++) {
    res.raw[i] = static_cast<uint8>(a.raw[i] ^ b.raw[i]);
  }
  return res;
}

template <size_t size>
bool is_zero(const UInt<size> &a) {
  for (size_t i = 0; i * 8 < size; i++) {
    if (a.raw[i]) {
      return false;
    }
  }
  return true;
}

template <size_t size>
int get_kth_bit(const UInt<size> &a, uint32 bit) {
  uint8 b = a.raw[bit / 8];
  bit &= 7;
  return (b >> (7 - bit)) & 1;
}

template <size_t size>
bool operator<(const UInt<size> &a, const UInt<size> &b) {
  return std::memcmp(a.raw, b.raw, sizeof(a.raw)) < 0;
}

using UInt128 = UInt<128>;
using UInt256 = UInt<256>;

}  // namespace td
