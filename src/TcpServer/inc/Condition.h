#ifndef __WIZ_CONDITION_H__
#define __WIZ_CONDITION_H__ 

#include "Noncopyable.h"
#include <pthread.h>

namespace wiz
{
class MutexLock;
class Condition
: Noncopyable
{
public:
	Condition(MutexLock & mutex);
	~Condition();

	void wait();
	void notify();
	void notifyAll();
private:
	MutexLock & _mutex;
	pthread_cond_t _cond;
};
}

#endif

