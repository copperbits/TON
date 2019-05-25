#include "common/bigint.hpp"

namespace td {

template class AnyIntView<BigIntInfo>;
template class BigIntG<257, BigIntInfo>;

namespace literals {
BigInt256 operator""_i256(const char* str, std::size_t str_len) {
  BigInt256 x;
  x.enforce(x.parse_dec(str, (int)str_len) == (int)str_len);
  return x;
}

BigInt256 operator""_x256(const char* str, std::size_t str_len) {
  BigInt256 x;
  x.enforce(x.parse_hex(str, (int)str_len) == (int)str_len);
  return x;
}

}  // namespace literals

}  // namespace td
