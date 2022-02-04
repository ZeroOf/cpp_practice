//
// Created by Will Lee on 2022/2/2.
//

#include "demo.h"
bool Demo::OnActivite() {
  return false;
}
void Demo::OnDeactivite() {

}
std::string &Demo::AppName() {
  static std::string name("Demo");
  return name;
}
