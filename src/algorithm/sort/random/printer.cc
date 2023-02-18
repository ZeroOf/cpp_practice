//
// Created by God on 2021/5/31.
//

#include <iostream>
#include "printer.h"

void Printer::Print(std::vector<int> &numbers) {
    for (int i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << "\t";
    }
    std::cout << std::endl;
}
