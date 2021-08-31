//
// Created by Singl on 2021/4/28.
//

#ifndef CPP_PRACTICE_TCPCLIENT_H
#define CPP_PRACTICE_TCPCLIENT_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "io_interface.h"
#include "client.h"


class TcpClient : public Client {
public:
    TcpClient(boost::asio::thread_pool &threadPool, const std::shared_ptr<TcpIO::IOInterface> &ptrIoInterface);

    void Close() override;

    virtual ~TcpClient();

    void HandleConnect(const boost::system::error_code &ec, const boost::asio::ip::tcp::endpoint &remote);

    void Read() override;

private:
    void HandelSend(const boost::system::error_code &ec, size_t send_size, uint32_t msgType);

    void Connect(const boost::system::error_code &ec,
                 boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> remote) override;

protected:
    void SendInLoop() override;

private:
    boost::asio::ip::tcp::socket socket_;

};

#endif //CPP_PRACTICE_TCPCLIENT_H
