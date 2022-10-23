//
// Created by Will Lee on 2021/12/11.
//

#ifndef CPP_PRACTICE_INITSTATE_H
#define CPP_PRACTICE_INITSTATE_H

#include "TaskState.h"

class InitState : public TaskState {
 public:
  void PreProcess(std::shared_ptr<Task> pTask) override;
  void Process(std::shared_ptr<Task> pTask, TaskMsg *pTaskMsg) override;
};

#endif //CPP_PRACTICE_INITSTATE_H
