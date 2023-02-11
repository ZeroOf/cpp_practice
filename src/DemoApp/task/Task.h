//
// Created by Will Lee on 2021/12/11.
//

#ifndef CPP_PRACTICE_TASK_H
#define CPP_PRACTICE_TASK_H

#include <string>
#include <boost/asio/strand.hpp>
#include "TaskMsg.h"
#include "InitState.h"
#include "OptionState.h"
#include <boost/asio.hpp>

class TaskState;

class Task {
 public:
  explicit Task(uint32_t index);
  void ChangeState(TaskState *pNewState);

  void Process(std::shared_ptr<TaskMsg> pTaskMsg);

 private:
  uint32_t index_ = 0;
  uint32_t seq_ = 0;
  std::string request_;
  std::string response_;
  TaskState *p_state_{};
  static InitState init_state_;
  static OptionState option_state_;
};

#endif //CPP_PRACTICE_TASK_H
