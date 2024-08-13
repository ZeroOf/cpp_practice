

#ifndef __WILL_EPOLL_POLLER_H
#define __WILL_EPOLL_POLLER_H

#include "noncopyable.h"
#include "tcp_connection.h"
#include "mutex_lock.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>

namespace component {

class Acceptor;

class EpollPoller : Noncopyable {
 public:
  typedef TcpConnection::TcpConnectionCallback EpollCallback;
  typedef std::function<void()> Functor;

  EpollPoller(Acceptor &acceptor);

  ~EpollPoller();

  void loop();

  void unloop();

  void runInLoop(const Functor &&cb);

  void doPendingFunctors();

  void wakeup();

  void setConnectionCallback(EpollCallback cb);

  void setMessageCallback(EpollCallback cb);

  void setCloseCallback(EpollCallback cb);

 private:
  void WaitEpollFd();

  void handleConnection();

  void handleMessage(int peerfd);

  void handleRead();

 private:
  Acceptor &acceptor_;
  int epoll_fd_;
  int event_fd_;
  int listen_fd_;
  bool isLooping_;

  MutexLock _mutex;
  std::vector<Functor> _pendingFunctors;

  typedef std::vector<struct epoll_event> EventList;
  EventList eventsList_;

  typedef std::map<int, TcpConnectionPtr> ConnectionMap;
  ConnectionMap connMap_;

  EpollCallback onConnectionCb_;
  EpollCallback onMessageCb_;
  EpollCallback onCloseCb_;
};

}//end of namespace net

#endif
