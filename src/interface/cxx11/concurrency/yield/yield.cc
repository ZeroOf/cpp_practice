

#include <chrono>
#include <thread>
#include <iostream>

void LittleSleep(std::chrono::microseconds us) {
  auto start = std::chrono::system_clock::now();
  auto expires = start + us;
  do {
    std::this_thread::yield();
    std::cout << "yield back" << std::endl;
  } while (std::chrono::system_clock::now() < expires);
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  LittleSleep(std::chrono::seconds(1));
  auto elapsed = std::chrono::high_resolution_clock::now() - start;
  std::cout << "waited for " << elapsed / std::chrono::microseconds(1) << " microseconds\n";
  return 0;
}