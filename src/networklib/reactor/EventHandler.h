//
// Created by Will Lee on 2021/9/10.
//

#ifndef CPP_PRACTICE_EVENTHANDLER_H
#define CPP_PRACTICE_EVENTHANDLER_H

#include <cstdint>

namespace net {
    using HandleID = uint32_t;

    class EventHandler {
    public:
        virtual void HandleRead() = 0;

        virtual void HandleWrite() = 0;

        virtual void HandletimeOut() = 0;

        virtual HandleID GetHandleID() = 0;
    };
}


#endif //CPP_PRACTICE_EVENTHANDLER_H
