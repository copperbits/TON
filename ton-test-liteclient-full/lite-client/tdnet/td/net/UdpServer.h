#pragma once

#include "td/actor/actor.h"
#include "td/utils/BufferedUdp.h"

#include "td/utils/port/UdpSocketFd.h"

namespace td {

class UdpServer : public td::actor::Actor {
 public:
  class Callback {
   public:
    virtual ~Callback() = default;
    virtual void on_udp_message(td::UdpMessage udp_message) = 0;
  };
  virtual void send(td::UdpMessage &&message) = 0;

  static Result<actor::ActorOwn<UdpServer>> create(td::Slice name, int32 port, std::unique_ptr<Callback> callback);
  static Result<actor::ActorOwn<UdpServer>> create_via_tcp(td::Slice name, int32 port,
                                                           std::unique_ptr<Callback> callback);
};

}  // namespace td
