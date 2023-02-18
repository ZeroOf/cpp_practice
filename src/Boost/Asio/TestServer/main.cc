//
// Created by Will Lee on 2022/1/1.
//

#include <iostream>
#include <Asio/AsioWrapper/server.h>
#include "tcp_factory.h"
#include "Log/logwrapper/LogWrapper.h"

int main() {
  LogWrapper::get_mutable_instance().Init("TestServer");
  boost::asio::thread_pool thread_pool;
  std::shared_ptr<TcpFactory> ptr_tcp_factory = std::make_shared<TcpFactory>(thread_pool);
  TcpIO::Server server(thread_pool, ptr_tcp_factory);
  server.Start("0.0.0.0", 8080);
  thread_pool.attach();
}