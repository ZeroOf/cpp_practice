//
// Created by Will Lee on 2022/12/8.
//

#ifndef CPP_PRACTICE_SRC_DEMOAPP_TASK_TASKWRAPPER_H_
#define CPP_PRACTICE_SRC_DEMOAPP_TASK_TASKWRAPPER_H_

template<typename TaskType>
class TaskWrapper {
 public:
  TaskWrapper(const std::shared_ptr<TaskType> &ptask, const std::shared_ptr<message::Msg> &p_msg)
      : ptask_(ptask), pMsg_(p_msg) {}
 private:
  void operator()() {
    ptask_->Process(pMsg_);
  }
 private:
  std::shared_ptr<TaskType> ptask_;
  std::shared_ptr<message::Msg> pMsg_;
};

#endif //CPP_PRACTICE_SRC_DEMOAPP_TASK_TASKWRAPPER_H_
