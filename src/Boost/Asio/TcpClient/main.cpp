//
// Created by God on 2021/5/1.
//

#include "tcp_client.h"
#include <boost/make_shared.hpp>
#include "test_client.h"
#include <boost/thread.hpp>
#include <LogWrapper.h>

boost::shared_ptr<TcpIO::TestClient> Start(boost::asio::io_context &ioContext);

int main() {
    boost::asio::io_context ioContext;
    auto pC = Start(ioContext);
    boost::thread_group threadPool;
    LOG_INFO("thread number is " << boost::thread::hardware_concurrency());
    for (size_t i = 0; i < boost::thread::hardware_concurrency(); ++i) {
        threadPool.create_thread(boost::bind(&boost::asio::io_context::run, &ioContext));
    }
    threadPool.join_all();
}

boost::shared_ptr<TcpIO::TestClient> Start(boost::asio::io_context &ioContext) {
    boost::shared_ptr<TcpIO::TestClient> pClient = boost::make_shared<TcpIO::TestClient>(ioContext, "127.0.0.1",
                                                                                         "1133");
    pClient->Start();
    return pClient;
}
