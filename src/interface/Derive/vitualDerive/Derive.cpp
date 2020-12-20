
#include <iostream>
#include "Derive.h"

Derive::Derive() {
    std::cout << __func__ << std::endl;
    std::cout << static_cast<Derive*>(this) << std::endl;
}

Derive::~Derive() {
    std::cout << __func__ << std::endl;
}
