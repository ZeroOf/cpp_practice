
#include <iostream>
#include "Brace.h"

int Brace::operator()(int i, int j) {
    ++count_;
    return i + j;
}

int Brace::operator()(int i, int j, int k) {
    return i + j + k;
}

int main() {
    Brace b;
    std::cout << b(1, 2) << std::endl;
    std::cout << b(1, 2, 3) << std::endl;
    std::cout << b.count_ << std::endl;
    return 0;
}
