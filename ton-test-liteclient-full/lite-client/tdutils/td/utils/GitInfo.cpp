#include "td/utils/GitInfo.h"

#include "auto/git_info.h"

namespace td {

CSlice GitInfo::commit() {
  return GIT_COMMIT;
}
bool GitInfo::is_dirty() {
  return GIT_DIRTY;
}

}  // namespace td
