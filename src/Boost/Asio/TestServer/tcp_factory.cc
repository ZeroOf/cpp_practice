//
// Created by Will Lee on 2022/1/1.
//

#include "tcp_factory.h"
#include <Asio/AsioWrapper/tcp_client.h>
#include "test_client.h"
std::shared_ptr<TcpIO::Client> TcpFactory::GetClient(boost::asio::ip::tcp::socket &&socket) {
  auto pClientInterface = std::make_shared<TcpIO::TestClient>(thread_pool_,
                                                              socket.remote_endpoint().address().to_string(),
                                                              socket.remote_endpoint().port(),
                                                              *this);
  auto pClient = std::make_shared<TcpIO::TcpClient>(thread_pool_,
                                                    std::static_pointer_cast<TcpIO::IOInterface>(pClientInterface),
                                                    std::move(socket));
  pClientInterface->SetClient(pClient);
  return pClient;
}

TcpFactory::TcpFactory(boost::asio::thread_pool &thread_pool)
    : thread_pool_(thread_pool), strand_(boost::asio::make_strand(thread_pool_)) {}

void TcpFactory::Release(std::shared_ptr<TcpIO::TestClient> ptr_Client) {
}
