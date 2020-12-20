#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

class Thread
{
public: 
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback && cb);
	~Thread();

	void start();
	void join() const;

	bool isRunning()const
	{
		return _isRunning;
	}
private:
	static void * threadFunc(void * arg);
private:
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;
};

#endif
