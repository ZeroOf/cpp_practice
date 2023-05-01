//
// Created by Singl on 2021/4/28.
//

#include "tcp_client.h"
#include "client.h"
#include <iostream>
#include <log_wrapper.h>

namespace TcpIO {

TcpClient::TcpClient(boost::asio::thread_pool &threadPool, const std::shared_ptr<TcpIO::IOInterface> &ptrIoInterface)
    : Client(threadPool, ptrIoInterface, CLIENT), socket_(strand_) {}

TcpClient::TcpClient(boost::asio::thread_pool &thread_pool,
                     std::shared_ptr<TcpIO::IOInterface> ptr_io_interface,
                     boost::asio::ip::tcp::socket &&socket) : Client(thread_pool, ptr_io_interface, SERVER),
                                                              socket_(std::move(socket)) {
}

TcpClient::~TcpClient() {

}

void TcpClient::Close() {
  socket_.cancel();
  socket_.close();
  ptr_io_interface_->OnClose();
}

void TcpClient::HandleSend(const boost::system::error_code &ec,
                           size_t sendSize,
                           uint32_t msgType,
                           std::shared_ptr<std::string> pMsg) {
  if (ec) {
    LOG_ERROR("send msg failed, cause " << ec.what());
    ptr_io_interface_->OnSend(false, msgType);
    SendInLoop();
    return;
  }
  out_box_.pop_front();
  LOG_DEBUG("send " << sendSize << " bytes");
  ptr_io_interface_->OnSend(true, msgType);
}

void TcpClient::HandleConnect(const boost::system::error_code &ec, const boost::asio::ip::tcp::endpoint &remote) {
  if (ec) {
    ptr_io_interface_->OnConnectFailed(host_, service_);
    return;
  }
  socket_.non_blocking(true);
  ptr_io_interface_->OnConnected(remote.address().to_string(), remote.port());
  Read();
}

void TcpClient::Read() {
  boost::asio::async_read_until(socket_,
                                boost::asio::dynamic_buffer(recv_buf_),
                                std::bind(&TcpIO::IOInterface::IsPackageComplete,
                                          ptr_io_interface_,
                                          std::placeholders::_1,
                                          std::placeholders::_2),
                                std::bind(&Client::HandleRead,
                                          shared_from_this(),
                                          std::placeholders::_1,
                                          std::placeholders::_2));
}

void TcpClient::Connect(const boost::system::error_code &ec,
                        boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> remote) {
  if (ec) {
    ptr_io_interface_->OnConnectFailed(host_, service_);
    return;
  }
  boost::asio::async_connect(socket_,
                             remote,
                             std::bind(&TcpClient::HandleConnect,
                                       std::static_pointer_cast<TcpClient>(shared_from_this()),
                                       std::placeholders::_1,
                                       std::placeholders::_2));
}
void TcpClient::SendInLoop() {
  if (out_box_.empty()) {
    return;
  }
  auto &msgPair = out_box_.front();
  boost::asio::async_write(socket_,
                           boost::asio::buffer(*msgPair.first),
                           std::bind(&TcpClient::HandleSend,
                                     std::static_pointer_cast<TcpClient>(shared_from_this()),
                                     std::placeholders::_1,
                                     std::placeholders::_2,
                                     msgPair.second,
                                     msgPair.first));
}
}
