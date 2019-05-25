#include "cp0.h"
#include "opctable.h"
#include "stackops.h"
#include "arithops.h"
#include "cellops.h"
#include "contops.h"
#include "dictops.h"
#include "debugops.h"
#include "tonops.h"

namespace vm {

const OpcodeTable* init_op_cp0() {
  static const OpcodeTable* static_op_cp0 = [] {
    auto op_cp0 = new OpcodeTable("TEST CODEPAGE", Codepage::test_cp);
    register_stack_ops(*op_cp0);         // stackops.cpp
    register_arith_ops(*op_cp0);         // arithops.cpp
    register_cell_ops(*op_cp0);          // cellops.cpp
    register_continuation_ops(*op_cp0);  // contops.cpp
    register_dictionary_ops(*op_cp0);    // dictops.cpp
    register_ton_ops(*op_cp0);           // tonops.cpp
    register_debug_ops(*op_cp0);         // debugops.cpp
    register_codepage_ops(*op_cp0);      // contops.cpp
    op_cp0->finalize()->register_table(Codepage::test_cp);
    return op_cp0;
  }();
  return static_op_cp0;
}

}  // namespace vm
