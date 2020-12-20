//
// Created by Singl on 2021/4/28.
//

#ifndef CPP_PRACTICE_TCPCLIENT_H
#define CPP_PRACTICE_TCPCLIENT_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "io_interface.h"

typedef boost::shared_ptr<TcpIO::IOInterface> InterfacePtr;

class TcpClient : public boost::enable_shared_from_this<TcpClient> {
public:
    TcpClient(boost::asio::io_context &ioContext, boost::shared_ptr<TcpIO::IOInterface> ptr_io_interface);

    void Start(const std::string &host, const std::string &service);

    void SendMsg(const std::string msg, uint32_t msg_type);

    void Close();

    virtual ~TcpClient();

private:
    void HandleConnect(const boost::system::error_code &ec);

    void HandleRead(const boost::system::error_code &ec, size_t recv_size);

    void HandelSend(const boost::system::error_code &ec, size_t send_size, uint32_t msgType);

    void Connect(const boost::system::error_code &ec,
                 boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> remote);

    void Read();

private:
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::ip::tcp::socket socket_;
    boost::weak_ptr<TcpIO::IOInterface> ptr_io_interface_;
    boost::asio::streambuf recv_buf_;
    boost::asio::ip::tcp::resolver resolver_;
};

#endif //CPP_PRACTICE_TCPCLIENT_H
