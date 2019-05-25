#pragma once

namespace vm {

class OpcodeTable;

void register_continuation_ops(OpcodeTable& cp0);
void register_codepage_ops(OpcodeTable& cp0);

}  // namespace vm
