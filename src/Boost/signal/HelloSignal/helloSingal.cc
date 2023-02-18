//
// Created by Will Lee on 2021/10/30.
//

#include <boost/signals2.hpp>
#include <iostream>

struct HelloWorld {
  void operator()() const {
    std::cout << "Hello, World!" << std::endl;
  }
};

int main() {
  // Signal with no arguments and a void return value
  boost::signals2::signal<void()> sig;

  // Connect a HelloWorld slot
  HelloWorld hello;
  sig.connect(hello);

  // Call all of the slots
  sig();
}