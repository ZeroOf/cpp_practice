#ifndef __WILL_EVENTFD_THREAD_H__
#define __WILL_EVENTFD_THREAD_H__

#include "thread.h"
#include "eventfd.h"

COMPONENT_SPACE_START

class EventfdThread {
 public:
  using EventfdCallback = std::function<void()>;

  EventfdThread(EventfdCallback &&cb);

  void Start();

  void Stop();

  void WakeUp();

 private:
  Eventfd eventfd_;
  Thread thread_;
};

COMPONENT_SPACE_END

#endif
