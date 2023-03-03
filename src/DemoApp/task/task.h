//
// Created by Will Lee on 2021/12/11.
//

#ifndef CPP_PRACTICE_TASK_H
#define CPP_PRACTICE_TASK_H

#include <string>
#include <boost/asio/strand.hpp>
#include "task_msg.h"
#include "init_state.h"
#include "option_state.h"
#include <boost/asio.hpp>

class TaskState;

class Task {
 public:
  Task(uint32_t index, boost::asio::thread_pool &threadPool);
  void ChangeState(TaskState *pNewState);
  void Process(std::shared_ptr<TaskMsg> pTaskMsg);
  uint32_t GetSeq() const;
  void SetSeq(uint32_t seq);
  void SetTimer();
  void OnTimer(const boost::system::error_code &error);
  static OptionState option_state_;
  static InitState init_state_;
 private:
  uint32_t index_ = 0;
  uint32_t seq_ = 0;
  uint32_t client_id_;
 public:
  uint32_t GetClientId() const;
  void SetClientId(uint32_t client_id);
 private:
  std::string request_;
  std::string response_;
  TaskState *p_state_{};
  boost::asio::steady_timer timer_;
};

#endif //CPP_PRACTICE_TASK_H
