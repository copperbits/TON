#include "td/utils/Slice.h"
#if TD_HAVE_OPENSSL
#include <openssl/crypto.h>
#endif

namespace td {

void MutableSlice::fill(char c) {
  std::memset(data(), c, size());
}
void MutableSlice::fill_zero() {
  fill(0);
}
void MutableSlice::fill_zero_secure() {
#if TD_HAVE_OPENSSL
  OPENSSL_cleanse(begin(), size());
#else
  volatile char *ptr = begin();
  for (size_t i = 0; i < size(); i++) {
    ptr[i] = 0;
  }
#endif
}

}  // namespace td
