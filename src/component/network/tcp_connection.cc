
#include "tcp_connection.h"
#include "epoll_poller.h"
#include <string.h>
#include <stdio.h>


namespace component {

TcpConnection::TcpConnection(int sockfd, EpollPoller *loop)
    : socket_(sockfd),
      sockIO_(sockfd),
      localAddr_(component::Socket::getLocalAddr(sockfd)),
      peerAddr_(component::Socket::getPeerAddr(sockfd)),
      isShutdownWrite_(false),
      loop_(loop) {
  socket_.nonblock();
}


TcpConnection::~TcpConnection() {
  if (!isShutdownWrite_) {
    isShutdownWrite_ = true;
    shutdown();
  }
  printf("~TcpConnection()\n");
}

std::string TcpConnection::receive() {
  char buf[65536];
  memset(buf, 0, sizeof(buf));
  size_t ret = sockIO_.readline(buf, sizeof(buf));
  if (ret == 0) {
    return std::string();
  } else
    return std::string(buf);
}

void TcpConnection::send(const std::string &msg) {
  sockIO_.writen(msg.c_str(), msg.size());
}


void TcpConnection::shutdown() {
  if (!isShutdownWrite_)
    socket_.shutdownWrite();
  isShutdownWrite_ = true;
}

std::string TcpConnection::toString() {
  char str[100];
  snprintf(str, sizeof(str), "%s:%d -> %s:%d",
           localAddr_.IP().c_str(),
           localAddr_.port(),
           peerAddr_.IP().c_str(),
           peerAddr_.port());
  return std::string(str);
}


void TcpConnection::setConnectionCallback(TcpConnectionCallback cb) {
  onConnectionCb_ = cb;
}

void TcpConnection::setMessageCallback(TcpConnectionCallback cb) {
  onMessageCb_ = cb;
}

void TcpConnection::setCloseCallback(TcpConnectionCallback cb) {
  onCloseCb_ = cb;
}

void TcpConnection::handleConnectionCallback() {
  if (onConnectionCb_)
    onConnectionCb_(shared_from_this());
}

void TcpConnection::handleMessageCallback() {
  if (onMessageCb_)
    onMessageCb_(shared_from_this());
}

void TcpConnection::handleCloseCallback() {
  if (onCloseCb_)
    onCloseCb_(shared_from_this());
}

void TcpConnection::sendInLoop(const std::string &msg) {
  loop_->runInLoop(std::bind(&TcpConnection::send, this, msg));
}

}// end of namespace net
