
#ifndef __WILL_EVENTFD_H__
#define __WILL_EVENTFD_H__

#include <functional>
#include <common.h>

COMPONENT_SPACE_START

class Eventfd {
 public:
  using EventfdCallback = std::function<void()>;

  explicit Eventfd(EventfdCallback &&callback);

  ~Eventfd();

  void Start();

  void Stop();

  // use Wakeup to
  void Wakeup();

 private:
  int CreateEventFD();

  void HandleRead();

  void HandlePollEvents(short events);

 private:
  int eventfd_;
  bool isStarted_;
  EventfdCallback callback_;
};

COMPONENT_SPACE_END

#endif
