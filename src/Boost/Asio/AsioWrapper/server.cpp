//
// Created by Will Lee on 2021/12/22.
//

#include "server.h"
#include "LogWrapper.h"

Server::Server(boost::asio::thread_pool &threadPool, std::shared_ptr<ClientFactory> pClientFactory) : acceptor_(
    threadPool), pClientFactory_(pClientFactory) {

}

void Server::Start(std::string ip, uint32_t port) {
  ip_ = ip;
  port_ = port_;
  try {
    local_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip_), port);
    acceptor_.open(local_.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(local_);
    acceptor_.listen();
  } catch (const std::exception &exception) {
    LOG_ERROR(exception.what());
    exit(-1);
  }
  acceptor_.async_accept(std::bind(&Server::HandleAccept, this, std::placeholders::_1, std::placeholders::_2));
}

void Server::HandleAccept(const boost::system::error_code &ec, boost::asio::ip::tcp::socket s) {
  if (ec) {
    LOG_ERROR("accect failed, error : " << ec);
    exit(-1);
  }
  auto client = pClientFactory_->GetClient(s);
  client->Start();
  acceptor_.async_accept(std::bind(&Server::HandleAccept, this, std::placeholders::_1, std::placeholders::_2));
}
