#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>
#include <map>
#include <unordered_map>

void foo();

using namespace std;

void TestMapArray() {
  std::unordered_map<int, std::array<int, 10>> i2array;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; j++) {
      // when i2array[i] dose not exist, it will create a new array with zero-initialized
      std::cout << i2array[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  foo();
  TestMapArray();
  return 0;
}

void foo() {
  array<int, 3> array1;
  cout << array1.size() << endl;
  cout << array1.max_size() << endl;
  copy(array1.begin(), array1.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
}
