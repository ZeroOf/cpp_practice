#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

#include <iostream>

class socketio
{
public:
	socketio(int sockfd);
	size_t readn(char * buf,size_t count);
	size_t writen(const char * buf,size_t count);
	size_t readline(char * buf, size_t max_len);
private:
	size_t recv_peek(char * buf, size_t count);
	int _sockfd;
};
#endif
