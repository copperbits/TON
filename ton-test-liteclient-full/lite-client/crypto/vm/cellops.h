#pragma once
#include "vm/cellslice.h"

namespace vm {

class OpcodeTable;

void register_cell_ops(OpcodeTable &cp0);

std::string dump_push_ref(CellSlice &cs, unsigned args, int pfx_bits, std::string name);
int compute_len_push_ref(const CellSlice &cs, unsigned args, int pfx_bits);

// TODO: move these functions to a better place, such as cell/Cell.h or cell/CellSlice.h
// If can_be_special is not null, than it is allowed to load special cell
// Flag whether loaded cell is actually special will be stored into can_be_special
CellSlice load_cell_slice(const Ref<Cell> &cell, bool *can_be_special = nullptr);
Ref<CellSlice> load_cell_slice_ref(const Ref<Cell> &cell, bool *can_be_special = nullptr);
void print_load_cell(std::ostream &os, Ref<Cell> cell, int indent = 0, bool can_be_special = true);

}  // namespace vm
