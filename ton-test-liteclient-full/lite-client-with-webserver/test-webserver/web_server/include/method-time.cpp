void TestNode::get_server_time_web(std::shared_ptr<HttpServer::Response> response) {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getTime>(), true);

  envelope_send_web(std::move(b), [&, Self = actor_id(this), response](td::Result<td::BufferSlice> res) -> void {
    if (res.is_error()) {
      response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                        "{\"error\":\"cannot get server time\"}");
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_currentTime>(res.move_as_ok(), true);
      if (F.is_error()) {
        response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                          "{\"error\":\"cannot parse answer to liteServer.getTime\"}");
      } else {
        server_time_ = F.move_as_ok()->now_;
        server_time_got_at_ = static_cast<td::uint32>(td::Clocks::system());
        response -> write("{\"result\":\"" + std::to_string(server_time_) + "\"}");
      }
    }
  }, response);
}