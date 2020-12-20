//
// Created by God on 2021/5/4.
//

#ifndef CPP_PRACTICE_SRC_BOOST_ASIO_TCPCLIENT_IO_INTERFACE_H_TEST_CLIENT_H_
#define CPP_PRACTICE_SRC_BOOST_ASIO_TCPCLIENT_IO_INTERFACE_H_TEST_CLIENT_H_

#include <boost/asio/buffers_iterator.hpp>
#include "io_interface.h"
#include "tcp_client.h"

namespace TcpIO {

    class TestClient : public IOInterface {
    public:
        TestClient(boost::asio::io_context &ioContext, const std::string &host, const std::string &service);

        void OnRead(std::vector<char> msg) override;

        void OnConnected() override;

        void OnConnectFailed() override;

        void OnSend(bool isSendSuccess, uint32_t msgType) override;

        std::pair<buffer_iterator, bool> IsPackageComplete(buffer_iterator begin, buffer_iterator end) override;

        void OnClose() override;

        void Start();

        virtual ~TestClient();

    private:
        void DelayConnect();

    private:
        boost::asio::io_context &io_context_;
        boost::shared_ptr<TcpClient> ptr_client_;
        boost::asio::strand<boost::asio::io_context::executor_type> strand_;
        boost::asio::steady_timer timer_;
        std::string host_;
        std::string service_;
    };

}

#endif //CPP_PRACTICE_SRC_BOOST_ASIO_TCPCLIENT_IO_INTERFACE_H_TEST_CLIENT_H_
