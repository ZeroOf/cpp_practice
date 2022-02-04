//
// Created by Will Lee on 2021/12/11.
//

#ifndef CPP_PRACTICE_TASKSTATE_H
#define CPP_PRACTICE_TASKSTATE_H

#include "TaskMsg.h"

class Task;

class TaskState {
public:
    virtual void PreProcess(Task *pTask) = 0;

    virtual void Process(Task *pTask, TaskMsg *pTaskMsg) = 0;
};


#endif //CPP_PRACTICE_TASKSTATE_H
