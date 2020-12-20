
#include <iostream>
#include "Base.h"

Base::Base() {
    std::cout << __func__ << std::endl;
    std::cout << this << std::endl;
}

Base::~Base() {
    std::cout << __func__ << std::endl;
}

Base::Base(const Base &) {
    std::cout << "Base copy" << std::endl;
}
