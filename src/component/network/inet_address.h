
#ifndef _WILL_INET_ADDRESS_H
#define _WILL_INET_ADDRESS_H


#include <netinet/in.h>
#include <string>
#include "common.h"

COMPONENT_SPACE_START

class InetAddress {
 public:
  InetAddress(short port);

  InetAddress(const char *pIp, short port);

  InetAddress(const struct sockaddr_in &addr);

  const struct sockaddr_in *GetSockAddrPtr() const;

  std::string IP() const;

  unsigned short port() const;

 private:
  struct sockaddr_in addr_;
};


COMPONENT_SPACE_END

#endif
