//
// Created by God on 2021/5/1.
//

#include "tcp_client.h"
#include <memory>
#include "test_client.h"
#include <boost/thread.hpp>
#include "ssl_client.h"

std::shared_ptr<TcpIO::TestClient> Start(boost::asio::thread_pool &threadPool);

int main(int argc, const char *argv[]) {
  boost::asio::thread_pool threadPool;
  auto pC = Start(threadPool);
  threadPool.join();
}

std::shared_ptr<TcpIO::TestClient> Start(boost::asio::thread_pool &threadPool) {
  std::shared_ptr<TcpIO::TestClient> pClient = std::make_shared<TcpIO::TestClient>(threadPool, "127.0.0.1", "8080");
  pClient->Start(std::shared_ptr<boost::asio::ssl::context>());
  return pClient;
}
