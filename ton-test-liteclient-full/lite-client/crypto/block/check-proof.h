#pragma once

#include "vm/cells.h"
#include "block/block.h"

namespace block {
td::Status check_block_header_proof(td::Ref<vm::Cell> root, ton::BlockIdExt blkid,
                                    ton::Bits256* store_shard_hash_to = nullptr, bool check_state_hash = false);
td::Status check_shard_proof(ton::BlockIdExt blk, ton::BlockIdExt shard_blk, td::Slice shard_proof);
td::Status check_account_proof(td::Slice proof, ton::BlockIdExt shard_blk, const block::StdAddress& addr,
                               td::Ref<vm::Cell> root, ton::LogicalTime* last_trans_lt = nullptr,
                               ton::Bits256* last_trans_hash = nullptr);

struct AccountState {
  ton::BlockIdExt blk;
  ton::BlockIdExt shard_blk;
  td::BufferSlice shard_proof;
  td::BufferSlice proof;
  td::BufferSlice state;

  struct Info {
    td::Ref<vm::Cell> root;
    ton::LogicalTime last_trans_lt = 0;
    ton::Bits256 last_trans_hash;
  };

  td::Result<Info> validate(ton::BlockIdExt ref_blk, block::StdAddress addr) const;
};

struct Transaction {
  ton::BlockIdExt blkid;
  ton::LogicalTime lt;
  ton::Bits256 hash;
  td::Ref<vm::Cell> root;

  struct Info {
    ton::BlockIdExt blkid;
    ton::LogicalTime prev_trans_lt;
    ton::Bits256 prev_trans_hash;
    td::Ref<vm::Cell> transaction;
  };
  td::Result<Info> validate();
};

struct TransactionList {
  ton::LogicalTime lt;
  ton::Bits256 hash;
  std::vector<ton::BlockIdExt> blkids;
  td::BufferSlice transactions_boc;

  struct Info {
    std::vector<Transaction::Info> transactions;
  };

  td::Result<Info> validate() const;
};

}  // namespace block
