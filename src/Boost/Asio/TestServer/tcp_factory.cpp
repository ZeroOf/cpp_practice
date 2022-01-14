//
// Created by Will Lee on 2022/1/1.
//

#include "tcp_factory.h"
#include <Asio/AsioWrapper/tcp_client.h>
#include "test_client.h"
std::shared_ptr<Client> TcpFactory::GetClient(boost::asio::ip::tcp::socket &socket) {
  auto client = std::make_shared<TcpIO::TestClient>(thread_pool_, "", "");
  clients_.insert(client);
  return std::shared_ptr<TcpClient>(new TcpClient(thread_pool_,
                                                  std::static_pointer_cast<TcpIO::IOInterface>(client),
                                                  std::move(socket)),
                                    [client](TcpClient *tcp_client) { delete tcp_client; });
}
TcpFactory::TcpFactory(boost::asio::thread_pool &thread_pool) : thread_pool_(thread_pool) {}
