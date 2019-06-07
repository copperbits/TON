#pragma once

#include "encryptor.h"
#include "crypto/Ed25519.h"
#include "auto/tl/ton_api.h"
#include "tl-utils/tl-utils.hpp"

namespace ton {

class EncryptorNone : public Encryptor {
 public:
  td::Result<td::BufferSlice> encrypt(td::Slice data) override {
    return td::BufferSlice(data);
  }
  td::Status check_signature(td::Slice message, td::Slice signature) override {
    return td::Status::OK();
  }

  EncryptorNone() {
  }
};

class DecryptorNone : public Decryptor {
 public:
  td::Result<td::BufferSlice> decrypt(td::Slice data) override {
    return td::BufferSlice(data);
  }
  td::Result<td::BufferSlice> sign(td::Slice data) override {
    return td::BufferSlice("");
  }
  DecryptorNone() {
  }
};

class EncryptorFail : public Encryptor {
 public:
  td::Result<td::BufferSlice> encrypt(td::Slice data) override {
    return td::Status::Error("Fail encryptor");
  }
  td::Status check_signature(td::Slice message, td::Slice signature) override {
    return td::Status::Error("Fail encryptor");
  }

  EncryptorFail() {
  }
};

class DecryptorFail : public Decryptor {
 public:
  td::Result<td::BufferSlice> decrypt(td::Slice data) override {
    return td::Status::Error("Fail decryptor");
  }
  td::Result<td::BufferSlice> sign(td::Slice data) override {
    return td::Status::Error("Fail decryptor");
  }
  DecryptorFail() {
  }
};

class EncryptorEd25519 : public Encryptor {
 private:
  td::Ed25519::PublicKey pub_;

 public:
  td::Result<td::BufferSlice> encrypt(td::Slice data) override;
  td::Status check_signature(td::Slice message, td::Slice signature) override;

  EncryptorEd25519(td::UInt256 key) : pub_(as_slice(key)) {
  }
};

class DecryptorEd25519 : public Decryptor {
 private:
  td::Ed25519::PrivateKey pk_;

 public:
  td::Result<td::BufferSlice> decrypt(td::Slice data) override;
  td::Result<td::BufferSlice> sign(td::Slice data) override;
  DecryptorEd25519(td::UInt256 key) : pk_(as_slice(key)) {
  }
};

class EncryptorOverlay : public Encryptor {
 public:
  EncryptorOverlay() {
  }
  td::Result<td::BufferSlice> encrypt(td::Slice data) override {
    return td::Status::Error("overlay id can not be used for encryption");
  }
  td::Status check_signature(td::Slice message, td::Slice signature) override {
    auto R = fetch_tl_object<ton_api::dht_keyDescription>(message, false);
    if (R.is_error()) {
      return R.move_as_error();
    }
    if (signature.size() > 0) {
      return td::Status::Error("overlay signature must be empty");
    }
    auto G = R.move_as_ok();
    if (G->update_rule_->get_id() != ton_api::dht_updateRule_overlayNodes::ID) {
      return td::Status::Error("overlay update rule should be 'overlayNodes'");
    }
    if (G->signature_.size() > 0) {
      return td::Status::Error("overlay signature must be empty");
    }
    return td::Status::OK();
  }
};

class EncryptorAES : public Encryptor {
 private:
  td::UInt256 shared_secret_;

 public:
  td::Result<td::BufferSlice> encrypt(td::Slice data) override;
  td::Status check_signature(td::Slice message, td::Slice signature) override {
    return td::Status::Error("can no sign channel messages");
  }

  EncryptorAES(td::UInt256 shared_secret) : shared_secret_(shared_secret) {
  }
};

class DecryptorAES : public Decryptor {
 private:
  td::UInt256 shared_secret_;

 public:
  td::Result<td::BufferSlice> decrypt(td::Slice data) override;
  td::Result<td::BufferSlice> sign(td::Slice data) override {
    return td::Status::Error("can no sign channel messages");
  }
  DecryptorAES(td::UInt256 shared_secret) : shared_secret_(shared_secret) {
  }
};

}  // namespace ton
