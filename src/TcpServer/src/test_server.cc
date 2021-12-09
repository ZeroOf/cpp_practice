#include "TcpServer.h"
#include "Threadpool.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Task
{
public:
	Task(const string & query, const wiz::TcpConnectionPtr & conn)
	: _query(query)
	, _conn(conn)
	{}
	void process()
	{
		cout << ">task is processing" << endl;
		_conn->sendInLoop(_query);
	}
private:
	  string  _query;
	  wiz::TcpConnectionPtr _conn;
};

wiz::Threadpool * g_threadpool = NULL;

void onConnection(const wiz::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
	conn->send("Hello, welcome to Char Server.\n");
}

void onMessege(const wiz::TcpConnectionPtr &conn)
{
	string s(conn->receive());

	Task task(s,conn);
	g_threadpool->addTask(std::bind(&Task::process, task));
	cout << "> add task to threadpool" << endl;
}

void onClose(const wiz::TcpConnectionPtr & conn)
{
	printf("%s close\n", conn->toString().c_str());
}

int main(int argc, char const * argv[])
{
	wiz::Threadpool threadpool(4,10);
	g_threadpool = & threadpool;
    threadpool.Start();

	wiz::TcpServer tcpserver("192.168.79.130",9999);
	tcpserver.setConnectionCallback(onConnection);
	tcpserver.setMessageCallback(onMessege);
	tcpserver.setCloseCallback(onClose);
    tcpserver.Start();
	return 0;
}
