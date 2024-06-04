//
// Created by Will Lee on 2021/12/9.
//

#include "appbase.h"
#include <boost/asio/signal_set.hpp>
#include <Boost/Log/logwrapper/log_wrapper.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

AppBase::AppBase() {}

void AppBase::Run() {
  if (nullptr != ptr_thread_pool_) {
    LOG_ERROR("thread pool is not null");
    return;
  }
  ptr_thread_pool_ = std::make_shared<boost::asio::thread_pool>(4);

  if (!InitLog()) {
    LOG_ERROR("init log failed");
    return;
  }
  if (nullptr != ptr_sig_handler_) {
    LOG_ERROR("sig handler is not null");
    return;
  }
  ptr_sig_handler_ = std::make_unique<boost::asio::signal_set>(*ptr_thread_pool_);
  SetSignal();
  OnActivate();
  LOG_INFO(AppName() << " activate success");
//  threadPool_.join();
  ptr_thread_pool_->join();
  OnDeactivate();
}

void AppBase::SetSignal() {
  LOG_DEBUG("set signal");
  ptr_sig_handler_->add(SIGINT);
  ptr_sig_handler_->async_wait(std::bind(&AppBase::HandleSignal, this, std::placeholders::_1, std::placeholders::_2));
}

void AppBase::HandleSignal(const boost::system::error_code &ec, int sigNo) {
  LOG_DEBUG("get signal");
  if (ec) {
    LOG_ERROR("get ec " << ec.what());
    return;
  }
  LOG_INFO("get sig " << sigNo);
  if (sigNo == SIGINT) {
    LOG_INFO("get sigint sig, Stop all");
    ptr_thread_pool_->stop();
    return;
  }
  ptr_sig_handler_->async_wait(std::bind(&AppBase::HandleSignal, this, std::placeholders::_1, std::placeholders::_2));
}

struct SharedMemoryData {
  bool modified;
  int logLevel;
};

const int SHARED_MEMORY_SIZE = sizeof(SharedMemoryData);

void AppBase::CheckLogLevel() {
  if (ptr_shared_memory_data_->modified) {
    LOG_INFO("log level change to " << static_cast<LogLevel>(ptr_shared_memory_data_->logLevel));
    ptr_shared_memory_data_->modified = false;
    LogWrapper::get_mutable_instance().SetLevel(static_cast<LogLevel>(ptr_shared_memory_data_->logLevel));
  }
  ptr_check_log_level_timer_->expires_from_now(std::chrono::seconds(1));
  ptr_check_log_level_timer_->async_wait(std::bind(&AppBase::CheckLogLevel, this));
}

bool AppBase::InitLog() {
  LogWrapper::get_mutable_instance().Init(AppName());
  if (nullptr != ptr_check_log_level_timer_) {
    LOG_ERROR("check log level timer is not null");
    return false;
  }
  try {
    shared_memory_object shm(open_or_create, "Log_Shared_Memory", read_write);
    shm.truncate(SHARED_MEMORY_SIZE);

    //将共享内存映射到当前进程的地址空间
    ptr_mapped_region_ = std::make_unique<mapped_region>(shm, read_write);

    //获取共享内存的地址
    void *address = ptr_mapped_region_->get_address();

    //将地址转换为共享内存的结构体类型
    ptr_shared_memory_data_ = static_cast<SharedMemoryData *>(address);

    //初始化共享内存数据
    ptr_shared_memory_data_->modified = false;
    ptr_shared_memory_data_->logLevel = LogLevel::ERROR;

    ptr_check_log_level_timer_ = std::make_unique<boost::asio::steady_timer>(*ptr_thread_pool_);
    ptr_check_log_level_timer_->expires_from_now(std::chrono::seconds(1));
    ptr_check_log_level_timer_->async_wait(std::bind(&AppBase::CheckLogLevel, this));
  } catch (std::exception &ex) {
    LOG_ERROR("init log failed " << ex.what());
    return false;
  }
  return true;
}
