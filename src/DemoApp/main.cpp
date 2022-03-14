//
// Created by Will Lee on 2022/2/10.
//

#include <demo.h>

int main() {
  daemon(1, 0);
  Demo demo;
  demo.Run();
}