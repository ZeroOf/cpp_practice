//
// Created by Will Lee on 2021/9/10.
//

#ifndef CPP_PRACTICE_EPOLLREACTOR_H
#define CPP_PRACTICE_EPOLLREACTOR_H

#include "reactor/ReactorInterface.h"
#include <sys/epoll.h>
#include <vector>
#include <map>

namespace net {
    class EpollReactor : public ReactorInterface {
    public:
        EpollReactor();

        void RegisterRead(EventHandler &eventHandler) final;

        void RegisterWrite(EventHandler &eventHander) final;

        void RegisterTimeout(EventHandler &eventHandler, size_t second) final;

        void Run();

    private:
        int epollfd_;
        std::vector<epoll_event> events_;
        std::map<int, epoll_event> registerdFd_;
        uint32_t eventSize_;
        bool isRunning_;
    };
}


#endif //CPP_PRACTICE_EPOLLREACTOR_H
