
#include "eventfd_thread.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace net;

EventfdThread::EventfdThread(EventfdCallback &&cb)
    : _eventfd(std::move(cb)), _thread(std::bind(&Eventfd::Start, &_eventfd)) {
}

//
void EventfdThread::Start() {
  _thread.Start();
}

void EventfdThread::Stop() {
  _eventfd.Stop();
  _thread.Join();
}

void EventfdThread::WakeUp() {
  _eventfd.Wakeup();
}
