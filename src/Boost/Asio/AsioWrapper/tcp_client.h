//
// Created by Singl on 2021/4/28.
//

#ifndef CPP_PRACTICE_TCPCLIENT_H
#define CPP_PRACTICE_TCPCLIENT_H

#include <boost/asio.hpp>
#include <memory>
#include "io_interface.h"
#include "client.h"

namespace TcpIO {

class TcpClient : public Client {
 public:
  TcpClient(boost::asio::thread_pool &threadPool, const std::shared_ptr<TcpIO::IOInterface> &ptrIoInterface);
  TcpClient(boost::asio::thread_pool &thread_pool,
            std::shared_ptr<TcpIO::IOInterface> ptr_io_interface,
            boost::asio::ip::tcp::socket &&socket);

  void Close() override;

  virtual ~TcpClient();

  void HandleConnect(const boost::system::error_code &ec, const boost::asio::ip::tcp::endpoint &remote);

  void Read() override;

  void HandleSend(const boost::system::error_code &ec,
                  size_t sendSize,
                  uint32_t msgType,
                  std::shared_ptr<std::string> pMsg);
 private:

  void Connect(const boost::system::error_code &ec,
               boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> remote) override;

 protected:
  void SendInLoop() override;

 private:
  boost::asio::ip::tcp::socket socket_;

};

}
#endif //CPP_PRACTICE_TCPCLIENT_H
