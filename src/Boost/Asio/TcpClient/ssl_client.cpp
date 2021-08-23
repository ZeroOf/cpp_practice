//
// Created by God on 2021/8/15.
//

#include "ssl_client.h"
#include <LogWrapper.h>
#include <boost/bind.hpp>
#include <functional>

SSLClient::SSLClient(boost::asio::io_context &ioContext, boost::asio::ssl::context &sslContext,
                     const boost::shared_ptr<TcpIO::IOInterface> &ptrIoInterface)
    : Client(ioContext, ptrIoInterface), ssl_stream_(ioContext, sslContext) {}

void SSLClient::Read() {
    if (auto pInterface = ptr_io_interface_.lock()) {
        boost::asio::async_read_until(
            ssl_stream_, recv_buf_,
            boost::bind(
                &TcpIO::IOInterface::IsPackageComplete, pInterface, boost::placeholders::_1, boost::placeholders::_2),
            boost::asio::bind_executor(
                strand_, boost::bind(&SSLClient::HandleRead, shared_from_this(),
                                     boost::placeholders::_1,
                                     boost::placeholders::_2)));
    }
    LOG_ERROR("interface has gone, close connection");
}

void SSLClient::HandleConnect(const boost::system::error_code &ec) {
    LOG_DEBUG("connect to " << ssl_stream_.lowest_layer().remote_endpoint() << " success!");
}


void SSLClient::SendMsg(const std::string msg, uint32_t msg_type) {
    auto self = shared_from_this();
    boost::asio::defer(strand_, [=, this]() {
        ssl_stream_.async_write_some(
            boost::asio::buffer(msg), boost::asio::bind_executor(
                strand_, std::bind(
                    &SSLClient::HandleSend, boost::static_pointer_cast<SSLClient>(shared_from_this()),
                    std::placeholders::_1, std::placeholders::_2, msg_type)));
    });
}

void SSLClient::Connect(const boost::system::error_code &ec,
                        boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> remote) {
    boost::asio::async_connect(
        ssl_stream_.lowest_layer(),
        remote,
        [this](const boost::system::error_code &ec, const boost::asio::ip::tcp::endpoint &endpoint) {
            if (ec) {
                LOG_ERROR("connect to " << endpoint << " failed!");
                return;
            }
            HandShake();
        });
}

void SSLClient::HandShake() {
    auto self = shared_from_this();
    ssl_stream_.async_handshake(
        boost::asio::ssl::stream_base::client,
        [this, self](const boost::system::error_code &ec) {
            auto pInterface = ptr_io_interface_.lock();
            if (!pInterface) {
                LOG_DEBUG("interface has gone, bye");
                return;
            };
            if (ec) {
                LOG_DEBUG("shake hand failed, " << ec);
                auto pInterface = ptr_io_interface_.lock();
                pInterface->OnConnectFailed();
            } else {
                pInterface->OnConnected();
            }
        });
}

void SSLClient::HandleSend(const boost::system::error_code &ec, std::size_t size, uint32_t msgType) {
    auto pinterface = ptr_io_interface_.lock();
    if (!pinterface) {
        LOG_ERROR("pinterface has gone.");
        return;
    }
    if (ec) {
        LOG_ERROR("send msg failed, cause " << ec);
        pinterface->OnSend(false, msgType);
        return;
    }
    pinterface->OnSend(true, msgType);
}
