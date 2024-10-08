#ifndef __WIZ_EPOLLPOLLER_H__
#define __WIZ_EPOLLPOLLER_H__

#include "Noncopyable.h"
#include "tcp_connection.h"
#include "mutex_lock.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>

namespace wiz {

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
  void waitEpollfd();

  void handleConnection();

  void handleMessage(int peerfd);

  void handleRead();

 private:
  Acceptor &_acceptor;
  int _epollfd;
  int _eventfd;
  int _listenfd;
  bool _isLooping;

  MutexLock _mutex;
  std::vector<Functor> _pendingFunctors;

  typedef std::vector<struct epoll_event> EventList;
  EventList _eventsList;
  typedef std::map<int, TcpConnectionPtr> ConnectionMap;
  ConnectionMap _connMap;

  EpollCallback _onConnectionCb;
  EpollCallback _onMessageCb;
  EpollCallback _onCloseCb;
};
}

#endif
