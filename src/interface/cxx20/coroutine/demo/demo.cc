//
// Created by Will Lee on 2021/10/1.
//


#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>

#define LOG(msg) std::cout << __FILE_NAME__ << ":" << __LINE__ << ":" << __func__ << ":" <<  msg << std::endl

auto switch_to_new_thread(std::jthread &out) {
  LOG("Coroutine suspended on thread: " << std::this_thread::get_id());
  struct awaitable {
    std::jthread *p_out;

    bool await_ready() {
      LOG("ready");
      return false;
    }

    void await_suspend(std::coroutine_handle<> h) {
      LOG("suspend");
      LOG("start sleep 2s");
      std::this_thread::sleep_for(std::chrono::seconds(2));
      LOG("after sleep 2s");
      std::jthread &out = *p_out;
      if (out.joinable())
        throw std::runtime_error("Output jthread parameter not empty");
      out = std::jthread([h] {
        LOG("start sleep 2s");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        LOG("after sleep 2s");
        LOG("before resume at thread " << std::this_thread::get_id());
        h.resume();
        LOG("end resume at thread " << std::this_thread::get_id());
      });
      // Potential undefined behavior: accessing potentially destroyed *this
      LOG("await_suspend end at thread " << std::this_thread::get_id());
    }

    void await_resume() {
      LOG("awaitable");
    }
  };
  return awaitable{&out};
}

struct task {
  struct promise_type {
    task get_return_object() {
      LOG("promise_type");
      return {};
    }

    std::suspend_never initial_suspend() {
      LOG("promise_type");
      return {};
    }

    std::suspend_never final_suspend() noexcept {
      LOG("promise_type");
      return {};
    }

    void return_void() {
      LOG("promise_type");
    }

    void unhandled_exception() {
      LOG("promise_type");
    }
  };
};

task resuming_on_new_thread(std::jthread &out) {
  LOG("Coroutine started on thread: " << std::this_thread::get_id());
  co_await switch_to_new_thread(out);
  // awaiter destroyed here
  LOG("Coroutine resumed on thread: " << std::this_thread::get_id());
}

int main() {
  LOG("before main, sizeof task : " << sizeof(task));
  LOG("main started on thread: " << std::this_thread::get_id());
  std::jthread out;
  resuming_on_new_thread(out);
  LOG("main after resuming_on_new_thread");
}