//
// Created by Will Lee on 2021/9/10.
//

#include "EpollReactor.h"
#include "EventHandler.h"

using namespace net;

EpollReactor::EpollReactor() {}

void EpollReactor::RegisterRead(EventHandler &eventHandler) {
//    epoll_ctl(epollfd_, EPOLL_CTL_MOD)
}

void EpollReactor::RegisterWrite(EventHandler &eventHander) {

}

void EpollReactor::RegisterTimeout(EventHandler &eventHandler) {

}

void EpollReactor::Run() {
    while (isRunning_) {
        int nread = epoll_wait(epollfd_, events_.data(), eventSize_, 1);
        if (nread == -1 && errno == EAGAIN) {
            continue;
        }

        for (int i = 0; i < nread; ++i) {
            if (events_[i].events & EPOLLIN & EPOLLHUP) {
                static_cast<EventHandler *>(events_[i].data.ptr)->HandleRead();
                continue;
            }
//            if (events_[i].events & EPOLLOUT)
        }
    }
}


