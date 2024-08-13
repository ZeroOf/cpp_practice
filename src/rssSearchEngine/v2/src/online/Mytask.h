#ifndef __MYTASK_H__
#define __MYTASK_H__
#include "TcpServer.h"
#include "Threadpool.h"
#include "Configuration.h"
#include "DictProductor.h"
#include "Mydict.h"
#include "Cache.h"
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

inline int  min_of_three(int a,int b, int c)
{
	return c < (a < b ? a : b ) ? c : ( a< b? a: b);
}

struct MyResult
{
    std::string  candidate_word;
    int frequency;
    int distance;
};

struct Compare
{
	bool operator()(MyResult &lhs ,MyResult &rhs)
	{
		bool ret = false;
		if(lhs.distance > rhs.distance)	ret = true;
		else if(lhs.distance == rhs.distance && lhs.frequency < rhs.frequency) ret = true;
		return ret;
	}
};

class Task
{
public:
	Task(const string & query, const component::TcpConnectionPtr & conn);
	
	int calcDistance(std::string & rhs);
	//process的执行是在一个计算线程里面完成的
	void process();
private:
	string _query;
	component::TcpConnectionPtr _conn;
	priority_queue<MyResult,vector<MyResult>,Compare> _que;
};


void onConnection(const component::TcpConnectionPtr &conn);
void onMessage(const component::TcpConnectionPtr &conn);
void onClose(const component::TcpConnectionPtr &conn);
#endif
