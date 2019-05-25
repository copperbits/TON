#pragma once
#include "BinlogReaderInterface.h"

#include "td/db/utils/StreamInterface.h"
#include "td/db/utils/FileSyncState.h"

#include "td/actor/actor.h"

#include "td/utils/port/FileFd.h"

namespace td {
class BinlogReaderInterface;
class StreamToFileActor;
namespace detail {
class FlushHelperActor;
}  // namespace detail
class Binlog {
 public:
  explicit Binlog(string path);

  Status replay_sync(BinlogReaderInterface& binlog_reader);
  void replay_async(std::shared_ptr<BinlogReaderInterface> binlog_reader, Promise<Unit> promise);

  static void destroy(CSlice path);
  void destroy();

 private:
  string path_;
};

class BinlogWriter {
 public:
  BinlogWriter(std::string path);

  Status open();

  template <class EventT>
  Status write_event(EventT&& event, BinlogReaderInterface* binlog_reader);
  Status lazy_flush();
  Status flush();
  Status sync();

  Status close();

 private:
  string path_;
  FileFd fd_;

  StreamReader buf_reader_;
  StreamWriter buf_writer_;
};

class BinlogWriterAsync {
 public:
  BinlogWriterAsync(std::string path);
  ~BinlogWriterAsync();

  Status open();

  template <class EventT>
  Status write_event(EventT&& event, BinlogReaderInterface* binlog_reader);

  void close(Promise<> promise);

  void lazy_flush();

  void flush();
  void sync(Promise<Unit> promise = {});

 private:
  std::string path_;
  StreamWriter buf_writer_;
  actor::ActorId<StreamToFileActor> writer_actor_;
  actor::ActorOwn<detail::FlushHelperActor> flush_helper_actor_;

  FileSyncState::Reader sync_state_reader_;
};

template <class EventT>
Status BinlogWriter::write_event(EventT&& event, BinlogReaderInterface* binlog_reader) {
  int64 need_size = -event.serialize({});
  auto dest = buf_writer_.prepare_write_at_least(need_size).truncate(need_size);
  auto written = event.serialize(dest);
  CHECK(written == need_size);

  if (binlog_reader != nullptr) {
    TRY_RESULT(parsed, binlog_reader->parse(dest));
    binlog_reader->flush();
    CHECK(parsed == written);
  }

  buf_writer_.confirm_write(written);
  return lazy_flush();
}

template <class EventT>
Status BinlogWriterAsync::write_event(EventT&& event, BinlogReaderInterface* binlog_reader) {
  int64 need_size = -event.serialize({});
  auto dest = buf_writer_.prepare_write_at_least(need_size).truncate(need_size);
  auto written = event.serialize(dest);
  CHECK(written == need_size);

  if (binlog_reader != nullptr) {
    TRY_RESULT(parsed, binlog_reader->parse(dest));
    CHECK(parsed == written);
  }

  buf_writer_.confirm_write(written);
  lazy_flush();
  return Status::OK();
}

}  // namespace td
