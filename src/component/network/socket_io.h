
#ifndef _WILL_SOCKET_IO_H
#define _WILL_SOCKET_IO_H

#include <stdio.h>
#include "common.h"

COMPONENT_SPACE_START

class SocketIO {
 public:
  SocketIO(int sockfd);

  size_t readn(char *buf, size_t count);

  size_t writen(const char *buf, size_t count);

  size_t readline(char *buf, size_t max_len);

 private:
  size_t recv_peek(char *buf, size_t count);

 private:
  int sockfd_;
};

COMPONENT_SPACE_END

#endif
