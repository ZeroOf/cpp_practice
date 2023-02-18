
#include <iostream>
#include "Impl.h"

Impl::Impl() {
    std::cout << __func__ << std::endl;
}

Impl::~Impl() {
    std::cout << __func__ << std::endl;
}

void Impl::Print() const {
    std::cout << this << std::endl;
}

bool Impl::isInitEnd() {
    return true;
}

void Impl::init() {
    std::cout << __func__ << std::endl;
}
