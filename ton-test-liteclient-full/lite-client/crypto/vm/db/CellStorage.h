#pragma once
#include "td/db/KeyValue.h"
#include "vm/db/DynamicBagOfCellsDb.h"
#include "vm/cells.h"

#include "td/utils/Slice.h"
#include "td/utils/Status.h"

namespace vm {
using KeyValue = td::KeyValue;
using KeyValueReader = td::KeyValueReader;

class CellLoader {
 public:
  struct LoadResult {
   public:
    enum { Ok, NotFound } status{NotFound};

    Ref<DataCell> &cell() {
      DCHECK(status == Ok);
      return cell_;
    }

    td::int32 refcnt() const {
      return refcnt_;
    }

    Ref<DataCell> cell_;
    td::int32 refcnt_{0};
  };
  CellLoader(std::shared_ptr<KeyValueReader> reader);
  td::Result<LoadResult> load(td::Slice hash, bool need_data, ExtCellCreator &ext_cell_creator);

 private:
  std::shared_ptr<KeyValueReader> reader_;
};

class CellStorer {
 public:
  CellStorer(KeyValue &kv);
  td::Status erase(td::Slice hash);
  td::Status set(td::int32 refcnt, const DataCell &cell);

 private:
  KeyValue &kv_;
};
}  // namespace vm
