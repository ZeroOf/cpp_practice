//
// Created by Will Lee on 2021/9/10.
//

#ifndef CPP_PRACTICE_EVENTHANDLER_H
#define CPP_PRACTICE_EVENTHANDLER_H

#include <cstdint>

namespace component {
    using HandleID = uint32_t;

    class EventHandler {
    public:
        virtual void HandleRead() = 0;

        virtual void HandleWrite() = 0;

        virtual void HandleTimeOut() = 0;

        virtual void HandleErr() = 0;

        virtual HandleID GetHandleID() = 0;
    };
}


#endif //CPP_PRACTICE_EVENTHANDLER_H
