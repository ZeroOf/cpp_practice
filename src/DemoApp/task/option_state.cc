//
// Created by Will Lee on 2021/12/11.
//

#include "option_state.h"
#include "task.h"
#include "Boost/Log/logwrapper/LogWrapper.h"
#include <demo.h>

void OptionState::PreProcess(Task *pTask) {
  LOG_DEBUG(" option state prepare");
  pTask->SetTimer();
}
void OptionState::Process(Task *pTask, std::shared_ptr<TaskMsg> pTaskMsg) {
  Demo::get_mutable_instance().SendBack(pTask->GetClientId(), std::vector<char>());
  pTask->Release();
}
