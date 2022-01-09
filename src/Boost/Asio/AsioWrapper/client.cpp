//
// Created by God on 2021/8/9.
//

#include <iostream>
#include "client.h"
#include <LogWrapper.h>

void Client::Start(const std::string &host, const std::string &service) {
    host_ = host;
    service_ = service;
    resolver_.async_resolve(host, service, boost::asio::bind_executor(
        strand_, std::bind(&Client::Connect, shared_from_this(), std::placeholders::_1, std::placeholders::_2)));
}

void Client::HandleRead(const boost::system::error_code &ec, size_t recv_size) {
    auto pInterface = ptr_io_interface_.lock();
    if (!pInterface) {
        return;
    }
    if (ec) {
        if (ec == boost::asio::error::operation_aborted) {
            return;
        }
        LOG_ERROR("Read failed, error : " << ec.message());
        pInterface->OnClose();
        return;
    }
    pInterface->OnRead(std::vector<char>(recv_buf_.begin(), recv_buf_.begin() + recv_size));
    recv_buf_.erase(recv_buf_.begin(), recv_buf_.begin() + recv_size);
    Read();
}

Client::Client(boost::asio::thread_pool &thread_pool, std::shared_ptr<TcpIO::IOInterface> ptr_io_interface)
    : strand_(boost::asio::make_strand(thread_pool)), resolver_(thread_pool),
      ptr_io_interface_(ptr_io_interface) {
}

void Client::SendMsg(const std::string &msg, uint32_t msg_type) {
    auto self = shared_from_this();
    boost::asio::post(strand_, [msg, self, this, msg_type]() {
        out_box_.emplace_back(msg, msg_type);
        if (out_box_.size() == 1) {
            SendInLoop();
        }
    });
}

void Client::Start() {

}
