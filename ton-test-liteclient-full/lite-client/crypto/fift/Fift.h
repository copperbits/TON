#pragma once

#include "SourceLookup.h"
#include "vm/db/TonDb.h"
#include "Dictionary.h"

#include "td/utils/Status.h"

namespace fift {
struct IntCtx;
int funny_interpret_loop(IntCtx& ctx);

struct Fift {
 public:
  struct Config {
    fift::SourceLookup source_lookup;
    vm::TonDb ton_db;
    fift::Dictionary dictionary;
    std::ostream* output_stream{&std::cout};
    std::ostream* error_stream{&std::cerr};
  };
  // Fift must own ton_db and dictionary, no concurrent access is allowed
  explicit Fift(Config config);

  td::Result<int> interpret_file(std::string fname, std::string current_dir, bool interactive = false);
  td::Result<int> interpret_istream(std::istream& stream, std::string current_dir, bool interactive = true);

  Config& config();

 private:
  Config config_;

  td::Result<int> do_interpret(IntCtx& ctx);
};
}  // namespace fift
