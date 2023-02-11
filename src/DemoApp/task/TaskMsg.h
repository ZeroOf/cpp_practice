//
// Created by Will Lee on 2021/12/11.
//

#ifndef CPP_PRACTICE_TASKMSG_H
#define CPP_PRACTICE_TASKMSG_H

#include <cstdint>
#include <message.pb.h>

struct TaskMsg {
  uint32_t seq_;
  enum MsgType {
    TimeOut,
    TcpMsg
  } msgType_;
};

struct RequestMsg : public TaskMsg {
  RequestMsg(std::shared_ptr<message::Msg> &p_msg, uint32_t seq) : TaskMsg{seq, MsgType::TcpMsg}, pMsg(p_msg) {}
  std::shared_ptr<message::Msg> pMsg;
};

#endif //CPP_PRACTICE_TASKMSG_H
