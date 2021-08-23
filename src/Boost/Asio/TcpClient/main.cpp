//
// Created by God on 2021/5/1.
//

#include "tcp_client.h"
#include <boost/make_shared.hpp>
#include "test_client.h"
#include <boost/thread.hpp>
#include <LogWrapper.h>
#include "ssl_client.h"

boost::shared_ptr<TcpIO::TestClient> Start(boost::asio::io_context &ioContext);

boost::shared_ptr<TcpIO::TestClient>
StartSSL(boost::asio::io_context &ioContext, std::shared_ptr<boost::asio::ssl::context> pSSLContext) {
    boost::shared_ptr<TcpIO::TestClient> pClient =
        boost::make_shared<TcpIO::TestClient>(ioContext, "127.0.0.1", "1133");
    pClient->Start(pSSLContext);
    return pClient;
}

int main() {
    boost::asio::io_context ioContext;
    std::shared_ptr<boost::asio::ssl::context> pSSLContext
        = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv13);
    pSSLContext->load_verify_file("ca.pem");
    auto pC = StartSSL(ioContext, pSSLContext);
    boost::thread_group threadPool;
    LOG_INFO("thread number is " << boost::thread::hardware_concurrency());
    for (size_t i = 0; i < boost::thread::hardware_concurrency(); ++i) {
        threadPool.create_thread(boost::bind(&boost::asio::io_context::run, &ioContext));
    }
    threadPool.join_all();
}

boost::shared_ptr<TcpIO::TestClient> Start(boost::asio::io_context &ioContext) {
    boost::shared_ptr<TcpIO::TestClient> pClient =
        boost::make_shared<TcpIO::TestClient>(ioContext, "127.0.0.1", "1133");
    pClient->Start(std::shared_ptr<boost::asio::ssl::context>());
    return pClient;
}
