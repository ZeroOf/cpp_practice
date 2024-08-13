#include <cerrno>
#include "epoll_reactor.h"
#include "reactor/event_handler.h"

using namespace component;

EpollReactor::EpollReactor() {}

void EpollReactor::RegisterRead(EventHandler &eventHandler) {
  RegisterEvent(eventHandler, EPOLLIN);
}

void EpollReactor::RegisterWrite(EventHandler &eventHander) {
  RegisterEvent(eventHander, EPOLLOUT);
}

void EpollReactor::RegisterTimeout(EventHandler &eventHandler, size_t second) {

}

void EpollReactor::Run() {
  while (isRunning_) {
    int nread = epoll_wait(epollFd_, events_.data(), eventSize_, 1);
    if (nread == -1 && errno == EAGAIN || errno == EINTR) {
      continue;
    }

    for (int i = 0; i < nread; ++i) {
      if (events_[i].events & EPOLLIN & EPOLLHUP) {
        static_cast<EventHandler *>(events_[i].data.ptr)->HandleRead();
      }
      if (events_[i].events & EPOLLOUT) {
        static_cast<EventHandler *>(events_[i].data.ptr)->HandleWrite();
      }
      if (events_[i].events & EPOLLERR) {
        static_cast<EventHandler *>(events_[i].data.ptr)->HandleErr();

      }
    }
  }
}

void EpollReactor::RegisterEvent(EventHandler &eventHandler, uint32_t event) {
  auto it = registeredFd_.find(eventHandler.GetHandleID());
  if (registeredFd_.end() != it) {
    if (it->second.events & event) {
      return;
    } else {
      it->second.events &= event;
      epoll_ctl(epollFd_, EPOLL_CTL_MOD, it->first, &it->second);
      return;
    }
  } else {
    epoll_ctl(epollFd_, EPOLL_CTL_ADD, it->first, &it->second);
  }
}


