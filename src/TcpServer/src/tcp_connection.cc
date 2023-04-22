#include "TcpConnection.h"
#include "EpollPoller.h"
#include <string.h>
#include <stdio.h>


namespace wiz
{

TcpConnection::TcpConnection(int sockfd, EpollPoller * loop)
: _sockfd(sockfd)
, _sockIO(sockfd)
, _localAddr(wiz::Socket::getLocalAddr(sockfd))
, _peerAddr(wiz::Socket::getPeerAddr(sockfd))
, _isShutdownWrite(false)
, _loop(loop)
{
	_sockfd.nonblock();
}

TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite)
	{
		_isShutdownWrite = true;
		shutdown();
	}
	printf("~TcpConnection()\n");
}

std::string TcpConnection::receive()
{
	char buf[65536];
	memset(buf,0,sizeof(buf));
	size_t ret = _sockIO.readline(buf,sizeof(buf));
	if(ret == 0){
		return std::string();
	}else
		return std::string(buf);
}

void TcpConnection::send(const std::string & msg)
{
	_sockIO.writen(msg.c_str(), msg.size());
}

void TcpConnection::shutdown()
{
	if(!_isShutdownWrite)
		_sockfd.shutdownWrite();
	_isShutdownWrite = true;
}

std::string TcpConnection::toString()
{
	char str[100];
	snprintf(str,sizeof(str),"%s:%d -> %s:%d",
			_localAddr.ip().c_str(),
			_localAddr.port(),
			_peerAddr.ip().c_str(),
			_peerAddr.port());
	return std::string(str);
}

void TcpConnection::setConnectionCallback(TcpConnectionCallback cb)
{
	_onConnectionCb = cb;
}

void TcpConnection::setMessageCallback(TcpConnectionCallback cb)
{
	_onMessageCb = cb;
}

void TcpConnection::setCloseCallback(TcpConnectionCallback cb)
{
	_onCloseCb = cb;
}

void TcpConnection::handleConnectionCallback()
{
	if(_onConnectionCb)
		_onConnectionCb(shared_from_this());
}

void TcpConnection::handleMessageCallback()
{
	if(_onConnectionCb)
		_onMessageCb(shared_from_this());
}
void TcpConnection::handleCloseCallback()
{
	if(_onConnectionCb)
		_onCloseCb(shared_from_this());
}

void TcpConnection::sendInLoop(const std::string & msg)
{
	_loop->runInLoop(std::bind(&TcpConnection::send,this,msg));
}

}
