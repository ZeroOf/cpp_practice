#include "Inetaddress.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

inetAddress::inetAddress(unsigned short port)
{
	memset(&_addr,0,sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
}

inetAddress::inetAddress(const string & ip, unsigned short port)
{
	memset(&_addr,0,sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

inetAddress::inetAddress(struct sockaddr_in addr)
: _addr(addr){}

sockaddr_in * inetAddress::getAddressPtr()
{
	return &_addr;
}

string inetAddress::ip()const
{
	return string(inet_ntoa(_addr.sin_addr));
}

unsigned short inetAddress::port()const
{
	return ntohs(_addr.sin_port);
}

void inetAddress::debut()
{
	cout << ip() << endl;
	cout << port() << endl;
}
