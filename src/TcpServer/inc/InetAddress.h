#ifndef __WIZ_INETADDRESS_H__
#define __WIZ_INETADDRESS_H__

#include <netinet/in.h>
#include <string>

namespace wiz
{

class InetAddress
{
public:
	InetAddress(short port);
	InetAddress(const char * Ip, short port);
	InetAddress(const struct sockaddr_in & addr);

	const struct sockaddr_in * getSockAddrPtr() const;
	std::string ip() const;
	unsigned short port() const;
private:
	struct sockaddr_in _addr;
};
}
#endif
