//
// Created by Will Lee on 2022/12/8.
//

#include "TaskManager.h"
#include "Boost/Log/logwrapper/LogWrapper.h"
TaskManager::TaskManager(boost::asio::thread_pool &thread_pool) : thread_pool_(thread_pool), task_pool_(thread_pool) {}
void TaskManager::ProcessMsg(std::shared_ptr<message::Msg> pMsg) {
  auto pTask = task_pool_.GetTask(pMsg->seq());
  if (!pTask) {
    LOG_ERROR("Cannot found the task : " << pMsg->seq());
    return;
  }
  std::shared_ptr<TaskMsg>
      pTaskMsg = std::static_pointer_cast<TaskMsg>(std::make_shared<RequestMsg>(pMsg, pMsg->seq()));
  pTask->Process(pTaskMsg);
}
