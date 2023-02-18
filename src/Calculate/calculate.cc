//
// Created by Will Lee on 2022/1/27.
//

#include "calculate.h"
Calculate::Calculate(const std::vector<std::pair<int, int>> &prices) : prices_(prices), accumulate_{0} {
  for (int i = 1; i < prices_.size(); ++i) {
    accumulate_.push_back(accumulate_[i - 1] + (prices_[i].first - prices[i - 1].first) * prices_[i].second);
  }
}
int Calculate::GetPrice(int nums) {
  int pre = 0, end = accumulate_.size() - 1, mid = (pre + end) / 2;
  while (pre < end) {
    mid = (pre + end) / 2;
    if (prices_[mid].first < nums) {
      pre = mid + 1;
    } else if (prices_[mid].first > nums) {
      end = mid - 1;
    } else {
      pre = mid;
      end = mid;
      break;
    }
    return accumulate_[mid] + (nums - prices_[mid].first) * prices_[mid].second;
  }
  return 0;
}
