#ifndef __WIZ_THREAD_H__
#define __WIZ_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

namespace wiz
{

extern __thread int pthname;

class Thread
: Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback && cb, int name = 0);
	~Thread();
	
	void start();
	void join();

	bool isRunning() const { return _isRunning; }

private:
	static void * threadFunc(void * arg);
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;
	int _name;
};

}// end of namespace wiz

#endif
