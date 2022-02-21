//
// Created by God on 2021/5/4.
//

#ifndef CPP_PRACTICE_SRC_BOOST_ASIO_TCPCLIENT_IO_INTERFACE_H_TEST_CLIENT_H_
#define CPP_PRACTICE_SRC_BOOST_ASIO_TCPCLIENT_IO_INTERFACE_H_TEST_CLIENT_H_

#include <boost/asio/buffers_iterator.hpp>
#include "io_interface.h"
#include "tcp_client.h"
#include <optional>
#include <boost/asio/ssl.hpp>

namespace TcpIO {

class TestClient : public IOInterface {
 public:
  TestClient(boost::asio::thread_pool &threadPool,
             const std::string &&host,
             unsigned short service);

  bool OnRead(std::vector<char> msg) override;

  void OnConnected() override;

  void OnConnectFailed() override;

  void OnSend(bool isSendSuccess, uint32_t msgType) override;

  std::pair<buffer_iterator, bool> IsPackageComplete(buffer_iterator begin, buffer_iterator end) override;

  void OnClose() override;

  void Start();

  virtual ~TestClient();

 private:
  void DelayConnect();

 private:
  boost::asio::thread_pool &thread_pool_;
  std::shared_ptr<Client> ptr_client_;
  boost::asio::strand<boost::asio::thread_pool::executor_type> strand_;
  boost::asio::steady_timer timer_;
  std::string host_;
  unsigned short port_;
  size_t seq_ = 0;
  bool isConnected_ = false;
};

}

#endif //CPP_PRACTICE_SRC_BOOST_ASIO_TCPCLIENT_IO_INTERFACE_H_TEST_CLIENT_H_
