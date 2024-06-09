//
// Created by Will Lee on 2022/9/6.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_SERVERA_SERVER_A_ADAPTER_H_
#define CPP_PRACTICE_SRC_DEMOAPP_SERVERA_SERVER_A_ADAPTER_H_

#include <memory>
#include "server_adapter.h"
#include <sw/redis++/redis++.h>
#include <boost/redis.hpp>

class ServerAAdapter : public ServerAdapter {
 public:
  ServerAAdapter();

  bool SendMessage(std::vector<char> buffer) override;

  bool Init() final;

 private:
  std::shared_ptr<boost::asio::executor> ptr_executor_;
  std::unique_ptr<sw::redis::Redis> ptr_redis_;
  std::unique_ptr<boost::redis::connection> ptr_boost_redis_;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_SERVERA_SERVER_A_ADAPTER_H_
