#pragma once

#include "td/actor/actor.h"
#include "td/utils/buffer.h"

#include <functional>
#include <ostream>

namespace td {

class TerminalIOOutputter {
 public:
  static const size_t BUFFER_SIZE = 128 * 1024;
  TerminalIOOutputter()
      : buffer_(new char[BUFFER_SIZE]), sb_(std::make_unique<StringBuilder>(td::MutableSlice{buffer_, BUFFER_SIZE})) {
  }
  TerminalIOOutputter(TerminalIOOutputter &&X) = default;

  template <class T>
  TerminalIOOutputter &operator<<(const T &other) {
    *sb_ << other;
    return *this;
  }
  TerminalIOOutputter &operator<<(std::ostream &(*pManip)(std::ostream &)) {
    *sb_ << '\n';
    return *this;
  }

  auto &sb() {
    return *sb_;
  }

  MutableCSlice as_cslice() {
    return sb_->as_cslice();
  }
  bool is_error() const {
    return sb_->is_error();
  }
  ~TerminalIOOutputter();

 private:
  char *buffer_;
  std::unique_ptr<StringBuilder> sb_;
};

class TerminalIO : public actor::Actor {
 public:
  class Callback {
   public:
    virtual ~Callback() = default;
    virtual void line_cb(td::BufferSlice line) = 0;
    //virtual std::vector<std::string> autocomplete_cb(std::string line) = 0;
  };

  virtual ~TerminalIO() = default;
  virtual void update_prompt(std::string new_prompt) = 0;
  virtual void update_callback(std::unique_ptr<Callback> callback) = 0;
  static void output(std::string line);
  static void output(td::Slice slice);
  static TerminalIOOutputter out() {
    return TerminalIOOutputter{};
  }
  virtual void output_line(std::string line) = 0;
  virtual void set_log_interface() = 0;

  static td::actor::ActorOwn<TerminalIO> create(std::string prompt, bool use_readline,
                                                std::unique_ptr<Callback> callback);
};

}  // namespace td
