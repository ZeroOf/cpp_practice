#include "TimerThread.h"
#include <iostream>

TimerThread::TimerThread(int initialTime, int perodicTime, TimerCallback &&cb)
        : _timer(initialTime, perodicTime, std::move(cb)), _thread(std::bind(&Timer::start, &_timer)) {}

void TimerThread::start() {
    _thread.start();
}

void TimerThread::stop() {
    _timer.stop();
    _thread.join();
}
