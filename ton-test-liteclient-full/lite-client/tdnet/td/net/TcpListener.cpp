#include "td/net/TcpListener.h"

namespace td {
TcpListener::TcpListener(int port, std::unique_ptr<Callback> callback) : port_(port), callback_(std::move(callback)) {
}
void TcpListener::notify() {
  td::actor::send_closure_later(self_, &TcpListener::on_net);
}
void TcpListener::on_net() {
  loop();
}

void TcpListener::start_up() {
  self_ = actor_id(this);

  auto r_socket = td::ServerSocketFd::open(port_);
  if (r_socket.is_error()) {
    LOG(ERROR) << r_socket.error();
    return stop();
  }

  server_socket_fd_ = r_socket.move_as_ok();

  // Subscribe for socket updates
  // NB: Interface will be changed
  td::actor::SchedulerContext::get()->get_poll().subscribe(server_socket_fd_.get_poll_info().extract_pollable_fd(this),
                                                           PollFlags::Read());
}

void TcpListener::tear_down() {
  // unsubscribe from socket updates
  // nb: interface will be changed
  td::actor::SchedulerContext::get()->get_poll().unsubscribe(server_socket_fd_.get_poll_info().get_pollable_fd_ref());
}

void TcpListener::loop() {
  auto status = [&] {
    while (td::can_read(server_socket_fd_)) {
      auto r_socket = server_socket_fd_.accept();
      if (r_socket.is_error() && r_socket.error().code() == -1) {
        break;
      }
      TRY_RESULT(client_socket, std::move(r_socket));
      LOG(ERROR) << "Accept";
      callback_->accept(std::move(client_socket));
    }
    if (td::can_close(server_socket_fd_)) {
      stop();
    }
    return td::Status::OK();
  }();

  if (status.is_error()) {
    LOG(ERROR) << "Server error " << status;
    return stop();
  }
}

}  // namespace td
