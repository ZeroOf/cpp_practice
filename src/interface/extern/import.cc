//
// Created by Will Lee on 2021/10/19.
//

#include <iostream>

void TestImport() {
    extern int a;
    extern int b;
    std::cout << "a = " << a << std::endl;
//    std::cout << "b = " << b << std::endl;
}
