#include "td/actor/actor.h"

#include "td/utils/BufferedFd.h"
#include "td/utils/OptionsParser.h"
#include "td/utils/port/SocketFd.h"
#include "td/utils/port/ServerSocketFd.h"
#include "td/utils/Observer.h"

#include "td/net/TcpListener.h"

class PingClient : public td::actor::Actor, td::ObserverBase {
 public:
  PingClient(td::SocketFd fd) : buffered_fd_(std::move(fd)) {
  }

 private:
  td::BufferedFd<td::SocketFd> buffered_fd_;
  td::actor::ActorId<PingClient> self_;
  void notify() override {
    // NB: Interface will be changed
    send_closure_later(self_, &PingClient::on_net);
  }
  void on_net() {
    loop();
  }

  void start_up() override {
    self_ = actor_id(this);
    LOG(INFO) << "Start";
    // Subscribe for socket updates
    // NB: Interface will be changed
    td::actor::SchedulerContext::get()->get_poll().subscribe(buffered_fd_.get_poll_info().extract_pollable_fd(this),
                                                             td::PollFlags::ReadWrite());

    alarm_timestamp() = td::Timestamp::now();
  }

  void tear_down() override {
    LOG(INFO) << "Close";
    // unsubscribe from socket updates
    // nb: interface will be changed
    td::actor::SchedulerContext::get()->get_poll().unsubscribe(buffered_fd_.get_poll_info().get_pollable_fd_ref());
  }

  void loop() override {
    auto status = [&] {
      TRY_STATUS(buffered_fd_.flush_read());
      auto &input = buffered_fd_.input_buffer();
      while (input.size() >= 12) {
        auto query = input.cut_head(12).move_as_buffer_slice();
        LOG(INFO) << "Got query " << td::format::escaped(query.as_slice());
        if (query[5] == 'i') {
          LOG(INFO) << "Send ping";
          buffered_fd_.output_buffer().append("magkpongpong");
        } else {
          LOG(INFO) << "Got pong";
        }
      }

      TRY_STATUS(buffered_fd_.flush_write());
      if (td::can_close(buffered_fd_)) {
        stop();
      }
      return td::Status::OK();
    }();
    if (status.is_error()) {
      LOG(ERROR) << "Client got error " << status;
      stop();
    }
  }

  void alarm() override {
    alarm_timestamp() = td::Timestamp::in(5);
    LOG(INFO) << "Send ping";
    buffered_fd_.output_buffer().append("magkpingping");
    loop();
  }
};

int main(int argc, char *argv[]) {
  td::OptionsParser options_parser;
  options_parser.set_description("Tcp ping server/client (based on td::actors2)");

  int port = 8081;
  bool is_client = false;
  options_parser.add_option('p', "port", "listen/connect to tcp port (8081 by default)", [&](td::Slice arg) {
    port = td::to_integer<int>(arg);
    return td::Status::OK();
  });
  options_parser.add_option('c', "client", "Work as client (server by default)", [&]() {
    is_client = true;
    return td::Status::OK();
  });
  auto status = options_parser.run(argc, argv);
  if (status.is_error()) {
    LOG(ERROR) << status.error();
    LOG(INFO) << options_parser;
    return 1;
  }

  // NB: Interface will be changed
  td::actor::Scheduler scheduler({2});
  scheduler.run_in_context([&] {
    if (is_client) {
      td::IPAddress ip_address;
      ip_address.init_ipv4_port("127.0.0.1", port).ensure();
      td::actor::create_actor<PingClient>(td::actor::ActorOptions().with_name("TcpClient").with_poll(),
                                          td::SocketFd::open(ip_address).move_as_ok())
          .release();
    } else {
      class Callback : public td::TcpListener::Callback {
       public:
        void accept(td::SocketFd fd) override {
          td::actor::create_actor<PingClient>(td::actor::ActorOptions().with_name("TcpClient").with_poll(),
                                              std::move(fd))
              .release();
        }
      };
      td::actor::create_actor<td::TcpListener>(td::actor::ActorOptions().with_name("TcpServer").with_poll(), port,
                                               std::make_unique<Callback>())
          .release();
    }
  });
  scheduler.run();
  return 0;
}
