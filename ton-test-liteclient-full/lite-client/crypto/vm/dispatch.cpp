#include "vm/dispatch.h"
#include "vm/excno.hpp"
#include <cassert>
#include <map>
#include <mutex>

namespace vm {

namespace {
std::mutex dispatch_tables_mutex;
std::map<int, const DispatchTable*> dispatch_tables;
}  // namespace

DummyDispatchTable dummy_dispatch_table;

bool DispatchTable::register_table(Codepage _cp, const DispatchTable& dt) {
  assert(dt.is_final());
  int cp = (int)_cp;
  if (cp < -0x8000 || cp >= 0x8000 || cp == -1) {
    return false;
  } else {
    std::lock_guard<std::mutex> guard(dispatch_tables_mutex);
    return dispatch_tables.emplace(cp, &dt).second;
  }
}

bool DispatchTable::register_table(Codepage cp) const {
  return register_table(cp, *this);
}

const DispatchTable* DispatchTable::get_table(Codepage cp) {
  return get_table((int)cp);
}

const DispatchTable* DispatchTable::get_table(int cp) {
  std::lock_guard<std::mutex> guard(dispatch_tables_mutex);
  auto entry = dispatch_tables.find(cp);
  return entry != dispatch_tables.end() ? entry->second : 0;
}

int DummyDispatchTable::dispatch(VmState* st, CellSlice& cs) const {
  throw VmError{Excno::inv_opcode, "empty opcode table"};
}

std::string DummyDispatchTable::dump_instr(CellSlice& cs) const {
  return "";
}

int DummyDispatchTable::instr_len(const CellSlice& cs) const {
  return 0;
}

}  // namespace vm
