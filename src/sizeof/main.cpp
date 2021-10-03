//
// Created by Will Lee on 2021/9/26.
//

#include <iostream>

struct Test {
    int a: 16;
    int : 16;
    int a2 : 4;
};

int main() {
    std::cout << sizeof(Test) << std::endl;
    Test test{1, 1};
    std::cout << "end " << std::endl;
}