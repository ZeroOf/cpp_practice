//
// Created by Will Lee on 2022/1/5.
//

#include <iostream>

extern int staticA;
auto staticB = staticA;

int main() {
  std::cout << "\n";
  std::cout << typeid(staticA).name() << std::endl;
  std::cout << typeid(staticB).name() << std::endl;
  std::cout << "staticB: " << staticB << "\n";
  staticA = 2;
  staticB = 3;
  std::cout << std::endl;
  return 0;
}
