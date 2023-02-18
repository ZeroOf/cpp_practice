
#include "Base.h"
#include <iostream>

Base::Base() {
    std::cout << __func__ << std::endl;
    std::cout << static_cast<Base*>(this) << std::endl;
}

Base::~Base() {
    std::cout << __func__ << std::endl;
}
