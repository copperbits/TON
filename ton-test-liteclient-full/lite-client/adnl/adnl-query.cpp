#include "adnl-query.h"
#include "common/errorcode.h"
#include "td/utils/Random.h"

namespace ton {
void AdnlQuery::alarm() {
  promise_.set_error(td::Status::Error(ErrorCode::timeout, "adnl query timeout"));
  stop();
}
void AdnlQuery::result(td::BufferSlice data) {
  promise_.set_value(std::move(data));
  alarm_timestamp() = td::Timestamp::never();
  stop();
}

AdnlQueryId AdnlQuery::random_query_id() {
  AdnlQueryId q_id;
  td::Random::secure_bytes(q_id.as_slice());
  return q_id;
}

}  // namespace ton
