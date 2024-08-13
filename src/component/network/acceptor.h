
#ifndef __WILL_ACCEPTOR_H__
#define __WILL_ACCEPTOR_H__

#include "socket.h"
#include "inet_address.h"

COMPONENT_SPACE_START

class Acceptor {
 public:
  Acceptor(int listenfd, const InetAddress &addr);

  void ready();

  int accept();

  int fd() const { return listenSock_.fd(); }

 private:
  void setReuseAddr(bool on);

  void setReusePort(bool on);

  void bind();

  void listen();

 private:
  Socket listenSock_;
  InetAddress addr_;
};

COMPONENT_SPACE_END

#endif
