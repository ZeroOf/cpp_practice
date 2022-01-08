//
// Created by Will Lee on 2022/1/1.
//

#ifndef CPP_PRACTICE_TCP_FACTORY_H
#define CPP_PRACTICE_TCP_FACTORY_H

#include <Asio/AsioWrapper/client_factory.h>
#include <memory>
#include <boost/asio/ip/tcp.hpp>

class TcpFactory : public ClientFactory {
 public:
  std::shared_ptr<Client> GetClient(boost::asio::ip::tcp::socket &socket) override;

 private:
  boost::asio::thread_pool &thread_pool_;
};

#endif //CPP_PRACTICE_TCP_FACTORY_H
