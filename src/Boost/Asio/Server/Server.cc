#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind/bind.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>

namespace ssl = boost::asio::ssl;
using boost::asio::ip::tcp;
using boost::system::error_code;

class session : public std::enable_shared_from_this<session> {
 public:
  session(tcp::socket socket, ssl::context &context) : socket_(std::move(socket), context) {
  }

  void start() {
    do_handshake();
  }

 private:
  void do_handshake() {
    auto self(shared_from_this());
    socket_.async_handshake(ssl::stream_base::server, [this, self](error_code error) {
      if (!error) {
        do_read();
      }
    });
  }

  void do_read() {
    auto self(shared_from_this());

    socket_.async_read_some(boost::asio::buffer(data_), [this, self](error_code ec, std::size_t length) {
      if (!ec) {
        std::cout << "get <";
        std::cout.write(data_.data(), length);
        std::cout << std::endl;
        do_write(length);
      }
    });
  }

  void do_write(std::size_t length) {
    auto self(shared_from_this());
    std::cout << "send <";
    std::cout.write(data_.data(), length);
    std::cout << std::endl;
    boost::asio::async_write(socket_,
                             boost::asio::buffer(data_.data(), length),
                             [this, self](error_code ec, std::size_t /*length*/) {
                               if (!ec) {
                                 do_read();
                               }
                             });
  }

  ssl::stream<tcp::socket> socket_;
  std::array<char, 1024> data_;
};

class server {
 public:
  server(boost::asio::io_context &io_context, unsigned short port) : acceptor_(io_context,
                                                                               tcp::endpoint(tcp::v4(), port)),
                                                                     context_(ssl::context::sslv23) {
    context_.set_options(ssl::context::default_workarounds | ssl::context::no_sslv2 | ssl::context::single_dh_use);
    context_.set_password_callback(std::bind(&server::get_password, this));
    context_.use_certificate_chain_file("server.pem");
    context_.use_private_key_file("server.pem", ssl::context::pem);
    context_.use_tmp_dh_file("dh2048.pem");

    do_accept();
  }

 private:
  std::string get_password() const {
    return "test";
  }

  void do_accept() {
    acceptor_.async_accept([this](error_code error, tcp::socket socket) {
      if (!error) {
        std::make_shared<session>(std::move(socket), context_)->start();
      }

      do_accept();
    });
  }

  tcp::acceptor acceptor_;
  ssl::context context_;
};

int main(int argc, char *argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    server s(io_context, std::atoi(argv[1]));

    io_context.run();
    return 0;
  } catch (std::exception const &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
}