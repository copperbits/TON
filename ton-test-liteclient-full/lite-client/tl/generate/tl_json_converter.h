#pragma once

#include <string>

#include "td/tl/tl_config.h"

namespace td {

void gen_json_converter(const tl::tl_config &config, const std::string &file_name, const std::string &tl_name);

}  // namespace td
