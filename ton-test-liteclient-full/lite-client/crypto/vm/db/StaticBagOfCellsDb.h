#pragma once

#include "vm/cells.h"
#include "vm/db/BlobView.h"

#include "td/utils/Status.h"

namespace vm {
class StaticBagOfCellsDb : public std::enable_shared_from_this<StaticBagOfCellsDb> {
 public:
  virtual ~StaticBagOfCellsDb() = default;
  // TODO: handle errors
  virtual td::Result<size_t> get_root_count() = 0;
  virtual td::Result<Ref<Cell>> get_root_cell(size_t idx) = 0;

 protected:
  virtual td::Result<Ref<DataCell>> load_by_idx(int idx) = 0;
  friend class StaticBocLoader;
  friend class StaticBocRootLoader;
  td::Result<Ref<Cell>> create_ext_cell(Cell::LevelMask level_mask, td::Slice hash, td::Slice depth, int idx);
  td::Result<Ref<Cell>> create_root_ext_cell(Cell::LevelMask level_mask, td::Slice hash, td::Slice depth, int idx);
};

class StaticBagOfCellsDbBaseline {
 public:
  static td::Result<std::shared_ptr<StaticBagOfCellsDb>> create(std::unique_ptr<BlobView> data);
  static td::Result<std::shared_ptr<StaticBagOfCellsDb>> create(td::Slice data);
};

class StaticBagOfCellsDbLazy {
 public:
  struct Options {
    Options() {
    }
    bool check_crc32c{false};
  };
  static td::Result<std::shared_ptr<StaticBagOfCellsDb>> create(std::unique_ptr<BlobView> data, Options options = {});
  static td::Result<std::shared_ptr<StaticBagOfCellsDb>> create(td::BufferSlice data, Options options = {});
  static td::Result<std::shared_ptr<StaticBagOfCellsDb>> create(std::string data, Options options = {});
};

}  // namespace vm
