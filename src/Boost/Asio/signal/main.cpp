//
// Created by Will Lee on 2022/1/5.
//

#include <boost/asio/signal_set.hpp>
#include <iostream>
void handler(const boost::system::error_code &error, int signal_number, boost::asio::signal_set &set) {
  if (!error) {
    std::cout << signal_number << std::endl;
  }
  set.async_wait(std::bind(&handler,std::placeholders::_1, std::placeholders::_2, std::ref(set)));
}

int main() {

  boost::asio::io_context io_context;
// Construct a signal set registered for process termination.
  boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);

// Start an asynchronous wait for one of the signals to occur.
  signals.async_wait(std::bind(&handler,std::placeholders::_1, std::placeholders::_2, std::ref(signals)));
  io_context.run();
}