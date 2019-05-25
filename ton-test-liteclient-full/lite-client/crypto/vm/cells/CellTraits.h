#pragma once
#include "td/utils/int_types.h"
#include "common/refcnt.hpp"

namespace td {
class StringBuilder;
}

namespace vm {
class CellTraits : public td::CntObject {
 public:
  enum class SpecialType : td::uint8 {
    Ordinary = 0,
    PrunnedBranch = 1,
    Library = 2,
    MerkleProof = 3,
    MerkleUpdate = 4
  };
  enum {
    max_refs = 4,
    max_bytes = 128,
    max_bits = 1023,
    hash_bytes = 32,
    hash_bits = hash_bytes * 8,
    depth_bytes = 2,
    depth_bits = depth_bytes * 8,
    max_level = 3,
    max_depth = 1024,
    max_virtualization = 7,
    max_serialized_bytes = 2 + max_bytes + (max_level + 1) * (hash_bytes + depth_bytes)
  };
};
td::StringBuilder& operator<<(td::StringBuilder& sb, CellTraits::SpecialType special_type);
}  // namespace vm
