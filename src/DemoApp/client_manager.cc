//
// Created by Will Lee on 2022/2/2.
//

#include "client_manager.h"
#include "Boost/Asio/AsioWrapper/tcp_client.h"

std::shared_ptr<TcpIO::Client> ClientManager::GetClient(boost::asio::ip::tcp::socket &&socket) {
  std::shared_ptr<TcpIO::IOInterface> pInterface = std::make_shared<ClientHandler>(seq_++);
  std::shared_ptr<TcpIO::Client>
      pClient = std::make_shared<TcpIO::TcpClient>(thread_pool_, pInterface, std::move(socket));
  return pClient;
}
ClientManager::ClientManager(boost::asio::thread_pool &thread_pool) : thread_pool_(thread_pool) {}

void ClientManager::OnClose(size_t client_seq) {
  living_clients_.erase(client_seq);
}
