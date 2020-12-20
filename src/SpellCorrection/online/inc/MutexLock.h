#ifndef __WIZ_MUTEXLOCK_H__
#define __WIZ_MUTEXLOCK_H__

#include "Noncopyable.h"
#include <pthread.h>

namespace wiz
{

class MutexLock
: Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();
	bool isLocking() const { return _isLocking; }

	pthread_mutex_t * getMutexLockPtr() { return & _mutex; }

private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};//end of MutexLock

class MutexLockGuard
: Noncopyable
{
public:
	MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}
	~MutexLockGuard()
	{
		_mutex.unlock();
	}
private:
	MutexLock & _mutex;
};// end of MutexLockGuard

}//end of namespace wiz
#endif
