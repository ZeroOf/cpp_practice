//
// Created by Will Lee on 2021/12/9.
//

#include <unistd.h>
#include <boost/asio/signal_set.hpp>
#include "AppBase.h"
#include <Boost/Log/logwrapper/LogWrapper.h>

AppBase::AppBase() : sigHandler_(threadPool_) {}

void AppBase::Run() {
  Daemon();
  LogWrapper::get_mutable_instance().Init(AppName());
  SetSignal();
  OnActivite();
  LOG_INFO("activite success");
  OnDeactivite();
}

void AppBase::Daemon() {
//  daemon(1, 0);
}
void AppBase::SetSignal() {
//  boost::asio::signal_set signals(threadPool_, SIGINT, SIGTERM);
  sigHandler_.add(SIGINT);
  sigHandler_.async_wait(std::bind(&AppBase::HandleSignal, this, std::placeholders::_1, std::placeholders::_2));
}
void AppBase::HandleSignal(const boost::system::error_code &ec, int sigNo) {
  if (ec) {
    LOG_ERROR("get ec " << ec.what());
    return;
  }
  LOG_INFO("get sig " << sigNo);
  sigHandler_.async_wait(std::bind(&AppBase::HandleSignal, this, std::placeholders::_1, std::placeholders::_2));
}
