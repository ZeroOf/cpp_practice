#ifndef __WILL_THREAD_H__
#define __WILL_THREAD_H__

#include <pthread.h>
#include <functional>
#include "noncopyable.h"

COMPONENT_SPACE_START

class Thread : Noncopyable {
 public:
  using ThreadCallback = std::function<void()>;

  Thread(ThreadCallback &&cb);

  ~Thread();

  void Start();

  void Join();

  bool IsRunning() const { return isRunning_; }

  bool SetCPUAffinity(unsigned cupID);

 private:
  static void *threadFunc(void *arg);//线程的执行体
 private:
  pthread_t threadID_;
  bool isRunning_;
  ThreadCallback callback_;
};

COMPONENT_SPACE_END

#endif



