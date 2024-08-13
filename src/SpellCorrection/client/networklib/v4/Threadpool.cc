 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 15:28:36
 ///
 
#include "Threadpool.h"
#include "Thread.h"
#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

using namespace component;


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
      Stop();
	}
}

void Threadpool::Start()
{
	//创建N个子线程对象
	for(size_t idx = 0; idx != _threadNum; ++idx){
		unique_ptr<Thread> up(new Thread(
			std::bind(&Threadpool::ThreadFunc, this)));
		_threads.push_back(std::move(up));
	}
	//开启N个子线程
	for(auto & thread : _threads)
		thread->start();
}

void Threadpool::Stop()
{
	cout << ">>> Threadpool::Stop() enter" << endl;
	if(!_isExit){
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
	cout << ">>> Threadpool::Stop() exit" << endl;
}

void Threadpool::AddTask(Task && task)
{
	_taskQue.push(std::move(task));
}

Threadpool::Task Threadpool::GetTask()
{
	return _taskQue.pop();
}

//该方法是每一个子线程要执行的
void Threadpool::ThreadFunc()
{
	while(!_isExit)
	{
		Task task = GetTask();
		if(task)
			task();
	}
}
