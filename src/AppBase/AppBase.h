//
// Created by Will Lee on 2021/12/9.
//

#ifndef CPP_PRACTICE_APPBASE_H
#define CPP_PRACTICE_APPBASE_H

#include <boost/asio.hpp>

class AppBase {
 public:

  AppBase();
  void Run();

 private:
  virtual bool OnActivite() = 0;

  virtual void OnDeactivate() = 0;

  void SetSignal();

  virtual std::string &AppName() = 0;

 protected:
  boost::asio::thread_pool threadPool_;
  boost::asio::signal_set sigHandler_;
 private:
  void HandleSignal(const boost::system::error_code &ec, int sigNo);
};

#endif //CPP_PRACTICE_APPBASE_H
