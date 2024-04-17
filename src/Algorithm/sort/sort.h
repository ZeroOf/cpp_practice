//
// Created by Will Lee on 2023/8/23.
//

#ifndef CPP_PRACTICE_SRC_ALGORITHM_SORT_SORT_H_
#define CPP_PRACTICE_SRC_ALGORITHM_SORT_SORT_H_

#include <vector>
// Sort vectors in increasing order
class Sorter {
 public:
  virtual void Sort(std::vector<int> &input) = 0;
  virtual ~Sorter();
};

#endif //CPP_PRACTICE_SRC_ALGORITHM_SORT_SORT_H_
