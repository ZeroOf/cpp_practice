
#include "TcpServer.h"
#include "Threadpool.h"
#include <iostream>
using std::cout;
using std::endl;


class Task
{
public:
	Task(const string & query, const component::TcpConnectionPtr & conn)
	: _queury(query)
	, _conn(conn)
	{}
	
	//process的执行是在一个计算线程里面完成的
	void process()
	{
		cout << "> task is processing" << endl;
		//_conn->send(_queury);//如果直接去使用send，在计算线程里面完成了数据发送,不可取
		_conn->sendInLoop(_queury);
	}
private:
	string _queury;
	component::TcpConnectionPtr _conn;
};

component::Threadpool * g_threadpool = NULL;

void onConnection(const component::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
    conn->send("hello, welcome to Chat Server.\r\n");
}

//运行在IO线程
void onMessage(const component::TcpConnectionPtr &conn)
{
    std::string s(conn->receive());

	Task task(s, conn);
  g_threadpool->AddTask(std::bind(&Task::process, task));
	cout << "> add task to threadpool" << endl;
}

void onClose(const component::TcpConnectionPtr &conn)
{
    printf("%s close\n", conn->toString().c_str());
}

//class EchoServer
//{
//public:
//	void Start();
//	void onMessage();
//	void onConnection();
//	void onClose();
//private:
//	Threadpool _threadpool;
//	TcpServer _server;
//};

int main(int argc, char const *argv[])
{
	component::Threadpool threadpool(4, 10);
	g_threadpool = &threadpool;
  threadpool.Start();

	component::TcpServer tcpserver("192.168.137.128", 9999);
	tcpserver.setConnectionCallback(&onConnection);
	tcpserver.setMessageCallback(&onMessage);
	tcpserver.setCloseCallback(&onClose);

  tcpserver.Start();

    return 0;
}
