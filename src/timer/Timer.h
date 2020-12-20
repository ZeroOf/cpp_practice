#ifndef __TIMER_H__
#define __TIMER_H__
#include <functional>
class Timer
{
public:
	using TimerCallback = std::function<void()>;

	Timer(int initialTime, int _perodicTime, TimerCallback && cb);
	~Timer();

	void start();
	void stop();
private:
	static int createTimerfd();
	void setTimerfd(int initialTime, int perodicTime) const;
	void handleRead() const;
private:
	int _fd;
	int _initialTime;
	int _perodicTime;
	bool _isStarted;
	TimerCallback _cb;
};
#endif
