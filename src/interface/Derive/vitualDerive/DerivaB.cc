
#include "DeriveB.h"
#include <iostream>

DeriveB::DeriveB() {
    std::cout << __func__ << std::endl;
    std::cout << static_cast<DeriveB*>(this) << std::endl;
}

DeriveB::~DeriveB() {
    std::cout << __func__ << std::endl;
}
