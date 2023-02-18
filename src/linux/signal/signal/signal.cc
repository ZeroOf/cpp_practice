//
// Created by Will Lee on 2021/11/1.
//

#include <csignal>
#include <iostream>
#include <thread>
#include <vector>

void Handle(int sig) {
    std::cout << __func__ << " run on " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::cout << "hello signal " << std::endl;
    signal(SIGINT, Handle);
    std::vector<std::thread> threadGrp;
    for (int i = 0; i < 10; ++i) {
        threadGrp.emplace_back([]() {
            while (true) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        });
    }
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}