//
// Created by Will Lee on 2021/12/9.
//

#include <boost/asio/signal_set.hpp>
#include "appbase.h"
#include <Boost/Log/logwrapper/LogWrapper.h>

AppBase::AppBase() : sigHandler_(threadPool_) {}

void AppBase::Run() {
  LogWrapper::get_mutable_instance().Init(AppName());
  SetSignal();
  OnActivate();
  LOG_INFO(AppName() << "activite success");
//  threadPool_.join();
  OnDeactivate();
}

void AppBase::SetSignal() {
  sigHandler_.add(SIGINT);
  sigHandler_.async_wait(std::bind(&AppBase::HandleSignal, this, std::placeholders::_1, std::placeholders::_2));
}

void AppBase::HandleSignal(const boost::system::error_code &ec, int sigNo) {
  if (ec) {
    LOG_ERROR("get ec " << ec.what());
    return;
  }
  LOG_INFO("get sig " << sigNo);
  if (sigNo == SIGINT) {
    LOG_INFO("get sigint sig, stop all");
    threadPool_.stop();
    return;
  }
  sigHandler_.async_wait(std::bind(&AppBase::HandleSignal, this, std::placeholders::_1, std::placeholders::_2));
}
