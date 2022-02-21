//
// Created by Will Lee on 2022/2/2.
//

#include "client_handler.h"
#include <proto/message.pb.h>
#include <Boost/Log/logwrapper/LogWrapper.h>
#include "demo.h"
bool ClientHandler::OnRead(std::vector<char> msg) {
  if (msg.empty()) {
    return false;
  }
  std::shared_ptr<message::Msg> pInput;
  try {
    pInput->ParseFromArray(msg.data() + sizeof(uint32_t), msg.size() - sizeof(uint32_t));
  } catch (std::exception exception) {
    LOG_ERROR("Decode failed " << exception.what());
    return false;
  }
  Demo::get_mutable_instance().OnMessage(pInput);
}
void ClientHandler::OnConnected() {

}
void ClientHandler::OnConnectFailed() {

}
void ClientHandler::OnSend(bool isSendSuccess, uint32_t msgType) {

}
std::pair<TcpIO::buffer_iterator, bool> ClientHandler::IsPackageComplete(TcpIO::buffer_iterator begin,
                                                                         TcpIO::buffer_iterator end) {
  if (end - begin < sizeof(uint32_t)) {
    return std::pair<TcpIO::buffer_iterator, bool>(begin, false);
  }
  uint32_t packageLen = 0;
  std::copy(begin, end, &packageLen);
  packageLen = htonl(packageLen);
  if (packageLen > MAX_PACKAGE) {
    return std::pair<TcpIO::buffer_iterator, bool>(begin, true);
  }
  if (packageLen > end - begin) {
    return std::pair<TcpIO::buffer_iterator, bool>(begin, false);
  }
  return std::pair<TcpIO::buffer_iterator, bool>(begin + packageLen, true);
}
void ClientHandler::OnClose() {

}
void ClientHandler::Start() {
  IOInterface::Start();
}
