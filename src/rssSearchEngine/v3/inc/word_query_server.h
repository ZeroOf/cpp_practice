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
	component::TcpServer _tcpserver;
	component::Threadpool _tpl;
	void onConnection(const component::TcpConnectionPtr & conn);
	void onMessage(const component::TcpConnectionPtr & conn);
	void onClose(const component::TcpConnectionPtr & conn);
	void dotask(const component::TcpConnectionPtr & conn, const std::string & msg);
};
#endif
