//
// Created by Will Lee on 2022/12/8.
//

#include "TaskManager.h"
#include "Boost/Log/logwrapper/LogWrapper.h"
TaskManager::TaskManager(boost::asio::thread_pool &thread_pool) : thread_pool_(thread_pool) {}
void TaskManager::ProcessMsg(std::shared_ptr<message::Msg> pMsg, std::unique_ptr<TaskMsg> pTaskMsg) {
  auto pTask = task_pool_.GetTask(pMsg->seq());
  if (!pTask) {
    LOG_ERROR("Cannot found the task : " << pMsg->seq());
    return;
  }
  pTask->Process(pMsg);
}
