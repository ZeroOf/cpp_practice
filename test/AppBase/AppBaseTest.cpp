//
// Created by Will Lee on 2021/12/10.
//

#include <AppBase.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace testing {
static std::string name("MockAppBase");
class MockAppBase : public AppBase {
 public:
  MOCK_METHOD(bool, OnActivate, (), (override));
  MOCK_METHOD(void, OnDeactivate, (), (override));
  MOCK_METHOD(std::string&, AppName,(), (override));
  void Delegate(){
    ON_CALL(*this, AppName).WillByDefault([this]()->std::string&{
      return name;
    });
  }
};

TEST(AppBase, run) {
  MockAppBase app;
  AppBase &appRef = app;
  EXPECT_CALL(app, OnActivite())
      .Times(1);
  EXPECT_CALL(app, OnDeactivite()).Times(1);
  EXPECT_CALL(app, AppName()).Times(2);
  std::string ret("hello");
  ON_CALL(app, AppName).WillByDefault([&app,&ret]() -> std::string& {
    return ret;
  });
  appRef.Run();
}
}
