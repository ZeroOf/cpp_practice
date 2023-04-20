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
#include "server_adapter.h"

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
  std::shared_ptr<TcpIO::ClientFactory> ptr_client_factory_;
  std::shared_ptr<TcpIO::Server> ptr_server_;
  std::shared_ptr<TaskManager> ptr_task_manager_;
  std::unique_ptr<ServerAdapter> ptr_server_a_;
  std::unique_ptr<ServerAdapter> ptr_server_b_;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_DEMO_H_
