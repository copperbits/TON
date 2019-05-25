#pragma once

#include "adnl-node-id.hpp"
#include "td/utils/port/IPAddress.h"

namespace ton {

class AdnlExtClient : public td::actor::Actor {
 public:
  class Callback {
   public:
    virtual ~Callback() = default;
    virtual void on_ready() = 0;
    virtual void on_stop_ready() = 0;
  };
  virtual ~AdnlExtClient() = default;
  virtual void check_ready(td::Promise<td::Unit> promise) = 0;
  virtual void send_query(std::string name, td::BufferSlice data, td::Timestamp timeout,
                          td::Promise<td::BufferSlice> promise) = 0;
  static td::actor::ActorOwn<AdnlExtClient> create(AdnlNodeIdFull dst, td::IPAddress dst_addr,
                                                   std::unique_ptr<AdnlExtClient::Callback> callback);
};

}  // namespace ton
