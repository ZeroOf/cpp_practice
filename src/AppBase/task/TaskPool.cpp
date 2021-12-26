//
// Created by Will Lee on 2021/12/11.
//

#include "TaskPool.h"

std::shared_ptr<Task> TaskPool::GetTask(uint32_t seq) {
    std::scoped_lock lock(lockTasks_);
    if (freeTasks_.empty()) {
        NewTasks();
    }
    auto it = freeTasks_.front();
    std::shared_ptr<Task> pTask(&*it, [it, this](auto p) {
        std::scoped_lock lock(lockTasks_);
        freeTasks_.push_back(it);
    });
    return pTask;
}

void TaskPool::NewTasks() {
    Tasks_.resize(Tasks_.size() + 50);
    for (int i = 0; i < 50; ++i) {
        freeTasks_.push_back(Tasks_.end() - i - 1);
    }
}
