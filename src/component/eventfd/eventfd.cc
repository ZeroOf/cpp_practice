#include "eventfd.h"

#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <sys/eventfd.h>
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

COMPONENT_SPACE_START

Eventfd::Eventfd(EventfdCallback &&callback)
    : eventfd_(CreateEventFD()), isStarted_(false), callback_(std::move(callback)) {}

Eventfd::~Eventfd() {
  if (isStarted_) {
    Stop();
  }
}


void Eventfd::Start() {
  isStarted_ = true;

  struct pollfd pfd = {
      .fd = eventfd_,
      .events = POLLIN
  };

  const int pollTimeout = 5000; // 5 seconds

  while (isStarted_) {
    int pollResult = poll(&pfd, 1, pollTimeout);
    if (pollResult == -1) {
      if (errno == EINTR) {
        continue; // Interrupted by a signal, try again
      }
      std::cerr << "poll error: " << strerror(errno) << std::endl;
      break; // Exit the loop on error
    } else if (pollResult == 0) {
      std::cout << ">>> poll timed out" << std::endl;
    } else {
      HandlePollEvents(pfd.revents);
    }
  }
}

void Eventfd::HandlePollEvents(short events) {
  if (events & POLLIN) {
    HandleRead(); // Handle read event from the file descriptor
    if (callback_) {
      callback_(); // Execute the callback function if set
    }
  }
}


void Eventfd::Stop() {
  if (isStarted_) {
    isStarted_ = false;
  }
}

int Eventfd::CreateEventFD() {
  int fd = eventfd(0, 0);
  if (fd == -1) {
    perror("eventfd error");
  }
  return fd;
}

void Eventfd::HandleRead() {
  uint64_t howMany;
  int ret = read(eventfd_, &howMany, sizeof(howMany));
  if (ret != sizeof(uint64_t)) {
    perror("read error");
  }
}

void Eventfd::Wakeup() {
  uint64_t one = 1;
  int ret = write(eventfd_, &one, sizeof(one));
  if (ret != sizeof(one)) {
    perror("write error");
  }
}

COMPONENT_SPACE_END