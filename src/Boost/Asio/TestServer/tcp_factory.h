//
// Created by Will Lee on 2022/1/1.
//

#ifndef CPP_PRACTICE_TCP_FACTORY_H
#define CPP_PRACTICE_TCP_FACTORY_H

#include <Asio/AsioWrapper/client_factory.h>
#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/thread_pool.hpp>
#include <set>
#include "test_client.h"

class TcpFactory : public ClientFactory {
 public:
  TcpFactory(boost::asio::thread_pool &thread_pool);
  std::shared_ptr<TcpIO::IOInterface> GetClient(boost::asio::ip::tcp::socket &socket) override;
  void Release(std::shared_ptr<TcpIO::TestClient> ptr_Client);

 private:
  boost::asio::thread_pool &thread_pool_;
  boost::asio::strand<boost::asio::thread_pool::executor_type> strand_;
  std::set<std::shared_ptr<TcpIO::TestClient>> clients_;
};

#endif //CPP_PRACTICE_TCP_FACTORY_H
