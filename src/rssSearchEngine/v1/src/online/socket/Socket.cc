#include "Socket.h"
#include "Socketutil.h"

Socket::Socket()
: _fd(create_socket_fd())
{}

Socket::Socket(int afd)
:_fd(afd)
{}

void Socket::nonblock()
{
	set_non_block(_fd);
}

void Socket::shutdownWrite()
{
	if(::shutdown(_fd,SHUT_WR) == -1)
		perror("shutdown write error\n");
}

int Socket::fd()const
{
	return _fd;
}

inetAddress Socket::getlocaladdress(int sockfd)
{
	sockaddr_in addr;
	socklen_t len = sizeof(addr);
	if(::getsockname(sockfd,(sockaddr *)&addr, &len) == -1)
		perror("get sockname err");
	return inetAddress(addr);
}

inetAddress Socket::getpeeraddress(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	if(::getpeername(sockfd,(struct sockaddr *)&addr,&len) == -1)
		perror("get peername err");
	return addr;
}
