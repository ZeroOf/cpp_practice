//
// Created by Will Lee on 2021/9/10.
//

#ifndef CPP_PRACTICE_REACTORINTERFACE_H
#define CPP_PRACTICE_REACTORINTERFACE_H

#include <memory>
#include "Noncopyable.h"


namespace net {

    class EventHandler;

    class ReactorInterface {
    public:

        virtual void RegisterRead(EventHandler &eventHandler) = 0;

        virtual void RegisterWrite(EventHandler &eventHander) = 0;

        virtual void RegisterTimeout(EventHandler &eventHandler) = 0;

    };
}

#endif //CPP_PRACTICE_REACTORINTERFACE_H
