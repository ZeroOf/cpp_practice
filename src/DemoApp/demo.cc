//
// Created by Will Lee on 2022/2/2.
//

#include "demo.h"
#include "Boost/Log/logwrapper/LogWrapper.h"
#include <client_manager.h>
#include "task/task_wrapper.hpp"

Demo::Demo() : pClientFactory_(std::make_shared<ClientManager>(thread_pool_)), server_(thread_pool_, pClientFactory_) {}

bool Demo::OnActivate() {
  server_.Start("127.0.0.1", 8080);
  return true;
}
void Demo::OnDeactivate() {
  LOG_INFO("Demo exit");
}
std::string &Demo::AppName() {
  static std::string name("Demo");
  return name;
}

void Demo::OnMessage(std::shared_ptr<message::Msg> ptr, uint32_t clientID) {
  pTaskManager_->ProcessMsg(ptr, clientID);
}
void Demo::SendMsg2AServer() {

}
