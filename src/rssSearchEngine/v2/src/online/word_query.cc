#include "WordQuery.h"
#include "Configuration.h"
#include "OLWebPage.h"
#include <math.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <json/json.h>

using std::stable_sort;
using std::ifstream;
using std::istringstream;
using std::make_pair;
using std::vector;
using std::map;
using std::string;
using std::pair;
using std::cout;
using std::endl;
using std::getline;

struct SimilarityCompare
{
	SimilarityCompare(vector<double> & base)
	:_base(base){}

	bool operator()(const pair<int,vector<double> > & lhs,const pair<int,vector<double> > &rhs)
	{
		return rhs.first > lhs.first;
	}
	vector<double> _base;
};

wordQuery::wordQuery(Configuration & conf)
	:_conf(conf)
{
	loadLibrary();
}

void wordQuery::loadLibrary()
{
	ifstream ifspl(_conf.getConfigMap()["newripepage"]);
	ifstream ifsol(_conf.getConfigMap()["newoffset"]);
	if(!ifspl.good() || !ifsol.good())
	{
		cout << "data lib get fail, quiting..." << endl;
	}
	int docid, offset, len;
	string line;
	while(getline(ifsol,line))
	{
		istringstream iss(line);
		iss >> docid >> offset >> len;

		string doc;
		doc.resize(len,' ');
		ifspl.seekg(offset,ifspl.beg);
		ifspl.read(&*doc.begin(),len);

		OLWebPage owp(doc,_conf,_jieba);
		_offsetlib.insert(make_pair(docid,make_pair(offset,len)));
		_pagelib.insert(make_pair(docid,owp));
	}
	ifstream ifsiit(_conf.getConfigMap()["invertIndex"]);
	if(!ifsiit.good())
	{
		cout << "index table get fail, quiting..." << endl;
	}
	string word;
	double weight;
	while(getline(ifsiit,line))
	{
		istringstream iss(line);
		iss >> word;
		set<pair<int,double> > setID;
		while(iss >> docid >> weight)
		{
			setID.insert(make_pair(docid,weight));
		}
		_invertIndexTable.insert(make_pair(word,setID));
	}
	ifsol.close();
	ifsiit.close();
	ifspl.close();
	cout << "loadLibrary() end" <<endl;
}

string wordQuery::doQuery(const string & strin)
{
	vector<string> queryword;
	if(strin.size() > 0)
	{
		queryword = _jieba.cut(strin);
	}
	for(auto & item:queryword)
	{
		cout << item << " ";
		auto result = _invertIndexTable.find(item);
		cout << _invertIndexTable[item].size();
		if(result == _invertIndexTable.end()){
			cout << "no result " << item << endl;
			return returnNoAnswer();
		}
	}
	cout << endl;
	vector<double> weightlist = getQueryWordsWeightVector(queryword);
	SimilarityCompare simcmp(weightlist);
	vector<pair<int,vector<double> > > resultVec;
	if(executeQuery(queryword,resultVec))
	{
		stable_sort(resultVec.begin(),resultVec.end(),simcmp);
		vector<int> docIdVec;
		for(auto & item: resultVec)
		{
			docIdVec.push_back(item.first);
		}
		return createJson(docIdVec,queryword);
	}
	return returnNoAnswer();
}

vector<double> wordQuery::getQueryWordsWeightVector(vector<string> & queryword)
{
	map<string,int> wordFreqmap;
	for(auto & item : queryword)
	{
		++wordFreqmap[item];
	}
	vector<double> weightlist;
	double weightsum = 0;
	int total = _offsetlib.size();
	for(auto & item: queryword)
	{
		int df = _invertIndexTable[item].size();
		double idf = (log(total) - log(df+1))/log(2);
		double weightitem = idf * wordFreqmap[item];
		weightlist.push_back(weightitem);
		weightsum += pow(weightitem,2);
	}
	for(auto & item : weightlist)
	{
		item /= weightsum;
		cout << "weightlist elem: " <<item << "\t";
	}
	return weightlist;
}

bool wordQuery::executeQuery(const vector<string> & queryword, vector<pair<int,vector<double>>> & resultVec)
{
	if(queryword.size()<=0)
		return 0;
	int minVec = 1 << 20;
	typedef set<pair<int,double>>::iterator setIt;
	vector<pair<setIt,int>> itVec;
	for(auto & item: queryword)
	{
		int crosssize = _invertIndexTable[item].size();
		if(crosssize<minVec){
			minVec = crosssize;
		}
		itVec.push_back(make_pair(_invertIndexTable[item].begin(),0));
		cout << "item" << _invertIndexTable[item].size() << endl;
	}
	cout << "minsize " << minVec << endl;
	if(minVec == 0)
		return 0;
	bool isExit = 0;
	while(!isExit)
	{
		size_t idx = 0;
		for(;idx != itVec.size()-1;++idx)
		{
			if(itVec[idx].first->first != itVec[idx+1].first->first)
				break;
		}
		if(idx == itVec.size()-1){
			vector<double> weightVec;
			int docid = itVec[0].first->first;
			for(idx = 0;idx != itVec.size();++idx)
			{
				weightVec.push_back(itVec[idx].first->second);
				++(itVec[idx].first);
				++(itVec[idx].second);
				if(itVec[idx].second == minVec)
					isExit = true;
			}
			resultVec.push_back(make_pair(docid,weightVec));
		}else{
			int itdx = 0;
			int minDocid = 1 << 20;
			for(idx = 0; idx != itVec.size(); ++idx)
			{
				if(itVec[idx].first->first < minDocid){
					minDocid = itVec[idx].first->first;
					itdx = idx;
				}
			}
			++(itVec[itdx].first);
			++(itVec[itdx].second);
			if(itVec[itdx].second == minVec){
				isExit = 1;
			}
		}
	}
	if(resultVec.size() > 0)
		return true;
	return 0;
}

string wordQuery::createJson(vector<int> & docIdVec,const vector<string> & queryword)
{
	Json::Value root;
	Json::Value arr;
	Json::Value elem;
	int cnt = 0;
	for(auto & id : docIdVec)
	{
		string summary = _pagelib[id].summary(queryword);
		string title = _pagelib[id].getDocTitle();
		string url = _pagelib[id].getDocUrl();

		elem["title"] = title;
		elem["summary"] = summary;
		elem["url"] = url;
		arr.append(elem);
		if(++cnt == 100)
			break;
	}

	root["files"] = arr;
	Json::StyledWriter writer;
	return writer.write(root);
}

string wordQuery::returnNoAnswer()
{
	Json::Value root;
	Json::Value arr;
	Json::Value elem;
	elem["title"] = "GG";
	elem["summary"] = "404 NOT FOUND";
	elem["url"] = "";
	arr.append(elem);
	root["file"] = arr;
	Json::StyledWriter writer;
	return writer.write(root);
}
