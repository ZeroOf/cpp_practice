//
// Created by Will Lee on 2021/9/16.
//

#include <mqueue.h>
#include <iostream>
#include <array>
#include <thread>
#include <chrono>

int main() {
    mqd_t mq = mq_open("/test", O_RDWR | O_NONBLOCK);
    if (mq == -1) {
        perror("mq_open");
        exit(-1);
    }
    auto size = mq_send(mq, "hello mq", 8, 0);
    std::cout << size << std::endl;
    perror("mq_send");
    while (true) {
        fd_set wrSet;
        FD_ZERO(&wrSet);
        FD_SET(mq, &wrSet);

        fd_set rdSet;
        FD_ZERO(&rdSet);
        FD_SET(mq, &rdSet);

        auto nReady = select(mq + 1, &rdSet, &wrSet, nullptr, nullptr);
        std::cout << "select return " << nReady << std::endl;
        if (nReady > 0) {
            if (FD_ISSET(mq, &wrSet)) {
                std::cout << std::boolalpha << FD_ISSET(mq, &wrSet) << std::endl;
                auto sendSize = mq_send(mq, "hello mq", 8, 0);
                if (sendSize == -1) {
                    perror("mq_send");
                    exit(-1);
                }
                std::cout << "send success" << std::endl;
            }
            if (FD_ISSET(mq, &rdSet)) {
                std::cout << std::boolalpha << FD_ISSET(mq, &rdSet) << std::endl;
                std::array<char, 10250> buffer{0};
                auto recvSize = mq_receive(mq, buffer.data(), 10250, nullptr);
                if (recvSize == -1) {
                    perror("mq_receive");
                    exit(-1);
                }
                std::cout << "recvsize " << recvSize << ", data : " << buffer.data() << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}