//
// Created by God on 2021/5/4.
//

#include "test_client.h"
#include "tcp_factory.h"
#include <Log/logwrapper/log_wrapper.h>
#include <boost/make_shared.hpp>

using namespace TcpIO;

TestClient::TestClient(boost::asio::thread_pool &threadPool,
                       const std::string &&host,
                       unsigned short port,
                       TcpFactory &tcpFactory)
    : thread_pool_(threadPool),
      strand_(boost::asio::make_strand(threadPool)),
      timer_(strand_),
      host_(host),
      port_(port),
      factory_(tcpFactory) {
}

bool TestClient::OnRead(std::vector<char> msg) {
  std::string recvMsg(msg.begin(), msg.end());
  LOG_INFO("get msg " << recvMsg << " msg size is " << msg.size());
  if (auto pClient = ptr_client_.lock()) {
    pClient->SendMsg(std::string(msg.begin(), msg.end()) + std::to_string(seq_), seq_++);
  } else {
    LOG_ERROR("Client gone");
    OnClose();
    return false;
  }
  return true;
}

void TestClient::OnConnected(const std::string &host, unsigned short port) {
  isConnected_ = true;
}

void TestClient::OnConnectFailed(const std::string &host, unsigned short port) {
  LOG_INFO("Connect to " << host_ << ":" << port_ << " failed");
}

void TestClient::OnSend(bool isSendSuccess, uint32_t msgType) {
  if (isSendSuccess) {
    LOG_DEBUG("send msg " << msgType << " success");
    return;
  }
  LOG_ERROR("send msg " << msgType << " failed");
}

std::pair<buffer_iterator, bool> TestClient::IsPackageComplete(buffer_iterator begin, buffer_iterator end) {
  return std::pair<buffer_iterator, bool>(end, bool(end - begin));
}

void TestClient::OnClose() {
  if (!isConnected_) {
    return;
  }
  isConnected_ = false;
  LOG_ERROR("connection with remote " << host_ << ":" << port_ << " Close")
  factory_.Release(std::dynamic_pointer_cast<TestClient>(shared_from_this()));
}

void TestClient::Start() {
  LOG_DEBUG("remote is " << host_ << ":" << port_);
  ptr_client_.lock()->Start(host_, port_);
}

TestClient::~TestClient() {
  LOG_DEBUG("destruct");
}
void TestClient::SetClient(std::shared_ptr<Client> ptr_client) {
  ptr_client_ = ptr_client;
}
