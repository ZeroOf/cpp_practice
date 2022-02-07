//
// Created by Will Lee on 2022/2/2.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_CLIENT_H_
#define CPP_PRACTICE_SRC_DEMOAPP_CLIENT_H_

#include <Boost/Asio/AsioWrapper/io_interface.h>

const uint32_t MAX_PACKAGE = 1024 * 1024;

class Client : public TcpIO::IOInterface {
 public:
  void OnRead(std::vector<char> msg) override;
  void OnConnected() override;
  void OnConnectFailed() override;
  void OnSend(bool isSendSuccess, uint32_t msgType) override;
  std::pair<TcpIO::buffer_iterator, bool> IsPackageComplete(TcpIO::buffer_iterator begin,
                                                            TcpIO::buffer_iterator end) override;
  void OnClose() override;
  void Start() override;

};

#endif //CPP_PRACTICE_SRC_DEMOAPP_CLIENT_H_
