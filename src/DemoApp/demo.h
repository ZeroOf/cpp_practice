//
// Created by Will Lee on 2022/2/2.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_
#define CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_

#include <AppBase/appbase.h>
#include <Boost/Asio/AsioWrapper/server.h>
#include <boost/serialization/singleton.hpp>
#include <message.pb.h>
#include "task/task_pool.h"
#include "task/task_manager.h"

class Demo : public AppBase, public boost::serialization::singleton<Demo> {
 public:
  Demo();
  void OnMessage(std::shared_ptr<message::Msg> ptr);
 private:
  bool OnActivate() override;
  void OnDeactivate() override;
  std::string &AppName() override;

 private:
  boost::asio::thread_pool thread_pool_;
  std::shared_ptr<TcpIO::ClientFactory> pClientFactory_;
  TcpIO::Server server_;
  std::shared_ptr<TaskManager> pTaskManager_;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_
