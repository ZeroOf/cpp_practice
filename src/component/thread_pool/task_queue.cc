
#include "task_queue.h"

USING_COMPONENT

TaskQueue::TaskQueue(int maxSize)
    : _maxSize(maxSize), _mutex(), _notFull(_mutex), _notEmpty(_mutex), shouldStop_(false) {}

bool TaskQueue::full() const {
  return _maxSize == _que.size();
}

bool TaskQueue::empty() const {
  return 0 == _que.size();
}

//运行在生产者线程
void TaskQueue::push(Type &&elem) {
  MutexLockGuard autoLock(_mutex);
  while (full()) {
    _notFull.wait();//使用while是为了防止被异常唤醒
  }
  _que.push(std::move(elem));
  _notEmpty.notify();
}

//运行在消费者线程
TaskQueue::Type TaskQueue::pop() {
  MutexLockGuard autoLock(_mutex);
  while (shouldStop_ && empty()) {
    _notEmpty.wait();
  }

  if (shouldStop_) {
    Type tmp = _que.front();
    _que.pop();
    _notFull.notify();
    return tmp;
  } else
    return nullptr;
}

void TaskQueue::WakeUp() {
  shouldStop_ = true;
  _notEmpty.notifyAll();
}
