#include "crypto/Ed25519.h"

#if TD_HAVE_OPENSSL

#include <openssl/opensslv.h>

#if OPENSSL_VERSION_NUMBER >= 0x10101000L

#include "td/utils/base64.h"
#include "td/utils/BigNum.h"
#include "td/utils/format.h"
#include "td/utils/logging.h"
#include "td/utils/misc.h"
#include "td/utils/ScopeGuard.h"

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

#else

#include "crypto/ellcurve/Ed25519.h"

#endif

namespace td {

Ed25519::PublicKey::PublicKey(Slice octet_string) : octet_string_(octet_string.str()) {
}

string Ed25519::PublicKey::as_octet_string() const {
  return octet_string_;
}

Ed25519::PrivateKey::PrivateKey(Slice octet_string) : octet_string_(octet_string.str()) {
}

string Ed25519::PrivateKey::as_octet_string() const {
  return octet_string_;
}

#if OPENSSL_VERSION_NUMBER >= 0x10101000L

namespace detail {

static const Slice PRIVATE_KEY_PREFIX = "\x30\x2e\x02\x01\x00\x30\x05\x06\x03\x2b\x65\x70\x04\x22\x04\x20";
static const Slice PUBLIC_KEY_PREFIX = "\x30\x2a\x30\x05\x06\x03\x2b\x65\x70\x03\x21\x00";

Result<string> X25519_key_from_PKEY(EVP_PKEY *pkey, bool is_private) {
  BIO *mem_bio = BIO_new(BIO_s_mem());
  SCOPE_EXIT {
    BIO_vfree(mem_bio);
  };
  if (is_private) {
    PEM_write_bio_PrivateKey(mem_bio, pkey, nullptr, nullptr, 0, nullptr, nullptr);
  } else {
    PEM_write_bio_PUBKEY(mem_bio, pkey);
  }

  constexpr int MAX_LINE_LENGTH = 100;
  char data[MAX_LINE_LENGTH + 1];
  int len = BIO_gets(mem_bio, data, sizeof(data));
  if (len == 0 || len >= MAX_LINE_LENGTH) {
    return Status::Error("Can't read first PEM string");
  }
  auto begin = trim(Slice(data, len));
  if (!begins_with(begin, "-----BEGIN") || !ends_with(begin, "-----")) {
    return Status::Error("Wrong first PEM line");
  }

  len = BIO_gets(mem_bio, data, sizeof(data));
  if (len == 0 || len >= MAX_LINE_LENGTH) {
    return Status::Error("Can't read second PEM string");
  }
  TRY_RESULT(key, base64_decode(trim(Slice(data, len))));
  auto prefix = is_private ? PRIVATE_KEY_PREFIX : PUBLIC_KEY_PREFIX;
  if (key.size() != prefix.size() + 32 || !begins_with(key, prefix)) {
    return Status::Error("Wrong key format");
  }

  len = BIO_gets(mem_bio, data, sizeof(data));
  if (len == 0 || len >= MAX_LINE_LENGTH) {
    return Status::Error("Can't read third PEM string");
  }

  auto end = trim(Slice(data, len));
  if (!begins_with(end, "-----END") || !ends_with(end, "-----")) {
    return Status::Error("Wrong third PEM line");
  }

  len = BIO_gets(mem_bio, data, sizeof(data));
  if (len != 0 || !BIO_eof(mem_bio)) {
    return Status::Error("Extra data after lastline");
  }
  return key.substr(prefix.size());
}

EVP_PKEY *X25519_key_to_PKEY(string key, bool is_private) {
  auto func = is_private ? &EVP_PKEY_new_raw_private_key : &EVP_PKEY_new_raw_public_key;
  return func(EVP_PKEY_ED25519, nullptr, Slice(key).ubegin(), key.size());
}

Result<string> X25519_pem_from_PKEY(EVP_PKEY *pkey, bool is_private, Slice password) {
  BIO *mem_bio = BIO_new(BIO_s_mem());
  SCOPE_EXIT {
    BIO_vfree(mem_bio);
  };
  if (is_private) {
    PEM_write_bio_PrivateKey(mem_bio, pkey, EVP_aes_256_cbc(), const_cast<unsigned char *>(password.ubegin()),
                             narrow_cast<int>(password.size()), nullptr, nullptr);
  } else {
    PEM_write_bio_PUBKEY(mem_bio, pkey);
  }
  char *data_ptr = nullptr;
  auto data_size = BIO_get_mem_data(mem_bio, &data_ptr);
  LOG(ERROR) << password;
  return std::string(data_ptr, data_size);
}

static int password_cb(char *buf, int size, int rwflag, void *u) {
  auto &password = *reinterpret_cast<Slice *>(u);
  auto password_size = narrow_cast<int>(password.size());
  if (size < password_size) {
    return -1;
  }
  if (rwflag == 0) {
    MutableSlice(buf, size).copy_from(password);
    LOG(ERROR) << "Use: " << Slice(buf, password_size);
  }
  return password_size;
}

EVP_PKEY *X25519_pem_to_PKEY(Slice pem, Slice password) {
  LOG(ERROR) << pem;
  LOG(ERROR) << password;
  BIO *mem_bio = BIO_new_mem_buf(pem.ubegin(), narrow_cast<int>(pem.size()));
  SCOPE_EXIT {
    BIO_vfree(mem_bio);
  };
  //EVP_PKEY *PEM_read_bio_PrivateKey(BIO *bp, EVP_PKEY **x, pem_password_cb *cb, void *u);

  return PEM_read_bio_PrivateKey(mem_bio, nullptr, password_cb, &password);
}

}  // namespace detail

Result<Ed25519::PrivateKey> Ed25519::generate_private_key() {
  EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_id(NID_ED25519, nullptr);
  if (pctx == nullptr) {
    return Status::Error("Can't create EVP_PKEY_CTX");
  }
  SCOPE_EXIT {
    EVP_PKEY_CTX_free(pctx);
  };

  if (EVP_PKEY_keygen_init(pctx) <= 0) {
    return Status::Error("Can't init keygen");
  }

  EVP_PKEY *pkey = nullptr;
  if (EVP_PKEY_keygen(pctx, &pkey) <= 0) {
    return Status::Error("Can't generate random private key");
  }
  SCOPE_EXIT {
    EVP_PKEY_free(pkey);
  };

  TRY_RESULT(private_key, detail::X25519_key_from_PKEY(pkey, true));
  return std::move(private_key);
}

Result<Ed25519::PublicKey> Ed25519::PrivateKey::get_public_key() const {
  auto pkey = detail::X25519_key_to_PKEY(octet_string_, true);
  if (pkey == nullptr) {
    return Status::Error("Can't import private key");
  }
  SCOPE_EXIT {
    EVP_PKEY_free(pkey);
  };

  TRY_RESULT(key, detail::X25519_key_from_PKEY(pkey, false));
  return Ed25519::PublicKey(key);
}

Result<string> Ed25519::PrivateKey::as_pem(Slice password) const {
  auto pkey = detail::X25519_key_to_PKEY(octet_string_, true);
  if (pkey == nullptr) {
    return Status::Error("Can't import private key");
  }
  SCOPE_EXIT {
    EVP_PKEY_free(pkey);
  };

  return detail::X25519_pem_from_PKEY(pkey, true, password);
}

Result<Ed25519::PrivateKey> Ed25519::PrivateKey::from_pem(Slice pem, Slice password) {
  auto pkey = detail::X25519_pem_to_PKEY(pem, password);
  if (pkey == nullptr) {
    return Status::Error("Can't import private key from pem");
  }
  TRY_RESULT(key, detail::X25519_key_from_PKEY(pkey, true));
  return Ed25519::PrivateKey(key);
}

Result<string> Ed25519::PrivateKey::sign(Slice data) const {
  auto pkey = detail::X25519_key_to_PKEY(octet_string_, true);
  if (pkey == nullptr) {
    return Status::Error("Can't import private key");
  }
  SCOPE_EXIT {
    EVP_PKEY_free(pkey);
  };

  EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
  if (md_ctx == nullptr) {
    return Status::Error("Can't create EVP_MD_CTX");
  }
  SCOPE_EXIT {
    EVP_MD_CTX_free(md_ctx);
  };

  if (EVP_DigestSignInit(md_ctx, nullptr, nullptr, nullptr, pkey) <= 0) {
    return Status::Error("Can't init DigestSign");
  }

  string res(64, '\0');
  size_t len = 64;
  if (EVP_DigestSign(md_ctx, MutableSlice(res).ubegin(), &len, data.ubegin(), data.size()) <= 0) {
    return Status::Error("Can't sign data");
  }
  return res;
}

Status Ed25519::PublicKey::verify_signature(Slice data, Slice signature) const {
  auto pkey = detail::X25519_key_to_PKEY(octet_string_, false);
  if (pkey == nullptr) {
    return Status::Error("Can't import public key");
  }
  SCOPE_EXIT {
    EVP_PKEY_free(pkey);
  };

  EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
  if (md_ctx == nullptr) {
    return Status::Error("Can't create EVP_MD_CTX");
  }
  SCOPE_EXIT {
    EVP_MD_CTX_free(md_ctx);
  };

  if (EVP_DigestVerifyInit(md_ctx, nullptr, nullptr, nullptr, pkey) <= 0) {
    return Status::Error("Can't init DigestVerify");
  }

  if (EVP_DigestVerify(md_ctx, signature.ubegin(), signature.size(), data.ubegin(), data.size())) {
    return Status::OK();
  }
  return Status::Error("Wrong signature");
}

Result<string> Ed25519::compute_shared_secret(const PublicKey &public_key, const PrivateKey &private_key) {
  BigNum p = BigNum::from_hex("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed").move_as_ok();
  auto public_y = public_key.as_octet_string();
  public_y[31] = static_cast<char>(public_y[31] & 127);
  BigNum y = BigNum::from_le_binary(public_y);
  BigNum y2 = y.clone();
  y += 1;
  y2 -= 1;

  BigNumContext context;

  BigNum::mod_sub(y2, p, y2, p, context);

  BigNum inverse_y_plus_1;
  BigNum::mod_inverse(inverse_y_plus_1, y2, p, context);

  BigNum u;
  BigNum::mod_mul(u, y, inverse_y_plus_1, p, context);

  auto pr_key = private_key.as_octet_string();
  unsigned char buf[64];
  SHA512(Slice(pr_key).ubegin(), 32, buf);
  buf[0] &= 248;
  buf[31] &= 127;
  buf[31] |= 64;

  auto pkey_private = EVP_PKEY_new_raw_private_key(EVP_PKEY_X25519, nullptr, buf, 32);
  if (pkey_private == nullptr) {
    return Status::Error("Can't import private key");
  }
  SCOPE_EXIT {
    EVP_PKEY_free(pkey_private);
  };
  // LOG(ERROR) << buffer_to_hex(Slice(buf, 32));

  auto pub_key = u.to_le_binary(32);
  auto pkey_public = EVP_PKEY_new_raw_public_key(EVP_PKEY_X25519, nullptr, Slice(pub_key).ubegin(), pub_key.size());
  if (pkey_public == nullptr) {
    return Status::Error("Can't import public key");
  }
  SCOPE_EXIT {
    EVP_PKEY_free(pkey_public);
  };
  // LOG(ERROR) << buffer_to_hex(pub_key);

  EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey_private, nullptr);
  if (ctx == nullptr) {
    return Status::Error("Can't create EVP_PKEY_CTX");
  }
  SCOPE_EXIT {
    EVP_PKEY_CTX_free(ctx);
  };

  if (EVP_PKEY_derive_init(ctx) <= 0) {
    return Status::Error("Can't init derive");
  }
  if (EVP_PKEY_derive_set_peer(ctx, pkey_public) <= 0) {
    return Status::Error("Can't init derive");
  }

  size_t result_len = 0;
  if (EVP_PKEY_derive(ctx, nullptr, &result_len) <= 0) {
    return Status::Error("Can't get result length");
  }
  if (result_len != 32) {
    return Status::Error("Unexpected result length");
  }

  string result(result_len, '\0');
  if (EVP_PKEY_derive(ctx, MutableSlice(result).ubegin(), &result_len) <= 0) {
    return Status::Error("Failed to compute shared secret");
  }
  return result;
}

#else

Result<Ed25519::PrivateKey> Ed25519::generate_private_key() {
  crypto::Ed25519::PrivateKey private_key;
  if (!private_key.random_private_key(true)) {
    return Status::Error("Can't generate random private key");
  }
  unsigned char private_key_buf[32];
  if (!private_key.export_private_key(private_key_buf)) {
    return Status::Error("Failed to export private key");
  }
  return PrivateKey(Slice(private_key_buf, 32));
}

Result<Ed25519::PublicKey> Ed25519::PrivateKey::get_public_key() const {
  crypto::Ed25519::PrivateKey private_key;
  if (!private_key.import_private_key(Slice(octet_string_).ubegin())) {
    return Status::Error("Bad private key");
  }
  unsigned char public_key[32];
  if (!private_key.get_public_key().export_public_key(public_key)) {
    return Status::Error("Failed to export public key");
  }
  return PublicKey(Slice(public_key, 32));
}

Result<string> Ed25519::PrivateKey::as_pem(Slice password) const {
  return Status::Error("Not supported");
}

Result<Ed25519::PrivateKey> Ed25519::PrivateKey::from_pem(Slice pem, Slice password) {
  return Status::Error("Not supported");
}

Result<string> Ed25519::PrivateKey::sign(Slice data) const {
  crypto::Ed25519::PrivateKey private_key;
  if (!private_key.import_private_key(Slice(octet_string_).ubegin())) {
    return Status::Error("Bad private key");
  }
  string signature(crypto::Ed25519::sign_bytes, '\0');
  if (!private_key.sign_message(signature, data)) {
    return Status::Error("Failed to sign message");
  }
  return std::move(signature);
}

Status Ed25519::PublicKey::verify_signature(Slice data, Slice signature) const {
  if (signature.size() != crypto::Ed25519::sign_bytes) {
    return Status::Error("Signature has invalid length");
  }

  crypto::Ed25519::PublicKey public_key;
  if (!public_key.import_public_key(Slice(octet_string_).ubegin())) {
    return Status::Error("Bad public key");
  }
  if (public_key.check_message_signature(signature, data)) {
    return Status::OK();
  }
  return Status::Error("Wrong signature");
}

Result<string> Ed25519::compute_shared_secret(const PublicKey &public_key, const PrivateKey &private_key) {
  crypto::Ed25519::PrivateKey tmp_private_key;
  if (!tmp_private_key.import_private_key(Slice(private_key.as_octet_string()).ubegin())) {
    return Status::Error("Bad private key");
  }
  crypto::Ed25519::PublicKey tmp_public_key;
  if (!tmp_public_key.import_public_key(Slice(public_key.as_octet_string()).ubegin())) {
    return Status::Error("Bad public key");
  }
  string shared_secret(32, '\0');
  if (!tmp_private_key.compute_shared_secret(shared_secret, tmp_public_key)) {
    return Status::Error("Failed to compute shared secret");
  }
  return std::move(shared_secret);
}

#endif

}  // namespace td

#endif
