//
// Created by God on 2021/5/31.
//

#include <random/random_generator.h>
#include <random/printer.h>
#include "quick_sort.h"

int main() {
    RandomGenerator generator;
    auto numbers = generator.Generate();
    Printer::Print(numbers);
    QuickSort tool;
    tool.Sort(numbers);

    Printer::Print(numbers);
}