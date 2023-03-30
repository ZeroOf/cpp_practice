#include "task_pool.h"
#include "Boost/Log/logwrapper/LogWrapper.h"

Task *TaskPool::GetTask(uint32_t seq) {
  LOG_DEBUG("GetTask seq : " << seq);
  if (seq > tasks_.size()) {
    return nullptr;
  }
  return &tasks_[seq];
}

void TaskPool::NewTasks() {
  for (int i = 0; i < 50; ++i) {
    tasks_.emplace_back(tasks_.size() + 1, threadPool_);
    free_tasks_.push_back(&tasks_.back());
  }
}
Task *TaskPool::GetTask() {
  LOG_DEBUG("GetTask");
  std::scoped_lock lock(tasks_lock_);
  if (free_tasks_.empty()) {
    NewTasks();
  }
  auto pTask = free_tasks_.front();
  free_tasks_.pop_front();
  return pTask;
}
TaskPool::TaskPool(boost::asio::thread_pool &thread_pool) : threadPool_(thread_pool) {}
