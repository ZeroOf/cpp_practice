#include "Thread.h"
#include <iostream>

using std::cout;
using std::endl;

namespace component {

    __thread int pthname = 0;

    Thread::Thread(ThreadCallback &&cb, int name)
            : threadID_(0), isRunning_(false), _cb(std::move(cb)), _name(name) {
    }

    Thread::~Thread() {
        if (isRunning_) {
            pthread_detach(threadID_);
          isRunning_ = false;
        }
    }

    void Thread::start() {
        pthread_create(&threadID_, NULL, threadFunc, this);
      isRunning_ = true;
    }

    void *Thread::threadFunc(void *arg) {
        Thread *pthread = static_cast<Thread *>(arg);
        pthname = pthread->_name;
        cout << "pthname: " << pthname << "_name" << pthread->_name << endl;
        if (pthread)
            pthread->_cb();

        pthread->isRunning_ = false;
        return NULL;
    }

    void Thread::join() {
        if (isRunning_)
            pthread_join(threadID_, NULL);
    }

}
