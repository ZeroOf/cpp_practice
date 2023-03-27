//
// Created by Will Lee on 2022/12/8.
//

#include "task_manager.h"
#include "Boost/Log/logwrapper/LogWrapper.h"
#include "demo.h"

const static size_t NUM_STRANDS = 8;

TaskManager::TaskManager(boost::asio::thread_pool &thread_pool)
    : thread_pool_(thread_pool),
      task_pool_(thread_pool),
      strands_(NUM_STRANDS, boost::asio::strand<boost::asio::thread_pool::executor_type>(thread_pool_.executor())) {}

void TaskManager::ProcessMsg(std::shared_ptr<message::Msg> pMsg, uint32_t clientID, uint32_t seq) {
  Task *pTask = nullptr;
  if (INVALID_SEQ == seq) {
    pTask = task_pool_.GetTask();
  } else {
    pTask = task_pool_.GetTask(seq);
  }
  if (nullptr == pTask) {
    LOG_ERROR("Cannot found the task : " << pMsg->seq());
    return;
  }
  pTask->SetClientId(clientID);
  boost::asio::post(strands_[pTask->GetSeq() % NUM_STRANDS], [pTask, pMsg]() {
    std::shared_ptr<TaskMsg>
        pTaskMsg = std::static_pointer_cast<TaskMsg>(std::make_shared<RequestMsg>(pMsg, pMsg->seq()));
    pTask->Process(pTaskMsg);
  });
}
