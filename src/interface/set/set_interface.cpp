//
// Created by Will Lee on 2023/1/19.
//
#include <iostream>
#include <set>
#include <functional>

void iterateSet(std::set<int *, std::function<bool(const int *, const int *)>> pS) {
  for (auto p : pS) {
    std::cout << *p << "\t";
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  std::function<bool(const int *lhs, const int *rhs)> comp = [](const int *lhs, const int *rhs) {
    return *lhs > *rhs;
  };
  std::set<int *, std::function<bool(const int *lhs, const int *rhs)>> ptrs(comp);
  int array[10] = {1, 3, 2, 5, 21, 10};
  for (int i = 0; i < 10; ++i) {
    ptrs.insert(array + i);
  }
  iterateSet(ptrs);
}