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
#include "task.h"

enum : uint32_t {
  INVALID_TASK_ID = UINT32_MAX
};

class TaskPool {
 public:
  explicit TaskPool(boost::asio::thread_pool &thread_pool);
  Task * GetTask(uint32_t seq);
  Task * GetTask();
 private:
  void NewTasks();
 private:
  std::deque<Task> tasks_;
  std::list<Task*> free_tasks_;
  std::map<uint32_t, std::deque<Task>::iterator> working_Tasks_;
  std::mutex tasks_lock_;
  boost::asio::thread_pool &threadPool_;
};

#endif //CPP_PRACTICE_TASKPOOL_H
