#pragma once
#include <string>

namespace vm {

class VmState;
class CellSlice;

enum class Codepage { test_cp = 0 };

class DispatchTable {
 public:
  DispatchTable() = default;
  virtual ~DispatchTable() = default;
  virtual int dispatch(VmState* st, CellSlice& cs) const = 0;
  virtual std::string dump_instr(CellSlice& cs) const = 0;
  virtual int instr_len(const CellSlice& cs) const = 0;
  virtual DispatchTable* finalize() = 0;
  virtual bool is_final() const = 0;
  static const DispatchTable* get_table(Codepage cp);
  static const DispatchTable* get_table(int cp);
  static bool register_table(Codepage cp, const DispatchTable& dt);
  bool register_table(Codepage cp) const;
};

class DummyDispatchTable : public DispatchTable {
 public:
  DummyDispatchTable() : DispatchTable() {
  }
  ~DummyDispatchTable() override = default;
  int dispatch(VmState* st, CellSlice& cs) const override;
  std::string dump_instr(CellSlice& cs) const override;
  int instr_len(const CellSlice& cs) const override;
  DispatchTable* finalize() override {
    return this;
  }
  bool is_final() const override {
    return true;
  }
};

extern DummyDispatchTable dummy_dispatch_table;

}  // namespace vm
