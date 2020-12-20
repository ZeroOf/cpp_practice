//
// Created by God on 2021/5/4.
//

#include "test_client.h"
#include <LogWrapper.h>
#include <boost/make_shared.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/bind.hpp>

using namespace TcpIO;

void TestClient::OnRead(std::vector<char> msg) {
    LOG_INFO("get msg " << msg.data() << " msg size is " << msg.size());
}

void TestClient::OnConnected() {
    ptr_client_->SendMsg("hello tcpclient", 1);
}

void TestClient::OnConnectFailed() {
    LOG_INFO("Connect to " << host_ << ":" << service_ << " failed");
}

void TestClient::OnSend(bool isSendSuccess, uint32_t msgType) {

}

std::pair<buffer_iterator, bool> TestClient::IsPackageComplete(buffer_iterator begin, buffer_iterator end) {
    if (end - begin < 8) {
        return std::pair<buffer_iterator, bool>(begin, false);
    }

    return std::pair<buffer_iterator, bool>(begin + 8, true);
}

void TestClient::OnClose() {
    LOG_ERROR("connection with remote " << host_ << ":" << service_ << " Close")
    strand_.defer(boost::bind(&TestClient::DelayConnect, boost::dynamic_pointer_cast<TestClient>(shared_from_this())),
                  std::allocator<char>());
}

TestClient::TestClient(boost::asio::io_context &ioContext, const std::string &host, const std::string &service)
        : io_context_(ioContext), strand_(ioContext.get_executor()), timer_(strand_), host_(host), service_(service) {}

void TestClient::Start() {
    LOG_DEBUG("remote is " << host_ << ":" << service_);
    ptr_client_ = boost::make_shared<TcpClient>(io_context_, shared_from_this());
    ptr_client_->Start(host_, service_);
}

void TestClient::DelayConnect() {
    timer_.expires_after(boost::asio::chrono::seconds(1));
    timer_.async_wait(boost::bind(&TestClient::Start, boost::dynamic_pointer_cast<TestClient>(shared_from_this())));
}

TestClient::~TestClient() {
    LOG_DEBUG("destruct");
}
