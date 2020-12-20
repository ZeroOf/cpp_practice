
#include "EventfdThread.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace wd;


EventfdThread::EventfdThread(EventfdCallback && cb)
: _eventfd(std::move(cb))
, _thread(std::bind(&Eventfd::Start, &_eventfd))
{
}

void EventfdThread::start()
{
    _thread.Start();
}

void EventfdThread::stop()
{
    _eventfd.Stop();
    _thread.Join();
}

void EventfdThread::wakeup()
{
    _eventfd.Wakeup();
}
