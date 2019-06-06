#include "Fift.h"
#include <vector>
namespace fift {
struct FiftOutput {
  SourceLookup source_lookup;
  std::string output;
};
td::Result<FiftOutput> mem_run_fift(std::string source, std::vector<std::string> args = {});
td::Result<td::Ref<vm::Cell>> compile_asm(td::Slice asm_code);
}  // namespace fift
