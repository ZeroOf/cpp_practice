//
// Created by Will Lee on 2021/12/22.
//

#include "server.h"


Server::Server(boost::asio::thread_pool &threadPool, std::shared_ptr<ClientFactory> pClientFactory) : acceptor_(
        threadPool), pClientFactory_(pClientFactory) {

}

void Server::Start(std::string ip, uint32_t port) {
    ip_ = ip;
    port_ = port_;
    acceptor_.bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip_), port));
    acceptor_.listen();
    acceptor_.async_accept(std::bind(&Server::HandleAccept, this, std::placeholders::_1, std::placeholders::_2));
}

void Server::HandleAccept(const boost::system::error_code &ec, boost::asio::ip::tcp::socket s) {
    auto client = pClientFactory_->GetClient(s);
    client->Start();
    acceptor_.async_accept(std::bind(&Server::HandleAccept, this, std::placeholders::_1, std::placeholders::_2));
}
