//
// Created by Will Lee on 2021/9/10.
//

#include "Reactor.h"

void net::Reactor::RegisterRead(EventHandler &eventHandler) {
    realReactor_->RegisterRead(eventHandler);
}

void net::Reactor::RegisterWrite(EventHandler &eventHander) {
    realReactor_->RegisterWrite(eventHander);
}

void net::Reactor::RegisterTimeout(EventHandler &eventHandler, size_t second) {
    realReactor_->RegisterTimeout(eventHandler, 0);
}

void net::Reactor::Init(std::unique_ptr<ReactorInterface> &&pReactor) {
    realReactor_ = std::move(pReactor);
}
