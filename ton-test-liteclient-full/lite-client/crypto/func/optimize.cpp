#include "func.h"

namespace funC {

/*
 * 
 *   PEEPHOLE OPTIMIZER
 * 
 */

void Optimizer::set_code(AsmOpConsList code) {
  code_ = std::move(code);
  unpack();
}

void Optimizer::unpack() {
  int i = 0, j = 0;
  for (AsmOpCons *p = code_.get(); p && i < n; p = p->cdr.get(), ++j) {
    if (p->car->is_very_custom()) {
      break;
    }
    if (p->car->is_comment()) {
      continue;
    }
    op_cons_[i] = p;
    op_[i] = std::move(p->car);
    offs_[i] = j;
    ++i;
  }
  l_ = i;
  indent_ = (i ? op_[0]->indent : 0);
}

void Optimizer::pack() {
  for (int i = 0; i < l_; i++) {
    op_cons_[i]->car = std::move(op_[i]);
    op_cons_[i] = nullptr;
  }
  l_ = 0;
}

void Optimizer::apply() {
  if (!p_ && !q_) {
    return;
  }
  assert(p_ > 0 && p_ <= l_ && q_ >= 0 && q_ <= n && l_ <= n);
  for (int i = p_; i < l_; i++) {
    assert(op_[i]);
    op_cons_[i]->car = std::move(op_[i]);
    op_cons_[i] = nullptr;
  }
  for (int c = offs_[p_ - 1]; c >= 0; --c) {
    code_ = std::move(code_->cdr);
  }
  for (int j = q_ - 1; j >= 0; j--) {
    assert(oq_[j]);
    oq_[j]->indent = indent_;
    code_ = AsmOpCons::cons(std::move(oq_[j]), std::move(code_));
  }
  l_ = 0;
}

AsmOpConsList Optimizer::extract_code() {
  pack();
  return std::move(code_);
}

void Optimizer::show_head() const {
  if (!debug_) {
    return;
  }
  std::cerr << "optimizing";
  for (int i = 0; i < l_; i++) {
    if (op_[i]) {
      std::cerr << ' ' << *op_[i] << ' ';
    } else {
      std::cerr << " (null) ";
    }
  }
  std::cerr << std::endl;
}

void Optimizer::show_left() const {
  if (!debug_) {
    return;
  }
  std::cerr << "// *** rewriting";
  for (int i = 0; i < p_; i++) {
    if (op_[i]) {
      std::cerr << ' ' << *op_[i] << ' ';
    } else {
      std::cerr << " (null) ";
    }
  }
}

void Optimizer::show_right() const {
  if (!debug_) {
    return;
  }
  std::cerr << "->";
  for (int i = 0; i < q_; i++) {
    if (oq_[i]) {
      std::cerr << ' ' << *oq_[i] << ' ';
    } else {
      std::cerr << " (null) ";
    }
  }
  std::cerr << std::endl;
}

bool Optimizer::say(std::string str) const {
  if (debug_) {
    std::cerr << str << std::endl;
  }
  return true;
}

bool Optimizer::is_const_push_swap() const {
  return l_ >= 3 && op_[0]->is_gconst() && op_[1]->is_push() && op_[1]->a >= 1 && op_[2]->is_swap();
}

// PUSHCONST c ; PUSH s(i+1) ; SWAP -> PUSH s(i) ; PUSHCONST c
bool Optimizer::rewrite_const_push_swap() {
  p_ = 3;
  q_ = 2;
  show_left();
  oq_[1] = std::move(op_[0]);
  oq_[0] = std::move(op_[1]);
  (oq_[0]->a)--;
  show_right();
  return true;
}

bool Optimizer::simple_rewrite(int p, AsmOp&& new_op) {
  assert(p > 0 && p <= l_);
  p_ = p;
  q_ = 1;
  show_left();
  oq_[0] = std::move(op_[0]);
  *oq_[0] = new_op;
  show_right();
  return true;
}

bool Optimizer::simple_rewrite_nop() {
  assert(p_ > 0 && p_ <= l_);
  q_ = 0;
  show_left();
  show_right();
  return true;
}

bool Optimizer::is_pred(const std::function<bool(const StackTransform&)>& pred, int min_p) {
  min_p = std::max(min_p, pb_);
  for (int p = l2_; p >= min_p; p--) {
    if (pred(tr_[p - 1])) {
      p_ = p;
      return true;
    }
  }
  return false;
}

bool Optimizer::is_same_as(const StackTransform& trans, int min_p) {
  return is_pred([&trans](const auto& t) { return t >= trans; }, min_p);
}

// s1 s3 XCHG ; s0 s2 XCHG -> 2SWAP
bool Optimizer::is_2swap() {
  static const StackTransform t_2swap{2, 3, 0, 1, 4};
  return is_same_as(t_2swap);
}

// s3 PUSH ; s3 PUSH -> 2OVER
bool Optimizer::is_2over() {
  static const StackTransform t_2over{2, 3, 0};
  return is_same_as(t_2over);
}

bool Optimizer::is_2dup() {
  static const StackTransform t_2dup{0, 1, 0};
  return is_same_as(t_2dup);
}

bool Optimizer::is_tuck() {
  static const StackTransform t_tuck{0, 1, 0, 2};
  return is_same_as(t_tuck);
}

bool Optimizer::is_2drop() {
  static const StackTransform t_2drop{2};
  return is_same_as(t_2drop);
}

bool Optimizer::is_rot() {
  return is_pred([](const auto& t) { return t.is_rot(); });
}

bool Optimizer::is_rotrev() {
  return is_pred([](const auto& t) { return t.is_rotrev(); });
}

bool Optimizer::is_nop() {
  return is_pred([](const auto& t) { return t.is_id(); }, 1);
}

bool Optimizer::is_xchg(int* i, int* j) {
  return is_pred([i, j](const auto& t) { return t.is_xchg(i, j) && ((*i < 16 && *j < 16) || (!*i && *j < 256)); });
}

bool Optimizer::is_push(int* i) {
  return is_pred([i](const auto& t) { return t.is_push(i) && *i < 256; });
}

bool Optimizer::is_pop(int* i) {
  return is_pred([i](const auto& t) { return t.is_pop(i) && *i < 256; });
}

bool Optimizer::is_xchg2(int* i, int* j) {
  return is_pred([i, j](const auto& t) { return t.is_xchg2(i, j) && *i < 16 && *j < 16; });
}

bool Optimizer::is_xcpu(int* i, int* j) {
  return is_pred([i, j](const auto& t) { return t.is_xcpu(i, j) && *i < 16 && *j < 16; });
}

bool Optimizer::is_puxc(int* i, int* j) {
  return is_pred([i, j](const auto& t) { return t.is_puxc(i, j) && *i < 16 && *j < 15; });
}

bool Optimizer::is_push2(int* i, int* j) {
  return is_pred([i, j](const auto& t) { return t.is_push2(i, j) && *i < 16 && *j < 16; });
}

bool Optimizer::is_xchg3(int* i, int* j, int* k) {
  return is_pred([i, j, k](const auto& t) { return t.is_xchg3(i, j, k) && *i < 16 && *j < 16 && *k < 16; });
}

bool Optimizer::is_xc2pu(int* i, int* j, int* k) {
  return is_pred([i, j, k](const auto& t) { return t.is_xc2pu(i, j, k) && *i < 16 && *j < 16 && *k < 16; });
}

bool Optimizer::is_xcpuxc(int* i, int* j, int* k) {
  return is_pred([i, j, k](const auto& t) { return t.is_xcpuxc(i, j, k) && *i < 16 && *j < 16 && *k < 15; });
}

bool Optimizer::is_xcpu2(int* i, int* j, int* k) {
  return is_pred([i, j, k](const auto& t) { return t.is_xcpu2(i, j, k) && *i < 16 && *j < 16 && *k < 16; });
}

bool Optimizer::is_puxc2(int* i, int* j, int* k) {
  return is_pred([i, j, k](const auto& t) { return t.is_puxc2(i, j, k) && *i < 16 && *j < 15 && *k < 15; });
}

bool Optimizer::is_puxcpu(int* i, int* j, int* k) {
  return is_pred([i, j, k](const auto& t) { return t.is_puxcpu(i, j, k) && *i < 16 && *j < 15 && *k < 15; });
}

bool Optimizer::is_pu2xc(int* i, int* j, int* k) {
  return is_pred([i, j, k](const auto& t) { return t.is_pu2xc(i, j, k) && *i < 16 && *j < 15 && *k < 14; });
}

bool Optimizer::is_push3(int* i, int* j, int* k) {
  return is_pred([i, j, k](const auto& t) { return t.is_push3(i, j, k) && *i < 16 && *j < 16 && *k < 16; });
}

bool Optimizer::is_blkswap(int* i, int* j) {
  return is_pred([i, j](const auto& t) { return t.is_blkswap(i, j) && *i > 0 && *j > 0 && *i <= 16 && *j <= 16; });
}

bool Optimizer::is_blkpush(int* i, int* j) {
  return is_pred([i, j](const auto& t) { return t.is_blkpush(i, j) && *i > 0 && *i < 16 && *j < 16; });
}

bool Optimizer::is_blkdrop(int* i) {
  return is_pred([i](const auto& t) { return t.is_blkdrop(i) && *i > 0 && *i < 16; });
}

bool Optimizer::is_reverse(int* i, int* j) {
  return is_pred([i, j](const auto& t) { return t.is_reverse(i, j) && *i >= 2 && *i <= 17 && *j < 16; });
}

bool Optimizer::compute_stack_transforms() {
  StackTransform trans;
  for (int i = 0; i < l_; i++) {
    if (!apply_op(trans, *op_[i])) {
      l2_ = i;
      return true;
    }
    tr_[i] = trans;
  }
  l2_ = l_;
  return true;
}

bool Optimizer::show_stack_transforms() const {
  show_head();
  // slow version
  /*
  StackTransform trans2;
  std::cerr << "id = " << trans2 << std::endl;
  for (int i = 0; i < l_; i++) {
    StackTransform op;
    if (!apply_op(op, *op_[i])) {
      std::cerr << "* (" << *op_[i] << " = invalid)\n";
      break;
    }
    trans2 *= op;
    std::cerr << "* " << *op_[i] << " = " << op << " -> " << trans2 << std::endl;
  }
  */
  // fast version
  StackTransform trans;
  for (int i = 0; i < l_; i++) {
    std::cerr << trans << std::endl << *op_[i] << " -> ";
    if (!apply_op(trans, *op_[i])) {
      std::cerr << " <not-applicable>" << std::endl;
      return true;
    }
  }
  std::cerr << trans << std::endl;
  return true;
}

bool Optimizer::find_at_least(int pb) {
  p_ = q_ = 0;
  pb_ = pb;
  // show_stack_transforms();
  int i = -100, j = -100, k = -100;
  return (is_const_push_swap() && 3 >= pb && rewrite_const_push_swap()) || (is_nop() && simple_rewrite_nop()) ||
         (is_xchg(&i, &j) && simple_rewrite(AsmOp::Xchg(i, j))) || (is_push(&i) && simple_rewrite(AsmOp::Push(i))) ||
         (is_pop(&i) && simple_rewrite(AsmOp::Pop(i))) || (is_rot() && simple_rewrite(AsmOp::Custom("ROT", 3, 3))) ||
         (is_rotrev() && simple_rewrite(AsmOp::Custom("-ROT", 3, 3))) ||
         (is_2dup() && simple_rewrite(AsmOp::Custom("2DUP", 2, 4))) ||
         (is_2swap() && simple_rewrite(AsmOp::Custom("2SWAP", 2, 4))) ||
         (is_2over() && simple_rewrite(AsmOp::Custom("2OVER", 2, 4))) ||
         (is_tuck() && simple_rewrite(AsmOp::Custom("TUCK", 2, 3))) ||
         (is_2drop() && simple_rewrite(AsmOp::Custom("2DROP", 2, 0))) ||
         (is_xchg2(&i, &j) && simple_rewrite(AsmOp::Xchg2(i, j))) ||
         (is_xcpu(&i, &j) && simple_rewrite(AsmOp::XcPu(i, j))) ||
         (is_puxc(&i, &j) && simple_rewrite(AsmOp::PuXc(i, j))) ||
         (is_push2(&i, &j) && simple_rewrite(AsmOp::Push2(i, j))) ||
         (is_blkswap(&i, &j) && simple_rewrite(AsmOp::BlkSwap(i, j))) ||
         (is_blkpush(&i, &j) && simple_rewrite(AsmOp::BlkPush(i, j))) ||
         (is_blkdrop(&i) && simple_rewrite(AsmOp::BlkDrop(i))) ||
         (is_reverse(&i, &j) && simple_rewrite(AsmOp::BlkReverse(i, j))) ||
         (is_xchg3(&i, &j, &k) && simple_rewrite(AsmOp::Xchg3(i, j, k))) ||
         (is_xc2pu(&i, &j, &k) && simple_rewrite(AsmOp::Xc2Pu(i, j, k))) ||
         (is_xcpuxc(&i, &j, &k) && simple_rewrite(AsmOp::XcPuXc(i, j, k))) ||
         (is_xcpu2(&i, &j, &k) && simple_rewrite(AsmOp::XcPu2(i, j, k))) ||
         (is_puxc2(&i, &j, &k) && simple_rewrite(AsmOp::PuXc2(i, j, k))) ||
         (is_puxcpu(&i, &j, &k) && simple_rewrite(AsmOp::PuXcPu(i, j, k))) ||
         (is_pu2xc(&i, &j, &k) && simple_rewrite(AsmOp::Pu2Xc(i, j, k))) ||
         (is_push3(&i, &j, &k) && simple_rewrite(AsmOp::Push3(i, j, k)));
}

bool Optimizer::find() {
  if (!compute_stack_transforms()) {
    return false;
  }
  for (int pb = l_; pb > 0; --pb) {
    if (find_at_least(pb)) {
      return true;
    }
  }
  return false;
}

bool Optimizer::optimize() {
  bool f = false;
  while (find()) {
    f = true;
    apply();
    unpack();
  }
  return f;
}

AsmOpConsList optimize_code_head(AsmOpConsList op_list) {
  Optimizer opt(std::move(op_list), true /* debug */);
  opt.optimize();
  return opt.extract_code();
}

AsmOpConsList optimize_code(AsmOpConsList op_list) {
  std::vector<std::unique_ptr<AsmOp>> v;
  while (op_list) {
    if (!op_list->car->is_comment()) {
      op_list = optimize_code_head(std::move(op_list));
    }
    if (op_list) {
      v.push_back(std::move(op_list->car));
      op_list = std::move(op_list->cdr);
    }
  }
  for (auto it = v.rbegin(); it < v.rend(); ++it) {
    op_list = AsmOpCons::cons(std::move(*it), std::move(op_list));
  }
  return std::move(op_list);
}

void optimize_code(AsmOpList& ops) {
  std::unique_ptr<AsmOpCons> op_list;
  for (auto it = ops.list_.rbegin(); it < ops.list_.rend(); ++it) {
    op_list = AsmOpCons::cons(std::make_unique<AsmOp>(std::move(*it)), std::move(op_list));
  }
  op_list = optimize_code(std::move(op_list));
  ops.list_.clear();
  while (op_list) {
    ops.list_.push_back(std::move(*(op_list->car)));
    op_list = std::move(op_list->cdr);
  }
}

}  // namespace funC
