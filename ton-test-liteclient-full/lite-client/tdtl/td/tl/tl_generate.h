#pragma once

#include "tl_config.h"
#include "tl_outputer.h"
#include "tl_writer.h"

#include <string>

namespace td {
namespace tl {

void write_tl(const tl_config &config, tl_outputer &out, const TL_writer &w);

tl_config read_tl_config_from_file(const std::string &file_name);
bool write_tl_to_file(const tl_config &config, const std::string &file_name, const TL_writer &w);

}  // namespace tl
}  // namespace td
