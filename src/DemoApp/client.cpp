//
// Created by Will Lee on 2022/2/2.
//

#include "client.h"
void Client::OnRead(std::vector<char> msg) {
  if (msg.empty()) {
  }
}
void Client::OnConnected() {

}
void Client::OnConnectFailed() {

}
void Client::OnSend(bool isSendSuccess, uint32_t msgType) {

}
std::pair<TcpIO::buffer_iterator, bool> Client::IsPackageComplete(TcpIO::buffer_iterator begin,
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
void Client::OnClose() {

}
void Client::Start() {
  IOInterface::Start();
}
