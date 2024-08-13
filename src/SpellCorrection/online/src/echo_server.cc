#include "CacheManager.h"
#include "TimerThread.h"
#include "TcpServer.h"
#include "Task.h"
#include "Threadpool.h"
#include "CfgProxy.h"
#include "Dict.h"
#include <string.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <queue>
#include <functional>

using std::priority_queue;
using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::set;
using std::priority_queue;
using std::stoi;

wiz::Threadpool * _pthreadpool = NULL;
class EchoServer
{
public:
	EchoServer()
	:_threadpool(stoi(CfgProxy::instance().getConfig("threadNum")),stoi(CfgProxy::instance().getConfig("queSize")))
	,_server(stoi(CfgProxy::instance().getConfig("port")))
	,_timerthread(std::bind(&CacheManager::periodicUpdateCaches), stoi(CfgProxy::instance().getConfig("init_time")), stoi(CfgProxy::instance().getConfig("update_time")))
	{
		CacheManager::initCache(stoi(CfgProxy::instance().getConfig("threadNum")),CfgProxy::instance().getConfig("mycache"));
	}

	void start()
	{
		Dict::instance().init(CfgProxy::instance().getConfig("myindex").c_str(), CfgProxy::instance().getConfig("cnindex").c_str());
		_pthreadpool = &_threadpool;
      _threadpool.Start();
      _timerthread.Start();

		_server.setConnectionCallback(&onConnection);
		_server.setMessageCallback(&onMessage);
		_server.setCloseCallback(&onClose);

      _server.Start();

	}
private:
	wiz::Threadpool _threadpool;
	wiz::TcpServer _server;
	TimerThread _timerthread;
};

void onConnection(const wiz::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
	conn->send("hello, welcome to Chat Server. \n");
}

void onMessage(const wiz::TcpConnectionPtr &conn)
{
	string s(conn->receive());
	Task task(s, conn);
  _pthreadpool->AddTask(std::bind(&Task::process, task));
	cout << ">add task to threadpool " << endl;
}

void onClose(const wiz::TcpConnectionPtr &conn)
{
	cout << conn->toString() << " close" << endl;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		cout << "filepath please!" << endl;
		exit(-1);
	}
	CfgProxy::instance().initialize(argv[1]);
	EchoServer Echo;
	Echo.start();
	return 0;
}
