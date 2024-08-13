
#include "thread.h"

COMPONENT_SPACE_START

Thread::Thread(ThreadCallback &&cb)
    : threadID_(0), isRunning_(false), callback_(std::move(cb)) {}

Thread::~Thread() {
  if (isRunning_) {
    pthread_detach(threadID_);
    isRunning_ = false;
  }
}

void Thread::Start() {
  pthread_create(&threadID_, nullptr, threadFunc, this);
  isRunning_ = true;
}

void *Thread::threadFunc(void *arg) {
  Thread *pthread = static_cast<Thread *>(arg);
  if (pthread)
    pthread->callback_();
  return nullptr;
}

void Thread::Join() {
  if (isRunning_)
    pthread_join(threadID_, nullptr);
}

bool Thread::SetCPUAffinity(unsigned int cupID) {
  cpu_set_t cpuSet;
  CPU_ZERO(&cpuSet);
  CPU_SET(cupID, &cpuSet);
  return 0 == pthread_setaffinity_np(threadID_, sizeof(cpu_set_t), &cpuSet);
}

COMPONENT_SPACE_END