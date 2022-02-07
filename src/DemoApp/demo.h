//
// Created by Will Lee on 2022/2/2.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_
#define CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_

#include <AppBase/AppBase.h>
#include <Boost/Asio/AsioWrapper/server.h>

class Demo : public AppBase {
  bool OnActivite() override;
  void OnDeactivite() override;
  std::string &AppName() override;

 private:
  TcpIO::Server server_;
 public:
  void OnMessage();
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_
