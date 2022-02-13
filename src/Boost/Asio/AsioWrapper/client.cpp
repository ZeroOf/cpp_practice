//
// Created by God on 2021/8/9.
//

#include <iostream>
#include "client.h"
#include <LogWrapper.h>

namespace TcpIO {

Client::Client(boost::asio::thread_pool &thread_pool,
               std::shared_ptr<TcpIO::IOInterface> ptr_io_interface,
               ClientType type)
    : strand_(boost::asio::make_strand(thread_pool)),
      resolver_(thread_pool),
      ptr_io_interface_(ptr_io_interface),
      type_(type) {
}

void Client::Start(const std::string &host, unsigned short service) {
  if (type_ == CLIENT) {
    host_ = host;
    service_ = service;
    resolver_.async_resolve(host,
                            std::to_string(service),
                            boost::asio::bind_executor(strand_,
                                                       std::bind(&Client::Connect,
                                                                 shared_from_this(),
                                                                 std::placeholders::_1,
                                                                 std::placeholders::_2)));
  } else {
    HandleConnect(boost::system::error_code(),
                  boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(host), service));
  }
}

void Client::HandleRead(const boost::system::error_code &ec, size_t recv_size) {
  if (ec) {
    if (ec == boost::asio::error::operation_aborted) {
      return;
    }
    LOG_ERROR("Read failed, error : " << ec.message());
    ptr_io_interface_->OnClose();
    return;
  }
  ptr_io_interface_->OnRead(std::vector<char>(recv_buf_.begin(), recv_buf_.begin() + recv_size));
  recv_buf_.erase(recv_buf_.begin(), recv_buf_.begin() + recv_size);
  Read();
}
void Client::SendMsg(const std::string &msg, uint32_t msg_type) {
  auto self = shared_from_this();
  boost::asio::post(strand_, [msg, self, this, msg_type]() {
    if (msg.empty()) {
      LOG_ERROR("send empty msg");
      return;
    }
    out_box_.emplace_back(std::make_shared<std::string>(msg), msg_type);
    if (out_box_.size() == 1) {
      SendInLoop();
    }
  });
}
Client::~Client() {
  LOG_DEBUG("~Client");
}
}
