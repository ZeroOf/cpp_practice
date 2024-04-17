//
// Created by Will Lee on 2023/8/26.
//

#include "insert_sort.h"
void InsertSort::Sort(std::vector<int> &input) {
  for (int ordered = 1; ordered <= input.size(); ++ordered) {
    // insert input[ordered+1] into 0-ordered
    if (input[ordered] < input[ordered - 1]) {
      Insert(input, ordered + 1);
    }
  }
  return;
}
// insert vector[i] into vector[0:i-1], let vector[0:i] ordered
void InsertSort::Insert(std::vector<int> &container, int i) {
  // find the first number bigger than container[i]
  int mid = i / 2, start = 0, end = i;
  while (start < end) {
    if (container[mid] > container[i]) {
      start = mid + 1;
    } else if (container[mid] < container[i]){

    }
    mid = (start + end) / 2;
  }
}
