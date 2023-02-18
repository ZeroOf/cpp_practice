//
// Created by Will Lee on 2021/10/7.
//

#include "Timer.h"
#include <sys/timerfd.h>

void net::Timer::HandleRead() {

}

void net::Timer::HandleWrite() {

}

void net::Timer::HandleTimeOut() {

}

net::HandleID net::Timer::GetHandleID() {
    return timerID_;
}

net::Timer::Timer() {
    timerID_ = timerfd_create(CLOCK_REALTIME, O_NONBLOCK | TFD_CLOEXEC);
}
