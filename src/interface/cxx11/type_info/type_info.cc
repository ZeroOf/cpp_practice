
#include <iostream>

class A {
 public:
  int i;
};

struct B {
  int i;
};

class CClass {
 public:
  CClass() {}

 private:

  int i;
};

int main() {
  A a;
  B b;
  std::cout << typeid(int).name() << std::endl;
  std::cout << typeid(a).name() << std::endl;
  std::cout << typeid(b).name() << std::endl;
  std::cout << typeid(CClass).name() << std::endl;

  std::cout << typeid(A).before(typeid(B)) << std::endl;
}