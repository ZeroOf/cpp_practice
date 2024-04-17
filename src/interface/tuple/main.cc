//
// Created by Will Lee on 4/6/2024.
//
#include <tuple>
#include <string>
#include <iostream>

int main() {
  std::tuple<int, char, std::string> demo;
  demo = {1, 'a', "hello"};
  std::cout << std::get<char>(demo) << std::endl;
  int num = 0;
  char c = 0;
  std::string word;
  std::tie(num, c, word) = demo;
  std::cout << num << c << word << std::endl;
}