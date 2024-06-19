#include <future>
#include "util/util.h"
#include <thread>

std::thread::id f() {
  LOG("Hello async");
  std::this_thread::sleep_for(std::chrono::seconds(2));
  auto id = std::this_thread::get_id();
  LOG("threadID : " << std::this_thread::get_id());
  return id;
}

int main() {
  LOG("Hello async, current threadID is " << std::this_thread::get_id());
  auto a1 = std::async(f);
  auto a2 = std::async(std::launch::deferred, f);
  LOG(a2.get());
  LOG(a1.get());
}