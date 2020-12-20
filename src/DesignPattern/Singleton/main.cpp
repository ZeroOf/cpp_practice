
#include <iostream>
#include "SingletonLazy.h"
#include "SingletonHungry.h"
#include "Singleton.hpp"
#include "Impl.h"
#include "TSSingleton.hpp"

void TestHungry() {
    std::cout << __func__ << std::endl;
    std::cout << SingletonHungry::getInstance() << std::endl;
    std::cout << SingletonHungry::getInstance() << std::endl;
    std::cout << SingletonHungry::getInstance() << std::endl;
}

void TestLazy() {
    std::cout << __func__ << std::endl;
    std::cout << (void *) SingletonLazy::instance() << std::endl;
    std::cout << (void *) SingletonLazy::instance() << std::endl;
    std::cout << (void *) SingletonLazy::instance() << std::endl;
}

void TestTemplate() {
    std::cout << __func__ << std::endl;
    Singleton<Impl>::getInstance()->Print();
    Singleton<Impl>::getInstance()->Print();
    Singleton<Impl>::getInstance()->Print();
}

void TestTemplate2() {
    std::cout << __func__ << std::endl;
    TSSingleton<Impl>::getInstance()->Print();
    TSSingleton<Impl>::getInstance()->Print();
    TSSingleton<Impl>::getInstance()->Print();
    TSSingleton<Impl>::getInstance()->Print();
}

int main() {
//    TestHungry();
//    TestLazy();
//    TestTemplate();
    TestTemplate2();
}