//
// Created by Will Lee on 2022/1/27.
//

#ifndef CPP_PRACTICE_SRC_CALCULATE_CALCULATE_H_
#define CPP_PRACTICE_SRC_CALCULATE_CALCULATE_H_

#include <vector>

class Calculate {
 public:
  Calculate(const std::vector<std::pair<int, int>> &prices);
  int GetPrice(int nums);
 private:
  std::vector<std::pair<int, int>> prices_;
  std::vector<int> accumulate_;
};

#endif //CPP_PRACTICE_SRC_CALCULATE_CALCULATE_H_
