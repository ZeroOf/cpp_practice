#ifndef CPP_PRACTICE_CLIENT_H
#define CPP_PRACTICE_CLIENT_H

#include <boost/asio.hpp>
#include <deque>
#include "io_interface.h"

using InterfacePtr = std::shared_ptr<TcpIO::IOInterface>;

enum ClientType {
  CLIENT, SERVER
};

class Client : public std::enable_shared_from_this<Client> {
 public:
  Client(boost::asio::thread_pool &thread_pool, std::shared_ptr<TcpIO::IOInterface> ptr_io_interface, ClientType type);

  virtual void Read() = 0;

  void Start(const std::string &host, unsigned short service);

  void HandleRead(const boost::system::error_code &ec, size_t recv_size);

  void SendMsg(const std::string &msg, uint32_t msg_type);

  virtual void Close() = 0;
  virtual ~Client();

 protected:
  virtual void HandleConnect(const boost::system::error_code &ec, const boost::asio::ip::tcp::endpoint &remote) = 0;
  virtual void Connect(const boost::system::error_code &ec,
                       boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> remote) = 0;

  virtual void SendInLoop() = 0;

 protected:
  std::weak_ptr<TcpIO::IOInterface> ptr_io_interface_;
  boost::asio::strand<boost::asio::thread_pool::executor_type> strand_;
  std::vector<char> recv_buf_;
  std::deque<std::pair<std::shared_ptr<std::string>, uint32_t>> out_box_;
  std::string host_;
  std::string service_;
  bool isConnected_ = false;
  ClientType type_;
 private:
  boost::asio::ip::tcp::resolver resolver_;
};

#define GET_INTERFACE(pInterface)               \
    auto pInterface = ptr_io_interface_.lock(); \
    if(!pInterface) {                           \
        LOG_ERROR("interface has gone");        \
        return;                                 \
    }

#endif //CPP_PRACTICE_CLIENT_H
