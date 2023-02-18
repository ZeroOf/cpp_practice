//
// Created by God on 2021/5/25.
//

#ifndef CPP_PRACTICE_HEAPSORT_H
#define CPP_PRACTICE_HEAPSORT_H

#include <vector>

class HeapSort {
public:
   void Sort(std::vector<int> &numbers);
private:
    void Heapify(std::vector<int> &numbers, size_t top, size_t buttom);
    void Heapify(std::vector<int>& numbers);

    size_t LeftChild(size_t top) const;

    size_t RightChild(size_t top) const;
    size_t Father(size_t position) const;
};


#endif //CPP_PRACTICE_HEAPSORT_H
