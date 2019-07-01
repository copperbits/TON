#pragma once

#include "ton/ton-types.h"
#include "auto/tl/ton_api.h"
#include "keys/keys.hpp"

namespace ton {

namespace validator {

class ValidatorFullId : public PublicKey {
 public:
  NodeIdShort short_id() const;
  operator Ed25519_PublicKey() const;

  ValidatorFullId(PublicKey id) : PublicKey{std::move(id)} {
  }
  ValidatorFullId(Ed25519_PublicKey key) : PublicKey{pubkeys::Ed25519{key.as_bits256()}} {
  }
};

}  // namespace validator

}  // namespace ton
