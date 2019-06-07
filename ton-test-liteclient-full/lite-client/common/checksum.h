#pragma once

#include "td/utils/int_types.h"
#include "crypto/common/bitstring.h"
#include "td/utils/crypto.h"

namespace td {

inline UInt256 sha256_uint256(Slice data) {
  UInt256 id;
  sha256(data, as_slice(id));
  return id;
}

inline Bits256 sha256_bits256(Slice data) {
  Bits256 id;
  sha256(data, id.as_slice());
  return id;
}

}  // namespace td
