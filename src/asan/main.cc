//
// Created by God on 2021/7/15.
//

#include <iostream>

size_t pdate;

void allock() {

    char *pfirst = new char[10];
    std::cout << (void*)pfirst << std::endl;
    pdate = (uintptr_t) pfirst;
}

int main() {
    std::cout << "hello asan" << std::endl;
    allock();
    char *psecond = new char[10];
    std::cout << (void*)psecond << std::endl;
    psecond[(uintptr_t) psecond - pdate + 1] = 0;
    std::cout << "end asan" << std::endl;
    delete[] psecond;
}