
#include "Thread.h"
#include <iostream>

using std::cout;
using std::endl;

namespace wiz
{

__thread int pthname = 0;

Thread::Thread(ThreadCallback && cb, int name)
: _pthid(0)
, _isRunning(false)
, _cb(std::move(cb))
, _name(name)
{}

Thread::~Thread()
{
	if(_isRunning)
	{
		pthread_detach(_pthid);
		_isRunning = false;
	}
}

void Thread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, this);
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
	Thread* pthread = static_cast<Thread*> (arg);
	pthname = pthread->_name;
	cout << "pthname : " << pthname << " _name" << pthread->_name << endl;
	if(pthread)
		pthread->_cb();
	pthread->_isRunning = false;
	return NULL;
}

void Thread::join()
{
	if(_isRunning)
		pthread_join(_pthid, NULL);
}

}// end of namespace wiz

