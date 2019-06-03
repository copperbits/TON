#pragma once

#if !TDDB_USE_ROCKSDB
#error "RocksDb is not supported"
#endif

#include "td/db/KeyValue.h"
#include "td/utils/Status.h"

namespace rocksdb {
class OptimisticTransactionDB;
class Transaction;
class WriteBatch;
class Snapshot;
class Statistics;
}  // namespace rocksdb

namespace td {
class RocksDb : public KeyValue {
 public:
  static Status destroy(Slice path);
  RocksDb clone() const;
  static Result<RocksDb> open(std::string path);

  Result<GetStatus> get(Slice key, std::string &value) override;
  Status set(Slice key, Slice value) override;
  Status erase(Slice key) override;
  Result<size_t> count(Slice prefix) override;

  Status begin_transaction() override;
  Status commit_transaction() override;
  Status abort_transaction() override;
  Status flush() override;

  Status begin_snapshot();
  Status end_snapshot();

  std::unique_ptr<KeyValueReader> snapshot() override;
  std::string stats() const override;

  RocksDb(RocksDb &&);
  RocksDb &operator=(RocksDb &&);
  ~RocksDb();

 private:
  std::shared_ptr<rocksdb::OptimisticTransactionDB> db_;
  std::shared_ptr<rocksdb::Statistics> statistics_;

  std::unique_ptr<rocksdb::Transaction> transaction_;
  std::unique_ptr<rocksdb::WriteBatch> write_batch_;
  class UnreachableDeleter {
   public:
    template <class T>
    void operator()(T *) {
      UNREACHABLE();
    }
  };
  std::unique_ptr<const rocksdb::Snapshot, UnreachableDeleter> snapshot_;

  explicit RocksDb(std::shared_ptr<rocksdb::OptimisticTransactionDB> db,
                   std::shared_ptr<rocksdb::Statistics> statistics);
};
}  // namespace td
