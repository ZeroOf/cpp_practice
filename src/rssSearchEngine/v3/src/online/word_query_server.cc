#include "WordQueryServer.h"
#include <stdlib.h>
#include <stdio.h>
#include <functional>
#include <iostream>

using std::cout;
using std::endl;
using std::bind;

WordQueryServer::WordQueryServer(Configuration & conf)
: _conf(conf)
, _wqo(_conf)
, _tcpserver(atoi(_conf.getConfigMap()["Port"].c_str()))
, _tpl(4,10)
{
	_tcpserver.setConnectionCallback(bind(&WordQueryServer::onConnection,this,std::placeholders::_1));
	_tcpserver.setMessageCallback(bind(&WordQueryServer::onMessage,this,std::placeholders::_1));
	_tcpserver.setCloseCallback(bind(&WordQueryServer::onClose,this,std::placeholders::_1));
}

void WordQueryServer::start()
{
  _tpl.Start();
  _tcpserver.Start();
}

void WordQueryServer::onConnection(const wd::TcpConnectionPtr & conn)
{
	printf("%s\n",conn->toString().c_str());
}

void WordQueryServer::onMessage(const wd::TcpConnectionPtr & conn)
{
	string s = conn->receive();
	string data;
	int pos = s.find('\n');
	if(pos >= 0)
		data = s.substr(0,pos);
	else
		data = s;
  _tpl.AddTask(bind(&WordQueryServer::dotask, this, conn, data));
	cout << "test -------" << endl;
}

void WordQueryServer::onClose(const wd::TcpConnectionPtr & conn)
{
	printf("%s close.\n",conn->toString().c_str());
}

void WordQueryServer::dotask(const wd::TcpConnectionPtr & conn, const string & data)
{
	string result = _wqo.doQuery(data);
	cout << "test -------------2" <<endl;
	cout << result << endl;
	conn -> sendInLoop(result);
}
