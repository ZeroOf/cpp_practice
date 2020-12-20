#ifndef __WIZ_THREADPOOL_H__
#define __WIZ_THREADPOOL_H__

#include "TaskQueue.h"

#include <vector>
#include <memory>
#include <functional>


namespace wiz
{
class Thread;
class Threadpool
{
public:
	typedef std::function<void()> Task;
	Threadpool(size_t threadNum, size_t queSize);
	~Threadpool();

	void start();
	void stop();
	void addTask(Task && task);
private:
	Task getTask();
	void threadFunc();
private:
	size_t _threadNum;
	size_t _queSize;
	std::vector<std::unique_ptr<Thread>> _threads;
	TaskQueue _taskQue;
	bool _isExit;
};
}

#endif
