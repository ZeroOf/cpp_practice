//
// Created by Singl on 2021/4/28.
//

#include "tcp_client.h"
#include <boost/bind/bind.hpp>
#include <iostream>

TcpClient::TcpClient(boost::asio::io_context &ioContext, boost::shared_ptr<TcpIO::IOInterface> ptr_io_interface)
        : strand_(ioContext.get_executor()), socket_(ioContext), resolver_(ioContext),
          ptr_io_interface_(ptr_io_interface) {
}

void TcpClient::HandleConnect(const boost::system::error_code &ec) {
    InterfacePtr pInterface = ptr_io_interface_.lock();
    if (!pInterface) {
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

void TcpClient::Start(const std::string &host, const std::string &service) {
    resolver_.async_resolve(
            host, service, boost::asio::bind_executor(
                    strand_, boost::bind(
                            &TcpClient::Connect, shared_from_this(), boost::placeholders::_1,
                            boost::placeholders::_2)));
}

void TcpClient::HandleRead(const boost::system::error_code &ec, size_t recv_size) {
    InterfacePtr pInterface = ptr_io_interface_.lock();
    if (!pInterface) {
        return;
    }
    if (ec) {
        pInterface->OnClose();
        return;
    }
    std::istream input(&recv_buf_);
    std::vector<char> input_buf(recv_size);
    input.readsome(input_buf.data(), recv_size);
    pInterface->OnRead(std::move(input_buf));
    Read();
}

void TcpClient::Close() {
    socket_.cancel();
    socket_.close();
    InterfacePtr pInterface = ptr_io_interface_.lock();
    if (pInterface) {
        pInterface->OnClose();
    }
}

void TcpClient::SendMsg(const std::string msg, uint32_t msg_type) {
    socket_.async_send(
            boost::asio::buffer(msg), boost::asio::bind_executor(
                    strand_, boost::bind(
                            &TcpClient::HandelSend, shared_from_this(), boost::placeholders::_1,
                            boost::placeholders::_2, msg_type)));
}

void TcpClient::HandelSend(const boost::system::error_code &ec, size_t recv_size, uint32_t msgType) {
    InterfacePtr pInterface = ptr_io_interface_.lock();
    if (!pInterface) {
        return;
    }
    if (ec) {
        pInterface->OnSend(false, msgType);
        return;
    }
    pInterface->OnSend(true, msgType);
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
    boost::asio::async_connect(
            socket_, remote, boost::asio::bind_executor(
                    strand_, boost::bind(&TcpClient::HandleConnect, shared_from_this(), boost::placeholders::_1)));
}

void TcpClient::Read() {
    InterfacePtr pInterface = ptr_io_interface_.lock();
    if (!pInterface) {
        return;
    }
    boost::asio::async_read_until(
            socket_, recv_buf_, boost::bind(
                    &TcpIO::IOInterface::IsPackageComplete, pInterface, boost::placeholders::_1,
                    boost::placeholders::_2),
            boost::asio::bind_executor(strand_, boost::bind(
                    &TcpClient::HandleRead, shared_from_this(), boost::placeholders::_1, boost::placeholders::_2)));
}

TcpClient::~TcpClient() {

}
