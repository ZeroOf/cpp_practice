 ///
 /// @file    TaskQueue.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 11:42:58
 ///
 
#ifndef __WILL_TASKQUEUE_H__
#define __WILL_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

namespace component
{


class TaskQueue
{
public:
	using Type = std::function<void()>;
	TaskQueue(int maxSize);

	bool full() const;
	bool empty() const;

	void push(Type && type);
	Type pop();

	void WakeUp();

private:
	size_t _maxSize;
	std::queue<Type> _que;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	bool shouldStop_;
};


}//end of namespace net




#endif
