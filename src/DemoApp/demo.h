//
// Created by Will Lee on 2022/2/2.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_
#define CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_

#include <AppBase/AppBase.h>
#include <Boost/Asio/AsioWrapper/server.h>

class Demo : public AppBase {
 public:
  Demo();
  void OnMessage();
 private:
  bool OnActivite() override;
  void OnDeactivite() override;
  std::string &AppName() override;

 private:
  boost::asio::thread_pool thread_pool_;
  std::shared_ptr<TcpIO::ClientFactory> pClientFactory_;
  TcpIO::Server server_;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_
