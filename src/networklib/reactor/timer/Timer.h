#ifndef CPP_PRACTICE_TIMER_H
#define CPP_PRACTICE_TIMER_H

#include <reactor/event_handler.h>
#include <unordered_map>

namespace component {

class Timer : public EventHandler {
 public:
  Timer();

  void HandleRead() override;

  void HandleWrite() override;

  void HandleTimeOut() override;

  HandleID GetHandleID() override;

 private:
  HandleID timerID_;
};

}


#endif //CPP_PRACTICE_TIMER_H
