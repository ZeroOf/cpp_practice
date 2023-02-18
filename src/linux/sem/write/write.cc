//
// Created by Will Lee on 2021/9/16.
//

#include <semaphore.h>
#include <iostream>
#include <memory>
#include <fcntl.h>

void CloesSem(sem_t *pSem) {
    std::cout << pSem << std::endl;
    sem_close(pSem);
}

int main() {
    std::unique_ptr<sem_t, decltype(&CloesSem)> ptrSem(sem_open("test", O_CREAT | O_RDWR), &CloesSem);

    std::cout << "Start post, pSem : " << ptrSem.get() << std::endl;
    while (0 != sem_post(ptrSem.get())) {
        std::cout << errno << std::endl;
    }
    std::cout << "post sem success" << std::endl;
}