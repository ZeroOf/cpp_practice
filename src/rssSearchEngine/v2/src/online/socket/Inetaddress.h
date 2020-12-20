#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <netinet/in.h>
#include <string>

class inetAddress
{
	struct sockaddr_in _addr;
public:
	inetAddress(unsigned short port);
	inetAddress(const std::string & ip,unsigned short port);
	inetAddress(struct sockaddr_in addr);
	sockaddr_in * getAddressPtr();
	std::string ip()const;
	unsigned short port()const;
	void debut();
};
#endif
