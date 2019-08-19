#include "common/refint.h"
#include <utility>
#include <iostream>

#include "td/utils/StringBuilder.h"
#include "td/utils/Slice.h"

namespace td {

template class Cnt<BigInt256>;
template class Ref<Cnt<BigInt256>>;

RefInt256 operator+(RefInt256 x, RefInt256 y) {
  (x.write() += *y).normalize();
  return x;
}

RefInt256 operator+(RefInt256 x, long long y) {
  x.write().add_tiny(y).normalize();
  return x;
}

RefInt256 operator-(RefInt256 x, RefInt256 y) {
  (x.write() -= *y).normalize();
  return x;
}

RefInt256 operator-(RefInt256 x, long long y) {
  x.write().add_tiny(-y).normalize();
  return x;
}

RefInt256 operator-(RefInt256 x) {
  x.write().negate().normalize();
  return x;
}

RefInt256 operator~(RefInt256 x) {
  x.write().logical_not().normalize();
  return x;
}

RefInt256 operator*(RefInt256 x, RefInt256 y) {
  RefInt256 z{true, 0};
  z.write().add_mul(*x, *y).normalize();
  return z;
}

RefInt256 operator*(RefInt256 x, long long y) {
  x.write().mul_short_opt(y).normalize();
  return x;
}

RefInt256 operator/(RefInt256 x, RefInt256 y) {
  RefInt256 quot{true};
  x.write().mod_div(*y, quot.write());
  quot.write().normalize();
  return quot;
}

RefInt256 div(RefInt256 x, RefInt256 y, int round_mode) {
  RefInt256 quot{true};
  x.write().mod_div(*y, quot.write(), round_mode);
  quot.write().normalize();
  return quot;
}

RefInt256 operator%(RefInt256 x, RefInt256 y) {
  BigInt256 quot;
  x.write().mod_div(*y, quot);
  return x;
}

RefInt256 mod(RefInt256 x, RefInt256 y, int round_mode) {
  BigInt256 quot;
  x.write().mod_div(*y, quot, round_mode);
  return x;
}

std::pair<RefInt256, RefInt256> divmod(RefInt256 x, RefInt256 y, int round_mode) {
  RefInt256 quot{true};
  x.write().mod_div(*y, quot.write(), round_mode);
  quot.write().normalize();
  return std::make_pair(std::move(quot), std::move(x));
}

RefInt256 operator&(RefInt256 x, RefInt256 y) {
  x.write() &= *y;
  return x;
}

RefInt256 operator|(RefInt256 x, RefInt256 y) {
  x.write() |= *y;
  return x;
}

RefInt256 operator^(RefInt256 x, RefInt256 y) {
  x.write() ^= *y;
  return x;
}

RefInt256 operator<<(RefInt256 x, int y) {
  (x.write() <<= y).normalize();
  return x;
}

RefInt256 operator>>(RefInt256 x, int y) {
  (x.write() >>= y).normalize();
  return x;
}

RefInt256 rshift(RefInt256 x, int y, int round_mode) {
  x.write().rshift(y, round_mode).normalize();
  return x;
}

RefInt256& operator+=(RefInt256& x, RefInt256 y) {
  (x.write() += *y).normalize();
  return x;
}

RefInt256& operator+=(RefInt256& x, long long y) {
  x.write().add_tiny(y).normalize();
  return x;
}

RefInt256& operator-=(RefInt256& x, RefInt256 y) {
  (x.write() -= *y).normalize();
  return x;
}

RefInt256& operator-=(RefInt256& x, long long y) {
  x.write().add_tiny(-y).normalize();
  return x;
}

RefInt256& operator*=(RefInt256& x, RefInt256 y) {
  RefInt256 z{true, 0};
  z.write().add_mul(*x, *y).normalize();
  return x = z;
}

RefInt256& operator*=(RefInt256& x, long long y) {
  x.write().mul_short_opt(y).normalize();
  return x;
}

RefInt256& operator/=(RefInt256& x, RefInt256 y) {
  RefInt256 quot{true};
  x.write().mod_div(*y, quot.write());
  quot.write().normalize();
  return x = quot;
}

RefInt256& operator%=(RefInt256& x, RefInt256 y) {
  BigInt256 quot;
  x.write().mod_div(*y, quot);
  return x;
}

RefInt256& operator&=(RefInt256& x, RefInt256 y) {
  x.write() &= *y;
  return x;
}

RefInt256& operator|=(RefInt256& x, RefInt256 y) {
  x.write() |= *y;
  return x;
}

RefInt256& operator^=(RefInt256& x, RefInt256 y) {
  x.write() ^= *y;
  return x;
}

RefInt256& operator<<=(RefInt256& x, int y) {
  (x.write() <<= y).normalize();
  return x;
}

RefInt256& operator>>=(RefInt256& x, int y) {
  (x.write() >>= y).normalize();
  return x;
}

int cmp(RefInt256 x, RefInt256 y) {
  return x->cmp(*y);
}

int cmp(RefInt256 x, long long y) {
  return x->cmp(y);
}

int sgn(RefInt256 x) {
  return x->sgn();
}

extern RefInt256 make_refint(long long x) {
  auto xx = td::RefInt256{true, x};
  xx.unique_write().normalize();
  return xx;
}

std::string dec_string(RefInt256 x) {
  return x.is_null() ? "(null)" : (x.is_unique() ? x.unique_write().to_dec_string_destroy() : x->to_dec_string());
}

std::string dec_string2(RefInt256&& x) {
  return x.is_null() ? "(null)" : (x.is_unique() ? x.unique_write().to_dec_string_destroy() : x->to_dec_string());
}

std::string hex_string(RefInt256 x) {
  return x.is_null() ? "(null)" : x->to_hex_string();
}

std::string binary_string(RefInt256 x) {
  return x.is_null() ? "(null)" : x->to_binary_string();
}

std::ostream& operator<<(std::ostream& os, const RefInt256& x) {
  //std::cout << "<a|";
  return os << dec_string(std::move(x));
  //std::cout << "|a>";
  //return os;
}

std::ostream& operator<<(std::ostream& os, RefInt256&& x) {
  //std::cout << "<A|";
  return os << dec_string2(std::move(x));
  //std::cout << "|A>";
  //return os;
}

StringBuilder& operator<<(StringBuilder& sb, const RefInt256& x) {
  return sb << dec_string(x);
}

namespace literals {

RefInt256 operator""_ri256(const char* str, std::size_t str_len) {
  RefInt256 x{true};
  x->enforce(x.unique_write().parse_dec(str, (int)str_len) == (int)str_len);
  return x;
}

RefInt256 operator""_rx256(const char* str, std::size_t str_len) {
  RefInt256 x{true};
  x->enforce(x.unique_write().parse_hex(str, (int)str_len) == (int)str_len);
  return x;
}

}  // namespace literals
}  // namespace td
