 ///
 /// @file    MutexLock.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 11:27:14
 ///
 
#ifndef __WILL_MUTEXLOCK_H__
#define __WILL_MUTEXLOCK_H__
#include "Noncopyable.h"
#include <pthread.h>

namespace component
{

class MutexLock
: Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void Lock();
	void Unlock();
	bool IsLocking() const{	return _isLocking;	}

	pthread_mutex_t * GetMutexLockPtr() {	return &_mutex;}

private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};


class MutexLockGuard
: Noncopyable
{
public:
	MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex)
	{
      _mutex.Lock();
	}

	~MutexLockGuard()
	{
      _mutex.Unlock();
	}

private:
	MutexLock & _mutex;
};

}//end of namespace net


#endif
