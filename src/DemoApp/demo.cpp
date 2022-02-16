//
// Created by Will Lee on 2022/2/2.
//

#include "demo.h"
#include <client_factory.h>
bool Demo::OnActivite() {
  return false;
}
void Demo::OnDeactivite() {

}
std::string &Demo::AppName() {
  static std::string name("Demo");
  return name;
}
Demo::Demo() : pClientFactory_(std::make_shared<ClientFactory>(thread_pool_)), server_(thread_pool_, pClientFactory_) {}
