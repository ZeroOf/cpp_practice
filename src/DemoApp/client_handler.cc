//
// Created by Will Lee on 2022/2/2.
//

#include "client_handler.h"
#include <message.pb.h>
#include <Boost/Log/logwrapper/LogWrapper.h>
#include "demo.h"
bool ClientHandler::OnRead(std::vector<char> msg) {
  if (msg.empty()) {
    LOG_ERROR("get empty message, close it");
    return false;
  }
  std::shared_ptr<message::Msg> pInput = std::make_shared<message::Msg>();
  try {
    pInput->ParseFromArray(msg.data() + sizeof(uint32_t), msg.size() - sizeof(uint32_t));
  } catch (std::exception exception) {
    LOG_ERROR("Decode failed " << exception.what());
    return false;
  }
  Demo::get_mutable_instance().OnMessage(pInput, seq_);
  return true;
}

void ClientHandler::OnConnected(const std::string &host, unsigned short port) {
  LOG_INFO("connect with " << host << ":" << port << " Established");
}
void ClientHandler::OnConnectFailed(const std::string &host, unsigned short port) {
  LOG_INFO("connect to " << host << ":" << port << " failed");
}
void ClientHandler::OnSend(bool isSendSuccess, uint32_t msgType) {
  if (isSendSuccess) {
    LOG_DEBUG("send message type : " << msgType << "success");
  } else {
    LOG_ERROR("send message type : " << msgType << "failed");
  }
}
std::pair<TcpIO::buffer_iterator, bool> ClientHandler::IsPackageComplete(TcpIO::buffer_iterator begin,
                                                                         TcpIO::buffer_iterator end) {
  if (end - begin < sizeof(uint32_t)) {
    return std::pair<TcpIO::buffer_iterator, bool>(begin, false);
  }
  uint32_t packageLen = 0;
  std::copy(begin, end, &packageLen);
  packageLen = ntohl(packageLen);
  if (packageLen > MAX_PACKAGE) {
    return std::pair<TcpIO::buffer_iterator, bool>(begin, true);
  }
  if (packageLen > end - begin) {
    return std::pair<TcpIO::buffer_iterator, bool>(begin, false);
  }
  return std::pair<TcpIO::buffer_iterator, bool>(begin + packageLen, true);
}
void ClientHandler::OnClose() {
  LOG_INFO("close connection");
  Demo::get_mutable_instance().RemoveClient(seq_);
}

void ClientHandler::Start() {
  IOInterface::Start();
}
ClientHandler::ClientHandler(size_t seq) : seq_(seq) {}
