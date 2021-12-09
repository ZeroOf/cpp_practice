#include "Timer.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <poll.h>
#include <iostream>

int createTimerfd()
{
	int ret = timerfd_create(CLOCK_REALTIME,0);
	if(-1 == ret)
	{
		perror("timerfd_create error");
	}
	return ret;
}

void setTimerfd(int fd, int init_sec, int interval_sec)
{
	struct itimerspec it;
	it.it_interval.tv_sec = interval_sec;
	it.it_interval.tv_nsec = 0;
	it.it_value.tv_sec = init_sec;
	it.it_value.tv_nsec = 0;
	int ret = timerfd_settime(fd,0,&it,NULL);
	if(-1 == ret)
	{
		perror("timerfd_settime error");
		exit(EXIT_FAILURE);
	}
}

void stopTimerfd(int fd)
{
	setTimerfd(fd,0,0);
}

int readTimerfd(int fd)
{
	uint64_t howmany;
	ssize_t ret = read(fd,&howmany,sizeof(howmany));
	if(ret != sizeof(howmany))
	{
		perror("read error");
	}
	return howmany;
}

Timer::Timer(TimerCallback cb, int init_sec, int interval_sec)
: _fd(createTimerfd())
, _cb(cb)
, _isStarted(false)
{
	setTimerfd(_fd,init_sec,interval_sec);
}

void Timer::Start()
{
	_isStarted = true;
	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;
	while(_isStarted)
	{
		int ret = poll(&pfd,1,-1);
		if(-1 == ret){
			if(errno == EINTR)
				continue;
			else{
				perror("poll error");
				exit(-1);
			}
		}else if(0 == ret){
			printf("> poll timeout!\n");
		}else{
			if(pfd.revents == POLLIN){
				readTimerfd(_fd);
				if(_cb){
					_cb();
				}
			}
		}
	}
}

void Timer::stop()
{
	if(_isStarted){
		stopTimerfd(_fd);
		_isStarted = false;
	}
}

Timer::~Timer()
{
	if(_isStarted)
	{
		stop();
	}
}
