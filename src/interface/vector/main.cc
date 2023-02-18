//
// Created by Will Lee on 2022/1/10.
//

#include <iostream>
#include <vector>

int main() {
  std::vector<int> demo;
  std::cout << demo.size() << std::endl;
  demo.insert(demo.end(), 10);
  std::cout << demo.size() << std::endl;
  demo.insert(demo.begin(), 10);
  std::cout << demo.size() << std::endl;
}