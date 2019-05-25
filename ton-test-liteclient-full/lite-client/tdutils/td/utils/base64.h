#pragma once

#include "td/utils/common.h"
#include "td/utils/Slice.h"
#include "td/utils/Status.h"

namespace td {

string base64_encode(Slice input);
Result<string> base64_decode(Slice base64);

string base64url_encode(Slice input);
Result<string> base64url_decode(Slice base64);

bool is_base64(Slice input);
bool is_base64url(Slice input);

string base64_filter(Slice input);

}  // namespace td
