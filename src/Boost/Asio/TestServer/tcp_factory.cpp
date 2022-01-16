//
// Created by Will Lee on 2022/1/1.
//

#include "tcp_factory.h"
#include <Asio/AsioWrapper/tcp_client.h>
#include "test_client.h"
std::shared_ptr<Client> TcpFactory::GetClient(boost::asio::ip::tcp::socket &socket) {
  auto pClientInterface = std::make_shared<TcpIO::TestClient>(thread_pool_, "", "", *this);
  clients_.insert(pClientInterface);
  auto pClient = std::make_shared<TcpClient>(thread_pool_,
                                             std::static_pointer_cast<TcpIO::IOInterface>(pClientInterface),
                                             std::move(socket));
  clients_.insert(pClientInterface);
  pClient->SetIOInterface(pClientInterface);
  pClientInterface->SetClient(pClient);
  return pClient;
}
TcpFactory::TcpFactory(boost::asio::thread_pool &thread_pool) : thread_pool_(thread_pool) {}
