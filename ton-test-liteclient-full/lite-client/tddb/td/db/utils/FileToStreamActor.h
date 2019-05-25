#pragma once

#include "StreamInterface.h"

#include "td/actor/actor.h"
#include "td/utils/port/FileFd.h"

namespace td {
class FileToStreamActor : public td::actor::Actor {
 public:
  struct Options {
    Options() {
    }
    int64 limit{-1};
    double read_tail_each{-1};
  };
  class Callback {
   public:
    virtual ~Callback() {
    }
    virtual void got_more() = 0;
  };
  FileToStreamActor(FileFd fd, StreamWriter writer, Options options = {});

  void set_callback(td::unique_ptr<Callback> callback);

 private:
  void got_more();
  void loop() override;
  FileFd fd_;
  StreamWriter writer_;
  td::unique_ptr<Callback> callback_;
  Options options_;
};
}  // namespace td
