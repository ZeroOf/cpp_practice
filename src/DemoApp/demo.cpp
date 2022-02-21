//
// Created by Will Lee on 2022/2/2.
//

#include "demo.h"
#include <client_factory.h>
Demo::Demo() : pClientFactory_(std::make_shared<ClientFactory>(thread_pool_)), server_(thread_pool_, pClientFactory_) {}

bool Demo::OnActivite() {
  server_.Start("127.0.0.1", 8080);
  return true;
}
void Demo::OnDeactivite() {

}
std::string &Demo::AppName() {
  static std::string name("Demo");
  return name;
}
void Demo::OnMessage(std::shared_ptr<message::Msg> ptr) {

}
