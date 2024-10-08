 ///
 /// @file    Condition.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 11:36:56
 ///
 
#ifndef __WILL_CONDITION_H__
#define __WILL_CONDITION_H__

#include "Noncopyable.h" 
#include <pthread.h>

namespace component
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

}//end of namespace net

#endif
