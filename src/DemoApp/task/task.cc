//
// Created by Will Lee on 2021/12/11.
//

#include "task.h"
#include "task_state.h"
#include "Boost/Log/logwrapper/LogWrapper.h"

InitState Task::init_state_;
OptionState Task::option_state_;

Task::Task(uint32_t index)
    : index_(index), p_state_(&init_state_) {}

void Task::Process(std::shared_ptr<TaskMsg> pTaskMsg) {
  if (nullptr != p_state_) {
    p_state_->Process(this, pTaskMsg);
  }
}

void Task::ChangeState(TaskState *pNewState) {
  p_state_ = pNewState;
  if (nullptr == p_state_) {
    LOG_ERROR("state pointer is null");
    assert(false);
  }
  p_state_->PreProcess(this);
}
