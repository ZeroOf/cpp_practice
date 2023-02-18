#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <array>
#include <iostream>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]) {
  mqd_t mqdes;
  struct sigevent sev;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <mq-name>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  mqdes = mq_open(argv[1], O_RDONLY);
  if (mqdes == (mqd_t) -1)
    handle_error("mq_open");

  while (true) {
    fd_set rdSet;
    FD_ZERO(&rdSet);
    FD_SET(mqdes, &rdSet);
    if (select(mqdes + 1, &rdSet, nullptr, nullptr, nullptr) > 0) {
      std::array<char, 10240> buf;
      auto nr = mq_receive(mqdes, buf.data(), 10240, nullptr);
      if (nr < 0) {
        handle_error("mq_receive");
      }
      std::cout << "get message : " << buf.data() << std::endl;
    }
  }

  pause();    /* Process will be terminated by thread function */
}