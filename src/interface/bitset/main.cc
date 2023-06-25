//
// Created by Will Lee on 2023/6/10.
//

#include <bitset>
#include <iostream>

int main() {
  std::bitset<sizeof(int) * 8> demo(7);
  std::cout << demo << std::endl;
  std::cout << demo.count() << std::endl;
}