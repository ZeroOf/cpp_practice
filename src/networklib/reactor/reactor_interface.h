#ifndef CPP_PRACTICE_REACTORINTERFACE_H
#define CPP_PRACTICE_REACTORINTERFACE_H

#include <memory>
#include "Noncopyable.h"

namespace component {

class EventHandler;

class ReactorInterface {
 public:

  virtual void RegisterRead(EventHandler &eventHandler) = 0;

  virtual void RegisterWrite(EventHandler &eventHander) = 0;

  virtual void RegisterTimeout(EventHandler &eventHandler, size_t second) = 0;

};
}

#endif //CPP_PRACTICE_REACTORINTERFACE_H
