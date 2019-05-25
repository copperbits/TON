#include "utils.h"
#include "words.h"
#include "td/utils/PathView.h"
#include "td/utils/filesystem.h"
#include "td/utils/port/path.h"
namespace fift {
namespace {
std::string fift_dir() {
  return td::PathView(td::realpath(__FILE__).move_as_ok()).parent_dir().str();
}
std::string load_source(std::string name, std::string dir = fift_dir()) {
  return td::read_file_str(dir + name).move_as_ok();
}
std::string load_Fift_fif() {
  return load_source("Fift.fif");
}
std::string load_Asm_fif() {
  return load_source("Asm.fif");
}

class MemoryFileLoader : public fift::FileLoader {
 public:
  td::Result<fift::FileLoader::File> read_file(td::CSlice filename) override {
    auto it = files_.find(filename);
    if (it == files_.end()) {
      return td::Status::Error();
    }
    fift::FileLoader::File res;
    res.data = std::move(it->second);
    res.path = it->first;
    return std::move(res);
  }

  td::Status write_file(td::CSlice filename, td::Slice data) override {
    files_[filename.str()] = data.str();
    return td::Status::OK();
  }

  void add_file(std::string path, std::string data) {
    files_[path] = std::move(data);
  }

 private:
  std::map<std::string, std::string, std::less<>> files_;
};
fift::SourceLookup create_source_lookup(std::string main, bool need_preamble = true, bool need_asm = true) {
  auto loader = std::make_unique<MemoryFileLoader>();
  loader->add_file("/main.fif", std::move(main));
  if (need_preamble) {
    loader->add_file("/Fift.fif", load_Fift_fif());
  }
  if (need_asm) {
    loader->add_file("/Asm.fif", load_Asm_fif());
  }
  auto res = fift::SourceLookup(std::move(loader));
  res.add_include_path("/");
  return res;
}

td::Result<fift::SourceLookup> run_fift(fift::SourceLookup source_lookup, std::ostream* stream,
                                        bool preload_fift = true) {
  fift::Fift::Config config;
  config.source_lookup = std::move(source_lookup);
  fift::init_words_common(config.dictionary);
  fift::init_words_vm(config.dictionary);
  fift::init_words_ton(config.dictionary);
  config.error_stream = stream;
  config.output_stream = stream;
  fift::Fift fift{std::move(config)};
  if (preload_fift) {
    TRY_STATUS(fift.interpret_file("Fift.fif", ""));
  }
  TRY_STATUS(fift.interpret_file("main.fif", ""));
  return std::move(fift.config().source_lookup);
}
}  // namespace
td::Result<FiftOutput> mem_run_fift(std::string source) {
  std::stringstream ss;
  TRY_RESULT(source_lookup, run_fift(create_source_lookup(source), &ss, true));
  FiftOutput res;
  res.source_lookup = std::move(source_lookup);
  res.output = ss.str();
  return std::move(res);
}
td::Result<td::Ref<vm::Cell>> compile_asm(td::Slice asm_code) {
  std::stringstream ss;
  TRY_RESULT(res, run_fift(create_source_lookup(PSTRING() << "\"Asm.fif\" include\n<{ " << asm_code
                                                          << "\n}>c boc>B \"res\" B>file"),
                           &ss));
  TRY_RESULT(boc, res.read_file("res"));
  return vm::std_boc_deserialize(std::move(boc.data));
}
}  // namespace fift
