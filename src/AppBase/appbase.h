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
  virtual bool OnActivate() = 0;

  virtual void OnDeactivate() = 0;

  void SetSignal();

  virtual std::string &AppName() = 0;

 protected:
  std::shared_ptr<boost::asio::thread_pool> ptr_thread_pool_;
  std::unique_ptr<boost::asio::signal_set> ptr_sig_handler_;
 private:
  void HandleSignal(const boost::system::error_code &ec, int sigNo);
};

#endif //CPP_PRACTICE_APPBASE_H
