#pragma once

#include "keys/keys.hpp"
#include "common/io.hpp"

namespace ton {

class AdnlNodeIdShort {
 public:
  explicit AdnlNodeIdShort(PublicKeyHash &hash) : hash_(hash) {
  }
  explicit AdnlNodeIdShort(PublicKeyHash &&hash) : hash_(std::move(hash)) {
  }
  AdnlNodeIdShort() {
  }
  explicit AdnlNodeIdShort(td::Slice data) : hash_(data) {
  }
  explicit AdnlNodeIdShort(td::UInt256 value) : hash_(value) {
  }

  const auto &pubkey_hash() const {
    return hash_;
  }

  bool operator==(const AdnlNodeIdShort &with) const {
    return hash_ == with.hash_;
  }
  bool operator!=(const AdnlNodeIdShort &with) const {
    return hash_ != with.hash_;
  }
  bool operator<(const AdnlNodeIdShort &with) const {
    return hash_ < with.hash_;
  }
  auto tl() const {
    return hash_.tl();
  }
  auto as_slice() {
    return hash_.as_slice();
  }
  auto as_slice() const {
    return hash_.as_slice();
  }
  auto uint256_value() const {
    return hash_.uint256_value();
  }
  auto bits256_value() const {
    return hash_.bits256_value();
  }
  static AdnlNodeIdShort zero() {
    return AdnlNodeIdShort{PublicKeyHash::zero()};
  }
  bool is_zero() const {
    return hash_.is_zero();
  }

 private:
  PublicKeyHash hash_;
};

class AdnlNodeIdFull {
 public:
  explicit AdnlNodeIdFull(PublicKey &pub) : pub_(pub) {
  }
  explicit AdnlNodeIdFull(PublicKey &&pub) : pub_(std::move(pub)) {
  }
  explicit AdnlNodeIdFull(const tl_object_ptr<ton_api::PublicKey> &pub) : pub_(pub) {
  }
  AdnlNodeIdFull() {
  }
  const auto &pubkey() const {
    return pub_;
  }
  bool empty() const {
    return pub_.empty();
  }
  bool operator==(const AdnlNodeIdFull &with) const {
    return pub_ == with.pub_;
  }
  bool operator!=(const AdnlNodeIdFull &with) const {
    return pub_ != with.pub_;
  }
  auto tl() const {
    return pub_.tl();
  }
  AdnlNodeIdShort compute_short_id() const {
    return AdnlNodeIdShort{pub_.compute_short_id()};
  }

 private:
  PublicKey pub_;
};

}  // namespace ton

namespace td {

inline StringBuilder &operator<<(StringBuilder &stream, const ton::AdnlNodeIdShort &value) {
  return stream << value.uint256_value();
}

}  // namespace td
