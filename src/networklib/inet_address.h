

#ifndef _WILL_INETADDRESS_H
#define _WILL_INETADDRESS_H


#include <netinet/in.h>
#include <string>

namespace component
{

class InetAddress
{
public:
	InetAddress(short port);

	InetAddress(const char * pIp, short port);

	InetAddress(const struct sockaddr_in & addr);

	const struct sockaddr_in * GetSockAddrPtr() const;
	std::string IP() const;
	unsigned short port() const;

private:
	struct sockaddr_in addr_;
};


}// end of namespace net



#endif
