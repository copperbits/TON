#include "Fift.h"
namespace fift {
struct FiftOutput {
  SourceLookup source_lookup;
  std::string output;
};
td::Result<FiftOutput> mem_run_fift(std::string source);
td::Result<td::Ref<vm::Cell>> compile_asm(td::Slice asm_code);
}  // namespace fift
