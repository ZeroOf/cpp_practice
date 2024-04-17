//
// Created by Will Lee on 2023/8/26.
//

#ifndef CPP_PRACTICE_SRC_ALGORITHM_SORT_INSERT_INSERT_SORT_H_
#define CPP_PRACTICE_SRC_ALGORITHM_SORT_INSERT_INSERT_SORT_H_

#include <sort.h>

class InsertSort : public Sorter {
 public:
  void Sort(std::vector<int> &input) override;

  void Insert(std::vector<int> &vector, int i);
};

#endif //CPP_PRACTICE_SRC_ALGORITHM_SORT_INSERT_INSERT_SORT_H_
