bool TestNode::get_server_mc_block_id_web(std::shared_ptr<HttpServer::Response> response) {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getMasterchainInfo>(), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this), response](td::Result<td::BufferSlice> res)->void {
    if (res.is_error()) {
      web_error_response(response, "cannot get masterchain info from server");
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_masterchainInfo>(res.move_as_ok(), true);
      if (F.is_error()) {
        web_error_response(response, "cannot parse answer to liteServer.getMasterchainInfo");
      } else {
        auto f = F.move_as_ok();
        auto blk_id = create_block_id(f->last_);
        // auto zstate_id = create_zero_state_id(f->init_);
        web_success_response(response, blk_id.to_str());
      }
    }
  });
}