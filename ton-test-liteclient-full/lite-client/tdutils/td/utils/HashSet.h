#pragma once

#include "td/utils/Hash.h"

#if TD_HAVE_ABSL
#include <absl/container/flat_hash_set.h>
#else
#include <unordered_set>
#endif
namespace td {
#if TD_HAVE_ABSL
template <class Key, class H = Hash<Key>>
using HashSet = absl::flat_hash_set<Key, H>;
#else
template <class Key, class H = Hash<Key>>
using HashSet = std::unordered_set<Key, H>;
#endif
}  // namespace td
