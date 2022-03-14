//
// Created by Will Lee on 2021/12/11.
//

#ifndef CPP_PRACTICE_TASK_H
#define CPP_PRACTICE_TASK_H

#include <string>
#include "TaskMsg.h"

class TaskState;

class Task {
 public:
  void ChangeState(TaskState *pNewState);

  void Process(TaskMsg *pTaskMsg);

 private:
  uint32_t index_;
  uint32_t seq_;
  std::string request_;
  std::string response_;
  TaskState *state_;
};

#endif //CPP_PRACTICE_TASK_H