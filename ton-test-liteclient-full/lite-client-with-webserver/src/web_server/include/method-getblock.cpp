void TestNode::get_block_web(std::string blkid_str, std::shared_ptr<HttpServer::Response> response, bool dump) {
    ton::BlockIdExt blkid;
    if(!TestNode::parse_block_id_ext(blkid_str, blkid, true))
        {
          web_error_response(response, "cannot parse block_id");
        }

  auto b = ton::serialize_tl_object(
      ton::create_tl_object<ton::ton_api::liteServer_getBlock>(ton::create_tl_block_id(blkid)), true);
  envelope_send_query(
      std::move(b), [ Self = actor_id(this), blkid, dump, response](td::Result<td::BufferSlice> res)->void {
        if (res.is_error()) {
          web_error_response(response, "cannot obtain block " + blkid.to_str() + \
                                       " from server : " + res.move_as_error().to_string());
          return;
        } else {
          auto F = ton::fetch_tl_object<ton::ton_api::liteServer_blockData>(res.move_as_ok(), true);
          if (F.is_error()) {
            web_error_response(response, "cannot parse answer to liteServer.getBlock : " +\
                               res.move_as_error().to_string());
          } else {
            auto f = F.move_as_ok();
            auto blk_id = ton::create_block_id(f->id_);
            if (blk_id != blkid) {
              web_error_response(response, "block id mismatch: expected data for block " + blkid.to_str() +\
                                           ", obtained for " + blk_id.to_str());
            }
            td::actor::send_closure_later(Self, &TestNode::got_block_web, blk_id, std::move(f->data_), dump, response);
          }
        }
      });
}


void TestNode::got_block_web(ton::BlockIdExt blkid, td::BufferSlice data, bool dump, std::shared_ptr<HttpServer::Response> response) {
  LOG(INFO) << "obtained " << data.size() << " data bytes for block " << blkid.to_str();
  ton::FileHash fhash;
  td::sha256(data.as_slice(), fhash.as_slice());
  if (fhash != blkid.file_hash) {
    web_error_response(response, "file hash mismatch for block " + blkid.to_str() +\
                                 ": expected " + blkid.file_hash.to_hex() + ", computed " + fhash.to_hex());
    return;
  }
  if (!db_root_.empty()) {
    auto res = save_db_file(fhash, data.clone());
    if (res.is_error()) {
      web_error_response(response, "error saving block file: " + res.to_string());
    }
  }
  if (dump) {
    auto res = vm::std_boc_deserialize(data.clone());
    if (res.is_error()) {
      web_error_response(response, "cannot deserialize block data " + res.move_as_error().to_string());
      return;
    }
    auto root = res.move_as_ok();
    ton::RootHash rhash{root->get_hash().bits()};
    if (rhash != blkid.root_hash) {
      web_error_response(response, "block root hash mismatch: data has " + rhash.to_hex() +\
                                   " , expected " + blkid.root_hash.to_hex());
      return;
    }
    //auto out = td::TerminalIO::out();
    //out << "block contents is ";
    std::ostringstream block_data, vm_data, header_data;
    block::gen::t_Block.print_ref(block_data, root);
    vm::load_cell_slice(root).print_rec(vm_data);
    give_block_header_description(header_data, blkid, std::move(root), 0xffff);


    pt::ptree result;
    result.put("block", block_data.str());
    result.put("vm", vm_data.str());
    result.put("header", header_data.str());

    web_success_response(response, result);
  } else {
    auto res = lazy_boc_deserialize(data.clone());
    if (res.is_error()) {
      web_error_response(response, "cannot lazily deserialize block data : " + res.move_as_error().to_string());
      return;
    }
    auto pair = res.move_as_ok();
    auto root = std::move(pair.first);
    ton::RootHash rhash{root->get_hash().bits()};
    if (rhash != blkid.root_hash) {
      web_error_response(response, "block root hash mismatch: data has " + rhash.to_hex() +\
                                   " , expected " + blkid.root_hash.to_hex());
      return;
    }
    show_block_header(blkid, std::move(root), 0xffff);
  }
}

bool TestNode::give_block_header_description(std::ostringstream& out, ton::BlockIdExt blkid, Ref<vm::Cell> root, int mode) {
  ton::RootHash vhash{root->get_hash().bits()};
  if (vhash != blkid.root_hash) {
    LOG(ERROR) << " block header for block " << blkid.to_str() << " has incorrect root hash " << vhash.to_hex()
               << " instead of " << blkid.root_hash.to_hex();
    return false;
  }
  std::vector<ton::BlockIdExt> prev;
  ton::BlockIdExt mc_blkid, blkid_u = blkid;
  bool after_split;
  auto res = block::unpack_block_prev_blk_ext(root, blkid_u, prev, mc_blkid, after_split);
  if (res.is_error()) {
    LOG(ERROR) << "cannot unpack header for block " << blkid.to_str() << " : " << res.to_string();
    return false;
  }
  if (blkid_u.id != blkid.id || blkid_u.root_hash != blkid.root_hash) {
    LOG(ERROR) << "block header claims it is for block " << blkid_u.to_str() << " not " << blkid.to_str();
    return false;
  }
  block::gen::Block::Record blk;
  block::gen::BlockInfo::Record info;
  if (!(tlb::unpack_cell(root, blk) && tlb::unpack_cell(blk.info, info))) {
    LOG(ERROR) << "cannot unpack header for block " << blkid.to_str();
    return false;
  }
  out << "block header of " << blkid.to_str() << " @ " << info.gen_utime << " lt " << info.start_lt << " .. "
      << info.end_lt << std::endl;
  out << "global_id=" << blk.global_id << " version=" << info.version << " not_master=" << info.not_master
      << " after_merge=" << info.after_merge << " after_split=" << info.after_split
      << " before_split=" << info.before_split << " want_merge=" << info.want_merge << " want_split=" << info.want_split
      << " validator_list_hash_short=" << info.gen_validator_list_hash_short
      << " catchain_seqno=" << info.gen_catchain_seqno << " min_ref_mc_seqno=" << info.min_ref_mc_seqno << std::endl;
  int cnt = 0;
  for (auto id : prev) {
    out << "previous block #" << ++cnt << " : " << id.to_str() << std::endl;
  }
  out << "reference masterchain block : " << mc_blkid.to_str() << std::endl;
  return true;
}