#include <iostream>
#include "Cast.h"
#include "Cast4IO.h"

class Base {
    int i;
};

class Derive : public Base {
    int j;
};

class Other {
    int k;
};

void TestStaticCast() {
    Other *pO = new Other();
//    static_cast decided in compile, so if it wrong you compiler will tell you,
//    Base* pB = static_cast<Base*>(pO);
    /*if (nullptr == pB) {
        std::cout << "cast error" << std::endl;
    }*/
    Base *pD = new Base();
    Derive *pA = static_cast<Derive *>(pD);
    std::cout << std::hex << pA << std::endl;
}

void TestCast() {
    //ok
    Cast cast(1);
    Cast cast2 = 1;
    std::cout << (int) cast << std::endl;
    std::cout << static_cast<int>(cast2) << std::endl;

    std::cout << (double) cast2 << std::endl;

}

void TestCastForIO() {
    std::cout << __FUNCTION__ << std::endl;
    Cast4IO cast4Io;
    std::cout << cast4Io << std::endl;
}

int main() {
    TestStaticCast();
    std::cout << "test Cast" << std::endl;
    TestCast();
    TestCastForIO();
}