
#include <iostream>
#include "DeriveNoCopy.h"
#include "DeriveWithCopy.h"

int main() {
    std::cout << "Hello Derive" << std::endl;
    {
        std::cout << "Hello Base copy" << std::endl;
        Base base;
        Base base2 = base;
    }
    {
        std::cout << "Hello DeriveNoCopy copy" << std::endl;
        DeriveNoCopy deriveNoCopy;
        DeriveNoCopy deriveNoCopy1 = deriveNoCopy;
    }
    {
        std::cout << "Hello DeriveWithCopy copy" << std::endl;
        DeriveWithCopy deriveWithCopy;
        DeriveWithCopy deriveWithCopy1 = deriveWithCopy;
    }
}