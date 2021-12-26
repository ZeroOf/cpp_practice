//
// Created by Will Lee on 2021/12/11.
//

#ifndef CPP_PRACTICE_TASKMSG_H
#define CPP_PRACTICE_TASKMSG_H


#include <cstdint>

struct TaskMsg {
    uint32_t seq_;
    enum MsgType {
        TimeOut,
        TcpMsg
    } msgType_;
};


#endif //CPP_PRACTICE_TASKMSG_H
