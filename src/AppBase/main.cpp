//
// Created by Will Lee on 2021/12/14.
//

#include <iostream>
#include "AppBase.h"
#include "task/TaskPool.h"
#include <Boost/Log/logwrapper/LogWrapper.h>

class Demo : public AppBase {
    bool OnActivite() override {
        LOG_INFO("start");
        while(true) {
          sleep(1);
        }
        return true;
    }

    void OnDeactivite() override {
        LOG_INFO("end");
    }

    TaskPool taskPool_;
};

int main() {
    Demo demo;
    demo.Run();
    std::cout << "hello app demo" << std::endl;
}