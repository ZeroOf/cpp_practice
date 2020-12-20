
#ifndef __TASK_H__
#define __TASK_H__

#include "TcpServer.h"
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

inline int min_of_three(int a, int b, int c)
{
	return c < (a < b ? a : b) ? c : (a < b ? a: b);
}

struct CmpRet
{
	std::string candidate_word;
	int frequency;
	int distance;
};

struct Compare
{
	bool operator()(CmpRet &lhs, CmpRet &rhs)
	{
		if(lhs.distance > rhs.distance)
		{
			return  true;
		}
		else if(lhs.distance == rhs.distance && lhs.frequency < rhs.frequency)
		{
			return true;
		}
		return false;
	}
};

class Task
{
	public:
		Task(const string &query, const wiz::TcpConnectionPtr & conn);

		int CalcDistance(std::string &rhs);

		void process();
private:
		string _query;
		wiz::TcpConnectionPtr _conn;
		priority_queue<CmpRet, vector<CmpRet>, Compare> _que;
};

void onConnection(const wiz::TcpConnectionPtr &conn);
void onMessage(const wiz::TcpConnectionPtr &conn);
void onClose(const wiz::TcpConnectionPtr &conn);
#endif
