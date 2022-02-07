//
// Created by Will Lee on 2021/12/11.
//

#ifndef CPP_PRACTICE_TASKPOOL_H
#define CPP_PRACTICE_TASKPOOL_H

#include <map>
#include <cstdint>
#include <memory>
#include <vector>
#include <deque>
#include <list>
#include <mutex>
#include "Task.h"

enum : uint32_t {
  INVALID_TASK_ID = UINT32_MAX
};

class TaskPool {
 public:
  std::shared_ptr<Task> GetTask(uint32_t seq);
  std::shared_ptr<Task> GetTask();

 private:

  void NewTasks();

 private:
  std::deque<Task> Tasks_;
  std::list<std::deque<Task>::iterator> freeTasks_;
  std::mutex lockTasks_;
};

#endif //CPP_PRACTICE_TASKPOOL_H
