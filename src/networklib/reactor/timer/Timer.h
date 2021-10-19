//
// Created by Will Lee on 2021/10/7.
//

#ifndef CPP_PRACTICE_TIMER_H
#define CPP_PRACTICE_TIMER_H

#include <reactor/EventHandler.h>
#include <unordered_map>

namespace net {

    class Timer : public EventHandler {
    public:
        Timer();

        void HandleRead() override;

        void HandleWrite() override;

        void HandletimeOut() override;

        HandleID GetHandleID() override;

    private:
        HandleID timerID_;
    };

}


#endif //CPP_PRACTICE_TIMER_H
