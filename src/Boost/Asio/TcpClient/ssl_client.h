//
// Created by God on 2021/8/15.
//

#ifndef CPP_PRACTICE_SSL_CLIENT_H
#define CPP_PRACTICE_SSL_CLIENT_H


#include <boost/asio/ssl.hpp>
#include "client.h"

class SSLClient : public Client {
public:
    SSLClient(boost::asio::io_context &ioContext, boost::asio::ssl::context &sslContext,
              const boost::shared_ptr<TcpIO::IOInterface> &ptrIoInterface);

    void Read() override;

    void HandleConnect(const boost::system::error_code &ec);

    void SendMsg(const std::string msg, uint32_t msg_type) override;

protected:
    void Connect(const boost::system::error_code &ec,
                 boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> remote) override;

    void HandleSend(const boost::system::error_code &ec, std::size_t size, uint32_t msgType);

private:
    void HandShake();

private:
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_stream_;
};

#endif //CPP_PRACTICE_SSL_CLIENT_H
