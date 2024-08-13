#include "timer_thread.h"

COMPONENT_SPACE_START

TimerThread::TimerThread(int initialTime, int perodicTime, TimerCallback &&cb)
    : _timer(initialTime, perodicTime, std::move(cb)), _thread(std::bind(&Timer::Start, &_timer)) {}

void TimerThread::Start() {
  _thread.Start();
}

void TimerThread::Stop() {
  _timer.Stop();
  _thread.Join();
}

COMPONENT_SPACE_END