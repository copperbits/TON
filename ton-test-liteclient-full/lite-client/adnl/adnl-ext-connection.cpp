#include "adnl-ext-connection.hpp"

namespace ton {

void AdnlExtConnection::send_uninit(td::BufferSlice data) {
  buffered_fd_.output_buffer().append(std::move(data));
  loop();
}

void AdnlExtConnection::send(td::BufferSlice data) {
  LOG(DEBUG) << "sending packet of size " << data.size();
  auto data_size = td::narrow_cast<td::uint32>(data.size()) + 32 + 32;
  if (data_size < 32 || data_size > (1 << 24)) {
    LOG(WARNING) << "bad packet size " << data_size;
    return;
  }

  td::BufferSlice d{data.size() + 4 + 32 + 32};
  auto S = d.as_slice();

  S.copy_from(td::Slice(reinterpret_cast<const td::uint8 *>(&data_size), 4));
  S.remove_prefix(4);
  auto Sc = S;
  td::Random::secure_bytes(S.copy().truncate(32));
  S.remove_prefix(32);
  S.copy_from(data.as_slice());
  S.remove_prefix(data.size());

  td::sha256(Sc.truncate(32 + data.size()), S);

  td::BufferSlice e{d.size()};

  out_ctr_.encrypt(d.as_slice(), e.as_slice());

  buffered_fd_.output_buffer().append(std::move(e));
  loop();
}

td::Status AdnlExtConnection::receive(td::ChainBufferReader &input, bool &exit_loop) {
  if (stop_read_) {
    exit_loop = true;
    return td::Status::OK();
  }
  if (input.size() > 0) {
    received_bytes_ = 1;
  }
  if (inited_) {
    if (!read_len_) {
      if (input.size() < 4) {
        exit_loop = true;
        return td::Status::OK();
      }

      char x[4];
      td::MutableSlice s{x, 4};
      input.advance(4, s);

      td::MutableSlice e{reinterpret_cast<td::uint8 *>(&len_), 4};
      in_ctr_.encrypt(s, e);
      LOG(DEBUG) << "len=" << len_;
      if (len_ > (1 << 24) || len_ < 32) {
        return td::Status::Error("Too big packet");
      }
      read_len_ = true;
    }
    if (input.size() < len_) {
      exit_loop = true;
      return td::Status::OK();
    }
    auto data = input.cut_head(len_).move_as_buffer_slice();
    update_timer();

    td::BufferSlice dec_data{data.size()};
    in_ctr_.encrypt(data.as_slice(), dec_data.as_slice());

    exit_loop = false;
    read_len_ = false;
    len_ = 0;
    return receive_packet(std::move(dec_data));
  } else {
    if (input.size() < 256) {
      exit_loop = true;
      return td::Status::OK();
    }

    auto data = input.cut_head(256).move_as_buffer_slice();
    update_timer();

    exit_loop = false;
    return process_init_packet(std::move(data));
  }
}

void AdnlExtConnection::loop() {
  auto status = [&] {
    TRY_STATUS(buffered_fd_.flush_read());
    auto &input = buffered_fd_.input_buffer();
    bool exit_loop = false;
    while (!exit_loop) {
      TRY_STATUS(receive(input, exit_loop));
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
  } else {
    send_ready();
  }
}

td::Status AdnlExtConnection::init_crypto(td::Slice S) {
  if (S.size() < 96) {
    return td::Status::Error(ErrorCode::protoviolation, "too small enc data");
  }
  CHECK(S.size() >= 96);
  td::UInt256 s1, s2;
  td::UInt128 v1, v2;
  as_slice(s1).copy_from(S.copy().truncate(32));
  S.remove_prefix(32);
  as_slice(s2).copy_from(S.copy().truncate(32));
  S.remove_prefix(32);
  as_slice(v1).copy_from(S.copy().truncate(16));
  S.remove_prefix(16);
  as_slice(v2).copy_from(S.copy().truncate(16));
  S.remove_prefix(16);
  if (is_client_) {
    in_ctr_.init(s1, v1);
    out_ctr_.init(s2, v2);
  } else {
    in_ctr_.init(s2, v2);
    out_ctr_.init(s1, v1);
  }
  inited_ = true;
  return td::Status::OK();
}

td::Status AdnlExtConnection::receive_packet(td::BufferSlice data) {
  LOG(DEBUG) << "received packet of size " << data.size();
  auto S = data.as_slice();
  S.truncate(data.size() - 32);
  auto D = data.as_slice();
  D.remove_prefix(data.size() - 32);

  if (td::sha256(S) != D) {
    return td::Status::Error(ErrorCode::protoviolation, "sha256 mismatch");
  }

  data.truncate(data.size() - 32);
  data.confirm_read(32);

  if (data.size() == 0) {
    // keepalive
    return td::Status::OK();
  }
  if (data.size() == 12) {
    auto F = fetch_tl_object<ton_api::tcp_ping>(data.clone(), true);
    if (F.is_ok()) {
      auto f = F.move_as_ok();
      auto obj = create_tl_object<ton_api::tcp_pong>(f->random_id_);
      send(serialize_tl_object(obj, true));
      return td::Status::OK();
    }
  }
  if (data.size() == 12) {
    auto F = fetch_tl_object<ton_api::tcp_pong>(data.clone(), true);
    if (F.is_ok()) {
      return td::Status::OK();
    }
  }

  return process_packet(std::move(data));
}

}  // namespace ton
