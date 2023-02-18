#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/thread.hpp>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>

using boost::asio::ip::tcp;
using boost::system::error_code;
using std::placeholders::_1;
using std::placeholders::_2;
namespace ssl = boost::asio::ssl;

using Executor = boost::asio::thread_pool::executor_type;

class client {
 public:
  client(Executor ex, ssl::context &context,
         const tcp::resolver::results_type &endpoints)
      : strand_(ex), socket_(strand_, context) {
    socket_.set_verify_mode(ssl::verify_peer);
    socket_.set_verify_callback(
        std::bind(&client::verify_certificate, this, _1, _2));

    connect(endpoints);
  }

 private:
  bool verify_certificate(bool preverified, ssl::verify_context &ctx) {
    char subject_name[256];
    X509 *cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying " << subject_name << "\n";

    return true;
  }

  void connect(const tcp::resolver::results_type &endpoints) {
    async_connect( //
        socket_.lowest_layer(), endpoints,
        bind_executor(
            strand_, [this](error_code error, const tcp::endpoint &) {
              if (!error) {
                handshake();
              } else {
                std::cout << "Connect failed: " << error.message() << "\n";
              }
            }));
  }

  void handshake() {
    socket_.async_handshake(
        ssl::stream_base::client,
        bind_executor(strand_, [this](error_code error) {
          if (!error) {
            send_request("hello ssl");
            recv(); // already on the strand in this completion handler
          } else {
            std::cout << "Handshake failed: " << error.message()
                      << "\n";
          }
        }));
  }

  void send_request(std::string msg) {
    outbox_.push_back(std::move(msg));
    if (outbox_.size() == 1) {
      send_loop();
    }
  }

  void send_loop() {
    async_write( //
        socket_, boost::asio::buffer(outbox_.back()),
        bind_executor(
            strand_, [this](error_code error, std::size_t length) {
              if (!error) {
                std::cout << "send data success, size : " << length << std::endl;
                outbox_.pop_back();
              } else {
                std::cout << "Write failed: " << error.message() << std::endl;
              }
              if (!outbox_.empty())
                send_loop();
            }));
  }

  void recv() {
    async_read(
        socket_, boost::asio::dynamic_buffer(buffer_), boost::asio::transfer_exactly(9),
        boost::asio::bind_executor(
            strand_, [this](error_code error, std::size_t length) {
              if (!error) {
                std::cout << buffer_ << std::endl;

                send_request(std::move(buffer_));
                recv(); // already on the strand in this completion handler
              } else {
                std::cout << "Read failed: " << error.message() << std::endl;
              }
            }));
  }

  boost::asio::strand<Executor> strand_;
  ssl::stream<tcp::socket> socket_;
  std::string buffer_;
  std::deque<std::string> outbox_;
};

int main(int argc, char *argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: client <host> <port>\n";
      return 1;
    }

    ssl::context ctx(ssl::context::sslv23);
    ctx.load_verify_file("ca.pem");

    boost::asio::thread_pool io;
    tcp::resolver resolver(io);

    client c(io.get_executor(), ctx, resolver.resolve(argv[1], argv[2]));
    io.join();

    return 0;
  } catch (std::exception const &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
}