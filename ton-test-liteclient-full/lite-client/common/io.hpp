#pragma once

#include "td/utils/buffer.h"
#include "td/utils/misc.h"
#include "td/utils/crypto.h"
#include "td/utils/format.h"
#include "td/utils/base64.h"
#include "td/utils/JsonBuilder.h"
#include "tl-utils/tl-utils.hpp"

#include "common/errorcode.h"
#include "common/status.h"
#include "keys/keys.hpp"

namespace td {

template <size_t size>
StringBuilder &operator<<(StringBuilder &stream, const UInt<size> &x) {
  return stream << td::base64_encode(as_slice(x));
}

inline StringBuilder &operator<<(StringBuilder &stream, const ton::PublicKeyHash &value) {
  return stream << value.uint256_value();
}

}  // namespace td
