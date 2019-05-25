#include "td/utils/crypto.h"
#include "td/utils/overloaded.h"

#include "adnl-encryptor.h"
#include "adnl-encryptor.hpp"
#include "auto/tl/ton_api.hpp"

#include "utils-status.hpp"
#include "adnl-node-id.hpp"
#include "adnl-error.h"

namespace ton {

td::Result<std::unique_ptr<AdnlEncryptor>> AdnlEncryptor::create(const ton_api::adnl_id_Full *id) {
  td::Result<std::unique_ptr<AdnlEncryptor>> res;
  ton_api::downcast_call(
      *const_cast<ton_api::adnl_id_Full *>(id),
      td::overloaded(
          [&](const ton_api::adnl_id_unenc &obj) { res = std::make_unique<AdnlEncryptorNone>(); },
          [&](const ton_api::adnl_id_ed25519 &obj) { res = std::make_unique<AdnlEncryptorEd25519>(obj.key_); },
          [&](const ton_api::adnl_id_overlay &obj) { res = std::make_unique<AdnlEncryptorOverlay>(); },
          [&](const ton_api::adnl_id_aes &obj) { res = std::make_unique<AdnlEncryptorAES>(obj.key_); }));
  return res;
}

td::Result<std::unique_ptr<AdnlDecryptor>> AdnlDecryptor::create(const ton_api::adnl_id_Pk *id) {
  td::Result<std::unique_ptr<AdnlDecryptor>> res;
  ton_api::downcast_call(
      *const_cast<ton_api::adnl_id_Pk *>(id),
      td::overloaded(
          [&](const ton_api::adnl_id_pk_unenc &obj) { res = std::make_unique<AdnlDecryptorNone>(); },
          [&](const ton_api::adnl_id_pk_ed25519 &obj) { res = std::make_unique<AdnlDecryptorEd25519>(obj.key_); },
          [&](const ton_api::adnl_id_pk_overlay &obj) { res = std::make_unique<AdnlDecryptorFail>(); },
          [&](const ton_api::adnl_id_pk_aes &obj) { res = std::make_unique<AdnlDecryptorAES>(obj.key_); }));
  return res;
}

td::Result<td::BufferSlice> AdnlEncryptorEd25519::encrypt(td::Slice data) {
  TRY_RESULT_PREFIX(pk, td::Ed25519::generate_private_key(), "failed to generate private key: ");
  TRY_RESULT_PREFIX(pubkey, pk.get_public_key(), "failed to get public key from private: ");
  auto pubkey_str = pubkey.as_octet_string();

  td::BufferSlice msg(pubkey_str.size() + 32 + data.size());
  td::MutableSlice slice = msg.as_slice();
  slice.copy_from(pubkey_str);
  slice.remove_prefix(pubkey_str.size());

  TRY_RESULT_PREFIX(shared_secret, td::Ed25519::compute_shared_secret(pub_, pk), "failed to compute shared secret: ");

  td::MutableSlice digest = slice.substr(0, 32);
  slice.remove_prefix(32);
  td::sha256(data, digest);

  td::UInt256 key;
  std::memcpy(key.raw, td::Slice(shared_secret).ubegin(), 16);
  std::memcpy(key.raw + 16, digest.ubegin() + 16, 16);

  td::UInt128 iv;
  std::memcpy(iv.raw, digest.ubegin(), 4);
  std::memcpy(iv.raw + 4, td::Slice(shared_secret).ubegin() + 20, 12);

  td::AesCtrState ctr;
  ctr.init(key, iv);
  ctr.encrypt(data, slice);

  return std::move(msg);
}

td::Status AdnlEncryptorEd25519::check_signature(td::Slice message, td::Slice signature) {
  return td::status_prefix(pub_.verify_signature(message, signature), "bad signature: ");
}

td::Result<td::BufferSlice> AdnlDecryptorEd25519::decrypt(td::Slice data) {
  if (data.size() < td::Ed25519::PublicKey::LENGTH + 32) {
    return td::Status::Error(AdnlError::protoviolation, "message is too short");
  }

  td::Slice pub = data.substr(0, td::Ed25519::PublicKey::LENGTH);
  data.remove_prefix(td::Ed25519::PublicKey::LENGTH);

  td::Slice digest = data.substr(0, 32);
  data.remove_prefix(32);

  TRY_RESULT_PREFIX(shared_secret, td::Ed25519::compute_shared_secret(td::Ed25519::PublicKey(pub), pk_),
                    "failed to generate shared secret: ");

  td::UInt256 key;
  std::memcpy(key.raw, td::Slice(shared_secret).ubegin(), 16);
  std::memcpy(key.raw + 16, digest.ubegin() + 16, 16);

  td::UInt128 iv;
  std::memcpy(iv.raw, digest.ubegin(), 4);
  std::memcpy(iv.raw + 4, td::Slice(shared_secret).ubegin() + 20, 12);

  td::BufferSlice res(data.size());

  td::AesCtrState ctr;
  ctr.init(key, iv);
  ctr.encrypt(data, res.as_slice());

  td::UInt256 real_digest;
  td::sha256(res.as_slice(), as_slice(real_digest));

  if (as_slice(real_digest) != digest) {
    return td::Status::Error(AdnlError::protoviolation, "sha256 mismatch after decryption");
  }

  return std::move(res);
}

td::Result<td::BufferSlice> AdnlDecryptorEd25519::sign(td::Slice data) {
  TRY_RESULT_PREFIX(signature, pk_.sign(data), "failed to sign: ");
  return td::BufferSlice(signature);
}

td::Result<td::BufferSlice> AdnlEncryptorAES::encrypt(td::Slice data) {
  td::BufferSlice msg(32 + data.size());
  td::MutableSlice slice = msg.as_slice();

  td::MutableSlice digest = slice.substr(0, 32);
  slice.remove_prefix(32);
  td::sha256(data, digest);

  td::UInt256 key;
  std::memcpy(key.raw, shared_secret_.raw, 16);
  std::memcpy(key.raw + 16, digest.ubegin() + 16, 16);

  td::UInt128 iv;
  std::memcpy(iv.raw, digest.ubegin(), 4);
  std::memcpy(iv.raw + 4, shared_secret_.raw + 20, 12);

  td::AesCtrState ctr;
  ctr.init(key, iv);
  ctr.encrypt(data, slice);

  return std::move(msg);
}

td::Result<td::BufferSlice> AdnlDecryptorAES::decrypt(td::Slice data) {
  if (data.size() < 32) {
    return td::Status::Error(AdnlError::protoviolation, "message is too short");
  }

  td::Slice digest = data.substr(0, 32);
  data.remove_prefix(32);

  td::UInt256 key;
  std::memcpy(key.raw, shared_secret_.raw, 16);
  std::memcpy(key.raw + 16, digest.ubegin() + 16, 16);

  td::UInt128 iv;
  std::memcpy(iv.raw, digest.ubegin(), 4);
  std::memcpy(iv.raw + 4, shared_secret_.raw + 20, 12);

  td::BufferSlice res(data.size());

  td::AesCtrState ctr;
  ctr.init(key, iv);
  ctr.encrypt(data, res.as_slice());

  td::UInt256 real_digest;
  td::sha256(res.as_slice(), as_slice(real_digest));

  if (as_slice(real_digest) != digest) {
    return td::Status::Error(AdnlError::protoviolation, "sha256 mismatch after decryption");
  }

  return std::move(res);
}

template <class T>
tl_object_ptr<ton_api::adnl_id_Full> get_public_key(T &pk) {
  UNREACHABLE();
}

tl_object_ptr<ton_api::adnl_id_Full> get_public_key(ton_api::adnl_id_pk_unenc &pk) {
  return create_tl_object<ton_api::adnl_id_unenc>(pk.data_.clone());
}

tl_object_ptr<ton_api::adnl_id_Full> get_public_key(ton_api::adnl_id_pk_ed25519 &pk) {
  td::Ed25519::PrivateKey pkey(as_slice(pk.key_));
  auto r_public_key = pkey.get_public_key();
  if (r_public_key.is_error()) {
    return nullptr;
  } else {
    auto public_key = r_public_key.ok().as_octet_string();
    td::UInt256 X;
    as_slice(X).copy_from(public_key);
    return create_tl_object<ton_api::adnl_id_ed25519>(X);
  }
}

AdnlNodeIdFull get_public_key(const tl_object_ptr<ton_api::adnl_id_Pk> &pk) {
  tl_object_ptr<ton_api::adnl_id_Full> res;
  ton_api::downcast_call(*pk.get(), [&](auto &obj) { res = get_public_key(obj); });
  return AdnlNodeIdFull{res};
}

AdnlNodePk adnl_generate_random_pk() {
  td::Result<td::Ed25519::PrivateKey> r_pkey;
  td::uint32 att = 0;
  while (true) {
    CHECK(att <= 10);
    r_pkey = td::Ed25519::generate_private_key();
    if (r_pkey.is_ok()) {
      break;
    }
    att++;
  }

  auto private_key = r_pkey.ok().as_octet_string();
  td::UInt256 pk;
  as_slice(pk).copy_from(private_key);
  return AdnlNodePk{create_tl_object<ton_api::adnl_id_pk_ed25519>(pk)};
}

std::vector<td::Result<td::BufferSlice>> AdnlDecryptor::sign_batch(std::vector<td::Slice> data) {
  std::vector<td::Result<td::BufferSlice>> r;
  r.resize(data.size());
  for (size_t i = 0; i < data.size(); i++) {
    r[i] = sign(data[i]);
  }
  return r;
}

}  // namespace ton
