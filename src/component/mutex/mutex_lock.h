
#ifndef __WILL_MUTEXLOCK_H__
#define __WILL_MUTEXLOCK_H__

#include "noncopyable.h"
#include <pthread.h>

COMPONENT_SPACE_START

class MutexLock
    : Noncopyable {
 public:
  MutexLock();

  ~MutexLock();

  void Lock();

  void Unlock();

  bool IsLocking() const { return _isLocking; }

  pthread_mutex_t *GetMutexLockPtr() { return &_mutex; }

 private:
  pthread_mutex_t _mutex;
  bool _isLocking;
};


class MutexLockGuard
    : Noncopyable {
 public:
  MutexLockGuard(MutexLock &mutex)
      : _mutex(mutex) {
    _mutex.Lock();
  }

  ~MutexLockGuard() {
    _mutex.Unlock();
  }

 private:
  MutexLock &_mutex;
};

}//end of namespace net


#endif
