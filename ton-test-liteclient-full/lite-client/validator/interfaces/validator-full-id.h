#pragma once

#include "ton/ton-types.h"
#include "auto/tl/ton_api.h"
#include "adnl/adnl-node-id.hpp"

namespace ton {

namespace validator {

class ValidatorFullId : public AdnlNodeIdFullImpl {
 public:
  NodeIdShort short_id() const;
  operator Ed25519_PublicKey() const;

  ValidatorFullId(AdnlNodeIdFull id);
  ValidatorFullId(Ed25519_PublicKey key);
};

}  // namespace validator

}  // namespace ton
