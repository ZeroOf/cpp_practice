#ifndef CPP_PRACTICE_TIMER_WHEEL_H
#define CPP_PRACTICE_TIMER_WHEEL_H

#include "second_grid.h"
#include <array>
#include <vector>
#include <list>


template<typename Task>
struct TimeWheel {
  int size;
  int tick;
  int position;
  std::vector<std::list<Task>> slots;

  TimeWheel(int size, int tick) : size(size), tick(tick), position(0), slots(size) {}

  void addTask(Task task, int delay) {
    // 计算任务应该被添加到哪个槽位
    int slot = (position + delay / tick) % size;
    slots[slot].push_back(task);
  }

  void advance() {
    position = (position + 1) % size;
    // 处理当前槽位中的任务
    for (auto it = slots[position].begin(); it != slots[position].end();) {
      if (it->Expired()) {
        it = slots[position].erase(it);
      } else {
        ++it;
      }
    }
  }
};


#endif //CPP_PRACTICE_TIMER_WHEEL_H
