//
// Created by Will Lee on 2021/12/25.
//

#ifndef CPP_PRACTICE_CLIENT_FACTORY_H
#define CPP_PRACTICE_CLIENT_FACTORY_H

#include "client.h"

namespace TcpIO {

class ClientFactory {
 public:
  virtual std::shared_ptr<TcpIO::IOInterface> GetClient(boost::asio::ip::tcp::socket &socket) = 0;
};

}

#endif //CPP_PRACTICE_CLIENT_FACTORY_H
