 ///
 /// @file    Condition.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 11:39:41
 ///
 
#include "Condition.h"
#include "MutexLock.h"

using namespace component;


Condition::Condition(MutexLock & mutex)
: _mutex(mutex)
{
	pthread_cond_init(&_cond, NULL);
}


Condition::~Condition()
{
	pthread_cond_destroy(&_cond);
}

void Condition::wait()
{
	pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());
}

void Condition::notify()
{
	pthread_cond_signal(&_cond);
}

void Condition::notifyAll()
{
	pthread_cond_broadcast(&_cond);
}
