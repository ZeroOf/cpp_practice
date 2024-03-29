#include "InetAddress.h"
#include <arpa/inet.h>
#include <string.h>

namespace wiz {

    InetAddress::InetAddress(short port) {
        ::memset(&_addr, 0, sizeof(_addr));
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(port);
        _addr.sin_addr.s_addr = INADDR_ANY;
    }

    InetAddress::InetAddress(const char *Ip, short port) {
        ::memset(&_addr, 0, sizeof(_addr));
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(port);
        _addr.sin_addr.s_addr = inet_addr(Ip);
    }

    InetAddress::InetAddress(const struct sockaddr_in &addr)
            : _addr(addr) {}

    const struct sockaddr_in *InetAddress::getSockAddrPtr() const {
        return &_addr;
    }

    std::string InetAddress::ip() const {
        return std::string(inet_ntoa(_addr.sin_addr));
    }

    unsigned short InetAddress::port() const {
        return ntohs(_addr.sin_port);
    }

}
