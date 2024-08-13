
#ifndef __WILL_NONCOPYABLE_H__
#define __WILL_NONCOPYABLE_H__

#include "common.h"

COMPONENT_SPACE_START

class Noncopyable {
 protected:
  Noncopyable() {}

  ~Noncopyable() {}

  Noncopyable(const Noncopyable &) = delete;

  Noncopyable &operator=(const Noncopyable &) = delete;
};

COMPONENT_SPACE_END
#endif
