//
// Created by Will Lee on 2022/1/1.
//

#include "tcp_factory.h"
#include <Asio/AsioWrapper/tcp_client.h>
std::shared_ptr<Client> TcpFactory::GetClient(boost::asio::ip::tcp::socket &socket) {
  return std::make_shared<TcpClient>();
}
