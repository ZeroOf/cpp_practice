//
// Created by God on 2021/5/4.
//

#include "test_client.h"
#include <Log/logwrapper/LogWrapper.h>
#include <boost/make_shared.hpp>

using namespace TcpIO;

void TestClient::OnRead(std::vector<char> msg) {
  std::string recvMsg(msg.begin(), msg.end());
  LOG_INFO("get msg " << recvMsg << " msg size is " << msg.size());
  ptr_client_->SendMsg(std::string("hello tcpClient ") + std::to_string(seq_), seq_++);
}

void TestClient::OnConnected() {
  isConnected_ = true;
  ptr_client_->SendMsg("hello tcpclient", 1);
}

void TestClient::OnConnectFailed() {
  LOG_INFO("Connect to " << host_ << ":" << service_ << " failed");
  DelayConnect();
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
  LOG_ERROR("connection with remote " << host_ << ":" << service_ << " Close")
  strand_.post(std::bind(&TestClient::DelayConnect, std::static_pointer_cast<TestClient>(shared_from_this())),
               std::allocator<char>());
}

TestClient::TestClient(boost::asio::thread_pool &threadPool, const std::string &host, const std::string &service)
    : thread_pool_(threadPool),
      strand_(boost::asio::make_strand(threadPool)),
      timer_(strand_),
      host_(host),
      service_(service) {}

void TestClient::Start(std::shared_ptr<boost::asio::ssl::context> pSSLContext) {
  LOG_DEBUG("remote is " << host_ << ":" << service_);
  pssl_context_ = pSSLContext;
  if (pSSLContext) {
    ptr_client_ = std::make_shared<SSLClient>(thread_pool_, *pSSLContext, shared_from_this());
    ptr_client_->Start(host_, service_);
    return;
  }
  ptr_client_ = std::make_shared<TcpClient>(thread_pool_, shared_from_this());
  ptr_client_->Start(host_, service_);
}

void TestClient::DelayConnect() {
  timer_.expires_after(boost::asio::chrono::seconds(1));
  timer_.async_wait(std::bind(&TestClient::Start,
                              std::dynamic_pointer_cast<TestClient>(shared_from_this()),
                              pssl_context_));
}

TestClient::~TestClient() {
  LOG_DEBUG("destruct");
}