#pragma once

namespace vm {

class OpcodeTable;

extern bool vm_debug_enabled;

void register_debug_ops(OpcodeTable& cp0);

}  // namespace vm
