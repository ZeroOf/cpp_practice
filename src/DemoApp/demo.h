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


const uint32_t INVALID_SEQ = -1;

class Demo : public AppBase, public boost::serialization::singleton<Demo> {
 public:
  Demo();
  void OnMessage(std::shared_ptr<message::Msg> ptr, uint32_t clientID, uint32_t seq);
  void SendMsg2AServer();
  void SendBack(uint32_t clientID, std::vector<char> buffer);
  void OnTimer(Task *pTask);
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
