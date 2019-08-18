#pragma once

#include "td/utils/int_types.h"
#include "td/utils/buffer.h"
#include "auto/tl/ton_api.h"
#include "td/utils/UInt.h"
#include "td/utils/Variant.h"
#include "td/actor/actor.h"
#include "crypto/common/bitstring.h"
#include "crypto/Ed25519.h"

namespace ton {

class Encryptor;
class EncryptorAsync;
class Decryptor;
class DecryptorAsync;

class PublicKeyHash {
 public:
  explicit PublicKeyHash(td::Bits256 value) : value_(value) {
  }
  explicit PublicKeyHash(const tl_object_ptr<ton_api::PublicKey> &value);
  PublicKeyHash() {
  }
  static PublicKeyHash zero() {
    return PublicKeyHash{td::Bits256::zero()};
  }
  explicit PublicKeyHash(td::Slice data) {
    CHECK(data.size() == 32);
    value_.as_slice().copy_from(data);
  }

  td::UInt256 uint256_value() const {
    td::UInt256 x;
    x.as_slice().copy_from(value_.as_slice());
    return x;
  }
  td::Bits256 bits256_value() const {
    return value_;
  }
  auto tl() const {
    return value_;
  }

  bool operator<(const PublicKeyHash &with) const {
    return value_ < with.value_;
  }
  bool operator==(const PublicKeyHash &with) const {
    return value_ == with.value_;
  }
  bool operator!=(const PublicKeyHash &with) const {
    return value_ != with.value_;
  }
  td::Slice as_slice() const {
    return td::as_slice(value_);
  }
  bool is_zero() const {
    return value_.is_zero();
  }

 private:
  td::Bits256 value_;
};

namespace pubkeys {

class Ed25519 {
 private:
  td::Bits256 data_;

 public:
  Ed25519(const ton_api::pub_ed25519 &obj) {
    data_ = obj.key_;
  }
  Ed25519(td::Bits256 id) : data_(id) {
  }
  Ed25519() {
  }
  Ed25519(td::Ed25519::PublicKey pk);
  td::Ed25519::PublicKey export_key() {
    return td::Ed25519::PublicKey{td::SecureString(data_.as_slice())};
  }

  auto raw() const {
    return data_;
  }
  td::uint32 serialized_size() const {
    return 36;
  }
  tl_object_ptr<ton_api::pub_ed25519> tl() const {
    return create_tl_object<ton_api::pub_ed25519>(data_);
  }
  bool operator==(const Ed25519 &with) const {
    return data_ == with.data_;
  }
  bool operator!=(const Ed25519 &with) const {
    return data_ != with.data_;
  }
};

class AES {
 private:
  td::Bits256 data_;

 public:
  ~AES() {
    data_.set_zero_s();
  }
  AES(const ton_api::pub_aes &obj) {
    data_ = obj.key_;
  }
  AES(td::Slice data) {
    CHECK(data.size() == 32);
    data_.as_slice().copy_from(data);
  }
  AES(td::Bits256 data) : data_(data) {
  }
  td::uint32 serialized_size() const {
    return 36;
  }
  tl_object_ptr<ton_api::pub_aes> tl() const {
    return create_tl_object<ton_api::pub_aes>(data_);
  }
  bool operator==(const AES &with) const {
    return data_ == with.data_;
  }
  bool operator!=(const AES &with) const {
    return data_ != with.data_;
  }
};

class Unenc {
 private:
  td::BufferSlice data_;

 public:
  Unenc(const ton_api::pub_unenc &obj) {
    data_ = obj.data_.clone();
  }
  Unenc(const Unenc &obj) {
    data_ = obj.data_.clone();
  }
  explicit Unenc(td::BufferSlice data) : data_(std::move(data)) {
  }
  td::uint32 serialized_size() const {
    return static_cast<td::uint32>(data_.size()) + 8;
  }
  tl_object_ptr<ton_api::pub_unenc> tl() const {
    return create_tl_object<ton_api::pub_unenc>(data_.clone());
  }
  bool operator==(const Unenc &with) const {
    return data_.as_slice() == with.data_.as_slice();
  }
  bool operator!=(const Unenc &with) const {
    return data_.as_slice() != with.data_.as_slice();
  }
};

class Overlay {
 private:
  td::BufferSlice data_;

 public:
  Overlay(const ton_api::pub_overlay &obj) {
    data_ = obj.name_.clone();
  }
  Overlay(const Overlay &obj) {
    data_ = obj.data_.clone();
  }
  explicit Overlay(td::BufferSlice data) : data_(std::move(data)) {
  }
  td::uint32 serialized_size() const {
    return static_cast<td::uint32>(data_.size()) + 8;
  }
  tl_object_ptr<ton_api::pub_overlay> tl() const {
    return create_tl_object<ton_api::pub_overlay>(data_.clone());
  }
  bool operator==(const Overlay &with) const {
    return data_.as_slice() == with.data_.as_slice();
  }
  bool operator!=(const Overlay &with) const {
    return data_.as_slice() != with.data_.as_slice();
  }
};

}  // namespace pubkeys

class PublicKey {
 private:
  class Empty {
   public:
    tl_object_ptr<ton_api::PublicKey> tl() const {
      UNREACHABLE();
    }
    td::uint32 serialized_size() const {
      UNREACHABLE();
    }
    bool operator==(const Empty &with) const {
      return false;
    }
    bool operator!=(const Empty &with) const {
      return true;
    }
  };
  td::Variant<Empty, pubkeys::Ed25519, pubkeys::AES, pubkeys::Unenc, pubkeys::Overlay> pub_key_{Empty{}};

 public:
  explicit PublicKey(const tl_object_ptr<ton_api::PublicKey> &id);
  PublicKey() {
  }
  PublicKey(pubkeys::Ed25519 pub) : pub_key_(std::move(pub)) {
  }
  PublicKey(pubkeys::AES pub) : pub_key_(std::move(pub)) {
  }
  PublicKey(pubkeys::Unenc pub) : pub_key_(std::move(pub)) {
  }
  PublicKey(pubkeys::Overlay pub) : pub_key_(std::move(pub)) {
  }

  bool empty() const;

  PublicKeyHash compute_short_id() const;
  td::uint32 serialized_size() const;
  tl_object_ptr<ton_api::PublicKey> tl() const;

  td::Result<std::unique_ptr<Encryptor>> create_encryptor() const;
  td::Result<td::actor::ActorOwn<EncryptorAsync>> create_encryptor_async() const;

  bool operator==(const PublicKey &with) const {
    return pub_key_ == with.pub_key_;
  }
  bool operator!=(const PublicKey &with) const {
    return !(pub_key_ == with.pub_key_);
  }
};

namespace privkeys {

class Ed25519 {
 private:
  td::Bits256 data_;

 public:
  ~Ed25519() {
    data_.set_zero_s();
  }
  Ed25519(const ton_api::pk_ed25519 &obj) {
    data_ = obj.key_;
  }
  Ed25519(td::Bits256 id) : data_(id) {
  }
  Ed25519() {
  }
  Ed25519(td::Ed25519::PrivateKey pk);
  td::Ed25519::PrivateKey export_key() {
    return td::Ed25519::PrivateKey{td::SecureString(data_.as_slice())};
  }
  tl_object_ptr<ton_api::pk_ed25519> tl() const {
    return create_tl_object<ton_api::pk_ed25519>(data_);
  }
  tl_object_ptr<ton_api::PublicKey> pub_tl() const;
  pubkeys::Ed25519 pub() const;
  static Ed25519 random();
};

class AES {
 private:
  td::Bits256 data_;

 public:
  ~AES() {
    data_.set_zero_s();
  }
  AES(const ton_api::pk_aes &obj) {
    data_ = obj.key_;
  }
  AES(td::Slice data) {
    CHECK(data.size() == 32);
    data_.as_slice().copy_from(data);
  }
  tl_object_ptr<ton_api::pk_aes> tl() const {
    return create_tl_object<ton_api::pk_aes>(data_);
  }
  tl_object_ptr<ton_api::PublicKey> pub_tl() const {
    return create_tl_object<ton_api::pub_aes>(data_);
  }
  pubkeys::AES pub() const {
    return pubkeys::AES{data_};
  }
};

class Unenc {
 private:
  td::BufferSlice data_;

 public:
  Unenc(const ton_api::pk_unenc &obj) {
    data_ = obj.data_.clone();
  }
  Unenc(const Unenc &obj) {
    data_ = obj.data_.clone();
  }
  tl_object_ptr<ton_api::pk_unenc> tl() const {
    return create_tl_object<ton_api::pk_unenc>(data_.clone());
  }
  tl_object_ptr<ton_api::PublicKey> pub_tl() const {
    return create_tl_object<ton_api::pub_unenc>(data_.clone());
  }
  pubkeys::Unenc pub() const {
    return pubkeys::Unenc{data_.clone()};
  }
};

class Overlay {
 private:
  td::BufferSlice data_;

 public:
  Overlay(const ton_api::pk_overlay &obj) {
    data_ = obj.name_.clone();
  }
  Overlay(const Overlay &obj) {
    data_ = obj.data_.clone();
  }
  tl_object_ptr<ton_api::pk_overlay> tl() const {
    return create_tl_object<ton_api::pk_overlay>(data_.clone());
  }
  tl_object_ptr<ton_api::PublicKey> pub_tl() const {
    return create_tl_object<ton_api::pub_overlay>(data_.clone());
  }
  pubkeys::Overlay pub() const {
    return pubkeys::Overlay{data_.clone()};
  }
};

}  // namespace privkeys

class PrivateKey {
 private:
  class Empty {
   public:
    tl_object_ptr<ton_api::PrivateKey> tl() const {
      UNREACHABLE();
    }
    tl_object_ptr<ton_api::PublicKey> pub_tl() const {
      UNREACHABLE();
    }
    PublicKey pub() const {
      UNREACHABLE();
    }
  };
  td::Variant<Empty, privkeys::Ed25519, privkeys::AES, privkeys::Unenc, privkeys::Overlay> priv_key_{Empty{}};

 public:
  explicit PrivateKey(const tl_object_ptr<ton_api::PrivateKey> &pk);
  template <class T>
  PrivateKey(T key) : priv_key_(std::move(key)) {
  }
  PrivateKey() {
  }

  bool empty() const;

  PublicKey compute_public_key() const;
  PublicKeyHash compute_short_id() const;
  tl_object_ptr<ton_api::PrivateKey> tl() const;

  td::Result<std::unique_ptr<Decryptor>> create_decryptor() const;
  td::Result<td::actor::ActorOwn<DecryptorAsync>> create_decryptor_async() const;
};

}  // namespace ton
