//
// Created by Will Lee on 2021/12/9.
//

#include <boost/asio/signal_set.hpp>
#include "appbase.h"
#include <Boost/Log/logwrapper/LogWrapper.h>

AppBase::AppBase() {}

void AppBase::Run() {
  LogWrapper::get_mutable_instance().Init(AppName());
  if (nullptr != ptr_thread_pool_) {
    LOG_ERROR("thread pool is not null");
    return;
  }
  ptr_thread_pool_ = std::make_shared<boost::asio::thread_pool>(4);
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
    LOG_INFO("get sigint sig, stop all");
    ptr_thread_pool_->stop();
    return;
  }
  ptr_sig_handler_->async_wait(std::bind(&AppBase::HandleSignal, this, std::placeholders::_1, std::placeholders::_2));
}
