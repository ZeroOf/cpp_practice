//
// Created by Will Lee on 2022/9/6.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_SERVERADAPTER_H_
#define CPP_PRACTICE_SRC_DEMOAPP_SERVERADAPTER_H_

#include <vector>
class ServerAdapter {
 public:
  virtual bool SendMessage(std::vector<char> buffer) = 0;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_SERVERADAPTER_H_
