//
// Created by Singl on 2021/4/28.
//

#include "tcp_client.h"
#include "client.h"
#include <iostream>
#include <LogWrapper.h>

void TcpClient::Close() {
  socket_.cancel();
  socket_.close();
  InterfacePtr pInterface = ptr_io_interface_.lock();
  if (pInterface) {
    pInterface->OnClose();
  }
}

void TcpClient::HandleSend(const boost::system::error_code &ec, size_t recv_size, uint32_t msgType) {
  InterfacePtr pInterface = ptr_io_interface_.lock();
  if (!pInterface) {
    return;
  }
  if (ec) {
    pInterface->OnSend(false, msgType);
    return;
  }
  out_box_.pop_front();
  LOG_DEBUG("send " << recv_size << " bytes");
  pInterface->OnSend(true, msgType);
  SendInLoop();
}

TcpClient::~TcpClient() {

}

void TcpClient::HandleConnect(const boost::system::error_code &ec, const boost::asio::ip::tcp::endpoint &remote) {
  InterfacePtr pInterface = ptr_io_interface_.lock();
  if (!pInterface) {
    LOG_DEBUG("interface has gone, bye");
    return;
  }
  if (ec) {
    pInterface->OnConnectFailed();
    return;
  }
  socket_.non_blocking(true);
  pInterface->OnConnected();
  Read();
}

void TcpClient::Read() {
  InterfacePtr pInterface = ptr_io_interface_.lock();
  if (!pInterface) {
    return;
  }
  boost::asio::async_read_until(socket_,
                                boost::asio::dynamic_buffer(recv_buf_),
                                std::bind(&TcpIO::IOInterface::IsPackageComplete,
                                          pInterface,
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
    InterfacePtr pInterface = ptr_io_interface_.lock();
    if (pInterface) {
      pInterface->OnConnectFailed();
    }
    return;
  }
  boost::asio::async_connect(socket_,
                             remote,
                             std::bind(&::TcpClient::HandleConnect,
                                       std::static_pointer_cast<TcpClient>(shared_from_this()),
                                       std::placeholders::_1,
                                       std::placeholders::_2));
}

TcpClient::TcpClient(boost::asio::thread_pool &threadPool, const std::shared_ptr<TcpIO::IOInterface> &ptrIoInterface)
    : Client(threadPool, ptrIoInterface), socket_(strand_) {}

void TcpClient::SendInLoop() {
  if (out_box_.empty()) {
    return;
  }
  auto &msgPair = out_box_.front();
  boost::asio::async_write(socket_,
                           boost::asio::buffer(msgPair.first),
                           std::bind(&TcpClient::HandleSend,
                                     std::static_pointer_cast<TcpClient>(shared_from_this()),
                                     std::placeholders::_1,
                                     std::placeholders::_2,
                                     msgPair.second));
}
TcpClient::TcpClient(boost::asio::thread_pool &thread_pool,
                     std::shared_ptr<TcpIO::IOInterface> ptr_io_interface,
                     boost::asio::ip::tcp::socket &&socket) : Client(thread_pool, ptr_io_interface),
                                                              socket_(std::move(socket)) {
}
