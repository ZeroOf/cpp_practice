//
// Created by Will Lee on 2022/12/8.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_TASK_TASKMANAGER_H_
#define CPP_PRACTICE_SRC_DEMOAPP_TASK_TASKMANAGER_H_

#include <memory>
#include <boost/asio/thread_pool.hpp>
#include "Task.h"
#include "message.pb.h"
#include "TaskPool.h"

class TaskManager {
 public:
  explicit TaskManager(boost::asio::thread_pool &thread_pool);
  void ProcessMsg(std::shared_ptr<message::Msg> pMsg);
 private:
  TaskPool task_pool_;
  boost::asio::thread_pool &thread_pool_;
  std::vector<boost::asio::strand<boost::asio::thread_pool::executor_type>> strands_;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_TASK_TASKMANAGER_H_
