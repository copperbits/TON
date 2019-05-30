#pragma once
#include "td/utils/Status.h"
#include "td/utils/logging.h"
namespace td {
class KeyValueReader {
 public:
  virtual ~KeyValueReader() = default;
  enum class GetStatus : int32 { Ok, NotFound };

  virtual Result<GetStatus> get(Slice key, std::string &value) = 0;
  virtual Result<size_t> count(Slice prefix) = 0;
};

class PrefixedKeyValueReader : public KeyValueReader {
 public:
  PrefixedKeyValueReader(std::shared_ptr<KeyValueReader> reader, Slice prefix)
      : reader_(std::move(reader)), prefix_(prefix.str()) {
  }
  Result<GetStatus> get(Slice key, std::string &value) override {
    return reader_->get(PSLICE() << prefix_ << key, value);
  }
  Result<size_t> count(Slice prefix) override {
    return reader_->count(PSLICE() << prefix_ << prefix);
  }

 private:
  std::shared_ptr<KeyValueReader> reader_;
  std::string prefix_;
};

class KeyValueUtils {
 public:
};

class KeyValue : public KeyValueReader {
 public:
  virtual Status set(Slice key, Slice value) = 0;
  virtual Status erase(Slice key) = 0;

  virtual Status begin_transaction() = 0;
  virtual Status commit_transaction() = 0;
  virtual Status abort_transaction() = 0;
  // Desctructor will abort transaction

  virtual std::unique_ptr<KeyValueReader> snapshot() = 0;

  virtual std::string stats() const {
    return "";
  }
  virtual Status flush() {
    return Status::OK();
  }
};
class PrefixedKeyValue : public KeyValue {
 public:
  PrefixedKeyValue(std::shared_ptr<KeyValue> kv, Slice prefix) : kv_(std::move(kv)), prefix_(prefix.str()) {
  }
  Result<GetStatus> get(Slice key, std::string &value) override {
    return kv_->get(PSLICE() << prefix_ << key, value);
  }
  Result<size_t> count(Slice prefix) override {
    return kv_->count(PSLICE() << prefix_ << prefix);
  }
  Status set(Slice key, Slice value) override {
    return kv_->set(PSLICE() << prefix_ << key, value);
  }
  Status erase(Slice key) override {
    return kv_->erase(PSLICE() << prefix_ << key);
  }

  Status begin_transaction() override {
    return kv_->begin_transaction();
  }
  Status commit_transaction() override {
    return kv_->commit_transaction();
  }
  Status abort_transaction() override {
    return kv_->abort_transaction();
  }
  // Desctructor will abort transaction

  std::unique_ptr<KeyValueReader> snapshot() override {
    return kv_->snapshot();
  }

  std::string stats() const override {
    return kv_->stats();
  }
  Status flush() override {
    return kv_->flush();
  }

 private:
  std::shared_ptr<KeyValue> kv_;
  std::string prefix_;
};

}  // namespace td
