#ifndef __WIZ_SOCKETIO_H__
#define __WIZ_SOCKETIO_H__
#include <stdio.h>

namespace wiz
{

class SocketIO
{
public:
	SocketIO(int sockfd);
	size_t readn(char * buf, size_t count);
	size_t writen(const char * buf, size_t count);
	size_t readline(char * buf, size_t max_len);

private:
	size_t recv_peek(char * buf, size_t count);
private:
	int _sockfd;
};

}

#endif
