#pragma once

#include "td/utils/common.h"
#include "td/utils/SharedSlice.h"
#include "td/utils/Status.h"

#if TD_HAVE_OPENSSL

namespace td {

class Ed25519 {
 public:
  class PublicKey {
   public:
    static constexpr size_t LENGTH = 32;

    explicit PublicKey(SecureString octet_string);

    SecureString as_octet_string() const;

    Status verify_signature(Slice data, Slice signature) const;

   private:
    SecureString octet_string_;
  };

  class PrivateKey {
   public:
    static constexpr size_t LENGTH = 32;

    explicit PrivateKey(SecureString octet_string);

    SecureString as_octet_string() const;

    Result<PublicKey> get_public_key() const;

    Result<SecureString> sign(Slice data) const;

    Result<SecureString> as_pem(Slice password) const;

    static Result<PrivateKey> from_pem(Slice pem, Slice password);

   private:
    SecureString octet_string_;
  };

  static Result<PrivateKey> generate_private_key();

  static Result<SecureString> compute_shared_secret(const PublicKey &public_key, const PrivateKey &private_key);
};

}  // namespace td

#endif
