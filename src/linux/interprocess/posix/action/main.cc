//
// Created by Will Lee on 2021/10/30.
//

#include <iostream>
#include <signal.h>
#include <thread>
#include <vector>

void SingnalHandler(int sigNum, siginfo_t *pInfo, void *pData) {
    std::cout << __func__ << " run on " << std::this_thread::get_id() << std::endl;
    std::cout << "sig Num is " << sigNum << std::endl;
    std::cout << "sig info " << pInfo->si_signo << std::endl;
}

int main() {
    struct sigaction action;
    action.sa_sigaction = SingnalHandler;
    action.sa_flags = SA_SIGINFO;

    if (0 > sigaction(SIGINT, &action, nullptr)) {
        perror("sigaction");
    }
    std::cout << __func__ << " run on " << std::this_thread::get_id() << std::endl;
    std::vector<std::thread> threadGrp;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGUSR1);
    for (int i = 0; i < 32; ++i) {
        threadGrp.emplace_back([&set]() {
            pthread_sigmask(SIG_BLOCK, &set, nullptr);
            std::cout << __func__ << "run on " << std::this_thread::get_id() << std::endl;
            for (int i = 60; i > 0; --i) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        });
    }
    std::thread sigWait([&set](){
        int sig;
        for(;;) {
//            std::this_thread::sleep_for(std::chrono::seconds(10));
            int s = sigwait(&set, &sig);
            if (s != 0) {
                perror("sigwait");
                exit(-1);
            }
            std::cout << "sig num " << sig << std::endl;
        }
    });
    pthread_sigmask(SIG_BLOCK, &set, nullptr);
    std::cout << __func__ << " run on " << std::this_thread::get_id() << std::endl;
    for (int i = 60; i > 0; --i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    for (auto &thread: threadGrp) {
        thread.join();
    }
    sigWait.join();
}