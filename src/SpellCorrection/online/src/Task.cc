#include "Task.h"
#include "Thread.h"
#include "CacheManager.h"
#include "Cache.h"

size_t nByteCode(const char ch)
{
	if(ch & (1 << 7))
	{
		int nBytes = 1;
		for(int idx = 0; idx != 6; ++idx)
		{
			if(ch & (1 << (6-idx)))
			{
				++nBytes;
			}
			else 
			{
				break;
			}
		}
		return nBytes;
	}
	return 1;
}

size_t length(const string & str)
{
	size_t len = 0;
	for(size_t idx = 0; idx!= str.size(); ++idx)
	{
		int nBytes = nByteCode(str[idx]);
		idx += nBytes -1;
		++len;
	}
	return len;
}

Task::Task(const string &query, const wiz::TcpConnectionPtr &conn)
: _query(query)
, _conn(conn)
{}

int Task::CalcDistance(std::string &rhs)
{
	size_t llen = length(_query);
	size_t rlen = length(rhs);
	int editDist[llen+1][rlen+1];
	for(size_t idx = 0; idx < llen; ++idx)
	{
		editDist[idx][0] = idx;
	}
	for(size_t idx = 0; idx < rlen; ++idx)
	{
		editDist[0][idx] = idx;
	}

	string lsub, rsub;
	for(size_t dist_i = 1, lidx = 0; dist_i <= llen; ++dist_i, ++lidx)
	{
		size_t nBytes = nByteCode(rhs[lidx]);
		lsub = _query.substr(lidx, nBytes);
		lidx += (nBytes - 1);
		for(size_t dist_j = 1, ridx = 0; dist_j <= rlen; ++dist_j, ++ridx)
		{
			nBytes = nByteCode(rhs[ridx]);
			rsub = rhs.substr(ridx, nBytes);
			ridx += (nBytes - 1);
			if(lsub == rsub)
			{
				editDist[dist_i][dist_j] = editDist[dist_i-1][dist_j-1];
			}
			else
			{
				editDist[dist_i][dist_j] = min_of_three(
						editDist[dist_i-1][dist_j] +1,
						editDist[dist_i][dist_j-1] +1,
						editDist[dist_i-1][dist_j-1] +1);
			}
		}
	}
	return editDist[llen][rlen];
}

void Task::process()
{
	cout << "> task is processing" << endl;
	Cache & cache = CacheManager::getCache(wiz::pthname);
	auto & index = Dict::instance().getIndexTable();
	auto & dict = Dict::instance().getDict();
	size_t size = _query.size();

	string tmp("");

	tmp = cache.query(_query);
	cout << wiz::pthname << endl;
	if(tmp.size() == 0)
	{
		cout << "query index for" << endl;
		string subs;
		set<int> res;
		for(size_t i = 0; i< size; ++i)
		{
			size_t nBytes = nByteCode(_query[i]);
			subs = _query.substr(i, nBytes);
			if( i == 0)
			{
				res = index[subs];
			}
			else
			{
				set<int> temp;
				set_intersection(res.begin(),res.end(),index[subs].begin(), index[subs].end(), inserter(temp,temp.begin()));
				if(temp.size())
				{
					res = move(temp);
				}
			}
			i += nBytes -1;
		}
		for(auto & i:res)
		{
			_que.push({dict[i].first, dict[i].second, CalcDistance(dict[i].first)});
		}

		for(int i = 0; i < 10; i++)
		{
			if(_que.size() == 0)
			{
				break;
			}
			tmp = tmp + _que.top().candidate_word + "\t" ;
			_que.pop();
		}
		cache.addElement(_query, tmp);
	}
	_conn->sendInLoop(tmp);
}
