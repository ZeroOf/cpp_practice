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
    kTimeOut,
    kTcpMsg
  } msg_type_;
};

struct RequestMsg : public TaskMsg {
  RequestMsg(std::shared_ptr<message::Msg> p_msg, uint32_t seq) : TaskMsg{seq, MsgType::kTcpMsg}, ptr_msg_(p_msg) {}
  std::shared_ptr<message::Msg> ptr_msg_;
};

#endif //CPP_PRACTICE_TASKMSG_H
