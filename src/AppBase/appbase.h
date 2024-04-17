
#ifndef CPP_PRACTICE_APPBASE_H
#define CPP_PRACTICE_APPBASE_H

#include <boost/asio.hpp>
#include <boost/interprocess/mapped_region.hpp>

struct SharedMemoryData;

//
class AppBase {
 public:

  AppBase();
  void Run();

 private:
  virtual bool OnActivate() = 0;

  virtual void OnDeactivate() = 0;

  void SetSignal();

  virtual std::string &AppName() = 0;

  void CheckLogLevel();

  bool InitLog();
 protected:
  std::shared_ptr<boost::asio::thread_pool> ptr_thread_pool_;
  std::unique_ptr<boost::asio::signal_set> ptr_sig_handler_;
  std::unique_ptr<boost::asio::steady_timer> ptr_check_log_level_timer_;
  std::unique_ptr<boost::interprocess::mapped_region> ptr_mapped_region_;
  SharedMemoryData *ptr_shared_memory_data_ = nullptr;
 private:
  void HandleSignal(const boost::system::error_code &ec, int sigNo);
};

#endif //CPP_PRACTICE_APPBASE_H
