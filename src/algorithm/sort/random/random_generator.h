//
// Created by God on 2021/5/25.
//

#ifndef CPP_PRACTICE_RANDOMGENERATOR_H
#define CPP_PRACTICE_RANDOMGENERATOR_H

#include <vector>
#include <random>

class RandomGenerator {
 public:
  static std::vector<int> Generate();

  static std::vector<int> Generate(size_t n);

 private:
  static std::random_device rd;
  static std::mt19937 gen;
  static std::uniform_int_distribution<int> d;
};

#endif //CPP_PRACTICE_RANDOMGENERATOR_H
