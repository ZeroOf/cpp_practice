//
// Created by Will Lee on 2021/9/11.
//
#include <pthread.h>
#include <iostream>

class Base {
public:
    Base() {
        DoSomething();
    }

    virtual void DoSomething() {
        std::cout << "Base" << std::endl;
    }

    virtual ~Base() {
        DoSomething();

    }
};

struct Derive : public Base {
    Derive() {
        DoSomething();
    }

    void DoSomething() override {
        std::cout << "Derive" << std::endl;
    }

    ~Derive() override {
        DoSomething();
    }

public:

};

int main() {
    Base* pDerive = new Derive;
    pDerive->DoSomething();
    auto ptr = dynamic_cast<Derive*>(pDerive);
    std::cout << ptr << std::endl;
    std::cout << typeid(*pDerive).name() << std::endl;
    delete pDerive;
}
