//
// Created by Will Lee on 2022/1/27.
//

#include <gtest/gtest.h>
#include <calculate.h>

TEST(Calculate, hello) {
  Calculate calculate({{0, 20}, {5, 10}, {10, 5}});
  std::cout << calculate.GetPrice(30) << std::endl;
}