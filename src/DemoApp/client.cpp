//
// Created by Will Lee on 2022/2/2.
//

#include "client.h"
void Client::OnRead(std::vector<char> msg) {

}
void Client::OnConnected() {

}
void Client::OnConnectFailed() {

}
void Client::OnSend(bool isSendSuccess, uint32_t msgType) {

}
std::pair<TcpIO::buffer_iterator, bool> Client::IsPackageComplete(TcpIO::buffer_iterator begin,
                                                                  TcpIO::buffer_iterator end) {
  return std::pair<TcpIO::buffer_iterator, bool>();
}
void Client::OnClose() {

}
void Client::Start() {
  IOInterface::Start();
}
