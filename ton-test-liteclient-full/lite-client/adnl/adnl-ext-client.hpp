#pragma once

#include "adnl-ext-connection.hpp"
#include "tl-utils/tl-utils.hpp"
#include "td/utils/Random.h"
#include "adnl-query.h"
#include "keys/encryptor.h"
#include "adnl-ext-client.h"

namespace ton {

class AdnlExtClientImpl;

class AdnlOutboundConnection : public AdnlExtConnection {
 private:
  AdnlNodeIdFull dst_;
  td::actor::ActorId<AdnlExtClientImpl> ext_client_;

 public:
  AdnlOutboundConnection(td::SocketFd fd, std::unique_ptr<AdnlExtConnection::Callback> callback, AdnlNodeIdFull dst,
                         td::actor::ActorId<AdnlExtClientImpl> ext_client)
      : AdnlExtConnection(std::move(fd), std::move(callback), true), dst_(std::move(dst)), ext_client_(ext_client) {
  }
  td::Status process_packet(td::BufferSlice data) override;
  td::Status process_init_packet(td::BufferSlice data) override {
    UNREACHABLE();
  }
  void start_up() override {
    AdnlExtConnection::start_up();
    auto X = dst_.pubkey().create_encryptor();
    if (X.is_error()) {
      LOG(ERROR) << "failed to init encryptor: " << X.move_as_error();
      stop();
      return;
    }
    auto enc = X.move_as_ok();

    td::BufferSlice d{256};
    auto id = dst_.compute_short_id();
    auto S = d.as_slice();
    S.copy_from(id.as_slice());
    S.remove_prefix(32);
    S.truncate(256 - 64 - 32);
    td::Random::secure_bytes(S);
    init_crypto(S);

    auto R = enc->encrypt(S);
    if (R.is_error()) {
      LOG(ERROR) << "failed to  encrypt: " << R.move_as_error();
      stop();
      return;
    }
    auto data = R.move_as_ok();
    CHECK(data.size() == 256 - 32) << "size=" << data.size();
    S = d.as_slice();
    S.remove_prefix(32);
    CHECK(S.size() == data.size());
    S.copy_from(data.as_slice());

    send_uninit(std::move(d));
  }
};

class AdnlExtClientImpl : public AdnlExtClient {
 public:
  AdnlExtClientImpl(AdnlNodeIdFull dst_id, td::IPAddress dst_addr, std::unique_ptr<Callback> callback)
      : dst_(std::move(dst_id)), dst_addr_(dst_addr), callback_(std::move(callback)) {
  }

  void start_up() override {
    alarm_timestamp() = next_create_at_;
  }
  void conn_stopped(td::actor::ActorId<AdnlExtConnection> conn) {
    if (!conn_.empty() && conn_.get() == conn) {
      callback_->on_stop_ready();
      conn_.reset();
      alarm_timestamp() = next_create_at_;
    }
  }
  void conn_ready(td::actor::ActorId<AdnlExtConnection> conn) {
    LOG(ERROR) << "conn ready";
    if (!conn_.empty() && conn_.get() == conn) {
      callback_->on_ready();
    }
  }
  void check_ready(td::Promise<td::Unit> promise) override;
  void send_query(std::string name, td::BufferSlice data, td::Timestamp timeout,
                  td::Promise<td::BufferSlice> promise) override {
    auto P = [SelfId = actor_id(this)](AdnlQueryId id) {
      td::actor::send_closure(SelfId, &AdnlExtClientImpl::destroy_query, id);
    };
    auto q_id = generate_next_query_id();
    out_queries_.emplace(q_id, AdnlQuery::create(std::move(promise), std::move(P), name, timeout, q_id));
    if (!conn_.empty()) {
      auto obj = create_tl_object<ton_api::adnl_message_query>(q_id, std::move(data));
      td::actor::send_closure(conn_, &AdnlOutboundConnection::send, serialize_tl_object(obj, true));
    }
  }
  void destroy_query(AdnlQueryId id) {
    out_queries_.erase(id);
  }
  void answer_query(AdnlQueryId id, td::BufferSlice data) {
    auto it = out_queries_.find(id);
    if (it != out_queries_.end()) {
      td::actor::send_closure(it->second, &AdnlQuery::result, std::move(data));
      out_queries_.erase(it);
    }
  }
  void alarm() override;
  AdnlQueryId generate_next_query_id() {
    while (true) {
      AdnlQueryId q_id = AdnlQuery::random_query_id();
      if (out_queries_.count(q_id) == 0) {
        return q_id;
      }
    }
  }

 private:
  AdnlNodeIdFull dst_;
  td::IPAddress dst_addr_;

  std::unique_ptr<Callback> callback_;

  td::actor::ActorOwn<AdnlOutboundConnection> conn_;
  td::Timestamp next_create_at_ = td::Timestamp::now_cached();

  std::map<AdnlQueryId, td::actor::ActorId<AdnlQuery>> out_queries_;
};

}  // namespace ton
