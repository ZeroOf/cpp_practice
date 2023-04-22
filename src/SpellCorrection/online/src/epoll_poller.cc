#include "EpollPoller.h"
#include "SocketUtil.h"
#include "Acceptor.h"

#include <assert.h>
#include <iostream>

#define MAXPOLLER 5000
using std::cout;
using std::endl;

namespace wiz
{

EpollPoller::EpollPoller(Acceptor & acceptor)
: _acceptor(acceptor)
, _epollfd(createEpollFd())
, _eventfd(createEventFd())
, _listenfd(_acceptor.fd())
, _isLooping(false)
, _eventsList(1024)
{
	addEpollFdRead(_epollfd,_listenfd);
	addEpollFdRead(_epollfd,_eventfd);
}

EpollPoller::~EpollPoller()
{
	::close(_epollfd);
}

void EpollPoller::loop()
{
	_isLooping = true;
	while(_isLooping)
	{
		waitEpollfd();
	}
}

void EpollPoller::unloop()
{
	if(_isLooping)
		_isLooping = false;
}

void EpollPoller::setConnectionCallback(EpollCallback cb)
{
	_onConnectionCb = cb;
}
void EpollPoller::setMessageCallback(EpollCallback cb)
{
	_onMessageCb = cb;
}
void EpollPoller::setCloseCallback(EpollCallback cb)
{
	_onCloseCb = cb;
}

void EpollPoller::waitEpollfd()
{
	int nready;
	do{
		nready = ::epoll_wait(_epollfd, &(*_eventsList.begin()),_eventsList.size(),MAXPOLLER);
	} while (nready == -1 && errno == EINTR);

	if (nready == -1)
	{
		perror("epoll_wait error");
		exit(EXIT_FAILURE);
	}
	else if (nready == 0)
	{
		cout << "epoll_wait timeout" << endl;
	}
	else
	{
		if (nready == static_cast<int>(_eventsList.size()))
		{
			_eventsList.resize(_eventsList.size() * 2);
		}
		for (int idx = 0; idx != nready; ++idx)
		{
			if (_listenfd == _eventsList[idx].data.fd)
			{
				if (_eventsList[idx].events & EPOLLIN)
				{
					handleConnection();
				}
			}
			else if (_eventfd == _eventsList[idx].data.fd)
			{
				handleRead();
				cout << "> doPendingFunction()" << endl;
				doPendingFunctors();
			}
			else
			{
				if (_eventsList[idx].events & EPOLLIN)
				{
					handleMessage(_eventsList[idx].data.fd);
				}
			}
		}
	}
}

void EpollPoller::handleConnection()
{
	int peerfd = _acceptor.accept();
	addEpollFdRead(_epollfd, peerfd);
	
	TcpConnectionPtr conn(new TcpConnection(peerfd, this));
	conn->setConnectionCallback(_onConnectionCb);
	conn->setMessageCallback(_onMessageCb);
	conn->setCloseCallback(_onCloseCb);

	std::pair<ConnectionMap::iterator, bool> ret;
	ret = _connMap.insert(std::make_pair(peerfd, conn));
	assert(ret.second == true);

	conn->handleConnectionCallback();
}

void EpollPoller::handleMessage(int peerfd)
{
	bool bIsClosed = isConnectionClosed(peerfd);
	ConnectionMap::iterator it = _connMap.find(peerfd);
	assert(it != _connMap.end());

	if (bIsClosed)
	{
		it->second->handleCloseCallback();
		delEpollReadFd(_epollfd,peerfd);
		_connMap.erase(it);
	}
	else
	{
		it->second->handleMessageCallback();
	}
}

void EpollPoller::runInLoop(const Functor && cb)
{
	do {
		MutexLockGuard Lock(_mutex);
		_pendingFunctors.push_back(std::move(cb));
	} while (0);
	wakeup();
}

void EpollPoller::doPendingFunctors()
{
	std::vector<Functor> tmp;
	do {
		MutexLockGuard mlg(_mutex);
		tmp.swap(_pendingFunctors);
	} while (0);

	for (auto & functor : tmp)
	{
		functor();
	}
}

void EpollPoller::handleRead()
{
	uint64_t count;
	int ret = ::read(_eventfd, &count, sizeof(count));
	if(ret != sizeof(count))
	{
		perror("read error");
	}
}

void EpollPoller::wakeup()
{
	uint64_t count = 1;
	int ret = ::write(_eventfd, &count, sizeof(count));
	if( ret != sizeof(count))
	{
		perror("write error");
	}
}

}//end of namespace wiz

