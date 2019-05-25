#pragma once

#include "ton-types.h"
#include "td/utils/base64.h"

namespace td {

static inline td::StringBuilder &operator<<(td::StringBuilder &stream, const ton::Bits256 &x) {
  return stream << td::base64_encode(td::Slice(x.data(), x.size() / 8));
}

static inline td::StringBuilder &operator<<(td::StringBuilder &stream, const ton::ShardIdFull &x) {
  return stream << "[ w=" << x.workchain << " s=" << x.shard << " ]";
}

static inline td::StringBuilder &operator<<(td::StringBuilder &stream, const ton::AccountIdPrefixFull &x) {
  return stream << "[ w=" << x.workchain << " s=" << x.account_id_prefix << " ]";
}

static inline td::StringBuilder &operator<<(td::StringBuilder &stream, const ton::BlockId &x) {
  return stream << "[ w=" << x.workchain << " s=" << x.shard << " seq=" << x.seqno << " ]";
}
static inline td::StringBuilder &operator<<(td::StringBuilder &stream, const ton::BlockIdExt &x) {
  return stream << "[ w=" << x.id.workchain << " s=" << x.id.shard << " seq=" << x.id.seqno << " " << x.root_hash << " "
                << x.file_hash << " ]";
}

}  // namespace td
