
#ifndef __WILL_TCP_SERVER_H__
#define __WILL_TCP_SERVER_H__

#include <string>

#include "acceptor.h"
#include "epoll_poller.h"

using std::string;

namespace component {


class TcpServer {
 public:
  using TcpServerCallback = EpollPoller::EpollCallback;

  TcpServer(const string &ip, unsigned short port);

  TcpServer(unsigned short port);

  void start();

  void stop();

  void setConnectionCallback(TcpServerCallback cb);

  void setMessageCallback(TcpServerCallback cb);

  void setCloseCallback(TcpServerCallback cb);

 private:
  Acceptor acceptor_;
  EpollPoller poller_;

  TcpServerCallback connectionCallback_;
  TcpServerCallback messageCallback_;
  TcpServerCallback closeCallback_;
};


}//end of namespace net

#endif
