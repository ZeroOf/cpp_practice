//
// Created by Will Lee on 2022/9/6.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_SERVERBADAPTER_H_
#define CPP_PRACTICE_SRC_DEMOAPP_SERVERBADAPTER_H_

#include "server_adapter.h"
class ServerBAdapter : public ServerAdapter {
 public:
  ServerBAdapter();
  bool SendMessage(std::vector<char> buffer) override;
  bool Init() override;

};

#endif //CPP_PRACTICE_SRC_DEMOAPP_SERVERBADAPTER_H_
