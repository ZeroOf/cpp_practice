//
// Created by Will Lee on 2021/12/10.
//

#include <AppBase.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace testing {
class MockAppBase : public AppBase {
 public:
  MOCK_METHOD(bool, OnActivite, (), (override));
  MOCK_METHOD(void, OnDeactivite, (), (override));
  MOCK_METHOD(std::string &, AppName, (), (override));
};

TEST(AppBase, run) {
  MockAppBase app;
  app.Run();
}
}
