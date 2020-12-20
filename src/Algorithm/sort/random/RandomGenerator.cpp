//
// Created by God on 2021/5/25.
//

#include <random>
#include "RandomGenerator.h"

std::random_device RandomGenerator::rd{};
std::mt19937 RandomGenerator::gen{rd()};
std::uniform_int_distribution<int> RandomGenerator::d{1, 100};

std::vector<int> RandomGenerator::Generate() {
    std::vector<int> result;
    for (int i = d(gen); i > 0; --i) {
        result.push_back(d(gen));
    }
    return result;
}

std::vector<int> RandomGenerator::Generate(size_t n) {
    std::vector<int> result;
    for (int i = n; i > 0; --i) {
        result.push_back(d(gen));
    }
    return result;
}
