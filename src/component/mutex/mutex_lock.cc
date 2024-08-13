
#include "mutex_lock.h"

using namespace component;

MutexLock::MutexLock()
    : _isLocking(false) {
  pthread_mutex_init(&_mutex, NULL);
}

MutexLock::~MutexLock() {
  pthread_mutex_destroy(&_mutex);
}

void MutexLock::Lock() {
  pthread_mutex_lock(&_mutex);
  _isLocking = true;
}

void MutexLock::Unlock() {
  pthread_mutex_unlock(&_mutex);
  _isLocking = false;
}
