#include "Timer.h"
#include <sys/timerfd.h>
#include <fcntl.h>

void component::Timer::HandleRead() {

}

void component::Timer::HandleWrite() {

}

void component::Timer::HandleTimeOut() {

}

component::HandleID component::Timer::GetHandleID() {
  return timerID_;
}

component::Timer::Timer() {
  timerID_ = timerfd_create(CLOCK_REALTIME, O_NONBLOCK | TFD_CLOEXEC);
}
