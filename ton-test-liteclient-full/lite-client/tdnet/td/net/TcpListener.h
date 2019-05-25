#pragma once

#include "td/actor/actor.h"

#include "td/utils/port/ServerSocketFd.h"
#include "td/utils/Observer.h"

namespace td {
class TcpListener : public td::actor::Actor, private td::ObserverBase {
 public:
  class Callback {
   public:
    virtual ~Callback() = default;
    virtual void accept(SocketFd fd) = 0;
  };

  TcpListener(int port, std::unique_ptr<Callback> callback);

 private:
  int port_;
  std::unique_ptr<Callback> callback_;
  td::ServerSocketFd server_socket_fd_;
  td::actor::ActorId<TcpListener> self_;

  void notify() override;
  void on_net();

  void start_up() override;

  void tear_down() override;

  void loop() override;
};
}  // namespace td
