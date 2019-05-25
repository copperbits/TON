#pragma once

#include "td/utils/int_types.h"
#include "td/utils/buffer.h"
#include "auto/tl/ton_api.h"
#include "td/utils/Variant.h"
#include "td/actor/actor.h"
#include "crypto/common/bitstring.h"
#include "crypto/Ed25519.h"

namespace ton {

class AdnlEncryptor;
class AdnlEncryptorAsync;
class AdnlDecryptor;
class AdnlDecryptorAsync;

class AdnlNodeIdShortImpl {
 public:
  explicit AdnlNodeIdShortImpl(td::UInt256 value) : value_(value) {
  }
  explicit AdnlNodeIdShortImpl(const tl_object_ptr<ton_api::adnl_id_Full> &value);
  AdnlNodeIdShortImpl() {
  }
  static AdnlNodeIdShortImpl zero() {
    return AdnlNodeIdShortImpl{td::UInt256::zero()};
  }
  explicit AdnlNodeIdShortImpl(td::Slice data) {
    CHECK(data.size() == 32);
    value_.as_slice().copy_from(data);
  }

  td::UInt256 uint256_value() const {
    return value_;
  }
  td::BitArray<256> bits256_value() const {
    td::BitArray<256> x;
    x.as_slice().copy_from(value_.as_slice());
    return x;
  }
  auto tl() const {
    return value_;
  }

  bool operator<(const AdnlNodeIdShortImpl &with) const {
    return value_ < with.value_;
  }
  bool operator==(const AdnlNodeIdShortImpl &with) const {
    return value_ == with.value_;
  }
  bool operator!=(const AdnlNodeIdShortImpl &with) const {
    return value_ != with.value_;
  }
  td::Slice as_slice() const {
    return td::as_slice(value_);
  }
  bool is_zero() const {
    return value_.is_zero();
  }

 private:
  td::UInt256 value_;
};
using AdnlNodeIdShort = AdnlNodeIdShortImpl;

namespace adnlid {

class AdnlEd25519Pub {
 private:
  td::UInt256 data_;

 public:
  AdnlEd25519Pub(const ton_api::adnl_id_ed25519 &obj) {
    data_ = obj.key_;
  }
  AdnlEd25519Pub(td::UInt256 id) : data_(id) {
  }
  AdnlEd25519Pub() {
  }
  AdnlEd25519Pub(td::Ed25519::PublicKey pk);
  td::Ed25519::PublicKey export_key() {
    return td::Ed25519::PublicKey{data_.as_slice()};
  }

  tl_object_ptr<ton_api::adnl_id_ed25519> tl() const {
    return create_tl_object<ton_api::adnl_id_ed25519>(data_);
  }
  bool operator==(const AdnlEd25519Pub &with) const {
    return data_ == with.data_;
  }
  bool operator!=(const AdnlEd25519Pub &with) const {
    return data_ != with.data_;
  }
};

class AdnlAESPub {
 private:
  td::UInt256 data_;

 public:
  AdnlAESPub(const ton_api::adnl_id_aes &obj) {
    data_ = obj.key_;
  }
  AdnlAESPub(td::Slice data) {
    CHECK(data.size() == 32);
    data_.as_slice().copy_from(data);
  }
  AdnlAESPub(td::UInt256 data) : data_(data) {
  }
  tl_object_ptr<ton_api::adnl_id_aes> tl() const {
    return create_tl_object<ton_api::adnl_id_aes>(data_);
  }
  bool operator==(const AdnlAESPub &with) const {
    return data_ == with.data_;
  }
  bool operator!=(const AdnlAESPub &with) const {
    return data_ != with.data_;
  }
};

class AdnlUnencPub {
 private:
  td::BufferSlice data_;

 public:
  AdnlUnencPub(const ton_api::adnl_id_unenc &obj) {
    data_ = obj.data_.clone();
  }
  AdnlUnencPub(const AdnlUnencPub &obj) {
    data_ = obj.data_.clone();
  }
  explicit AdnlUnencPub(td::BufferSlice data) : data_(std::move(data)) {
  }
  tl_object_ptr<ton_api::adnl_id_unenc> tl() const {
    return create_tl_object<ton_api::adnl_id_unenc>(data_.clone());
  }
  bool operator==(const AdnlUnencPub &with) const {
    return data_.as_slice() == with.data_.as_slice();
  }
  bool operator!=(const AdnlUnencPub &with) const {
    return data_.as_slice() != with.data_.as_slice();
  }
};

class AdnlOverlayPub {
 private:
  td::BufferSlice data_;

 public:
  AdnlOverlayPub(const ton_api::adnl_id_overlay &obj) {
    data_ = obj.name_.clone();
  }
  AdnlOverlayPub(const AdnlOverlayPub &obj) {
    data_ = obj.data_.clone();
  }
  explicit AdnlOverlayPub(td::BufferSlice data) : data_(std::move(data)) {
  }
  tl_object_ptr<ton_api::adnl_id_overlay> tl() const {
    return create_tl_object<ton_api::adnl_id_overlay>(data_.clone());
  }
  bool operator==(const AdnlOverlayPub &with) const {
    return data_.as_slice() == with.data_.as_slice();
  }
  bool operator!=(const AdnlOverlayPub &with) const {
    return data_.as_slice() != with.data_.as_slice();
  }
};

}  // namespace adnlid

class AdnlNodeIdFullImpl {
 private:
  class Empty {
   public:
    tl_object_ptr<ton_api::adnl_id_Full> tl() const {
      UNREACHABLE();
    }
    bool operator==(const Empty &with) const {
      return false;
    }
    bool operator!=(const Empty &with) const {
      return true;
    }
  };
  td::Variant<Empty, adnlid::AdnlEd25519Pub, adnlid::AdnlAESPub, adnlid::AdnlUnencPub, adnlid::AdnlOverlayPub> pub_key_{
      Empty{}};

 public:
  AdnlNodeIdFullImpl(const tl_object_ptr<ton_api::adnl_id_Full> &id);
  AdnlNodeIdFullImpl() {
  }
  AdnlNodeIdFullImpl(adnlid::AdnlEd25519Pub pub) : pub_key_(std::move(pub)) {
  }
  AdnlNodeIdFullImpl(adnlid::AdnlAESPub pub) : pub_key_(std::move(pub)) {
  }
  AdnlNodeIdFullImpl(adnlid::AdnlUnencPub pub) : pub_key_(std::move(pub)) {
  }
  AdnlNodeIdFullImpl(adnlid::AdnlOverlayPub pub) : pub_key_(std::move(pub)) {
  }

  bool empty() const;

  AdnlNodeIdShortImpl compute_short_id() const;
  tl_object_ptr<ton_api::adnl_id_Full> tl() const;

  td::Result<std::unique_ptr<AdnlEncryptor>> create_encryptor() const;
  td::Result<td::actor::ActorOwn<AdnlEncryptorAsync>> create_encryptor_async() const;

  bool operator==(const AdnlNodeIdFullImpl &with) const {
    return pub_key_ == with.pub_key_;
  }
  bool operator!=(const AdnlNodeIdFullImpl &with) const {
    return !(pub_key_ == with.pub_key_);
  }
};

using AdnlNodeIdFull = AdnlNodeIdFullImpl;

namespace adnlid {

class AdnlEd25519Priv {
 private:
  td::UInt256 data_;

 public:
  AdnlEd25519Priv(const ton_api::adnl_id_pk_ed25519 &obj) {
    data_ = obj.key_;
  }
  AdnlEd25519Priv(td::UInt256 id) : data_(id) {
  }
  AdnlEd25519Priv() {
  }
  AdnlEd25519Priv(td::Ed25519::PrivateKey pk);
  td::Ed25519::PrivateKey export_key() {
    return td::Ed25519::PrivateKey{data_.as_slice()};
  }
  tl_object_ptr<ton_api::adnl_id_pk_ed25519> tl() const {
    return create_tl_object<ton_api::adnl_id_pk_ed25519>(data_);
  }
  tl_object_ptr<ton_api::adnl_id_Full> pub_tl() const;
  AdnlEd25519Pub pub() const;
  static AdnlEd25519Priv random();
};

class AdnlAESPriv {
 private:
  td::UInt256 data_;

 public:
  AdnlAESPriv(const ton_api::adnl_id_pk_aes &obj) {
    data_ = obj.key_;
  }
  AdnlAESPriv(td::Slice data) {
    CHECK(data.size() == 32);
    data_.as_slice().copy_from(data);
  }
  tl_object_ptr<ton_api::adnl_id_pk_aes> tl() const {
    return create_tl_object<ton_api::adnl_id_pk_aes>(data_);
  }
  tl_object_ptr<ton_api::adnl_id_Full> pub_tl() const {
    return create_tl_object<ton_api::adnl_id_aes>(data_);
  }
  AdnlAESPub pub() const {
    return AdnlAESPub{data_};
  }
};

class AdnlUnencPriv {
 private:
  td::BufferSlice data_;

 public:
  AdnlUnencPriv(const ton_api::adnl_id_pk_unenc &obj) {
    data_ = obj.data_.clone();
  }
  AdnlUnencPriv(const AdnlUnencPriv &obj) {
    data_ = obj.data_.clone();
  }
  tl_object_ptr<ton_api::adnl_id_pk_unenc> tl() const {
    return create_tl_object<ton_api::adnl_id_pk_unenc>(data_.clone());
  }
  tl_object_ptr<ton_api::adnl_id_Full> pub_tl() const {
    return create_tl_object<ton_api::adnl_id_unenc>(data_.clone());
  }
  AdnlUnencPub pub() const {
    return AdnlUnencPub{data_.clone()};
  }
};

class AdnlOverlayPriv {
 private:
  td::BufferSlice data_;

 public:
  AdnlOverlayPriv(const ton_api::adnl_id_pk_overlay &obj) {
    data_ = obj.name_.clone();
  }
  AdnlOverlayPriv(const AdnlOverlayPriv &obj) {
    data_ = obj.data_.clone();
  }
  tl_object_ptr<ton_api::adnl_id_pk_overlay> tl() const {
    return create_tl_object<ton_api::adnl_id_pk_overlay>(data_.clone());
  }
  tl_object_ptr<ton_api::adnl_id_Full> pub_tl() const {
    return create_tl_object<ton_api::adnl_id_overlay>(data_.clone());
  }
  AdnlOverlayPub pub() const {
    return AdnlOverlayPub{data_.clone()};
  }
};

}  // namespace adnlid

class AdnlNodePkImpl {
 private:
  class Empty {
   public:
    tl_object_ptr<ton_api::adnl_id_Pk> tl() const {
      UNREACHABLE();
    }
    tl_object_ptr<ton_api::adnl_id_Full> pub_tl() const {
      UNREACHABLE();
    }
    AdnlNodeIdFull pub() const {
      UNREACHABLE();
    }
  };
  td::Variant<Empty, adnlid::AdnlEd25519Priv, adnlid::AdnlAESPriv, adnlid::AdnlUnencPriv, adnlid::AdnlOverlayPriv>
      priv_key_{Empty{}};

 public:
  explicit AdnlNodePkImpl(const tl_object_ptr<ton_api::adnl_id_Pk> &pk);
  AdnlNodePkImpl(adnlid::AdnlEd25519Priv priv) : priv_key_(std::move(priv)) {
  }
  AdnlNodePkImpl(adnlid::AdnlAESPriv priv) : priv_key_(std::move(priv)) {
  }
  AdnlNodePkImpl(adnlid::AdnlUnencPriv priv) : priv_key_(std::move(priv)) {
  }
  AdnlNodePkImpl(adnlid::AdnlOverlayPriv priv) : priv_key_(std::move(priv)) {
  }
  AdnlNodePkImpl() {
  }

  bool empty() const;

  AdnlNodeIdFullImpl compute_public_key() const;
  AdnlNodeIdShortImpl compute_short_id() const;
  tl_object_ptr<ton_api::adnl_id_Pk> tl() const;

  td::Result<std::unique_ptr<AdnlDecryptor>> create_decryptor() const;
  td::Result<td::actor::ActorOwn<AdnlDecryptorAsync>> create_decryptor_async() const;
};

using AdnlNodePk = AdnlNodePkImpl;

}  // namespace ton
