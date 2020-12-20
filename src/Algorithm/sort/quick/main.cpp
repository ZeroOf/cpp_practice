//
// Created by God on 2021/5/31.
//

#include <random/RandomGenerator.h>
#include <random/Printer.h>
#include "QuickSort.h"

int main() {
    RandomGenerator generator;
    auto numbers = generator.Generate();
    Printer::Print(numbers);
    QuickSort tool;
    tool.Sort(numbers);

    Printer::Print(numbers);
}