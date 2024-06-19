#include <future>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

#include <util/util.h>
#include <numeric>

namespace set_at_thread_exit {

void SetAtThreadExit() {
  std::promise<int> p;
  std::future<int> f = p.get_future();
  std::thread([&p] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    p.set_value_at_thread_exit(9);
  }).detach();
  std::cout << "Waiting ..." << std::flush;
  std::cout << "Done!\nResult is: " << f.get() << '\n';
}
}
namespace set_promise {

void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise) {
  int sum = std::accumulate(first, last, 0);
  accumulate_promise.set_value(sum); // Notify future
}

void do_work(std::promise<void> barrier) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  barrier.set_value();
}

void SetPromise() {
  LOG("test set promiess");
  // Demonstrate using promise<int> to transmit a result between threads.
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
  std::promise<int> accumulate_promise;
  std::future<int> accumulate_future = accumulate_promise.get_future();
  std::thread work_thread(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));

  // future::get() will wait until the future has a valid result and retrieves it.
  // Calling wait() before get() is not needed
  // accumulate_future.wait(); // wait for result
  std::cout << "result=" << accumulate_future.get() << '\n';
  work_thread.join(); // wait for thread completion

  // Demonstrate using promise<void> to signal state between threads.
  std::promise<void> barrier;
  std::future<void> barrier_future = barrier.get_future();
  std::thread new_work_thread(do_work, std::move(barrier));
  barrier_future.wait();
  new_work_thread.join();
  LOG("test set promiess end");
}
}

namespace promise_exception {
void PromiseException() {
  LOG(" TEST EXCEPTION");
  std::promise<int> p;
  std::future<int> f = p.get_future();

  std::thread([&p] {
    try {
      throw std::runtime_error("exception from thread");
    } catch (...) {
      p.set_exception(std::current_exception());
    }
  }).detach();

  try {
    std::cout << f.get() << '\n';
  } catch (const std::exception &e) {
    std::cout << "Caught exception: " << e.what() << '\n';
  }
}

}

int main() {
  set_at_thread_exit::SetAtThreadExit();

  set_promise::SetPromise();

  promise_exception::PromiseException();
}

