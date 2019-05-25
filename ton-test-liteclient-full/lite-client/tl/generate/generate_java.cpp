#include "tl_writer_java.h"

#include "td/tl/tl_config.h"
#include "td/tl/tl_generate.h"

#include <algorithm>
#include <string>

int main(int argc, char *argv[]) {
  if (argc < 5) {
    return 1;
  }

  std::string api_name = argv[1];
  std::string source = argv[2];
  std::string destination = argv[3];
  std::string package = argv[4];
  std::string package_name = package;
  std::replace(package_name.begin(), package_name.end(), '/', '.');
  destination += "/" + package + "/" + api_name + ".java";
  td::tl::write_tl_to_file(td::tl::read_tl_config_from_file(source), destination,
                           td::TD_TL_writer_java(api_name, package_name));
}
