
#ifndef _WILL_TCP_CONNECTION_H
#define _WILL_TCP_CONNECTION_H

#include "noncopyable.h"
#include "inet_address.h"
#include "socket.h"
#include "socket_io.h"

#include <string>
#include <memory>
#include <functional>

namespace component {


class EpollPoller;

class TcpConnection;

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection : Noncopyable,
                      public std::enable_shared_from_this<TcpConnection> {
 public:
  typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;

  TcpConnection(int sockfd, EpollPoller *loop);

  ~TcpConnection();

  std::string receive();

  void send(const std::string &msg);

  void sendInLoop(const std::string &msg);

  void shutdown();

  std::string toString();

  void setConnectionCallback(TcpConnectionCallback cb);

  void setMessageCallback(TcpConnectionCallback cb);

  void setCloseCallback(TcpConnectionCallback cb);

  void handleConnectionCallback();

  void handleMessageCallback();

  void handleCloseCallback();

 private:
  Socket socket_;
  SocketIO sockIO_;
  const InetAddress localAddr_;
  const InetAddress peerAddr_;
  bool isShutdownWrite_;
  EpollPoller *loop_;

  TcpConnectionCallback onConnectionCb_;
  TcpConnectionCallback onMessageCb_;
  TcpConnectionCallback onCloseCb_;

};

}//end of namespace net

#endif
