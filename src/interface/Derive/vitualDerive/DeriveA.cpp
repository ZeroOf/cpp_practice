
#include "DeriveA.h"
#include <iostream>

DeriveA::DeriveA() {
    std::cout << __func__ << std::endl;
    std::cout << static_cast<DeriveA*>(this) << std::endl;
}

DeriveA::~DeriveA() {
    std::cout << __func__ << std::endl;
}
