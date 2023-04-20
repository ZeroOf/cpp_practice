//
// Created by Will Lee on 2022/2/2.
//

#include "demo.h"
#include "Boost/Log/logwrapper/LogWrapper.h"
#include <client_manager.h>
#include "ServerA/server_a_adapter.h"
#include "ServerB/server_b_adapter.h"

Demo::Demo() {}

bool Demo::OnActivate() {
  ptr_client_factory_ = std::make_shared<ClientManager>(*ptr_thread_pool_);
  ptr_server_ = std::make_shared<TcpIO::Server>(*ptr_thread_pool_, ptr_client_factory_);
  ptr_task_manager_ = std::make_shared<TaskManager>(*ptr_thread_pool_);
  ptr_task_manager_->Init();
  if (!ptr_server_->Start("127.0.0.1", 8080)) {
    return false;
  }

  // init server a
  if (nullptr != ptr_server_a_) {
    LOG_ERROR("server a has been initialized");
    return false;
  }

  ptr_server_a_ = std::make_unique<ServerAAdapter>();
  if (!ptr_server_a_->Init()) {
    LOG_ERROR("server a init error");
    return false;
  }

  // init server b
  if (nullptr != ptr_server_b_) {
    LOG_ERROR("server b has been initialized");
    return false;
  }

  ptr_server_b_ = std::make_unique<ServerBAdapter>();

  if (!ptr_server_b_->Init()) {
    LOG_ERROR("server b init error");
    return false;
  }

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
  std::shared_ptr<message::Resp> ptr_msg = std::make_shared<message::Resp>();
  ptr_msg->set_seq(1);
  ptr_msg->set_msg("hello world");
  buffer.resize(ptr_msg->ByteSizeLong());
  ptr_msg->SerializeToArray(buffer.data(), buffer.size());
  std::static_pointer_cast<ClientManager>(ptr_client_factory_)->SendMsg(clientID, buffer);
}
void Demo::OnTimer(Task *pTask) {
  LOG_DEBUG("OnTimer");
  std::shared_ptr<TaskMsg> ptr_task_msg = std::make_shared<TaskMsg>();
  ptr_task_msg->msg_type_ = TaskMsg::MsgType::kTimeOut;
  ptr_task_msg->seq_ = pTask->GetSeq();
  ptr_task_manager_->ProcessMsg(ptr_task_msg, pTask);
}
