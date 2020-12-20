
#include "Eventfd.h"

#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <sys/eventfd.h>
#include <iostream>

using std::cout;
using std::endl;
using namespace wd;


Eventfd::Eventfd(EventfdCallback &&cb)
        : _fd(createEventfd()), _isStarted(false), _cb(std::move(cb)) {}

Eventfd::~Eventfd() {
    if (_isStarted) {
        Stop();
    }
}

void Eventfd::Start() {
    _isStarted = true;

    struct pollfd pfd;
    pfd.fd = _fd;
    pfd.events = POLLIN;

    while (_isStarted) {
        int nready = poll(&pfd, 1, 5000);
        if (nready == -1) {
            if (errno == EINTR)
                continue;
            perror("poll error");
            return;
        } else if (nready == 0)
            cout << ">>> poll time out" << endl;
        else {
            if (pfd.revents & POLLIN) {
                handleRead();//处理eventfd
                if (_cb)      // 执行任务
                    _cb();
            }
        }
    }
}

void Eventfd::Stop() {
    if (_isStarted) {
        _isStarted = false;
    }
}

int Eventfd::createEventfd() {
    int fd = eventfd(0, 0);
    if (fd == -1) {
        perror("eventfd error");
    }
    return fd;
}


void Eventfd::handleRead() {
    uint64_t howmany;
    int ret = read(_fd, &howmany, sizeof(howmany));
    if (ret != sizeof(uint64_t)) {
        perror("read error");
    }
}

void Eventfd::Wakeup() {
    uint64_t one = 1;
    int ret = write(_fd, &one, sizeof(one));
    if (ret != sizeof(one)) {
        perror("write error");
    }
}
