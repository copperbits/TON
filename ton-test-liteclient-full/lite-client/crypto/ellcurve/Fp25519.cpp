#include "ellcurve/Fp25519.h"

namespace ellcurve {
using namespace arith;

const Bignum& P25519() {
  static const Bignum P25519 = (Bignum(1) << 255) - 19;
  return P25519;
}

td::Ref<ResidueRing> Fp25519() {
  static const td::Ref<ResidueRing> Fp25519(true, P25519());
  return Fp25519;
}
}  // namespace ellcurve
