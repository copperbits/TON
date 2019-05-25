#pragma once

#include "td/utils/common.h"
#include "td/utils/Slice.h"

namespace td {

vector<string> get_word_transliterations(Slice word, bool allow_partial);

}  // namespace td
