#include "FileToStreamActor.h"

namespace td {
FileToStreamActor::FileToStreamActor(FileFd fd, StreamWriter writer, Options options)
    : fd_(std::move(fd)), writer_(std::move(writer)), options_(options) {
}

void FileToStreamActor::set_callback(td::unique_ptr<Callback> callback) {
  callback_ = std::move(callback);
  got_more();
}

void FileToStreamActor::got_more() {
  if (!callback_) {
    return;
  }
  callback_->got_more();
}
void FileToStreamActor::loop() {
  auto dest = writer_.prepare_write();
  if (options_.limit != -1) {
    dest.truncate(options_.limit);
  }
  if (dest.empty()) {
    //NB: Owner of CyclicBufer::Reader should notify this actor after each chunk is readed
    return;
  }

  auto r_size = fd_.read(dest);
  if (r_size.is_error()) {
    writer_.close_writer(r_size.move_as_error());
    got_more();
    return stop();
  }
  auto size = r_size.move_as_ok();
  writer_.confirm_write(size);
  got_more();
  if (options_.limit != -1) {
    options_.limit -= size;
  }
  if (options_.limit == 0) {
    writer_.close_writer(td::Status::OK());
    got_more();
    return stop();
  }
  if (size == 0) {
    if (options_.read_tail_each < 0) {
      writer_.close_writer(td::Status::OK());
      got_more();
      return stop();
    }
    alarm_timestamp() = Timestamp::in(options_.read_tail_each);
    return;
  }
  yield();
}

}  // namespace td
