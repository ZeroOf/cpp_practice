//
// Created by Will Lee on 2022/2/2.
//

#include "client_factory.h"
std::shared_ptr<TcpIO::Client> ClientFactory::GetClient(boost::asio::ip::tcp::socket &&socket) {
  return std::shared_ptr<TcpIO::Client>();
}
ClientFactory::ClientFactory(boost::asio::thread_pool &thread_pool) : thread_pool_(thread_pool) {}
