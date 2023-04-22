#ifndef __TIMERTHREAD_H__
#define __TIMERTHREAD_H__

#include "Thread.h"
#include "Timer.h"

class TimerThread
{
public:
	using TimerCallback = std::function<void()>;
	TimerThread(int initialTime, int perodicTime, TimerCallback && cb);
	void start();
	void stop();
private:
	Timer _timer;
	Thread _thread;
};
#endif
