#pragma once

#include "td/utils/common.h"
#include "td/utils/Slice.h"
#include "td/utils/Status.h"

#if TD_HAVE_OPENSSL

namespace td {

class Ed25519 {
 public:
  class PublicKey {
   public:
    static constexpr size_t LENGTH = 32;

    explicit PublicKey(Slice octet_string);

    string as_octet_string() const;

    Status verify_signature(Slice data, Slice signature) const;

   private:
    string octet_string_;
  };

  class PrivateKey {
   public:
    static constexpr size_t LENGTH = 32;

    explicit PrivateKey(Slice octet_string);

    string as_octet_string() const;

    Result<PublicKey> get_public_key() const;

    Result<string> sign(Slice data) const;

   private:
    string octet_string_;
  };

  static Result<PrivateKey> generate_private_key();

  static Result<string> compute_shared_secret(const PublicKey &public_key, const PrivateKey &private_key);
};

}  // namespace td

#endif
