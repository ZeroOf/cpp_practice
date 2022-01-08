//
// Created by Will Lee on 2021/12/9.
//

#include <unistd.h>
#include <boost/asio/signal_set.hpp>
#include "AppBase.h"
#include <Boost/Log/logwrapper/LogWrapper.h>

void AppBase::Run() {
  Daemon();
  SetSignal();
  OnActivite();
  LOG_INFO("activite success");
  OnDeactivite();
}

AppBase::AppBase() = default;

void AppBase::Daemon() {
  daemon(0, 0);
}

void AppBase::SetSignal() {
  boost::asio::signal_set signals(threadPool_, SIGINT, SIGTERM);
  signals.async_wait([this](boost::system::error_code ec, int sigNo) {
    if (ec) {
      LOG_ERROR("get ec " << ec);
    }
    LOG_INFO("get sig " << sigNo);
  });
}
