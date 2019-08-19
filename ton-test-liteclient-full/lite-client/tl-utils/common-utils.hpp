#pragma once
#include "tl/tl_object_parse.h"
#include "td/utils/tl_parsers.h"

#include "crypto/common/bitstring.h"

namespace ton {

template <class Tp>
td::BufferSlice serialize_tl_object(const tl_object_ptr<Tp> &T, bool boxed) {
  return serialize_tl_object(T.get(), boxed);
}

template <class Tp>
td::BufferSlice serialize_tl_object(const tl_object_ptr<Tp> &T, bool boxed, td::BufferSlice &&suffix) {
  return serialize_tl_object(T.get(), boxed, std::move(suffix));
}

template <class Tp>
td::BufferSlice serialize_tl_object(const tl_object_ptr<Tp> &T, bool boxed, td::Slice suffix) {
  return serialize_tl_object(T.get(), boxed, std::move(suffix));
}

template <class Tp>
td::UInt256 get_tl_object_sha256(const tl_object_ptr<Tp> &T) {
  return get_tl_object_sha256(T.get());
}

template <class Tp>
td::Bits256 get_tl_object_sha_bits256(const tl_object_ptr<Tp> &T) {
  return get_tl_object_sha_bits256(T.get());
}

template <typename T>
td::Result<tl_object_ptr<std::enable_if_t<std::is_constructible<T>::value, T>>> fetch_tl_object(td::BufferSlice data,
                                                                                                bool boxed) {
  td::TlParser p(data.as_slice());
  tl_object_ptr<T> R;
  if (boxed) {
    R = TlFetchBoxed<TlFetchObject<T>, T::ID>::parse(p);
  } else {
    R = move_tl_object_as<T>(T::fetch(p));
  }
  p.fetch_end();
  if (p.get_status().is_ok()) {
    return std::move(R);
  } else {
    return p.get_status();
  }
}

template <typename T>
td::Result<tl_object_ptr<std::enable_if_t<!std::is_constructible<T>::value, T>>> fetch_tl_object(td::BufferSlice data,
                                                                                                 bool boxed) {
  CHECK(boxed);
  td::TlParser p(data.as_slice());
  tl_object_ptr<T> R;
  R = move_tl_object_as<T>(T::fetch(p));
  p.fetch_end();
  if (p.get_status().is_ok()) {
    return std::move(R);
  } else {
    return p.get_status();
  }
}

template <typename T>
td::Result<tl_object_ptr<std::enable_if_t<std::is_constructible<T>::value, T>>> fetch_tl_object(td::Slice data,
                                                                                                bool boxed) {
  td::TlParser p(data);
  tl_object_ptr<T> R;
  if (boxed) {
    R = TlFetchBoxed<TlFetchObject<T>, T::ID>::parse(p);
  } else {
    R = move_tl_object_as<T>(T::fetch(p));
  }
  p.fetch_end();
  if (p.get_status().is_ok()) {
    return std::move(R);
  } else {
    return p.get_status();
  }
}

template <typename T>
td::Result<tl_object_ptr<std::enable_if_t<!std::is_constructible<T>::value, T>>> fetch_tl_object(td::Slice data,
                                                                                                 bool boxed) {
  CHECK(boxed);
  td::TlParser p(data);
  tl_object_ptr<T> R;
  R = move_tl_object_as<T>(T::fetch(p));
  p.fetch_end();
  if (p.get_status().is_ok()) {
    return std::move(R);
  } else {
    return p.get_status();
  }
}

template <typename T>
td::Result<tl_object_ptr<std::enable_if_t<std::is_constructible<T>::value, T>>> fetch_tl_prefix(td::BufferSlice &data,
                                                                                                bool boxed) {
  td::TlParser p(data.as_slice());
  tl_object_ptr<T> R;
  if (boxed) {
    R = TlFetchBoxed<TlFetchObject<T>, T::ID>::parse(p);
  } else {
    R = move_tl_object_as<T>(T::fetch(p));
  }
  if (p.get_status().is_ok()) {
    data.confirm_read(data.size() - p.get_left_len());
    return std::move(R);
  } else {
    return p.get_status();
  }
}

template <typename T>
td::Result<tl_object_ptr<std::enable_if_t<!std::is_constructible<T>::value, T>>> fetch_tl_prefix(td::BufferSlice &data,
                                                                                                 bool boxed) {
  CHECK(boxed);
  td::TlParser p(data.as_slice());
  tl_object_ptr<T> R;
  R = move_tl_object_as<T>(T::fetch(p));
  if (p.get_status().is_ok()) {
    data.confirm_read(data.size() - p.get_left_len());
    return std::move(R);
  } else {
    return p.get_status();
  }
}

template <class T>
tl_object_ptr<T> clone_tl_object(const tl_object_ptr<T> &obj) {
  auto B = serialize_tl_object(obj, true);
  auto R = fetch_tl_object<T>(std::move(B), true);
  CHECK(R.is_ok());
  return R.move_as_ok();
}

template <class T>
td::Result<typename T::ReturnType> fetch_result(td::Slice message, bool check_end = true) {
  td::TlParser parser(message);
  auto result = T::fetch_result(parser);

  if (check_end) {
    parser.fetch_end();
  }
  const char *error = parser.get_error();
  if (error != nullptr) {
    LOG(ERROR) << "Can't parse: " << td::format::as_hex_dump<4>(message);
    return td::Status::Error(500, td::Slice(error));
  }

  return std::move(result);
}

template <class T>
td::Result<typename T::ReturnType> fetch_result(const td::BufferSlice &message, bool check_end = true) {
  td::TlBufferParser parser(&message);
  auto result = T::fetch_result(parser);

  if (check_end) {
    parser.fetch_end();
  }
  const char *error = parser.get_error();
  if (error != nullptr) {
    LOG(ERROR) << "Can't parse: " << td::format::as_hex_dump<4>(message.as_slice());
    return td::Status::Error(500, td::Slice(error));
  }

  return std::move(result);
}

}  // namespace ton
