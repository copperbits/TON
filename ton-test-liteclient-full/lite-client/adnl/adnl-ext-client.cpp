#include "adnl-ext-client.hpp"
#include "adnl-ext-client.h"

namespace ton {

void AdnlExtClientImpl::alarm() {
  if (conn_.empty() || !conn_.is_alive()) {
    next_create_at_ = td::Timestamp::in(10.0);
    alarm_timestamp() = next_create_at_;

    auto fd = td::SocketFd::open(dst_addr_);
    if (fd.is_error()) {
      LOG(INFO) << "failed to connect to " << dst_addr_ << ": " << fd.move_as_error();
      return;
    }

    class Cb : public AdnlExtConnection::Callback {
     private:
      td::actor::ActorId<AdnlExtClientImpl> id_;

     public:
      void on_ready(td::actor::ActorId<AdnlExtConnection> conn) {
        td::actor::send_closure(id_, &AdnlExtClientImpl::conn_ready, conn);
      }
      void on_close(td::actor::ActorId<AdnlExtConnection> conn) {
        td::actor::send_closure(id_, &AdnlExtClientImpl::conn_stopped, conn);
      }
      Cb(td::actor::ActorId<AdnlExtClientImpl> id) : id_(id) {
      }
    };

    conn_ = td::actor::create_actor<AdnlOutboundConnection>(td::actor::ActorOptions().with_name("outconn").with_poll(),
                                                            fd.move_as_ok(), std::make_unique<Cb>(actor_id(this)), dst_,
                                                            actor_id(this));
  }
}

void AdnlExtClientImpl::check_ready(td::Promise<td::Unit> promise) {
  if (conn_.empty() || !conn_.is_alive()) {
    promise.set_error(td::Status::Error(AdnlError::notready, "not ready"));
    return;
  }
  td::actor::send_closure(td::actor::ActorId<AdnlExtConnection>{conn_.get()}, &AdnlExtConnection::check_ready_async,
                          std::move(promise));
}

td::actor::ActorOwn<AdnlExtClient> AdnlExtClient::create(AdnlNodeIdFull dst, td::IPAddress dst_addr,
                                                         std::unique_ptr<AdnlExtClient::Callback> callback) {
  return td::actor::create_actor<AdnlExtClientImpl>("extclient", std::move(dst), dst_addr, std::move(callback));
}

td::Status AdnlOutboundConnection::process_packet(td::BufferSlice data) {
  TRY_RESULT(F, fetch_tl_object<ton_api::adnl_message_answer>(std::move(data), true));
  td::actor::send_closure(ext_client_, &AdnlExtClientImpl::answer_query, F->query_id_, std::move(F->answer_));
  return td::Status::OK();
}

}  // namespace ton
