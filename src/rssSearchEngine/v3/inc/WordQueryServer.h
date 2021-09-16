#ifndef __WORDQUERYSERVER_H__
#define __WORDQUERYSERVER_H__

#include "Configuration.h"
#include "WordQuery.h"
#include "TcpServer.h"
#include "Threadpool.h"

class WordQueryServer
{ 
public:
	WordQueryServer(Configuration & conf);
	void start();
private:
	Configuration _conf;
	wordQuery _wqo;
	net::TcpServer _tcpserver;
	net::Threadpool _tpl;
	void onConnection(const net::TcpConnectionPtr & conn);
	void onMessage(const net::TcpConnectionPtr & conn);
	void onClose(const net::TcpConnectionPtr & conn);
	void dotask(const net::TcpConnectionPtr & conn, const std::string & msg);
};
#endif
