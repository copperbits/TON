
void TestNode::get_account_state_web(std::string address, std::shared_ptr<HttpServer::Response> response) {
  ton::WorkchainId workchain = ton::masterchainId;  // change to basechain later
  ton::StdSmcAddress addr;
  if (!TestNode::parse_account_addr(address, workchain, addr)){
    response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                      "{\"error\":\"parse_account_addr fail\"}");
    return;
  }

  if (!mc_last_id_.is_valid()) {
    response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                      "{\"error\":\"must obtain last block information before making other queries\"}");
    return;
  }
  if (!(ready_ && !client_.empty())) {
    response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                      "{\"error\":\"server connection not ready\"}");
    return;
  }

  auto a = ton::create_tl_object<ton::ton_api::liteServer_accountId>(workchain, ton::Bits256_2_UInt256(addr));
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getAccountState>(
                                        ton::create_tl_block_id(mc_last_id_), std::move(a)),
                                    true);

  envelope_send_web(
    std::move(b), [Self = actor_id(this), workchain, addr, response](td::Result<td::BufferSlice> R) -> void {
      if (R.is_error()) {
        response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                          "{\"error\":\"Unknown Error\"}");
        return;
      }
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_accountState>(R.move_as_ok(), true);
      if (F.is_error()) {
        response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                          "{\"error\":\"cannot parse answer to liteServer.getAccountState\"}");
      } else {
        auto f = F.move_as_ok();
        td::actor::send_closure_later(Self, &TestNode::got_account_state_web, ton::create_block_id(f->id_),
                                      ton::create_block_id(f->shardblk_), std::move(f->shard_proof_),
                                      std::move(f->proof_), std::move(f->state_), workchain, addr, response);
      }
    }, response);
}

void TestNode::got_account_state_web(ton::BlockIdExt blk, ton::BlockIdExt shard_blk, td::BufferSlice shard_proof,
                                     td::BufferSlice proof, td::BufferSlice state, ton::WorkchainId workchain,
                                     ton::StdSmcAddress addr, std::shared_ptr<HttpServer::Response> response) {
  if (state.empty()) {
    response -> write("{\"error\":\"account state is empty\"}");
  } else {
    auto R = vm::std_boc_deserialize(state.clone());
    if (R.is_error()) {
      response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                        "{\"error\":\"cannot deserialize account state\"}");
      return;
    }
    auto root = R.move_as_ok();
    std::ostringstream outp;
    block::gen::t_Account.print_ref(outp, root);
    vm::load_cell_slice(root).print_rec(outp);

    response -> write("{\"result\":\"" + outp.str() + "\"}");
  }
}