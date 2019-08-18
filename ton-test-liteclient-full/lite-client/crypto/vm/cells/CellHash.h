#pragma once
#include "vm/cells/CellTraits.h"
#include "common/bitstring.h"

#include "td/utils/as.h"

#include <array>
namespace td {
class StringBuilder;
}

namespace vm {
struct CellHash {
 public:
  td::Slice as_slice() const {
    return td::Slice(hash_.data(), hash_.size());
  }
  td::MutableSlice as_slice() {
    return td::MutableSlice(hash_.data(), hash_.size());
  }
  bool operator==(const CellHash& other) const {
    return hash_ == other.hash_;
  }
  bool operator<(const CellHash& other) const {
    return hash_ < other.hash_;
  }
  bool operator!=(const CellHash& other) const {
    return hash_ != other.hash_;
  }
  std::string to_hex() const {
    return td::ConstBitPtr{hash_.data()}.to_hex(hash_.size() * 8);
  }
  friend td::StringBuilder& operator<<(td::StringBuilder& sb, const CellHash& hash);
  td::ConstBitPtr bits() const {
    return td::ConstBitPtr{hash_.data()};
  }
  td::BitPtr bits() {
    return td::BitPtr{hash_.data()};
  }
  td::BitSlice as_bitslice() const {
    return td::BitSlice{hash_.data(), (unsigned int)hash_.size() * 8};
  }
  const std::array<td::uint8, CellTraits::hash_bytes>& as_array() const {
    return hash_;
  }

  static CellHash from_slice(td::Slice slice) {
    CellHash res;
    CHECK(slice.size() == res.hash_.size());
    td::MutableSlice(res.hash_.data(), res.hash_.size()).copy_from(slice);
    return res;
  }

 private:
  std::array<td::uint8, CellTraits::hash_bytes> hash_;
};
}  // namespace vm

namespace std {
template <>
struct hash<vm::CellHash> {
  typedef vm::CellHash argument_type;
  typedef std::size_t result_type;
  result_type operator()(argument_type const& s) const noexcept {
    return td::as<size_t>(s.as_slice().ubegin());
  }
};
}  // namespace std
namespace vm {
template <class H>
H AbslHashValue(H h, const CellHash& cell_hash) {
  return AbslHashValue(std::move(h), std::hash<vm::CellHash>()(cell_hash));
}
}  // namespace vm
