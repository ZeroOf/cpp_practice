//
// Created by Will Lee on 2021/12/11.
//

#include "init_state.h"
#include "Boost/Log/logwrapper/log_wrapper.h"
#include "task.h"
#include "demo.h"
void InitState::PreProcess(Task *pTask) {
  if (nullptr != pTask) {
    LOG_DEBUG("Init task : " << pTask->GetSeq());
  }
}
void InitState::Process(Task *pTask, std::shared_ptr<TaskMsg> pTaskMsg) {
  LOG_DEBUG("Init state process");
  if (pTask == nullptr || pTaskMsg == nullptr) {
    LOG_ERROR("pTask is nullptr");
  }
  switch (pTaskMsg->msg_type_) {
    case TaskMsg::kTimeOut: {
      LOG_ERROR("pTask is timeout");
      pTask->Release();
      return;
    }
    case TaskMsg::kTcpMsg: {
      LOG_DEBUG("get tcp msg");
      auto pRequestMsg = std::static_pointer_cast<RequestMsg>(pTaskMsg);
      pTask->SetRequest(pRequestMsg->ptr_msg_->msg());
      pTask->ChangeState(&Task::option_state_);
      return;
    }
    default: {
      LOG_ERROR("get unknown type msg:" << pTaskMsg->msg_type_);
      pTask->Release();
    }
  }
}
