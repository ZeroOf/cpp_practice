 ///
 /// @file    Acceptor.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-05-11 18:42:23
 ///
 
#ifndef __WILL_ACCEPTOR_H__
#define __WILL_ACCEPTOR_H__

#include "Socket.h"
#include "InetAddress.h"

namespace component
{

class Acceptor
{
public:
	Acceptor(int listenfd, const InetAddress & addr);

	void ready();
	int accept();

	int fd() const{	return listenSock_.fd();}
private:
	void setReuseAddr(bool on);
	void setReusePort(bool on);
	void bind();
	void listen();

private:
	Socket listenSock_;
	InetAddress addr_;
};


}//end of namespace net

#endif
