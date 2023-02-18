//
// Created by God on 2021/5/25.
//

#include <iostream>
#include <random/random_generator.h>
#include "heap_sort.h"
#include <random/printer.h>

using namespace std;

int main() {
    std::vector<int> random = RandomGenerator::Generate(10);

    Printer::Print(random);
    HeapSort tool;
    tool.Sort(random);

    Printer::Print(random);
}