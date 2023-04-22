
#include "DeriveNoCopy.h"
#include <iostream>

DeriveNoCopy::~DeriveNoCopy() {
    std::cout << __func__ << std::endl;
}

DeriveNoCopy::DeriveNoCopy() {
    std::cout << __func__ << std::endl;
}
