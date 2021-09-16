//
// Created by Will Lee on 2021/9/10.
//

#ifndef CPP_PRACTICE_EPOLLREACTOR_H
#define CPP_PRACTICE_EPOLLREACTOR_H

#include "ReactorInterface.h"
#include <sys/epoll.h>
#include <vector>

namespace net {
    class EpollReactor : public ReactorInterface {
    public:
        EpollReactor();

        void RegisterRead(EventHandler &eventHandler) final;

        void RegisterWrite(EventHandler &eventHander) final;

        void RegisterTimeout(EventHandler &eventHandler) final;

        void Run();

    private:
        int epollfd_;
        std::vector<epoll_event> events_;
        uint32_t eventSize_;
        bool isRunning_;
    };
}


#endif //CPP_PRACTICE_EPOLLREACTOR_H
