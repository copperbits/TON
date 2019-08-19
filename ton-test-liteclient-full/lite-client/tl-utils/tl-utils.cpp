#include "tl-utils.hpp"
#include "tl/tl_object_store.h"
#include "auto/tl/ton_api.hpp"
#include "td/utils/tl_storers.h"
#include "td/utils/crypto.h"
#include "crypto/common/bitstring.h"

namespace ton {

td::BufferSlice serialize_tl_object(const ton_api::Object *T, bool boxed, td::BufferSlice &&suffix) {
  return serialize_tl_object(T, boxed, suffix.as_slice());
}

td::BufferSlice serialize_tl_object(const ton_api::Object *T, bool boxed, td::Slice suffix) {
  td::TlStorerCalcLength X;
  T->store(X);
  auto l = X.get_length() + (boxed ? 4 : 0);
  auto len = l + suffix.size();

  td::BufferSlice B(len);
  td::TlStorerUnsafe Y(B.as_slice().ubegin());
  if (boxed) {
    Y.store_binary(T->get_id());
  }
  T->store(Y);

  auto S = B.as_slice();
  S.remove_prefix(l);
  S.copy_from(suffix);

  return B;
}

td::BufferSlice serialize_tl_object(const ton_api::Object *T, bool boxed) {
  td::TlStorerCalcLength X;
  T->store(X);
  auto l = X.get_length() + (boxed ? 4 : 0);
  auto len = l;

  td::BufferSlice B(len);
  td::TlStorerUnsafe Y(B.as_slice().ubegin());
  if (boxed) {
    Y.store_binary(T->get_id());
  }
  T->store(Y);

  return B;
}

td::BufferSlice serialize_tl_object(const ton_api::Function *T, bool boxed) {
  CHECK(boxed);
  td::TlStorerCalcLength X;
  T->store(X);
  auto l = X.get_length();
  auto len = l;

  td::BufferSlice B(len);
  td::TlStorerUnsafe Y(B.as_slice().ubegin());

  T->store(Y);

  return B;
}

td::BufferSlice serialize_tl_object(const ton_api::Function *T, bool boxed, td::BufferSlice &&suffix) {
  return serialize_tl_object(T, boxed, suffix.as_slice());
}

td::BufferSlice serialize_tl_object(const ton_api::Function *T, bool boxed, td::Slice suffix) {
  CHECK(boxed);
  td::TlStorerCalcLength X;
  T->store(X);
  auto l = X.get_length();
  auto len = l + suffix.size();

  td::BufferSlice B(len);
  td::TlStorerUnsafe Y(B.as_slice().ubegin());

  T->store(Y);

  auto S = B.as_slice();
  S.remove_prefix(l);
  S.copy_from(suffix);

  return B;
}

td::UInt256 get_tl_object_sha256(const ton_api::Object *T) {
  td::TlStorerCalcLength X;
  T->store(X);
  auto len = X.get_length() + 4;

  td::BufferSlice B(len);
  td::TlStorerUnsafe Y(B.as_slice().ubegin());
  Y.store_binary(T->get_id());
  T->store(Y);

  td::UInt256 id256;
  td::sha256(B.as_slice(), id256.as_slice());

  return id256;
}

td::Bits256 get_tl_object_sha_bits256(const ton_api::Object *T) {
  td::TlStorerCalcLength X;
  T->store(X);
  auto len = X.get_length() + 4;

  td::BufferSlice B(len);
  td::TlStorerUnsafe Y(B.as_slice().ubegin());
  Y.store_binary(T->get_id());
  T->store(Y);

  td::Bits256 id256;
  td::sha256(B.as_slice(), id256.as_slice());

  return id256;
}

}  // namespace ton
