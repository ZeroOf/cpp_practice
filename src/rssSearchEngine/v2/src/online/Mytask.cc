#include "Mytask.h"
#include "Thread.h"
#include "CacheManager.h"
#include "Cache.h"

size_t nBytesCode(const char ch)
{
	if(ch & (1<<7)){
		int nBytes = 1;
		for(int idx = 0; idx != 6; idx++)
		{
			if(ch & ( 1 <<(6 - idx))){
				++nBytes;		
			}
			else break;
		}
		return nBytes;
	}
	return 1;
}

size_t length(const string &str)
{
	size_t  ilen = 0;
	for(size_t idx = 0; idx != str.size(); idx ++)
	{
		int nBytes = nBytesCode(str[idx]);
		idx += nBytes - 1;
		++ ilen;
	}
	return ilen;
}

Task::Task(const string & query, const net::TcpConnectionPtr & conn)
: _query(query)
, _conn(conn)
{}
int Task::calcDistance(std::string & rhs)
{
	size_t lenl = length(_query);
	size_t lenr = length(rhs);
	int editDist[lenl+1][lenr+1];
	for(size_t idx = 0; idx < lenl; ++idx)
	{
		editDist[idx][0] = idx;
	}
	for(size_t idx = 0; idx < lenr; ++idx)
	{
		editDist[0][idx] = idx;
	}
	string subl,subr;
	for(size_t dist_i = 1, lhs_idx = 0; dist_i <= lenl;++dist_i,++lhs_idx)
	{
		size_t nBytes = nBytesCode(_query[lhs_idx]);
		subl = _query.substr(lhs_idx,nBytes);
		lhs_idx += (nBytes - 1);
		for(size_t dist_j = 1, rhs_idx = 0; dist_j <= lenr; ++dist_j, ++rhs_idx)
		{
			nBytes = nBytesCode(rhs[rhs_idx]);
			subr = rhs.substr(rhs_idx,nBytes);
			rhs_idx += (nBytes - 1);
			if(subl == subr){
				editDist[dist_i][dist_j] = 	editDist[dist_i-1][dist_j-1]; 
			}
			else{
				editDist[dist_i][dist_j] = min_of_three(
					editDist[dist_i-1][dist_j] +1, 		
					editDist[dist_i][dist_j-1] +1, 
					editDist[dist_i-1][dist_j-1] +1); 
			}
		}
	}
	return editDist[lenl][lenr];
}

void Task::process()
{
	cout << "> task is processing" << endl;

	Mydict * dic = Mydict::createInstance();
	auto & testindex = dic->getIndexTable();
	cout << testindex.size() << endl;
	vector<pair<string,int>> & testdic = dic->getDict();
	cout << testdic.size() << endl;
	size_t size = _query.size();
	//get Cache
	Cache & mcache = CacheManager::getCache(net::pthname);

	string tmp;
	//query cache
	tmp = mcache.query(_query);
	cout << net::pthname << endl;
	if(!tmp.size()){
	//query index
		cout << "query index for" << endl; 
		string subs;
		set<int> res;
		for(size_t i = 0; i < size ;i++)
		{
			size_t nBytes = nBytesCode(_query[i]);
			subs = _query.substr(i,nBytes);
			if(i == 0){
				res = testindex[subs];
			}else{
				set<int> temp;
				set_intersection(res.begin(),res.end(),testindex[subs].begin(),testindex[subs].end(),inserter(temp,temp.begin()));
				if(temp.size())
					res = move(temp);
			}
			i += (nBytes - 1);
		}
		// save results
		for(auto & i : res)
		{
			_que.push( {testdic[i].first, testdic[i].second ,calcDistance(testdic[i].first)});
		}
		//send results
		for(int i=0;i<10;i++)
		{
			if(_que.size() == 0) break;
			tmp = tmp +_que.top().candidate_word + "\t";
			_que.pop();
		}
		mcache.addElement(_query,tmp);
	}
	_conn->sendInLoop(tmp);
}
