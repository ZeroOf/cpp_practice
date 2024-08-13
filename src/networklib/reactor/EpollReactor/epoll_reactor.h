//
// Created by Will Lee on 2021/9/10.
//

#ifndef CPP_PRACTICE_EPOLLREACTOR_H
#define CPP_PRACTICE_EPOLLREACTOR_H

#include "reactor/reactor_interface.h"
#include <sys/epoll.h>
#include <vector>
#include <map>

namespace component {
class EpollReactor : public ReactorInterface {
 public:
  EpollReactor();

  void RegisterRead(EventHandler &eventHandler) final;

  void RegisterWrite(EventHandler &eventHander) final;

  void RegisterTimeout(EventHandler &eventHandler, size_t second) final;

  void Run();

 private:
  void RegisterEvent(EventHandler &eventHandler, uint32_t event);

 private:
  int epollFd_;
  std::vector<epoll_event> events_;
  std::map<int, epoll_event> registeredFd_;
  uint32_t eventSize_;
  bool isRunning_;
};
}


#endif //CPP_PRACTICE_EPOLLREACTOR_H
