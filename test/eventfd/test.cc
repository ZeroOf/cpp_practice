//
// Created by Will Lee on 2023/8/8.
//

#include <gtest/gtest.h>
#include <eventfd.h>
#include <gmock/gmock.h>
#include <chrono>

class Interface {
 public:
  Interface() {}
  virtual void Func() = 0;
  virtual ~Interface() {

  }
};

class CallBack : public Interface {
 public:
  CallBack() = default;
  MOCK_METHOD(void, Func, (), (override));
  ~CallBack() override {

  };
};

TEST(EVENT_TEST, Demo) {
  CallBack call_back;
  EXPECT_CALL(call_back, Func()).Times(testing::AtLeast(1));
  net::Eventfd eventfd(std::bind(&CallBack::Func, &call_back));
  std::thread thread([&eventfd]() {
    eventfd.Start();
  });
  std::this_thread::sleep_for(std::chrono::seconds(1));
  eventfd.Wakeup();
  eventfd.Stop();
  thread.join();
}