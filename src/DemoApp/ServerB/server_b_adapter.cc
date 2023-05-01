//
// Created by Will Lee on 2022/9/6.
//

#include "server_b_adapter.h"
#include "Boost/Log/logwrapper/log_wrapper.h"

bool ServerBAdapter::SendMessage(std::vector<char> buffer) {
  return false;
}

ServerBAdapter::ServerBAdapter() {}

bool ServerBAdapter::Init() {
  LOG_INFO("server b init");
  return false;
}
