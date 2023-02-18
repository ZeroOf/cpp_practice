
#include <iostream>
#include "SingletonHungry.h"

class SingletonHungry::AutoRelease {
public:
    AutoRelease() {
        std::cout << __func__ << std::endl;
    }

    virtual ~AutoRelease() {
        std::cout << __func__ << std::endl;
        if (pInstance_ != nullptr) {
            delete pInstance_;
        }
    }

};
SingletonHungry *SingletonHungry::pInstance_ = getInstance();

SingletonHungry::AutoRelease SingletonHungry::autoRelease_;

SingletonHungry *SingletonHungry::getInstance() {
    if (nullptr == pInstance_) {
        pInstance_ = new SingletonHungry;
    }
    return pInstance_;
}
