#include "tl_writer_cpp.h"
#include "tl_writer_h.h"
#include "tl_writer_hpp.h"
#include "tl_writer_jni_h.h"
#include "tl_writer_jni_cpp.h"
#include "tl_json_converter.h"

#include "td/tl/tl_config.h"
#include "td/tl/tl_generate.h"

#include <string>
#include <vector>

template <class WriterCpp = td::TD_TL_writer_cpp, class WriterH = td::TD_TL_writer_h,
          class WriterHpp = td::TD_TL_writer_hpp>
static void generate_cpp(const std::string &directory, const std::string &tl_name, const std::string &string_type,
                         const std::string &bytes_type, const std::vector<std::string> &ext_cpp_includes,
                         const std::vector<std::string> &ext_h_includes) {
  std::string path = directory + "/" + tl_name;
  td::tl::tl_config config = td::tl::read_tl_config_from_file("scheme/" + tl_name + ".tlo");
  td::tl::write_tl_to_file(config, path + ".cpp", WriterCpp(tl_name, string_type, bytes_type, ext_cpp_includes));
  td::tl::write_tl_to_file(config, path + ".h", WriterH(tl_name, string_type, bytes_type, ext_h_includes));
  td::tl::write_tl_to_file(config, path + ".hpp", WriterHpp(tl_name, string_type, bytes_type));
}

int main() {
  generate_cpp("auto/tl", "ton_api", "std::string", "td::BufferSlice",
               {"\"tl/tl_object_parse.h\"", "\"tl/tl_object_store.h\"", "\"td/utils/int_types.h\"",
                "\"crypto/common/bitstring.h\""},
               {"<string>", "\"td/utils/buffer.h\"", "\"crypto/common/bitstring.h\""});
  td::gen_json_converter(td::tl::read_tl_config_from_file("scheme/ton_api.tlo"), "auto/tl/ton_api_json", "ton_api");

#ifdef TONLIB_ENABLE_JNI
  generate_cpp<td::TD_TL_writer_jni_cpp, td::TD_TL_writer_jni_h>(
      "auto/tl", "tonlib_api", "std::string", "std::string",
      {"\"tl/tl_jni_object.h\"", "\"tl/tl_object_store.h\"", "\"td/utils/int_types.h\" "}, {"<string>"});
#else
  generate_cpp<>("auto/tl", "tonlib_api", "std::string", "std::string",
                 {"\"tl/tl_object_parse.h\"", "\"tl/tl_object_store.h\"", "\"td/utils/int_types.h\""}, {"<string>"});
#endif
  td::gen_json_converter(td::tl::read_tl_config_from_file("scheme/tonlib_api.tlo"), "auto/tl/tonlib_api_json",
                         "tonlib_api");
}
