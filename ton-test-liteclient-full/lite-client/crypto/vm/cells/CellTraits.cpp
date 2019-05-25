#include "vm/cells/CellTraits.h"

#include "td/utils/StringBuilder.h"
#include "td/utils/Slice.h"

namespace vm {
td::StringBuilder& operator<<(td::StringBuilder& sb, CellTraits::SpecialType special_type) {
  switch (special_type) {
    case CellTraits::SpecialType::Ordinary:
      sb << "Ordinary";
      break;
    case CellTraits::SpecialType::MerkleProof:
      sb << "MerkleProof";
      break;
    case CellTraits::SpecialType::MerkleUpdate:
      sb << "MerkleUpdate";
      break;
    case CellTraits::SpecialType::PrunnedBranch:
      sb << "PrunnedBranch";
      break;
    case CellTraits::SpecialType::Library:
      sb << "Library";
      break;
  }
  return sb;
}
}  // namespace vm
