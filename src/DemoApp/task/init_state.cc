//
// Created by Will Lee on 2021/12/11.
//

#include "init_state.h"
#include "Boost/Log/logwrapper/LogWrapper.h"
#include "task.h"
#include "demo.h"
void InitState::PreProcess(Task *pTask) {
  if (nullptr != pTask) {
    LOG_DEBUG("Init task : " << pTask->GetSeq());
  }
}
void InitState::Process(Task *pTask, std::shared_ptr<TaskMsg> pTaskMsg) {
  LOG_DEBUG("Init state process");
  Demo::get_mutable_instance().SendMsg2AServer();
  pTask->ChangeState(&Task::option_state_);
}
