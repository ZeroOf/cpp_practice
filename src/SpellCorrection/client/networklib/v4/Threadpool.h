#ifndef __WILL_THREADPOOL_H__
#define __WILL_THREADPOOL_H__

#include "TaskQueue.h"

#include <vector>
#include <memory>
#include <functional>
using std::unique_ptr;
using std::vector;

namespace component {

class Thread;
class Threadpool {
 public:
  typedef std::function<void()> Task;
  Threadpool(size_t threadNum, size_t queSize);
  ~Threadpool();

  void Start();
  void Stop();
  void AddTask(Task &&task);
 private:
  Task GetTask();

  void ThreadFunc();
 private:
  size_t _threadNum;
  size_t _queSize;
  vector<unique_ptr<Thread>> _threads;
  TaskQueue _taskQue;
  bool _isExit;
};

}//end of namespac net


#endif
