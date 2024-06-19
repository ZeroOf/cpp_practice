

#include <chrono>
#include <thread>
#include <iostream>

void LittleSleep(std::chrono::microseconds us) {
  auto start = std::chrono::system_clock::now();
  auto expires = start + us;
  do {
    std::this_thread::yield();
  } while (std::chrono::system_clock::now() < expires);
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  LittleSleep(std::chrono::microseconds(100));
  auto elapsed = std::chrono::high_resolution_clock::now() - start;
  std::cout << "waited for " << elapsed / std::chrono::microseconds(1) << " microseconds\n";
  return 0;
}