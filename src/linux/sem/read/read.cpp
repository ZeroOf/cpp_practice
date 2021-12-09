//
// Created by Will Lee on 2021/9/15.
//

#include <semaphore.h>
#include <memory>
#include <fcntl.h>
#include <iostream>

void CloesSem(sem_t *pSem) {
    std::cout << pSem << std::endl;
    sem_close(pSem);
    sem_unlink("test");
}

int main() {
    std::unique_ptr<sem_t, decltype(&CloesSem)> ptrSem(sem_open("test", O_CREAT | O_RDWR), &CloesSem);
    sem_init(ptrSem.get(), 1, 0);
    std::cout << "Start wait, pSem : " << ptrSem.get() << std::endl;
    while(0 != sem_wait(ptrSem.get())) {
        std::cout << errno << std::endl;
    }
    std::cout << "get sem" << std::endl;
}