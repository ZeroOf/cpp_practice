#include "timer.h"
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <poll.h>
#include <sys/timerfd.h>
#include <cstdint>

COMPONENT_SPACE_START

Timer::Timer(int initialTime, int periodicTime, TimerCallback &&cb)
    : _fd(CreateTimer()), _initialTime(initialTime), _periodicTime(periodicTime), _isStarted(false), _cb(cb) {}

Timer::~Timer() {
  if (_isStarted)
    Stop();
}

void Timer::Start() {
  _isStarted = true;

  struct pollfd pfd{_fd, POLLIN};

  SetTimer(_initialTime, _periodicTime);

  while (_isStarted) {
    int readyCount = poll(&pfd, 1, 5000);
    if (readyCount == -1) {
      if (errno == EINTR) {
        continue;
      }
      perror("poll error");
      return;
    } else if (readyCount == 0) {
      std::cout << "poll time out" << std::endl;
    } else {
      HandleRead();
      if (_cb) {
        _cb();
      }
    }
  }
}

void Timer::Stop() {
  if (_isStarted) {
    SetTimer(0, 0);
    _isStarted = false;
  }
}

int Timer::CreateTimer() {
  int fd = timerfd_create(CLOCK_REALTIME, 0);
  if (fd == -1) {
    perror("timerfd_create error");
  }
  return fd;
}

void Timer::SetTimer(int initialTime, int periodicTime) const {
  struct itimerspec value{};
  value.it_value.tv_sec = initialTime;
  value.it_value.tv_nsec = 0;
  value.it_interval.tv_sec = periodicTime;
  value.it_interval.tv_nsec = 0;

  int ret = timerfd_settime(_fd, 0, &value, nullptr);
  if (ret == -1) {
    perror("timerfd_settime error");
  }
}

void Timer::HandleRead() const {
  uint64_t buffer;
  int ret = read(_fd, &buffer, sizeof(buffer));
  if (ret != sizeof(uint64_t)) {
    perror("read error");
  }
}

COMPONENT_SPACE_END