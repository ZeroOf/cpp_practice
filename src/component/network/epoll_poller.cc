
#include "epoll_poller.h"
#include "socket_util.h"
#include "acceptor.h"
#include <assert.h>
#include <iostream>

using std::cout;
using std::endl;

COMPONENT_SPACE_START

EpollPoller::EpollPoller(Acceptor &acceptor)
    : acceptor_(acceptor), epoll_fd_(createEpollFd()), event_fd_(createEventFd()), listen_fd_(acceptor_.fd()),
      isLooping_(false), eventsList_(1024) {
  addEpollFdRead(epoll_fd_, listen_fd_);
  addEpollFdRead(epoll_fd_, event_fd_);
}

EpollPoller::~EpollPoller() {
  ::close(epoll_fd_);
}

void EpollPoller::loop() {
  isLooping_ = true;
  while (isLooping_) {
    WaitEpollFd();
  }
}

void EpollPoller::unloop() {
  if (isLooping_)
    isLooping_ = false;
}

void EpollPoller::setConnectionCallback(EpollCallback cb) {
  onConnectionCb_ = cb;
}

void EpollPoller::setMessageCallback(EpollCallback cb) {
  onMessageCb_ = cb;
}

void EpollPoller::setCloseCallback(EpollCallback cb) {
  onCloseCb_ = cb;
}

void EpollPoller::WaitEpollFd() {
  int readyFdCount;
  do {
    readyFdCount = ::epoll_wait(epoll_fd_, &(*eventsList_.begin()), eventsList_.size(), 5000);
  } while (readyFdCount == -1 && errno == EINTR);

  if (readyFdCount == -1) {
    perror("epoll_wait error");
    exit(EXIT_FAILURE);
  } else if (readyFdCount == 0) {
    printf("epoll_wait timeout\n");
  } else {
    //做一个扩容的操作
    if (readyFdCount == static_cast<int>(eventsList_.size())) {
      eventsList_.resize(eventsList_.size() * 2);
    }

    //遍历每一个激活的文件描述符
    for (int idx = 0; idx != readyFdCount; ++idx) {
      if (eventsList_[idx].data.fd == listen_fd_) {
        if (eventsList_[idx].events & EPOLLIN) {
          handleConnection();
        }
      } else if (eventsList_[idx].data.fd == event_fd_) {
        handleRead();
        cout << "> doPendingFunctors()" << endl;
        doPendingFunctors();
      } else {
        if (eventsList_[idx].events & EPOLLIN) {
          handleMessage(eventsList_[idx].data.fd);
        }
      }
    }//end for
  }//end else
}

void EpollPoller::handleConnection() {
  int peerfd = acceptor_.accept();
  addEpollFdRead(epoll_fd_, peerfd);

  TcpConnectionPtr conn(new TcpConnection(peerfd, this));
  //...给客户端发一个欢迎信息==> 挖一个空: 等...
  //conn->send("welcome to server.\n");
  conn->setConnectionCallback(onConnectionCb_);
  conn->setMessageCallback(onMessageCb_);
  conn->setCloseCallback(onCloseCb_);

  std::pair<ConnectionMap::iterator, bool> ret;
  ret = connMap_.insert(std::make_pair(peerfd, conn));
  assert(ret.second == true);
  (void) ret;
  //connMap_[peerfd] = conn;

  conn->handleConnectionCallback();
}

void EpollPoller::handleMessage(int peerfd) {
  bool isClosed = isConnectionClosed(peerfd);
  ConnectionMap::iterator it = connMap_.find(peerfd);
  assert(it != connMap_.end());

  if (isClosed) {
    it->second->handleCloseCallback();
    delEpollReadFd(epoll_fd_, peerfd);
    connMap_.erase(it);
  } else {
    it->second->handleMessageCallback();
  }
}

//在计算线程中执行
void EpollPoller::runInLoop(const Functor &&cb) {
  {
    MutexLockGuard mlg(_mutex);
    _pendingFunctors.push_back(std::move(cb));
  }
  wakeup();
}

void EpollPoller::doPendingFunctors() {
  std::vector<Functor> tmp;

  {
    MutexLockGuard mlg(_mutex);
    tmp.swap(_pendingFunctors);
  }
  for (auto &functor : tmp) {
    functor();
  }
}

void EpollPoller::handleRead() {
  uint64_t howmany;
  int ret = ::read(event_fd_, &howmany, sizeof(howmany));
  if (ret != sizeof(howmany)) {
    perror("read error");
  }
}

void EpollPoller::wakeup() {
  uint64_t one = 1;
  int ret = ::write(event_fd_, &one, sizeof(one));
  if (ret != sizeof(one)) {
    perror("write error");
  }
}

COMPONENT_SPACE_END