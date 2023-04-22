#include <iostream>
#include "SingletonLazy.h"

SingletonLazy *SingletonLazy::pInstance_ = nullptr;
pthread_once_t SingletonLazy::once_ = PTHREAD_ONCE_INIT;

SingletonLazy *SingletonLazy::instance() {
    pthread_once(&once_, init);
    return pInstance_;
}

SingletonLazy::SingletonLazy() {
    std::cout << __FUNCTION__ << std::endl;
}

SingletonLazy::~SingletonLazy() {
    std::cout << __FUNCTION__ << std::endl;
}

void SingletonLazy::init() {
    pInstance_ = new SingletonLazy;
    ::atexit(destroy);
}

void SingletonLazy::destroy() {
    if (nullptr != pInstance_) {
        delete pInstance_;
    }
}