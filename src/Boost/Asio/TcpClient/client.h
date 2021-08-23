//
// Created by God on 2021/8/9.
//

#ifndef CPP_PRACTICE_CLIENT_H
#define CPP_PRACTICE_CLIENT_H


#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "io_interface.h"

class Client : public ::boost::enable_shared_from_this<Client> {
public:
    Client(boost::asio::io_context &ioContext, boost::shared_ptr<TcpIO::IOInterface> ptr_io_interface);

    virtual void Read() = 0;

    void Start(const std::string &host, const std::string &service);

    virtual void SendMsg(const std::string msg, uint32_t msg_type) = 0;

    void HandleRead(const boost::system::error_code &ec, size_t recv_size);

protected:
    virtual void Connect(const boost::system::error_code &ec,
                         boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> remote) = 0;

protected:
    boost::weak_ptr<TcpIO::IOInterface> ptr_io_interface_;
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::streambuf recv_buf_;
    boost::asio::ip::tcp::endpoint local_endpoint_;
    boost::asio::ip::tcp::endpoint remote_endpoint_;
private:
    boost::asio::ip::tcp::resolver resolver_;
};


#endif //CPP_PRACTICE_CLIENT_H
