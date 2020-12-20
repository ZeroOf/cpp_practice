#include "Thread.h"


Thread::Thread(ThreadCallback &&cb)
        : _pthid(0), _isRunning(false), _cb(std::move(cb)) {}

Thread::~Thread() {
    if (_isRunning) {
        pthread_detach(_pthid);
        _isRunning = false;
    }
}

void Thread::start() {
    pthread_create(&_pthid, nullptr, threadFunc, this);
    _isRunning = true;
}

void *Thread::threadFunc(void *arg) {
    auto *pthread = static_cast<Thread *>(arg);
    if (pthread)
        pthread->_cb();
    return nullptr;
}

void Thread::join() const {
    if (_isRunning)
        pthread_join(_pthid, nullptr);
}

