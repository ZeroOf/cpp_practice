//
// Created by Will Lee on 2022/2/2.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_CLIENT_FACTORY_H_
#define CPP_PRACTICE_SRC_DEMOAPP_CLIENT_FACTORY_H_

#include <Boost/Asio/AsioWrapper/client_factory.h>
#include <map>
#include "client_handler.h"

class ClientManager : public TcpIO::ClientFactory {
 public:
  ClientManager(boost::asio::thread_pool &thread_pool);
  std::shared_ptr<TcpIO::Client> GetClient(boost::asio::ip::tcp::socket &&socket) override;
 private:
  boost::asio::thread_pool &thread_pool_;
  std::map<size_t, std::shared_ptr<TcpIO::Client>> living_clients_;
  std::atomic_size_t seq_ = 0;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_CLIENT_FACTORY_H_
