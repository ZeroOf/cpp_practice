//
// Created by Will Lee on 2022/2/2.
//

#include "client_factory.h"
#include "Boost/Asio/AsioWrapper/tcp_client.h"

std::shared_ptr<TcpIO::Client> ClientFactory::GetClient(boost::asio::ip::tcp::socket &&socket) {
  std::shared_ptr<TcpIO::IOInterface> pInterface = std::make_shared<ClientHandler>();
  std::shared_ptr<TcpIO::Client> pClient = std::make_shared<TcpIO::TcpClient>(thread_pool_, pInterface, std::move(socket));
  return pClient;
}
ClientFactory::ClientFactory(boost::asio::thread_pool &thread_pool) : thread_pool_(thread_pool) {}
