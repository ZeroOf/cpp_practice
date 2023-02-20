//
// Created by Will Lee on 2022/2/2.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_CLIENT_HANDLER_H_
#define CPP_PRACTICE_SRC_DEMOAPP_CLIENT_HANDLER_H_

#include <Boost/Asio/AsioWrapper/io_interface.h>

const uint32_t MAX_PACKAGE = 1024 * 1024;

class ClientHandler : public TcpIO::IOInterface {
 public:
  explicit ClientHandler(size_t seq);
  bool OnRead(std::vector<char> msg) override;
  void OnConnected(const std::string &host, unsigned short port) override;
  void OnConnectFailed(const std::string &host, unsigned short port) override;
  void OnSend(bool isSendSuccess, uint32_t msgType) override;
  std::pair<TcpIO::buffer_iterator, bool> IsPackageComplete(TcpIO::buffer_iterator begin,
                                                            TcpIO::buffer_iterator end) override;
  void OnClose() override;
  void Start() override;
 private:
  size_t seq_;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_CLIENT_HANDLER_H_
