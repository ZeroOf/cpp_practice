//
// Created by God on 2021/5/31.
//

#ifndef CPP_PRACTICE_QUICKSORT_H
#define CPP_PRACTICE_QUICKSORT_H

#include <vector>

class QuickSort {
public:
    void Sort(std::vector<int> &numbers);

private:
    int Patition(std::vector<int> &numbers, int begin, int end) const;

    void Sort(std::vector<int> &numbers, int begin, int end);
};


#endif //CPP_PRACTICE_QUICKSORT_H
