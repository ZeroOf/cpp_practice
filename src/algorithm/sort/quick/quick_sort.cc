//
// Created by God on 2021/5/31.
//

#include "quick_sort.h"
//little to big

void QuickSort::Sort(std::vector<int> &numbers) {
    int pivotPos = Patition(numbers, 0, numbers.size() - 1);
    Sort(numbers, 0, pivotPos - 1);
    Sort(numbers, pivotPos + 1, numbers.size() - 1);
}

int QuickSort::Patition(std::vector<int> &numbers, int begin, int end) const {
    int pivot = numbers[begin];
    while (begin < end) {
        while (begin < end && numbers[end] >= pivot) {
            --end;
        }
        numbers[begin] = numbers[end];
        while (begin < end && numbers[begin] <= pivot) {
            ++begin;
        }
        numbers[end] = numbers[begin];
    }
    numbers[begin] = pivot;
    return begin;
}

void QuickSort::Sort(std::vector<int> &numbers, int begin, int end) {
    if (begin >= end) {
        return;
    }
    int pivotPos = Patition(numbers, begin, end);
    Sort(numbers, begin, pivotPos - 1);
    Sort(numbers, pivotPos + 1, end);
}
