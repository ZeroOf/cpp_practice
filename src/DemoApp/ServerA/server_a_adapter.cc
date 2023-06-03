//
// Created by Will Lee on 2022/9/6.
//

#include "server_a_adapter.h"
#include "Boost/Log/logwrapper/log_wrapper.h"

bool ServerAAdapter::SendMessage(std::vector<char> buffer) {
  static int i = 0;
  LOG_DEBUG("server a send message : " << buffer.size());
  if (nullptr == ptr_redis_) {
    LOG_ERROR("redis is not initialized");
    return false;
  }
  ptr_redis_->set(std::to_string(i++), std::string(buffer.begin(), buffer.end()), std::chrono::seconds(10));
  return true;
}
bool ServerAAdapter::Init() {
  if (nullptr != ptr_redis_) {
    LOG_ERROR("redis has been initialized");
    return false;
  }
  try {
    LOG_INFO("redis init");
    ptr_redis_ = std::make_unique<sw::redis::Redis>("tcp://127.0.0.1:6379");
  }
  catch (const std::exception &e) {
    LOG_ERROR("redis init error: {" << e.what() << "}");
    return false;
  }
  LOG_INFO("redis init success");
  return true;
}
