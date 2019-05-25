#pragma once

#include <string>

namespace td {
namespace tl {

std::string get_file_contents(const std::string &file_name, const std::string &mode);

bool put_file_contents(const std::string &file_name, const std::string &mode, const std::string &contents);

std::string remove_documentation(const std::string &str);

}  // namespace tl
}  // namespace td
