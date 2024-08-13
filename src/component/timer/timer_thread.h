#ifndef __TIMERTHREAD_H__
#define __TIMERTHREAD_H__

#include "thread.h"
#include "timer.h"

COMPONENT_SPACE_START

class TimerThread {
 public:
  using TimerCallback = std::function<void()>;

  TimerThread(int initialTime, int perodicTime, TimerCallback &&cb);

  void Start();

  void Stop();

 private:
  Timer _timer;
  Thread _thread;
};

COMPONENT_SPACE_END

#endif
