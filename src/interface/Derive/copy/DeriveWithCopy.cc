
#include "DeriveWithCopy.h"
#include <iostream>

DeriveWithCopy::~DeriveWithCopy() {
    std::cout << __func__ << std::endl;
}

DeriveWithCopy::DeriveWithCopy() {
    std::cout << __func__ << std::endl;
}

DeriveWithCopy::DeriveWithCopy(const DeriveWithCopy &) {
    std::cout << __func__ << " copy" << std::endl;
}
