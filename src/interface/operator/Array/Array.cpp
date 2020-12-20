
#include <iostream>
#include "Array.h"

int main() {
    std::cout << "hello world" << std::endl;
    Array<int> array(10);
    std::cout << array[1] << std::endl;
    for (int i = 0; i <= 10; ++i) {
        std::cout << array[i] << std::endl;
    }
}