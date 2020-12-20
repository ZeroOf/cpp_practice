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
	wd::TcpServer _tcpserver;
	wd::Threadpool _tpl;
	void onConnection(const wd::TcpConnectionPtr & conn);
	void onMessage(const wd::TcpConnectionPtr & conn);
	void onClose(const wd::TcpConnectionPtr & conn);
	void dotask(const wd::TcpConnectionPtr & conn,const std::string & msg);
};
#endif
