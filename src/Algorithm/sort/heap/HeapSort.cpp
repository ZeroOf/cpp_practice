//
// Created by God on 2021/5/25.
//

#include "HeapSort.h"

void HeapSort::Heapify(std::vector<int> &numbers, size_t top, size_t buttom) {
    size_t left = LeftChild(top);
    size_t right = RightChild(top);
    size_t maxPos = top;
    if (right < buttom && numbers[maxPos] < numbers[right]) {
        maxPos = right;
    }
    if (left < buttom && numbers[maxPos] < numbers[left]) {
        maxPos = left;
    }
    if (maxPos != top) {
        std::swap(numbers[top], numbers[maxPos]);
        Heapify(numbers, maxPos, buttom);
    }
}

size_t HeapSort::RightChild(size_t top) const {
    return top * 2 + 2;
}

size_t HeapSort::LeftChild(size_t top) const {
    return top * 2 + 1;
}

void HeapSort::Sort(std::vector<int> &numbers) {
    Heapify(numbers);

    for (int i = numbers.size() - 1; i > 0; --i) {
        Heapify(numbers, 0, i + 1);
        std::swap(numbers[0], numbers[i]);
    }
}

void HeapSort::Heapify(std::vector<int> &numbers) {
    size_t lastFather = Father(numbers.size() - 1);
    for (int i = lastFather; i >= 0; --i) {
        Heapify(numbers, i, numbers.size() - 1);
    }
}

size_t HeapSort::Father(size_t position) const {
    return (position - 1) / 2;
}
