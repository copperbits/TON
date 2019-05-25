#pragma once
#include <string>
#include "td/utils/Slice.h"
#include "td/utils/buffer.h"

namespace td {

std::size_t compute_base64_encoded_size(size_t bindata_size);
std::size_t buff_base64_encode(td::MutableSlice buffer, td::Slice raw, bool base64_url = false);
std::string str_base64_encode(std::string raw, bool base64_url = false);
std::string str_base64_encode(td::Slice raw, bool base64_url = false);

bool is_valid_base64(std::string encoded, bool allow_base64_url = true);
bool is_valid_base64(td::Slice encoded, bool allow_base64_url = true);
long decoded_base64_size(std::string encoded, bool allow_base64_url = true);
long decoded_base64_size(td::Slice encoded, bool allow_base64_url = true);

std::size_t buff_base64_decode(td::MutableSlice buffer, td::Slice data, bool allow_base64_url = true);
td::BufferSlice base64_decode(std::string encoded, bool allow_base64_url = true);
td::BufferSlice base64_decode(td::Slice encoded, bool allow_base64_url = true);
std::string str_base64_decode(std::string encoded, bool allow_base64_url = true);
std::string str_base64_decode(td::Slice encoded, bool allow_base64_url = true);

}  // namespace td
