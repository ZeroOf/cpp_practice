#include "Timer.h"
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <poll.h>
#include <sys/timerfd.h>

Timer::Timer(int initialTime, int perodicTime, TimerCallback &&cb)
        : _fd(createTimerfd()), _initialTime(initialTime), _perodicTime(perodicTime), _isStarted(false), _cb(cb) {}

Timer::~Timer() {
    if (_isStarted)
        stop();
}

void Timer::Start() {
    _isStarted = true;

    struct pollfd pfd{_fd, POLLIN};

    setTimerfd(_initialTime, _perodicTime);

    while (_isStarted) {
        int nready = poll(&pfd, 1, 5000);
        if (nready == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("poll error");
            return;
        } else if (nready == 0) {
            std::cout << "poll time out" << std::endl;
        } else {
            handleRead();
            if (_cb) {
                _cb();
            }
        }
    }
}

void Timer::stop() {
    if (_isStarted) {
        setTimerfd(0, 0);
        _isStarted = false;
    }
}

int Timer::createTimerfd() {
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if (fd == -1) {
        perror("timerfd_create error");
    }
    return fd;
}

void Timer::setTimerfd(int initialTime, int perodicTime) const {
    struct itimerspec value{};
    value.it_value.tv_sec = initialTime;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = perodicTime;
    value.it_interval.tv_nsec = 0;

    int ret = timerfd_settime(_fd, 0, &value, nullptr);
    if (ret == -1) {
        perror("timerfd_settime error");
    }
}

void Timer::handleRead() const {
    uint64_t howmany;
    int ret = read(_fd, &howmany, sizeof(howmany));
    if (ret != sizeof(uint64_t)) {
        perror("read error");
    }
}
