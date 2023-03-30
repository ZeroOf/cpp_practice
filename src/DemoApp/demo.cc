//
// Created by Will Lee on 2022/2/2.
//

#include "demo.h"
#include "Boost/Log/logwrapper/LogWrapper.h"
#include <client_manager.h>
#include "task/task_wrapper.hpp"

Demo::Demo() {}

bool Demo::OnActivate() {
  ptr_thread_pool_ = std::make_shared<boost::asio::thread_pool>(4);
  ptr_client_factory_ = std::make_shared<ClientManager>(*ptr_thread_pool_);
  ptr_server_ = std::make_shared<TcpIO::Server>(*ptr_thread_pool_, ptr_client_factory_);
  ptr_task_manager_ = std::make_shared<TaskManager>(*ptr_thread_pool_);
  ptr_task_manager_->Init();
  ptr_server_->Start("127.0.0.1", 8080);
  return true;
}
void Demo::OnDeactivate() {
  LOG_INFO("Demo exit");
}
std::string &Demo::AppName() {
  static std::string name("Demo");
  return name;
}

void Demo::OnMessage(std::shared_ptr<message::Msg> ptr, uint32_t clientID, uint32_t seq) {
  ptr_task_manager_->ProcessMsg(ptr, clientID, seq);
}
void Demo::SendMsg2AServer() {
  LOG_DEBUG("SendMsg2AServer");
}
void Demo::SendBack(uint32_t clientID, std::vector<char> buffer) {
  LOG_DEBUG("SendBack to client : " << clientID);
  std::shared_ptr<message::Msg> pMsg = std::make_shared<message::Msg>();
  pMsg->set_seq(1);
  pMsg->set_type(static_cast<message::MsgType>(1));
  pMsg->set_msg("hello world");
  std::static_pointer_cast<ClientManager>(ptr_client_factory_)->SendMsg(clientID, buffer);
}
void Demo::OnTimer(Task *pTask) {

}
