//
// Created by Will Lee on 2022/2/2.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_CLIENT_FACTORY_H_
#define CPP_PRACTICE_SRC_DEMOAPP_CLIENT_FACTORY_H_

#include <Boost/Asio/AsioWrapper/client_factory.h>

class ClientFactory : public TcpIO::ClientFactory {
 public:
  ClientFactory(boost::asio::thread_pool &thread_pool);
  std::shared_ptr<TcpIO::Client> GetClient(boost::asio::ip::tcp::socket &&socket) override;
 private:
  boost::asio::thread_pool &thread_pool_;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_CLIENT_FACTORY_H_
