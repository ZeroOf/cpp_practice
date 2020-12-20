#ifndef __TIMERTHREAD_H__
#define __TIMERTHREAD_H__ 

#include "Timer.h"
#include "Thread.h"
#include <functional>

class TimerThread
{
public:
	typedef std::function<void()> TimerThreadCallback;

	TimerThread(TimerThreadCallback cb, int init_sec, int interval_sec);

	void start();
	void stop();
private:
	Timer _timer;
	wd::Thread _thread;
};

#endif
