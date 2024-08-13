//
// Created by Will Lee on 2021/9/10.
//

#include "reactor.h"

void component::Reactor::RegisterRead(EventHandler &eventHandler) {
  realReactor_->RegisterRead(eventHandler);
}

void component::Reactor::RegisterWrite(EventHandler &eventHander) {
  realReactor_->RegisterWrite(eventHander);
}

void component::Reactor::RegisterTimeout(EventHandler &eventHandler, size_t second) {
  realReactor_->RegisterTimeout(eventHandler, 0);
}

void component::Reactor::Init(std::unique_ptr<ReactorInterface> &&pReactor) {
  realReactor_ = std::move(pReactor);
}
