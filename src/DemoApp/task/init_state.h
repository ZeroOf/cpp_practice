//
// Created by Will Lee on 2021/12/11.
//

#ifndef CPP_PRACTICE_INITSTATE_H
#define CPP_PRACTICE_INITSTATE_H

#include "task_state.h"

class InitState : public TaskState {
 public:
  void PreProcess(Task *pTask) override;
  void Process(Task *pTask, std::shared_ptr<TaskMsg> pTaskMsg) override;
};

#endif //CPP_PRACTICE_INITSTATE_H
