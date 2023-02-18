//
// Created by Will Lee on 2021/9/5.
//

#include <regex>
#include <iostream>
#include <algorithm>

int main() {
    std::string test("laskjdf?alsdkfj*");
    std::replace_if(test.begin(), test.end(), [](char c) {
        return c == '?';
    }, '.');
    std::cout << test << std::endl;
}