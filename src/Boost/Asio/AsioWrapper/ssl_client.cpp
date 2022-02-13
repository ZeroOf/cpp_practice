#include "ssl_client.h"
#include <LogWrapper.h>
#include <functional>

namespace TcpIO {

SSLClient::SSLClient(boost::asio::thread_pool &threadPool,
                     boost::asio::ssl::context &sslContext,
                     const std::shared_ptr<TcpIO::IOInterface> &ptrIoInterface) : Client(threadPool,
                                                                                         ptrIoInterface,
                                                                                         SERVER),
                                                                                  ssl_stream_(strand_, sslContext) {
}

void SSLClient::Read() {
  boost::asio::async_read_until(ssl_stream_,
                                boost::asio::dynamic_buffer(recv_buf_),
                                std::bind(&TcpIO::IOInterface::IsPackageComplete,
                                          ptr_io_interface_,
                                          std::placeholders::_1,
                                          std::placeholders::_2),
                                std::bind(&Client::HandleRead,
                                          shared_from_this(),
                                          std::placeholders::_1,
                                          std::placeholders::_2));
  return;
}

void SSLClient::HandleConnect(const boost::system::error_code &ec, const boost::asio::ip::tcp::endpoint &remote) {
  if (ec) {
    LOG_ERROR("connect to " << host_ << ":" << service_ << " failed!");
    ptr_io_interface_->OnConnectFailed();
    return;
  }
  LOG_DEBUG("connect to " << ssl_stream_.lowest_layer().remote_endpoint() << " success!");
  HandShake();
}

void SSLClient::Connect(const boost::system::error_code &ec,
                        boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> remote) {
  auto self = shared_from_this();
  boost::asio::async_connect(ssl_stream_.lowest_layer(),
                             remote,
                             std::bind(&SSLClient::HandleConnect,
                                       std::static_pointer_cast<SSLClient>(shared_from_this()),
                                       std::placeholders::_1,
                                       std::placeholders::_2));
}

void SSLClient::HandShake() {
  auto self = shared_from_this();
  ssl_stream_.async_handshake(boost::asio::ssl::stream_base::client, [this, self](const boost::system::error_code &ec) {
    if (ec) {
      LOG_DEBUG("shake hand failed, " << ec);
      ptr_io_interface_->OnConnectFailed();
    } else {
      isConnected_ = true;
      ssl_stream_.lowest_layer().non_blocking(true);
      ptr_io_interface_->OnConnected();
      Read();
    }
  });
}

void SSLClient::HandleSend(const boost::system::error_code &ec, std::size_t size, uint32_t msgType) {
  if (ec) {
    LOG_ERROR("send msg failed, cause " << ec);
    ptr_io_interface_->OnSend(false, msgType);
  } else {
    LOG_DEBUG("send " << size << " bytes");
    ptr_io_interface_->OnSend(true, msgType);
  }
  SendInLoop();
}

void SSLClient::Close() {
  LOG_DEBUG("close ssl connection");
  auto self = shared_from_this();
  boost::system::error_code ec;
  ssl_stream_.lowest_layer().cancel(ec);
  if (ec) {
    LOG_ERROR(ec.message());
  }
  ssl_stream_.async_shutdown([self, this](const boost::system::error_code &ec) {
    if (ec) {
      LOG_ERROR(ec.message())
    }
    LOG_DEBUG("close socket");
    boost::system::error_code ecClose;
    ssl_stream_.lowest_layer().close(ecClose);
    if (ecClose) {
      LOG_ERROR(ec.message());
    }
    ptr_io_interface_->OnClose();
  });
}

void SSLClient::SendInLoop() {
  if (out_box_.empty()) {
    return;
  }
  auto &msgPair = out_box_.front();
  boost::asio::async_write(ssl_stream_,
                           boost::asio::buffer(*msgPair.first),
                           std::bind(&SSLClient::HandleSend,
                                     std::static_pointer_cast<SSLClient>(shared_from_this()),
                                     std::placeholders::_1,
                                     std::placeholders::_2,
                                     msgPair.second));
}
}
