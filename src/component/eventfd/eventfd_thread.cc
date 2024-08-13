
#include "eventfd_thread.h"

COMPONENT_SPACE_START

EventfdThread::EventfdThread(EventfdCallback &&cb)
    : eventfd_(std::move(cb)), thread_(std::bind(&Eventfd::Start, &eventfd_)) {
}

void EventfdThread::Start() {
  thread_.Start();
}

void EventfdThread::Stop() {
  eventfd_.Stop();
  thread_.Join();
}

void EventfdThread::WakeUp() {
  eventfd_.Wakeup();
}

COMPONENT_SPACE_END