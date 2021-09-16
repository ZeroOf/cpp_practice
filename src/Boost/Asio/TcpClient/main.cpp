//
// Created by God on 2021/5/1.
//

#include "tcp_client.h"
#include <boost/make_shared.hpp>
#include "test_client.h"
#include <boost/thread.hpp>
#include <LogWrapper.h>
#include "ssl_client.h"

boost::shared_ptr<TcpIO::TestClient> Start(boost::asio::thread_pool &threadPool);

std::shared_ptr<TcpIO::TestClient>
StartSSL(boost::asio::thread_pool &threadPool, std::shared_ptr<boost::asio::ssl::context> pSSLContext,
         const char host[], const char service[]) {
    std::shared_ptr<TcpIO::TestClient> pClient = std::make_shared<TcpIO::TestClient>(threadPool, host, service);
    pClient->Start(pSSLContext);
    return pClient;
}

int main(int argc, const char *argv[]) {
    std::shared_ptr<boost::asio::ssl::context> pSSLContext
        = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv13);
    pSSLContext->load_verify_file("ca.pem");
    boost::asio::thread_pool threadPool;
//    auto pC = StartSSL(threadPool, pSSLContext, argv[1], argv[2]);
    auto pC = Start(threadPool);
    threadPool.join();
}

boost::shared_ptr<TcpIO::TestClient> Start(boost::asio::thread_pool &threadPool) {
    boost::shared_ptr<TcpIO::TestClient> pClient =
        boost::make_shared<TcpIO::TestClient>(threadPool, "127.0.0.1", "1133");
    pClient->Start(std::shared_ptr<boost::asio::ssl::context>());
    return pClient;
}
