#ifndef __WIZ_TASKQUEUE_H__
#define __WIZ_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

namespace wiz
{

class TaskQueue
{
public:
	using Type = std::function<void()>;
	TaskQueue(int queSize);
	bool full() const;
	bool empty() const;
	void push(Type && type);
	Type pop();
	void wakeup();
private:
	size_t _queSize;
	std::queue<Type> _que;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	bool _flag;
};


}



#endif
