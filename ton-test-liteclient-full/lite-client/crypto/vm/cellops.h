#pragma once
#include "vm/cellslice.h"

namespace vm {

class OpcodeTable;

void register_cell_ops(OpcodeTable &cp0);

std::string dump_push_ref(CellSlice &cs, unsigned args, int pfx_bits, std::string name);
int compute_len_push_ref(const CellSlice &cs, unsigned args, int pfx_bits);

}  // namespace vm
