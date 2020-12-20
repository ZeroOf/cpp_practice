#ifndef __WIZ_SOCKET_H__
#define __WIZ_SOCKET_H__

#include "Noncopyable.h"

namespace wiz
{
	
class InetAddress;;
class Socket 
: Noncopyable
{
public:
	Socket(int sockfd);
	Socket();
	~Socket();

	void shutdownWrite();
	int fd()const{return _sockfd;}

	void nonblock();
	static InetAddress getLocalAddr(int sockfd);
	static InetAddress getPeerAddr(int sockfd);
private:
	int _sockfd;
};

}
#endif
