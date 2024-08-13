#ifndef __TIMER_H__
#define __TIMER_H__

#include <functional>
#include <common.h>

COMPONENT_SPACE_START

class Timer {
 public:
  using TimerCallback = std::function<void()>;

  Timer(int initialTime, int periodicTime, TimerCallback &&cb);

  ~Timer();

  void Start();

  void Stop();

 private:
  static int CreateTimer();

  void SetTimer(int initialTime, int periodicTime) const;

  void HandleRead() const;

 private:
  int _fd;
  int _initialTime;
  int _periodicTime;
  bool _isStarted;
  TimerCallback _cb;
};

COMPONENT_SPACE_END

#endif
