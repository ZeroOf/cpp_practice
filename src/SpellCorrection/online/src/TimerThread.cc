
#include <string>
#include "TimerThread.h"

TimerThread::TimerThread(TimerThreadCallback cb, int init_sec, int interval_sec)
: _timer(cb, init_sec, interval_sec)
, _thread(std::bind(&Timer::start, &_timer))
{}

void TimerThread::start()
{
    _thread.Start(std::__cxx11::basic_string<char>(), nullptr);
}

void TimerThread::stop()
{
	_timer.stop();
}
