#pragma once
#include "td/utils/int_types.h"
#include "ton/ton-types.h"

namespace block {

namespace log {

#pragma pack(push, 4)

struct Start {
  static constexpr unsigned tag = 0x0442446b;
  static constexpr unsigned log_type = 0x290100;
  unsigned tag_field;
  unsigned type_field;
  unsigned created_at;
  unsigned char zerostate_root_hash[32];
  Start(const RootHash& hash, unsigned _now = 0)
      : tag_field(tag), type_field(log_type), created_at(_now ? _now : (unsigned)time(0)) {
    td::as<RootHash>(zerostate_root_hash) = hash;
  }
};

struct SetZeroState {
  static constexpr unsigned tag = 0x63ab3cd9;
  unsigned tag_field;
  unsigned flags;
  long long file_size;
  unsigned char file_hash[32];
  unsigned char root_hash[32];
  SetZeroState(const RootHash& rhash, const FileHash& fhash, unsigned long long _fsize, unsigned _flags = 0)
      : tag_field(tag), flags(_flags), file_size(_fsize) {
    td::as<FileHash>(file_hash) = fhash;
    td::as<RootHash>(root_hash) = rhash;
  }
};

struct NewBlock {
  static constexpr unsigned tag = 0x19f4bc63;
  unsigned tag_field;
  unsigned flags;  // lower 8 bits = authority
  int workchain;
  unsigned seqno;
  unsigned long long shard;
  long long file_size;
  unsigned char file_hash[32];
  unsigned char root_hash[32];
  unsigned char last_bytes[8];
  NewBlock(const ton::BlockId& block, const RootHash& rhash, const FileHash& fhash, unsigned long long _fsize,
           unsigned _flags)
      : tag_field(tag)
      , flags(_flags)
      , workchain(block.workchain)
      , seqno(block.seqno)
      , shard(block.shard)
      , file_size(_fsize) {
    td::as<FileHash>(file_hash) = fhash;
    td::as<RootHash>(root_hash) = rhash;
    td::as<unsigned long long>(last_bytes) = 0;
  }
};

struct NewState {
  static constexpr unsigned tag = 0x4190a21f;
  unsigned tag_field;
  unsigned flags;  // lower 8 bits = authority
  int workchain;
  unsigned seqno;
  unsigned long long shard;
  long long file_size;
  unsigned char file_hash[32];
  unsigned char root_hash[32];
  unsigned char last_bytes[8];
  NewState(const ton::BlockId& state, const RootHash& rhash, const FileHash& fhash, unsigned long long _fsize,
           unsigned _flags)
      : tag_field(tag)
      , flags(_flags)
      , workchain(state.workchain)
      , seqno(state.seqno)
      , shard(state.shard)
      , file_size(_fsize) {
    td::as<FileHash>(file_hash) = fhash;
    td::as<RootHash>(root_hash) = rhash;
    td::as<unsigned long long>(last_bytes) = 0;
  }
};

#pragma pack(pop)

}  // namespace log
}  // namespace block
