//
// Created by Will Lee on 2021/12/22.
//

#ifndef CPP_PRACTICE_SERVER_H
#define CPP_PRACTICE_SERVER_H

#include <memory>
#include <boost/asio.hpp>
#include "client_factory.h"

namespace TcpIO {


class Server : public std::enable_shared_from_this<Server> {
 public:
  Server(boost::asio::thread_pool &threadPool, std::shared_ptr<ClientFactory> pClientFactory);

  void Start(std::string ip, uint32_t port);

 private:
  void HandleAccept(const boost::system::error_code &ec, boost::asio::ip::tcp::socket s);

 private:
  boost::asio::ip::tcp::acceptor acceptor_;
  std::shared_ptr<ClientFactory> pClientFactory_;
  boost::asio::ip::tcp::endpoint local_;
  std::string ip_;
  uint32_t port_;
};

}

#endif //CPP_PRACTICE_SERVER_H
