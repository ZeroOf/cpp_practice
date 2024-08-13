 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 09:54:03
 ///
 
#include "Thread.h"
#include <iostream>
using std::cout;
using std::endl;

namespace component
{
Thread::Thread(ThreadCallback && cb)
: threadID_(0)
, isRunning_(false)
, _cb(std::move(cb))
{
}

Thread::~Thread()
{
	if(isRunning_)
	{
		pthread_detach(threadID_);
      isRunning_ = false;
	}
}

void Thread::start()
{
	pthread_create(&threadID_, NULL, threadFunc, this);
  isRunning_ = true;
}

void * Thread::threadFunc(void * arg)
{
	Thread * pthread = static_cast<Thread*>(arg);
	if(pthread)
		pthread->_cb();

	pthread->isRunning_ = false;
	return NULL;
}

void Thread::join()
{
	if(isRunning_)
		pthread_join(threadID_, NULL);
}

}
