#include <iostream>
#include <mutex>
#include <thread>
#include "util/util.h"

std::once_flag flag1, flag2;

void simple_do_once() {
  std::call_once(flag1, []() { std::cout << "Simple example: called once\n"; });
}

void may_throw_function(bool do_throw) {
  if (do_throw) {
    std::cout << "Throw: call_once will retry\n"; // this may appear more than once
    throw std::exception();
  }
  std::cout << "Did not throw, call_once will not attempt again\n"; // guaranteed once
}

void do_once(bool do_throw) {
  try {
    // may_throw_function will be called once, and then retried if it throws
    std::call_once(flag2, may_throw_function, do_throw);
  } catch (std::exception &e) {
    LOG(e.what());
  }
}

int main() {
  std::thread st1(simple_do_once);
  std::thread st2(simple_do_once);
  std::thread st3(simple_do_once);
  std::thread st4(simple_do_once);
  st1.join();
  st2.join();
  st3.join();
  st4.join();

  std::thread t1(do_once, true);
  std::thread t2(do_once, true);
  std::thread t3(do_once, false);
  std::thread t4(do_once, true);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}