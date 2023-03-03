//
// Created by Will Lee on 2021/12/11.
//

#include "task.h"
#include "task_state.h"
#include "Boost/Log/logwrapper/LogWrapper.h"

InitState Task::init_state_;
OptionState Task::option_state_;

Task::Task(uint32_t index, boost::asio::thread_pool &threadPool)
    : index_(index), p_state_(&init_state_), timer_(threadPool) {}

void Task::Process(std::shared_ptr<TaskMsg> pTaskMsg) {
  if (nullptr == p_state_) {
    LOG_ERROR("state is null");
    return;
  }
  p_state_->Process(this, pTaskMsg);
}

void Task::ChangeState(TaskState *pNewState) {
  p_state_ = pNewState;
  if (nullptr == p_state_) {
    LOG_ERROR("state pointer is null");
    assert(false);
  }
  p_state_->PreProcess(this);
}
uint32_t Task::GetSeq() const {
  return seq_;
}
void Task::SetSeq(uint32_t seq) {
  seq_ = seq;
}
void Task::SetTimer() {
  timer_.expires_after(std::chrono::seconds(10));
  timer_.async_wait(std::bind(&Task::OnTimer, this, std::placeholders::_1));
}
void Task::OnTimer(const boost::system::error_code &error) {

}
uint32_t Task::GetClientId() const {
  return client_id_;
}
void Task::SetClientId(uint32_t client_id) {
  client_id_ = client_id;
}
