#pragma once

#include "auto/tl/lite_api.h"

#include "tl/tl_object_parse.h"
#include "td/utils/tl_parsers.h"

#include "crypto/common/bitstring.h"

#include "common-utils.hpp"

namespace ton {
td::BufferSlice serialize_tl_object(const lite_api::Object *T, bool boxed);
td::BufferSlice serialize_tl_object(const lite_api::Function *T, bool boxed);
td::BufferSlice serialize_tl_object(const lite_api::Object *T, bool boxed, td::BufferSlice &&suffix);
td::BufferSlice serialize_tl_object(const lite_api::Function *T, bool boxed, td::BufferSlice &&suffix);

td::UInt256 get_tl_object_sha256(const lite_api::Object *T);

template <class Tp, std::enable_if_t<std::is_base_of<lite_api::Object, Tp>::value>>
td::UInt256 get_tl_object_sha256(const Tp &T) {
  return get_tl_object_sha256(static_cast<const lite_api::Object *>(&T));
}

td::Bits256 get_tl_object_sha_bits256(const lite_api::Object *T);

template <class Tp, std::enable_if_t<std::is_base_of<lite_api::Object, Tp>::value>>
td::Bits256 get_tl_object_sha_bits256(const Tp &T) {
  return get_tl_object_sha_bits256(static_cast<const lite_api::Object *>(&T));
}
}  // namespace ton
