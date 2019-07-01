void TestNode::web_error_response(std::shared_ptr<HttpServer::Response> response, std::string msg) {
  pt::ptree root;
  std::ostringstream oss;
  root.put("error", msg);
  pt::write_json(oss, root);
  response -> write(SimpleWeb::StatusCode::server_error_internal_server_error,
                    oss.str());
}

void TestNode::web_success_response(std::shared_ptr<HttpServer::Response> response, std::string msg) {
  pt::ptree root;
  std::ostringstream oss;
  root.put("result", msg);
  pt::write_json(oss, root);
  response -> write(oss.str());
}

void TestNode::web_success_response(std::shared_ptr<HttpServer::Response> response, pt::ptree result) {
  pt::ptree root;
  std::ostringstream oss;
  root.put_child("result", result);
  pt::write_json(oss, root);
  response -> write(oss.str());
}

void TestNode::run_web_server(td::actor::Scheduler* scheduler, td::actor::ActorOwn<TestNode>* x){
  HttpServer server;
  server.config.port = 8000;

  // get a time
  server.resource["^/time$"]["GET"] = [scheduler, x](std::shared_ptr<HttpServer::Response> response,
                                                     std::shared_ptr<HttpServer::Request> request) {

    std::thread work_thread([response, scheduler, x] {
      scheduler -> run_in_context([&] {
        td::actor::send_closure(x -> get(), &TestNode::get_server_time_web, response);
      });
    });
    work_thread.detach();
  };
  //

  // get a account
  server.resource["^/getaccount/(.+)$"]["GET"] = [scheduler, x](std::shared_ptr<HttpServer::Response> response,
                                                                          std::shared_ptr<HttpServer::Request> request) {
    std::string address = request -> path_match[1].str();

    std::thread work_thread([response, scheduler, x, address] {
      scheduler -> run_in_context([&] {
        td::actor::send_closure(x -> get(), &TestNode::get_account_state_web, address, response);
      });
    });
    work_thread.detach();
  };

  // get a block
  server.resource["^/getblock/(.+)$"]["GET"] = [scheduler, x](std::shared_ptr<HttpServer::Response> response,
                                                                          std::shared_ptr<HttpServer::Request> request) {
    std::string blkid_str = request -> path_match[1].str();
    std::thread work_thread([response, scheduler, x, blkid_str] {
      scheduler -> run_in_context([&] {
        td::actor::send_closure(x -> get(), &TestNode::get_block_web, blkid_str, response, true);
      });
    });
    work_thread.detach();
  };

  // get a last block
  server.resource["^/last$"]["GET"] = [scheduler, x](std::shared_ptr<HttpServer::Response> response,
                                                                          std::shared_ptr<HttpServer::Request> request) {
    std::thread work_thread([response, scheduler, x] {
      scheduler -> run_in_context([&] {
        td::actor::send_closure(x -> get(), &TestNode::get_server_mc_block_id_web, response);
      });
    });
    work_thread.detach();
  };
  
  server.start();
}