#include "vm/dispatch.h"
#include "vm/continuation.h"

#include "vm/log.h"

namespace vm {

int Continuation::jump_w(VmState* st) & {
  return static_cast<const Continuation*>(this)->jump(st);
}

bool Continuation::has_c0() const {
  const ControlData* cont_data = get_cdata();
  return cont_data && cont_data->save.c[0].not_null();
}

ControlRegs& ControlRegs::operator^=(const ControlRegs& save) {
  for (int i = 0; i < creg_num; i++) {
    c[i] ^= save.c[i];
  }
  for (int i = 0; i < dreg_num; i++) {
    d[i] ^= save.d[i];
  }
  return *this;
}

ControlRegs& ControlRegs::operator^=(ControlRegs&& save) {
  for (int i = 0; i < creg_num; i++) {
    c[i] ^= std::move(save.c[i]);
  }
  for (int i = 0; i < dreg_num; i++) {
    d[i] ^= std::move(save.d[i]);
  }
  return *this;
}

ControlRegs& ControlRegs::operator&=(const ControlRegs& save) {
  for (int i = 0; i < creg_num; i++) {
    c[i] &= save.c[i].is_null();
  }
  for (int i = 0; i < dreg_num; i++) {
    d[i] &= save.d[i].is_null();
  }
  return *this;
}

int ExcQuitCont::jump(VmState* st) const & {
  int n = 0;
  try {
    n = st->get_stack().pop_smallint_range(0xffff);
  } catch (const VmError& vme) {
    n = vme.get_errno();
  }
  VM_LOG(st) << "default exception handler, terminating vm with exit code " << n;
  return ~n;
}

int PushIntCont::jump(VmState* st) const & {
  VM_LOG(st) << "execute implicit PUSH " << push_val << " (slow)";
  st->get_stack().push_smallint(push_val);
  return st->jump(next);
}

int PushIntCont::jump_w(VmState* st) & {
  VM_LOG(st) << "execute implicit PUSH " << push_val;
  st->get_stack().push_smallint(push_val);
  return st->jump(std::move(next));
}

int ArgContExt::jump(VmState* st) const & {
  st->adjust_cr(data.save);
  if (data.cp != -1) {
    st->force_cp(data.cp);
  }
  return ext->jump(st);
}

int ArgContExt::jump_w(VmState* st) & {
  st->adjust_cr(std::move(data.save));
  if (data.cp != -1) {
    st->force_cp(data.cp);
  }
  return st->jump_to(std::move(ext));
}

int RepeatCont::jump(VmState* st) const & {
  VM_LOG(st) << "repeat " << count << " more times (slow)\n";
  if (count <= 0) {
    return st->jump(after);
  }
  if (body->has_c0()) {
    return st->jump(body);
  }
  st->set_c0(Ref<RepeatCont>{true, body, after, count - 1});
  return st->jump(body);
}

int RepeatCont::jump_w(VmState* st) & {
  VM_LOG(st) << "repeat " << count << " more times\n";
  if (count <= 0) {
    body.clear();
    return st->jump(std::move(after));
  }
  if (body->has_c0()) {
    after.clear();
    return st->jump(std::move(body));
  }
  // optimization: since this is unique, reuse *this instead of creating new object
  --count;
  st->set_c0(Ref<RepeatCont>{this});
  return st->jump(body);
}

int VmState::repeat(Ref<Continuation> body, Ref<Continuation> after, long long count) {
  if (count <= 0) {
    body.clear();
    return jump(std::move(after));
  } else {
    return jump(Ref<RepeatCont>{true, std::move(body), std::move(after), count});
  }
}

int AgainCont::jump(VmState* st) const & {
  VM_LOG(st) << "again an infinite loop iteration (slow)\n";
  if (!body->has_c0()) {
    st->set_c0(Ref<AgainCont>{this});
  }
  return st->jump(body);
}

int AgainCont::jump_w(VmState* st) & {
  VM_LOG(st) << "again an infinite loop iteration\n";
  if (!body->has_c0()) {
    st->set_c0(Ref<AgainCont>{this});
    return st->jump(body);
  } else {
    return st->jump(std::move(body));
  }
}

int VmState::again(Ref<Continuation> body) {
  return jump(Ref<AgainCont>{true, std::move(body)});
}

int UntilCont::jump(VmState* st) const & {
  VM_LOG(st) << "until loop body end (slow)\n";
  if (st->get_stack().pop_bool()) {
    VM_LOG(st) << "until loop terminated\n";
    return st->jump(after);
  }
  if (!body->has_c0()) {
    st->set_c0(Ref<UntilCont>{this});
  }
  return st->jump(body);
}

int UntilCont::jump_w(VmState* st) & {
  VM_LOG(st) << "until loop body end\n";
  if (st->get_stack().pop_bool()) {
    VM_LOG(st) << "until loop terminated\n";
    body.clear();
    return st->jump(std::move(after));
  }
  if (!body->has_c0()) {
    st->set_c0(Ref<UntilCont>{this});
    return st->jump(body);
  } else {
    after.clear();
    return st->jump(std::move(body));
  }
}

int VmState::until(Ref<Continuation> body, Ref<Continuation> after) {
  if (!body->has_c0()) {
    set_c0(Ref<UntilCont>{true, body, std::move(after)});
  }
  return jump(std::move(body));
}

int WhileCont::jump(VmState* st) const & {
  if (chkcond) {
    VM_LOG(st) << "while loop condition end (slow)\n";
    if (!st->get_stack().pop_bool()) {
      VM_LOG(st) << "while loop terminated\n";
      return st->jump(after);
    }
    if (!body->has_c0()) {
      st->set_c0(Ref<WhileCont>{true, cond, body, after, false});
    }
    return st->jump(body);
  } else {
    VM_LOG(st) << "while loop body end (slow)\n";
    if (!cond->has_c0()) {
      st->set_c0(Ref<WhileCont>{true, cond, body, after, true});
    }
    return st->jump(cond);
  }
}

int WhileCont::jump_w(VmState* st) & {
  if (chkcond) {
    VM_LOG(st) << "while loop condition end\n";
    if (!st->get_stack().pop_bool()) {
      VM_LOG(st) << "while loop terminated\n";
      cond.clear();
      body.clear();
      return st->jump(std::move(after));
    }
    if (!body->has_c0()) {
      chkcond = false;  // re-use current object since we hold the unique pointer to it
      st->set_c0(Ref<WhileCont>{this});
      return st->jump(body);
    } else {
      cond.clear();
      after.clear();
      return st->jump(std::move(body));
    }
  } else {
    VM_LOG(st) << "while loop body end\n";
    if (!cond->has_c0()) {
      chkcond = true;  // re-use current object
      st->set_c0(Ref<WhileCont>{this});
      return st->jump(cond);
    } else {
      body.clear();
      after.clear();
      return st->jump(std::move(cond));
    }
  }
}

int VmState::loop_while(Ref<Continuation> cond, Ref<Continuation> body, Ref<Continuation> after) {
  if (!cond->has_c0()) {
    set_c0(Ref<WhileCont>{true, cond, std::move(body), std::move(after), true});
  }
  return jump(std::move(cond));
}

int OrdCont::jump(VmState* st) const & {
  st->adjust_cr(data.save);
  st->set_code(code, data.cp);
  return 0;
}

int OrdCont::jump_w(VmState* st) & {
  st->adjust_cr(std::move(data.save));
  st->set_code(std::move(code), data.cp);
  return 0;
}

void VmState::init_cregs(bool same_c3, bool push_0) {
  cr.set_c0(quit0);
  cr.set_c1(quit1);
  cr.set_c2(Ref<ExcQuitCont>{true});
  if (same_c3) {
    cr.set_c3(Ref<OrdCont>{true, code, cp});
    if (push_0) {
      VM_LOG(this) << "implicit PUSH 0 at start\n";
      get_stack().push_smallint(0);
    }
  } else {
    cr.set_c3(Ref<ExcQuitCont>{true});
  }
  if (cr.d[0].is_null() || cr.d[1].is_null() || cr.d[2].is_null()) {
    auto empty_cell = CellBuilder{}.finalize();
    for (int i = 0; i < ControlRegs::dreg_num; i++) {
      if (cr.d[i].is_null()) {
        cr.d[i] = empty_cell;
      }
    }
  }
}

VmState::VmState() : cp(-1), dispatch(&dummy_dispatch_table), quit0(true, 0), quit1(true, 1) {
  ensure_throw(init_cp(0));
  init_cregs();
}

VmState::VmState(Ref<CellSlice> _code)
    : code(std::move(_code)), cp(-1), dispatch(&dummy_dispatch_table), quit0(true, 0), quit1(true, 1) {
  ensure_throw(init_cp(0));
  init_cregs();
}

VmState::VmState(Ref<CellSlice> _code, Ref<Stack> _stack, int flags, Ref<Cell> _data, VmLog log)
    : code(std::move(_code))
    , stack(std::move(_stack))
    , cp(-1)
    , dispatch(&dummy_dispatch_table)
    , quit0(true, 0)
    , quit1(true, 1)
    , log(log) {
  ensure_throw(init_cp(0));
  set_c4(std::move(_data));
  init_cregs(flags & 1, flags & 2);
}

VmState::VmState(Ref<CellSlice> _code, Ref<Stack> _stack, const GasLimits& gas, int flags, Ref<Cell> _data, VmLog log)
    : code(std::move(_code))
    , stack(std::move(_stack))
    , cp(-1)
    , dispatch(&dummy_dispatch_table)
    , quit0(true, 0)
    , quit1(true, 1)
    , log(log)
    , gas(gas) {
  ensure_throw(init_cp(0));
  set_c4(std::move(_data));
  init_cregs(flags & 1, flags & 2);
}

VmState::VmState(Ref<Cell> code_cell, Ref<Stack> _stack, const GasLimits& gas, int flags, Ref<Cell> _data,
                 std::vector<Ref<Cell>> _libraries, VmLog log)
    : stack(std::move(_stack))
    , cp(-1)
    , dispatch(&dummy_dispatch_table)
    , quit0(true, 0)
    , quit1(true, 1)
    , log(log)
    , gas(gas)
    , libraries(std::move(_libraries)) {
  ensure_throw(init_cp(0));
  Guard guard(this);
  code = load_cell_slice_ref(std::move(code_cell));
  set_c4(std::move(_data));
  init_cregs(flags & 1, flags & 2);
}

bool VmState::init_cp(int new_cp) {
  const DispatchTable* dt = DispatchTable::get_table(new_cp);
  if (dt) {
    cp = new_cp;
    dispatch = dt;
    return true;
  } else {
    return false;
  }
}

bool VmState::set_cp(int new_cp) {
  return new_cp == cp || init_cp(new_cp);
}

void VmState::force_cp(int new_cp) {
  if (!set_cp(new_cp)) {
    throw VmError{Excno::inv_opcode, "unsupported codepage"};
  }
}

// simple call to a continuation cont
int VmState::call(Ref<Continuation> cont) {
  const ControlData* cont_data = cont->get_cdata();
  if (cont_data) {
    if (cont_data->save.c[0].not_null()) {
      // call reduces to a jump
      return jump(std::move(cont));
    }
    if (cont_data->stack.not_null() || cont_data->nargs >= 0) {
      // if cont has non-empty stack or expects fixed number of arguments, call is not simple
      return call(std::move(cont), -1, -1);
    }
    // create return continuation, to be stored into new c0
    Ref<OrdCont> ret = Ref<OrdCont>{true, std::move(code), cp};
    ret.unique_write().get_cdata()->save.set_c0(std::move(cr.c[0]));
    cr.set_c0(
        std::move(ret));  // set c0 to its final value before switching to cont; notice that cont.save.c0 is not set
    return jump_to(std::move(cont));
  }
  // create return continuation, to be stored into new c0
  Ref<OrdCont> ret = Ref<OrdCont>{true, std::move(code), cp};
  ret.unique_write().get_cdata()->save.set_c0(std::move(cr.c[0]));
  // general implementation of a simple call
  cr.set_c0(std::move(ret));  // set c0 to its final value before switching to cont; notice that cont.save.c0 is not set
  return jump_to(std::move(cont));
}

// call with parameters to continuation cont
int VmState::call(Ref<Continuation> cont, int pass_args, int ret_args) {
  const ControlData* cont_data = cont->get_cdata();
  if (cont_data) {
    if (cont_data->save.c[0].not_null()) {
      // call reduces to a jump
      return jump(std::move(cont), pass_args);
    }
    int depth = stack->depth();
    if (pass_args > depth || cont_data->nargs > depth) {
      throw VmError{Excno::stk_und, "stack underflow while calling a continuation: not enough arguments on stack"};
    }
    if (cont_data->nargs > pass_args && pass_args >= 0) {
      throw VmError{Excno::stk_und,
                    "stack underflow while calling a closure continuation: not enough arguments passed"};
    }
    auto old_c0 = std::move(cr.c[0]);
    // optimization(?): decrease refcnts of unused continuations in c[i] as early as possible
    preclear_cr(cont_data->save);
    // no exceptions should be thrown after this point
    int copy = cont_data->nargs, skip = 0;
    if (pass_args >= 0) {
      if (copy >= 0) {
        skip = pass_args - copy;
      } else {
        copy = pass_args;
      }
    }
    // copy=-1 : pass whole stack, else pass top `copy` elements, drop next `skip` elements.
    Ref<Stack> new_stk;
    if (cont_data->stack.not_null() && !cont_data->stack->is_empty()) {
      // `cont` already has a stack, create resulting stack from it
      if (copy < 0) {
        copy = stack->depth();
      }
      if (cont->is_unique()) {
        // optimization: avoid copying stack if we hold the only copy of `cont`
        new_stk = std::move(cont.unique_write().get_cdata()->stack);
      } else {
        new_stk = cont_data->stack;
      }
      new_stk.write().move_from_stack(get_stack(), copy);
      if (skip > 0) {
        get_stack().pop_many(skip);
      }
    } else if (copy >= 0) {
      new_stk = get_stack().split_top(copy, skip);
    } else {
      new_stk = std::move(stack);
      stack.clear();
    }
    // create return continuation using the remainder of current stack
    Ref<OrdCont> ret = Ref<OrdCont>{true, std::move(code), cp, std::move(stack), ret_args};
    ret.unique_write().get_cdata()->save.set_c0(std::move(old_c0));
    Ref<OrdCont> ord_cont = static_cast<Ref<OrdCont>>(cont);
    set_stack(std::move(new_stk));
    cr.set_c0(std::move(ret));  // ??? if codepage of code in ord_cont is unknown, will end up with incorrect c0
    return jump_to(std::move(cont));
  } else {
    // have no continuation data, situation is somewhat simpler
    int depth = stack->depth();
    if (pass_args > depth) {
      throw VmError{Excno::stk_und, "stack underflow while calling a continuation: not enough arguments on stack"};
    }
    // create new stack from the top `pass_args` elements of the current stack
    Ref<Stack> new_stk = (pass_args >= 0 ? get_stack().split_top(pass_args) : std::move(stack));
    // create return continuation using the remainder of the current stack
    Ref<OrdCont> ret = Ref<OrdCont>{true, std::move(code), cp, std::move(stack), ret_args};
    ret.unique_write().get_cdata()->save.set_c0(std::move(cr.c[0]));
    set_stack(std::move(new_stk));
    cr.set_c0(std::move(ret));  // ??? if codepage of code in ord_cont is unknown, will end up with incorrect c0
    return jump_to(std::move(cont));
  }
}

// simple jump to continuation cont
int VmState::jump(Ref<Continuation> cont) {
  const ControlData* cont_data = cont->get_cdata();
  if (cont_data && (cont_data->stack.not_null() || cont_data->nargs >= 0)) {
    // if cont has non-empty stack or expects fixed number of arguments, jump is not simple
    return jump(std::move(cont), -1);
  } else {
    return jump_to(std::move(cont));
  }
}

// general jump to continuation cont
int VmState::jump(Ref<Continuation> cont, int pass_args) {
  const ControlData* cont_data = cont->get_cdata();
  if (cont_data) {
    // first do the checks
    int depth = stack->depth();
    if (pass_args > depth || cont_data->nargs > depth) {
      throw VmError{Excno::stk_und, "stack underflow while jumping to a continuation: not enough arguments on stack"};
    }
    if (cont_data->nargs > pass_args && pass_args >= 0) {
      throw VmError{Excno::stk_und,
                    "stack underflow while jumping to closure continuation: not enough arguments passed"};
    }
    // optimization(?): decrease refcnts of unused continuations in c[i] as early as possible
    preclear_cr(cont_data->save);
    // no exceptions should be thrown after this point
    int copy = cont_data->nargs;
    if (pass_args >= 0 && copy < 0) {
      copy = pass_args;
    }
    // copy=-1 : pass whole stack, else pass top `copy` elements, drop the remainder.
    if (cont_data->stack.not_null() && !cont_data->stack->is_empty()) {
      // `cont` already has a stack, create resulting stack from it
      if (copy < 0) {
        copy = get_stack().depth();
      }
      Ref<Stack> new_stk;
      if (cont->is_unique()) {
        // optimization: avoid copying the stack if we hold the only copy of `cont`
        new_stk = std::move(cont.unique_write().get_cdata()->stack);
      } else {
        new_stk = cont_data->stack;
      }
      new_stk.write().move_from_stack(get_stack(), copy);
      set_stack(std::move(new_stk));
    } else {
      if (copy >= 0) {
        get_stack().drop_bottom(stack->depth() - copy);
      }
    }
    return jump_to(std::move(cont));
  } else {
    // have no continuation data, situation is somewhat simpler
    if (pass_args >= 0) {
      int depth = get_stack().depth();
      if (pass_args > depth) {
        throw VmError{Excno::stk_und, "stack underflow while jumping to a continuation: not enough arguments on stack"};
      }
      get_stack().drop_bottom(depth - pass_args);
    }
    return jump_to(std::move(cont));
  }
}

int VmState::ret() {
  Ref<Continuation> cont = quit0;
  cont.swap(cr.c[0]);
  return jump(std::move(cont));
}

int VmState::ret(int ret_args) {
  Ref<Continuation> cont = quit0;
  cont.swap(cr.c[0]);
  return jump(std::move(cont), ret_args);
}

int VmState::ret_alt() {
  Ref<Continuation> cont = quit1;
  cont.swap(cr.c[1]);
  return jump(std::move(cont));
}

int VmState::ret_alt(int ret_args) {
  Ref<Continuation> cont = quit1;
  cont.swap(cr.c[1]);
  return jump(std::move(cont), ret_args);
}

Ref<OrdCont> VmState::extract_cc(int save_cr, int stack_copy, int cc_args) {
  Ref<Stack> new_stk;
  if (stack_copy < 0 || stack_copy == stack->depth()) {
    new_stk = std::move(stack);
    stack.clear();
  } else if (stack_copy > 0) {
    stack->check_underflow(stack_copy);
    new_stk = get_stack().split_top(stack_copy);
  } else {
    new_stk = Ref<Stack>{true};
  }
  Ref<OrdCont> cc = Ref<OrdCont>{true, std::move(code), cp, std::move(stack), cc_args};
  stack = std::move(new_stk);
  if (save_cr & 7) {
    ControlData* cdata = cc.unique_write().get_cdata();
    if (save_cr & 1) {
      cdata->save.set_c0(std::move(cr.c[0]));
      cr.set_c0(quit0);
    }
    if (save_cr & 2) {
      cdata->save.set_c1(std::move(cr.c[1]));
      cr.set_c1(quit1);
    }
    if (save_cr & 4) {
      cdata->save.set_c2(std::move(cr.c[2]));
      // cr.set_c2(Ref<ExcQuitCont>{true});
    }
  }
  return cc;
}

int VmState::throw_exception(int excno) {
  Stack& stack_ref = get_stack();
  stack_ref.clear();
  stack_ref.push_smallint(0);
  stack_ref.push_smallint(excno);
  code.clear();
  consume_gas(exception_gas_price);
  return jump(get_c2());
}

int VmState::throw_exception(int excno, StackEntry&& arg) {
  Stack& stack_ref = get_stack();
  stack_ref.clear();
  stack_ref.push(std::move(arg));
  stack_ref.push_smallint(excno);
  code.clear();
  consume_gas(exception_gas_price);
  return jump(get_c2());
}

void GasLimits::gas_exception() const {
  throw VmNoGas{};
}

void GasLimits::set_limits(long long _max, long long _limit, long long _credit) {
  gas_max = _max;
  gas_limit = _limit;
  gas_credit = _credit;
  change_base(_limit + _credit);
}

void GasLimits::change_limit(long long _limit) {
  _limit = std::min(std::max(_limit, 0LL), gas_max);
  gas_credit = 0;
  gas_limit = _limit;
  change_base(_limit);
}

bool VmState::set_gas_limits(long long _max, long long _limit, long long _credit) {
  gas.set_limits(_max, _limit, _credit);
  return true;
}

void VmState::change_gas_limit(long long new_limit) {
  VM_LOG(this) << "changing gas limit to " << std::min(new_limit, gas.gas_max);
  gas.change_limit(new_limit);
}

int VmState::step() {
  assert(!code.is_null());
  //VM_LOG(st) << "stack:";  stack->dump(VM_LOG(st));
  //VM_LOG(st) << "; cr0.refcnt = " << get_c0()->get_refcnt() - 1 << std::endl;
  ++steps;
  if (code->size()) {
    return dispatch->dispatch(this, code.write());
  } else if (code->size_refs()) {
    VM_LOG(this) << "execute implicit JMPREF\n";
    Ref<Continuation> cont = Ref<OrdCont>{true, load_cell_slice_ref(code->prefetch_ref()), get_cp()};
    return jump(std::move(cont));
  } else {
    VM_LOG(this) << "execute implicit RET\n";
    return ret();
  }
}

int VmState::run() {
  int res;
  Guard guard(this);
  do {
    // LOG(INFO) << "[BS] data cells: " << DataCell::get_total_data_cells();
    try {
      res = step();
      gas.check();
    } catch (const VmError& vme) {
      VM_LOG(this) << "handling exception code " << vme.get_errno() << ": " << vme.get_msg();
      try {
        // LOG(INFO) << "[EX] data cells: " << DataCell::get_total_data_cells();
        ++steps;
        res = throw_exception(vme.get_errno());
      } catch (const VmError& vme2) {
        VM_LOG(this) << "exception " << vme2.get_errno() << " while handling exception: " << vme.get_msg();
        // LOG(INFO) << "[EXX] data cells: " << DataCell::get_total_data_cells();
        return ~vme2.get_errno();
      }
    } catch (VmNoGas vmoog) {
      ++steps;
      VM_LOG(this) << "unhandled out-of-gas exception: gas consumed=" << gas.gas_consumed()
                   << ", limit=" << gas.gas_limit;
      get_stack().clear();
      get_stack().push_smallint(gas.gas_consumed());
      return vmoog.get_errno();  // no ~ for unhandled exceptions (to make their faking impossible)
    }
  } while (!res);
  // LOG(INFO) << "[EN] data cells: " << DataCell::get_total_data_cells();
  return res;
}

ControlData* force_cdata(Ref<Continuation>& cont) {
  if (!cont->get_cdata()) {
    cont = Ref<ArgContExt>{true, cont};
    return cont.unique_write().get_cdata();
  } else {
    return cont.write().get_cdata();
  }
}

ControlRegs* force_cregs(Ref<Continuation>& cont) {
  return &force_cdata(cont)->save;
}

int run_vm_code(Ref<CellSlice> code, Ref<Stack>& stack, int flags, Ref<Cell>* data_ptr, VmLog log, long long* steps,
                GasLimits* gas_limits) {
  VmState vm{code, std::move(stack), gas_limits ? *gas_limits : GasLimits{}, flags, data_ptr ? *data_ptr : Ref<Cell>{},
             log};
  int res = vm.run();
  stack = vm.get_stack_ref();
  if (res == -1 && data_ptr) {
    *data_ptr = vm.get_c4();
  }
  if (steps) {
    *steps = vm.get_steps_count();
  }
  if (gas_limits) {
    *gas_limits = vm.get_gas_limits();
    LOG(INFO) << "steps: " << vm.get_steps_count() << " gas: used=" << gas_limits->gas_consumed()
              << ", max=" << gas_limits->gas_max << ", limit=" << gas_limits->gas_limit
              << ", credit=" << gas_limits->gas_credit;
  }
  if ((vm.get_log().log_mask & vm::VmLog::DumpStack) != 0) {
    VM_LOG(&vm) << "BEGIN_STACK_DUMP";
    for (int i = stack->depth(); i > 0; i--) {
      VM_LOG(&vm) << (*stack)[i - 1].to_string();
    }
    VM_LOG(&vm) << "END_STACK_DUMP";
  }

  return ~res;
}

int run_vm_code(Ref<CellSlice> code, Stack& stack, int flags, Ref<Cell>* data_ptr, VmLog log, long long* steps,
                GasLimits* gas_limits) {
  Ref<Stack> stk{true};
  stk.unique_write().set_contents(std::move(stack));
  stack.clear();
  int res = run_vm_code(code, stk, flags, data_ptr, log, steps, gas_limits);
  assert(stack.is_unique());
  if (stk.is_null()) {
    stack.clear();
  } else if (&(*stk) != &stack) {
    VmState* st = nullptr;
    if (stk->is_unique()) {
      VM_LOG(st) << "move resulting stack (" << stk->depth() << " entries)";
      stack.set_contents(std::move(stk.unique_write()));
    } else {
      VM_LOG(st) << "copying resulting stack (" << stk->depth() << " entries)";
      stack.set_contents(*stk);
    }
  }
  return res;
}

// may throw a dictionary exception; returns nullptr if library is not found in context
Ref<vm::Cell> VmState::load_library(td::ConstBitPtr hash) {
  return {};
}

void VmState::register_cell_load() {
  consume_gas(cell_load_gas_price);
}

void VmState::register_cell_create() {
  consume_gas(cell_create_gas_price);
}

td::BitArray<256> VmState::get_state_hash() const {
  // TODO: implement properly, by serializing the stack etc, and computing the Merkle hash
  td::BitArray<256> res;
  res.clear();
  return res;
}

td::BitArray<256> VmState::get_final_state_hash(int exit_code) const {
  // TODO: implement properly, by serializing the stack etc, and computing the Merkle hash
  td::BitArray<256> res;
  res.clear();
  return res;
}

}  // namespace vm
