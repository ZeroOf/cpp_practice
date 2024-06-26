#include "Threadpool.h"
#include "Thread.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

using namespace wiz;

Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(_queSize)
, _isExit(false)
{
	_threads.reserve(_threadNum);
}

Threadpool::~Threadpool()
{
	if(!_isExit)
	{
		stop();
	}
}

void Threadpool::start()
{
	for(size_t idx = 0; idx != _threadNum; ++idx)
	{
		unique_ptr<Thread> up(new Thread(std::bind(&Threadpool::threadFunc, this), idx+1));
      up->Start();
		_threads.push_back(std::move(up));
	}
}

void Threadpool::stop()
{
	cout << ">>> Threadpool::Stop() enter" << endl;
	if(!_isExit)
	{
		while(!_taskQue.empty())
		{
			::sleep(1);
		}
		_isExit = true;

      _taskQue.WakeUp();
	}
	for(auto & pthread : _threads)
	{
		pthread->join();
	}
	cout << ">>>Threadpool::Stop() exit" << endl;
}

void Threadpool::addTask(Task && task)
{
	_taskQue.push(std::move(task));
}

Threadpool::Task Threadpool::getTask()
{
	return _taskQue.pop();
}

void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task task = getTask();
		if(task)
		{
			task();
		}
	}
}

