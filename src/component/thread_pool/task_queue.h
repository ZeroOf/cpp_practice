
#ifndef __WILL_TASKQUEUE_H__
#define __WILL_TASKQUEUE_H__

#include "mutex_lock.h"
#include "Condition.h"
#include <queue>
#include <functional>

COMPONENT_SPACE_START

class TaskQueue {
 public:
  using Type = std::function<void()>;

  TaskQueue(int maxSize);

  bool full() const;

  bool empty() const;

  void push(Type &&type);

  Type pop();

  void WakeUp();

 private:
  size_t _maxSize;
  std::queue<Type> _que;
  MutexLock _mutex;
  Condition _notFull;
  Condition _notEmpty;
  bool shouldStop_;
};

COMPONENT_SPACE_END

#endif
