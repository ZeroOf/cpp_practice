//
// Created by God on 2021/8/9.
//

#include <iostream>
#include <boost/bind/bind.hpp>
#include "client.h"
#include <LogWrapper.h>

void Client::Start(const std::string &host, const std::string &service) {
    resolver_.async_resolve(host, service, boost::asio::bind_executor(
        strand_, boost::bind(&Client::Connect, shared_from_this(), boost::placeholders::_1, boost::placeholders::_2)));
}

void Client::HandleRead(const boost::system::error_code &ec, size_t recv_size) {
    auto pInterface = ptr_io_interface_.lock();
    if (!pInterface) {
        return;
    }
    if (ec) {
        LOG_ERROR("Read failed, error : " << ec);
        pInterface->OnClose();
        return;
    }
    std::istream input(&recv_buf_);
    std::vector<char> input_buf(recv_size);
    input.readsome(input_buf.data(), recv_size);
    pInterface->OnRead(std::move(input_buf));
    Read();
}

Client::Client(boost::asio::io_context &ioContext, boost::shared_ptr<TcpIO::IOInterface> ptr_io_interface)
    : strand_(ioContext.get_executor()), resolver_(ioContext),
      ptr_io_interface_(ptr_io_interface) {
}