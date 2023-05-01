//
// Created by Will Lee on 2022/12/8.
//

#include "task_manager.h"
#include "Boost/Log/logwrapper/log_wrapper.h"
#include "demo.h"

const static size_t NUM_STRANDS = 8;

TaskManager::TaskManager(boost::asio::thread_pool &thread_pool)
    : thread_pool_(thread_pool),
      task_pool_(thread_pool),
      strands_(NUM_STRANDS, boost::asio::strand<boost::asio::thread_pool::executor_type>(thread_pool_.executor())) {
}

void TaskManager::ProcessMsg(std::shared_ptr<message::Msg> pMsg, uint32_t clientID, uint32_t seq) {
  LOG_DEBUG("Process msg : " << pMsg->seq() << ", clientID : " << clientID << ", seq : " << seq);
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
  LOG_DEBUG("Task " << pTask->GetSeq() << " process msg : " << pMsg->seq());
  pTask->SetClientId(clientID);
  boost::asio::post(strands_[pTask->GetSeq() % NUM_STRANDS], [pTask, pMsg]() {
    LOG_DEBUG("Task " << pTask->GetSeq() << " process msg : " << pMsg->seq());
    std::shared_ptr<TaskMsg>
        pTaskMsg = std::static_pointer_cast<TaskMsg>(std::make_shared<RequestMsg>(pMsg, pMsg->seq()));
    pTask->Process(pTaskMsg);
  });
}
void TaskManager::Init() {
  LOG_DEBUG("TaskManager init");
}
void TaskManager::ProcessMsg(std::shared_ptr<TaskMsg> ptr_task_msg, Task *ptr_task) {
  if (task_pool_.GetTask(ptr_task->GetSeq()) == nullptr) {
    LOG_ERROR("Cannot found the task : " << ptr_task->GetSeq());
    return;
  }
  boost::asio::post(strands_[ptr_task->GetSeq() % NUM_STRANDS], [ptr_task, ptr_task_msg]() {
    LOG_DEBUG("Task " << ptr_task->GetSeq() << " process msg : " << ptr_task_msg->seq_);
    ptr_task->Process(ptr_task_msg);
  });
}
void TaskManager::ReleaseTask(Task *ptr_task) {
  LOG_DEBUG("Release task : " << ptr_task->GetSeq());
  task_pool_.ReleaseTask(ptr_task);
}
