#ifndef __TIMER_H__
#define __TIMER_H__

#include "Noncopyable.h"
#include <functional>

class Timer
: component::Noncopyable
{
public:
	typedef std::function<void()> TimerCallback;
	Timer(TimerCallback cb, int init_sec,int interval_sec);
	~Timer();

	void Start();
	void stop();
private:
	int _fd;
	TimerCallback _cb;
	bool _isStarted;
};

#endif
