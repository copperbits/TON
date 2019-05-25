#include "adnl-node-id.hpp"
#include "auto/tl/ton_api.hpp"
#include "td/utils/overloaded.h"
#include "tl-utils.hpp"
#include "adnl-encryptor.h"
#include "crypto/Ed25519.h"

namespace ton {

AdnlNodeIdShortImpl::AdnlNodeIdShortImpl(const tl_object_ptr<ton_api::adnl_id_Full> &value) {
  value_ = get_tl_object_sha256(value);
}

AdnlNodeIdFullImpl::AdnlNodeIdFullImpl(const tl_object_ptr<ton_api::adnl_id_Full> &id) {
  ton_api::downcast_call(
      *const_cast<ton_api::adnl_id_Full *>(id.get()),
      td::overloaded([&](const ton_api::adnl_id_ed25519 &obj) { this->pub_key_ = adnlid::AdnlEd25519Pub{obj}; },
                     [&](const ton_api::adnl_id_aes &obj) { this->pub_key_ = adnlid::AdnlAESPub{obj}; },
                     [&](const ton_api::adnl_id_unenc &obj) { this->pub_key_ = adnlid::AdnlUnencPub{obj}; },
                     [&](const ton_api::adnl_id_overlay &obj) { this->pub_key_ = adnlid::AdnlOverlayPub{obj}; }));
}

AdnlNodeIdShortImpl AdnlNodeIdFullImpl::compute_short_id() const {
  return AdnlNodeIdShortImpl{get_tl_object_sha256(tl())};
}

tl_object_ptr<ton_api::adnl_id_Full> AdnlNodeIdFullImpl::tl() const {
  tl_object_ptr<ton_api::adnl_id_Full> res;
  pub_key_.visit([&](auto &obj) { res = obj.tl(); });
  return res;
}

td::Result<std::unique_ptr<AdnlEncryptor>> AdnlNodeIdFullImpl::create_encryptor() const {
  return AdnlEncryptor::create(tl().get());
}

td::Result<td::actor::ActorOwn<AdnlEncryptorAsync>> AdnlNodeIdFullImpl::create_encryptor_async() const {
  return AdnlEncryptorAsync::create(tl().get());
}

bool AdnlNodeIdFullImpl::empty() const {
  return pub_key_.get_offset() == pub_key_.offset<Empty>();
}

namespace adnlid {

tl_object_ptr<ton_api::adnl_id_Full> AdnlEd25519Priv::pub_tl() const {
  td::Ed25519::PrivateKey pkey(as_slice(data_));
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

AdnlEd25519Pub AdnlEd25519Priv::pub() const {
  td::Ed25519::PrivateKey pkey(as_slice(data_));
  return AdnlEd25519Pub{pkey.get_public_key().move_as_ok()};
}

AdnlEd25519Priv AdnlEd25519Priv::random() {
  while (true) {
    auto key = td::Ed25519::generate_private_key();
    if (key.is_error()) {
      LOG(WARNING) << "failed to generate private key: " << key.move_as_error();
    }
    return AdnlEd25519Priv{key.move_as_ok()};
  }
}

AdnlEd25519Priv::AdnlEd25519Priv(td::Ed25519::PrivateKey key) {
  auto s = key.as_octet_string();
  CHECK(s.length() == 32);
  data_.as_slice().copy_from(td::Slice(s));
}

AdnlEd25519Pub::AdnlEd25519Pub(td::Ed25519::PublicKey key) {
  auto s = key.as_octet_string();
  CHECK(s.length() == 32);
  data_.as_slice().copy_from(td::Slice(s));
}

}  // namespace adnlid

AdnlNodePkImpl::AdnlNodePkImpl(const tl_object_ptr<ton_api::adnl_id_Pk> &id) {
  ton_api::downcast_call(
      *const_cast<ton_api::adnl_id_Pk *>(id.get()),
      td::overloaded([&](const ton_api::adnl_id_pk_ed25519 &obj) { this->priv_key_ = adnlid::AdnlEd25519Priv{obj}; },
                     [&](const ton_api::adnl_id_pk_aes &obj) { this->priv_key_ = adnlid::AdnlAESPriv{obj}; },
                     [&](const ton_api::adnl_id_pk_unenc &obj) { this->priv_key_ = adnlid::AdnlUnencPriv{obj}; },
                     [&](const ton_api::adnl_id_pk_overlay &obj) { this->priv_key_ = adnlid::AdnlOverlayPriv{obj}; }));
}

bool AdnlNodePkImpl::empty() const {
  return priv_key_.get_offset() == priv_key_.offset<Empty>();
}

AdnlNodeIdFullImpl AdnlNodePkImpl::compute_public_key() const {
  AdnlNodeIdFull res;
  priv_key_.visit([&](auto &obj) { res = obj.pub(); });
  return res;
}

AdnlNodeIdShortImpl AdnlNodePkImpl::compute_short_id() const {
  tl_object_ptr<ton_api::adnl_id_Full> res;
  priv_key_.visit([&](auto &obj) { res = obj.pub_tl(); });
  return AdnlNodeIdShortImpl{res};
}

tl_object_ptr<ton_api::adnl_id_Pk> AdnlNodePkImpl::tl() const {
  tl_object_ptr<ton_api::adnl_id_Pk> res;
  priv_key_.visit([&](auto &obj) { res = obj.tl(); });
  return res;
}

td::Result<std::unique_ptr<AdnlDecryptor>> AdnlNodePkImpl::create_decryptor() const {
  return AdnlDecryptor::create(tl().get());
}

td::Result<td::actor::ActorOwn<AdnlDecryptorAsync>> AdnlNodePkImpl::create_decryptor_async() const {
  return AdnlDecryptorAsync::create(tl().get());
}

}  // namespace ton
