#pragma once

#include "common/refcnt.hpp"
#include "common/bigint.hpp"
#include <utility>
#include <string>

namespace td {
class StringBuilder;

extern template class Cnt<BigInt256>;
extern template class Ref<Cnt<BigInt256>>;
typedef Cnt<BigInt256> CntInt256;
typedef Ref<CntInt256> RefInt256;

extern RefInt256 operator+(RefInt256 x, RefInt256 y);
extern RefInt256 operator+(RefInt256 x, long long y);
extern RefInt256 operator-(RefInt256 x, RefInt256 y);
extern RefInt256 operator-(RefInt256 x, long long y);
extern RefInt256 operator*(RefInt256 x, RefInt256 y);
extern RefInt256 operator*(RefInt256 x, long long y);
extern RefInt256 operator/(RefInt256 x, RefInt256 y);
extern RefInt256 operator%(RefInt256 x, RefInt256 y);
extern RefInt256 div(RefInt256 x, RefInt256 y, int round_mode = -1);
extern RefInt256 mod(RefInt256 x, RefInt256 y, int round_mode = -1);
extern std::pair<RefInt256, RefInt256> divmod(RefInt256 x, RefInt256 y, int round_mode = -1);
extern RefInt256 operator-(RefInt256 x);
extern RefInt256 operator&(RefInt256 x, RefInt256 y);
extern RefInt256 operator|(RefInt256 x, RefInt256 y);
extern RefInt256 operator^(RefInt256 x, RefInt256 y);
extern RefInt256 operator~(RefInt256 x);
extern RefInt256 operator<<(RefInt256 x, int y);
extern RefInt256 operator>>(RefInt256 x, int y);
extern RefInt256 rshift(RefInt256 x, int y, int round_mode = -1);

extern RefInt256& operator+=(RefInt256& x, RefInt256 y);
extern RefInt256& operator+=(RefInt256& x, long long y);
extern RefInt256& operator-=(RefInt256& x, RefInt256 y);
extern RefInt256& operator-=(RefInt256& x, long long y);
extern RefInt256& operator*=(RefInt256& x, RefInt256 y);
extern RefInt256& operator*=(RefInt256& x, long long y);
extern RefInt256& operator/=(RefInt256& x, RefInt256 y);
extern RefInt256& operator%=(RefInt256& x, RefInt256 y);

extern RefInt256& operator&=(RefInt256& x, RefInt256 y);
extern RefInt256& operator|=(RefInt256& x, RefInt256 y);
extern RefInt256& operator^=(RefInt256& x, RefInt256 y);
extern RefInt256& operator<<=(RefInt256& x, int y);
extern RefInt256& operator>>=(RefInt256& x, int y);

template <typename T>
bool operator==(RefInt256 x, T y) {
  return cmp(x, y) == 0;
}

template <typename T>
bool operator!=(RefInt256 x, T y) {
  return cmp(x, y) != 0;
}

template <typename T>
bool operator<(RefInt256 x, T y) {
  return cmp(x, y) < 0;
}

template <typename T>
bool operator>(RefInt256 x, T y) {
  return cmp(x, y) > 0;
}

template <typename T>
bool operator<=(RefInt256 x, T y) {
  return cmp(x, y) <= 0;
}

template <typename T>
bool operator>=(RefInt256 x, T y) {
  return cmp(x, y) >= 0;
}

extern int cmp(RefInt256 x, RefInt256 y);
extern int cmp(RefInt256 x, long long y);
extern int sgn(RefInt256 x);

extern RefInt256 make_refint(long long x);

extern std::string dec_string(RefInt256 x);
extern std::string dec_string2(RefInt256&& x);
extern std::string hex_string(RefInt256 x);
extern std::string binary_string(RefInt256 x);

extern std::ostream& operator<<(std::ostream& os, const RefInt256& x);
extern std::ostream& operator<<(std::ostream& os, RefInt256&& x);
extern td::StringBuilder& operator<<(td::StringBuilder& os, const RefInt256& x);

namespace literals {

extern RefInt256 operator""_ri256(const char* str, std::size_t str_len);
extern RefInt256 operator""_rx256(const char* str, std::size_t str_len);

}  // namespace literals
}  // namespace td
