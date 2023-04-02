//
// Created by Will Lee on 2022/2/2.
//

#include "client_manager.h"
#include "Boost/Asio/AsioWrapper/tcp_client.h"
#include "Boost/Log/logwrapper/LogWrapper.h"

std::shared_ptr<TcpIO::Client> ClientManager::GetClient(boost::asio::ip::tcp::socket &&socket) {
  auto ptr_handler = std::make_shared<ClientHandler>(seq_++, shared_from_this());
  std::shared_ptr<TcpIO::Client>
      pClient = std::make_shared<TcpIO::TcpClient>(thread_pool_, ptr_handler, std::move(socket));
  {
    std::lock_guard<std::mutex> lock(lock4living_clients_);
    living_clients_.insert(std::make_pair(ptr_handler->GetSeq(), pClient));
  }
  return pClient;
}
ClientManager::ClientManager(boost::asio::thread_pool &thread_pool) : thread_pool_(thread_pool) {}

void ClientManager::OnClose(size_t client_seq) {
  std::lock_guard<std::mutex> lock(lock4living_clients_);
  living_clients_.erase(client_seq);
}
bool ClientManager::SendMsg(uint32_t clientSeq, std::vector<char> buf) {
  LOG_DEBUG("SendMsg to client : " << clientSeq);
  auto it = living_clients_.find(clientSeq);
  if (it != living_clients_.end()) {
    it->second->SendMsg(std::string(buf.begin(), buf.end()), 0);
    return true;
  }
  LOG_DEBUG("SendMsg to client : " << clientSeq << " failed");
  return false;
}
