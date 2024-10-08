#ifndef __WILL_THREADPOOL_H__
#define __WILL_THREADPOOL_H__

#include "TaskQueue.h"

#include <memory>
#include <vector>
#include <functional>

using std::unique_ptr;
using std::vector;

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
	vector<unique_ptr<Thread>> _threads;
	TaskQueue _taskQue;
	bool _isExit;
};//end of Threadpool

}// end of namespace wiz

#endif
