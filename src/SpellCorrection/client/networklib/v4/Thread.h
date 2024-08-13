 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 09:50:54
 ///
 
#ifndef __WILL_THREAD_H__
#define __WILL_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

namespace component
{

//这是一个具体类
class Thread
: Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback && cb);
	~Thread();

	void start();
	void join();

	bool isRunning() const{	return isRunning_;	}

private:
	static void * threadFunc(void * arg);//线程的执行体
private:
	pthread_t threadID_;
	bool isRunning_;
	ThreadCallback _cb;
};

}//end of namespace net
#endif 



