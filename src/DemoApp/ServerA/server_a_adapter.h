//
// Created by Will Lee on 2022/9/6.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_SERVERA_SERVER_A_ADAPTER_H_
#define CPP_PRACTICE_SRC_DEMOAPP_SERVERA_SERVER_A_ADAPTER_H_

#include "server_adapter.h"
class ServerAAdapter : public ServerAdapter {
 public:
  bool SendMessage(std::vector<char> buffer) override;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_SERVERA_SERVER_A_ADAPTER_H_
