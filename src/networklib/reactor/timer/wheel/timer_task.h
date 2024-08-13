//
// Created by Will Lee on 2021/10/16.
//

#ifndef CPP_PRACTICE_TIMER_TASK_H
#define CPP_PRACTICE_TIMER_TASK_H

#include <functional>
#include <cstdint>

struct TimerTask {
  uint64_t timerID_;
  uint64_t round_;
  std::function<void()> func_;
};

#endif //CPP_PRACTICE_TIMER_TASK_H
