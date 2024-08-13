//
// Created by Will Lee on 2021/9/10.
//

#ifndef CPP_PRACTICE_REACTOR_H
#define CPP_PRACTICE_REACTOR_H

#include "reactor_interface.h"

namespace component {

class Reactor : public ReactorInterface {
 public:
  void Init(std::unique_ptr<ReactorInterface> &&pReactor);

  void RegisterRead(EventHandler &eventHandler) override;

  void RegisterWrite(EventHandler &eventHander) override;

  void RegisterTimeout(EventHandler &eventHandler, size_t second) override;

 private:
  std::unique_ptr<ReactorInterface> realReactor_;
};
}

#endif //CPP_PRACTICE_REACTOR_H
