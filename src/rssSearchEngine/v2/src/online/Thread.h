 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 09:50:54
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

namespace net
{

//这是一个具体类

extern __thread int pthname;

class Thread
: Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback && cb,int name = 0);
	~Thread();

	void start();
	void join();

	bool isRunning() const{	return _isRunning;	}

private:
	static void * threadFunc(void * arg);//线程的执行体
private:
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;
	int _name;
};

}//end of namespace net
#endif 



