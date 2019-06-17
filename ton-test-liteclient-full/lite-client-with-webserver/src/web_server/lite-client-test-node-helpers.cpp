td::Result<std::pair<Ref<vm::Cell>, std::shared_ptr<vm::StaticBagOfCellsDb>>> lazy_boc_deserialize(
    td::BufferSlice data) {
  vm::StaticBagOfCellsDbLazy::Options options;
  options.check_crc32c = true;
  TRY_RESULT(boc, vm::StaticBagOfCellsDbLazy::create(vm::BufferSliceBlobView::create(std::move(data)), options));
  TRY_RESULT(rc, boc->get_root_count());
  if (rc != 1) {
    return td::Status::Error(-668, "bag-of-cells is not standard (exactly one root cell expected)");
  }
  TRY_RESULT(root, boc->get_root_cell(0));
  return std::make_pair(std::move(root), std::move(boc));
}

bool TestNode::parse_account_addr(std::string acc_string, ton::WorkchainId& wc, ton::StdSmcAddress& addr) {
  block::StdAddress a{acc_string};
  if (a.is_valid()) {
    wc = a.workchain;
    addr = a.addr;
    return true;
  }
  auto pos = acc_string.find(':');
  if (pos != std::string::npos) {
    std::string tmp{acc_string, 0, pos};
    char* end = 0;
    wc = static_cast<ton::WorkchainId>(strtoll(tmp.c_str(), &end, 10));
    if (end != tmp.c_str() + pos) {
      return false;
    }
    if (wc != 0 && wc != -1) {
      return false;
    }
    acc_string.erase(0, pos + 1);
  }
  LOG(DEBUG) << "parsing " << acc_string << " address";
  if (acc_string.size() == 64) {
    int i = 0;
    for (int c : acc_string) {
      int x = parse_hex_digit(c), m = 15;
      if (x < 0) {
        i = -1;
        break;
      }
      if (!(i & 1)) {
        x <<= 4;
        m <<= 4;
      }
      addr.data()[i >> 1] = (unsigned char)((addr.data()[i >> 1] & ~m) | x);
      i++;
    }
    if (i >= 0) {
      return wc != ton::workchainInvalid;
    }
  }
  return false;
}

bool TestNode::envelope_send_web(td::BufferSlice query,
                                 td::Promise<td::BufferSlice> promise,
                                 std::shared_ptr<HttpServer::Response> response) {
  if (!ready_ || client_.empty()) {
    web_error_response(response, "failed to send query to server: not ready");
    return false;
  }
  auto P = td::PromiseCreator::lambda([promise = std::move(promise), response](td::Result<td::BufferSlice> R) mutable {
    if (R.is_error()) {
      auto err = R.move_as_error();
      web_error_response(response, "failed query");
      promise.set_error(std::move(err));
      return;
    }
    auto data = R.move_as_ok();
    auto F = ton::fetch_tl_object<ton::ton_api::liteServer_error>(data.clone(), true);
    if (F.is_ok()) {
      auto f = F.move_as_ok();
      auto err = td::Status::Error(f->code_, f->message_);
      web_error_response(response, "received error");
      promise.set_error(std::move(err));
      return;
    }
    promise.set_result(std::move(data));
  });
  td::BufferSlice b =
      ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_query>(std::move(query)), true);
  td::actor::send_closure(client_, &ton::AdnlExtClient::send_query, "query", std::move(b), td::Timestamp::in(10.0),
                          std::move(P));
  return true;
}

bool TestNode::get_server_mc_block_id_silent() {
  auto b = ton::serialize_tl_object(ton::create_tl_object<ton::ton_api::liteServer_getMasterchainInfo>(), true);
  return envelope_send_query(std::move(b), [Self = actor_id(this)](td::Result<td::BufferSlice> res) -> void {
    if (res.is_error()) {
      return;
    } else {
      auto F = ton::fetch_tl_object<ton::ton_api::liteServer_masterchainInfo>(res.move_as_ok(), true);
      if (F.is_error()) {
      } else {
        auto f = F.move_as_ok();
        auto blk_id = create_block_id(f->last_);
        auto zstate_id = create_zero_state_id(f->init_);
        td::actor::send_closure_later(Self, &TestNode::got_server_mc_block_id_silent, blk_id, zstate_id);
      }
    }
  });
}

void TestNode::got_server_mc_block_id_silent(ton::BlockIdExt blkid, ton::ZeroStateIdExt zstateid) {
  if (!zstate_id_.is_valid()) {
    zstate_id_ = zstateid;
  } else if (zstate_id_ != zstateid) {
    stop();
    return;
  }
  register_blkid(blkid);
  //register_blkid(zstateid);
  if (!mc_last_id_.is_valid()) {
    mc_last_id_ = blkid;
    request_block(blkid);
    // request_state(blkid);
  } else if (mc_last_id_.id.seqno < blkid.id.seqno) {
    mc_last_id_ = blkid;
  }
}