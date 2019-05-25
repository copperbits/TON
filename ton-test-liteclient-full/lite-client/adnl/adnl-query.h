#pragma once

#include "auto/tl/ton_api.h"
#include "td/actor/actor.h"

#include <functional>

namespace ton {

class AdnlPeerPair;

using AdnlQueryId = td::UInt256;

class AdnlQuery : public td::actor::Actor {
 public:
  static td::actor::ActorId<AdnlQuery> create(td::Promise<td::BufferSlice> promise,
                                              std::function<void(AdnlQueryId)> destroy, std::string name,
                                              td::Timestamp timeout, AdnlQueryId id) {
    return td::actor::create_actor<AdnlQuery>("query", name, std::move(promise), std::move(destroy), timeout, id)
        .release();
  }
  static AdnlQueryId random_query_id();
  AdnlQuery(std::string name, td::Promise<td::BufferSlice> promise, std::function<void(AdnlQueryId)> destroy,
            td::Timestamp timeout, AdnlQueryId id)
      : name_(std::move(name)), timeout_(timeout), promise_(std::move(promise)), destroy_(std::move(destroy)), id_(id) {
  }
  void alarm() override;
  void result(td::BufferSlice data);
  void start_up() override {
    alarm_timestamp() = timeout_;
  }
  void tear_down() override {
    destroy_(id_);
  }

 private:
  std::string name_;
  td::Timestamp timeout_;
  td::Promise<td::BufferSlice> promise_;
  std::function<void(AdnlQueryId)> destroy_;
  AdnlQueryId id_;
};

}  // namespace ton
