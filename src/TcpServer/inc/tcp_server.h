#ifndef __WIZ_TCPSERVER_H__
#define __WIZ_TCPSERVER_H__

#include "Acceptor.h"
#include "EpollPoller.h"
#include <string>

namespace wiz
{
class TcpServer
{
public:
	typedef EpollPoller::EpollCallback TcpServerCallback;
	TcpServer(const std::string & ip, unsigned short port);
	TcpServer(unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);
private:
	Acceptor _acceptor;
	EpollPoller _poller;

	TcpServerCallback _connectionCallback;
	TcpServerCallback _messageCallback;
	TcpServerCallback _closeCallback;
};
}

#endif
