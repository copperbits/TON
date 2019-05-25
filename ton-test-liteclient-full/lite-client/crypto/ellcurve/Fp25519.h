#pragma once
#include "common/refcnt.hpp"
#include "openssl/residue.h"

namespace ellcurve {
using namespace arith;

// returns 2^255-19
const Bignum& P25519();

// residue ring modulo P25519
td::Ref<ResidueRing> Fp25519();

}  // namespace ellcurve
