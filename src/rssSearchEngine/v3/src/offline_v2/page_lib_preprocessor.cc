#include "PageLibPreprocessor.h"

#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::string;
using std::unordered_map;
using std::map;
using std::pair;

PageLibPreprocessor::PageLibPreprocessor(Configuration & conf)
: _conf(conf)
{}

void PageLibPreprocessor::doProcess()
{
	readInfoFromFile();
	cout << "read" << endl;
	cutRedundantPages();
	cout << "cut" << endl;
	buildInvertIndexTable();
	cout << "build" << endl;
	storeOnDisk();
	cout << "store" << endl;
}

void PageLibPreprocessor::readInfoFromFile()
{
	ifstream ifs(_conf.getConfigMap()["ripepage"]);
	if(!ifs){
		cout << "ripepage open error!" << endl; 
		exit(-1);
	}
	stringstream ss;
	ss << ifs.rdbuf();
	if(!ss){
		cout << "read to ss error!" << endl;
		exit(-1);
	}
	string  alldoc(ss.str());
	cout << alldoc.size() << endl;
	ss.str("");
	ss.clear();
	ifs.close();
	ifs.open(_conf.getConfigMap()["offset"]);
	if(!ifs){
		cout << " offset open error!" << endl; 
		exit(-1);
	}

	ss << ifs.rdbuf();
	if(!ss){
		cout << "read to ss error!" << endl;
		exit(-1);
	}
	int docid,begin,end;
	while(ss >> docid)
	{
		ss >> begin;
		ss >> end;
		string doc = alldoc.substr(begin,end-begin);
		_pageLib.push_back(WebPage(doc,_conf,_jieba));
	}
	cout << _pageLib.size() << endl;
}

void PageLibPreprocessor::cutRedundantPages()
{
	for(int i = 0; i<_pageLib.size(); i++)
	{
		for(int j = i + 1; j< _pageLib.size(); j++)
		{
			if(_pageLib[i] == _pageLib[j])
			{
				cout << "==" << endl;
				_pageLib.erase(_pageLib.begin()+j);
				--j;
			}
		}
	}
	cout << _pageLib.size() << endl;
}

void PageLibPreprocessor::buildInvertIndexTable()
{
	int N = _pageLib.size();
	unordered_map<string,int> DF;
	unordered_map<string,double> IDF;
	//计算DF
	for(auto webpage: _pageLib)
	{
		for(auto word: webpage.getWordsMap())
		{
			++DF[word.first];	
		}
	}

	//计算IDF逆文档频率
	double lg2 = log(2);
	for(auto df : DF)
	{
		IDF[df.first] = log(N*1.0/(df.second+1))/lg2;
	}

	//生成倒排索引
	for(auto webpage = _pageLib.begin();webpage!= _pageLib.end();webpage++)
	{
		//计算权重
		int docid = webpage - _pageLib.begin();
		unordered_map<string,double> w;
		for(auto word: webpage->getWordsMap())
		{
			w[word.first] = word.second*IDF[word.first];
		}

		//计算权系参数
		double rhs;
		for(auto i : w)
		{
			rhs += i.second * i.second;
		}
		rhs = sqrt(rhs);
		
		for(auto word: webpage ->getWordsMap())
		{
			_invertIndexTable[word.first].push_back({docid,w[word.first]/rhs});
		}
	}
}

void PageLibPreprocessor::storeOnDisk()
{
	//save new ripepage and new offset;
	ofstream ofset(_conf.getConfigMap()["newoffset"]);
	if(!ofset){
		cout << "newoffset open error" << endl;
		exit(-1);
	}
	ofstream ofs(_conf.getConfigMap()["newripepage"]);
	if(!ofs){
		cout << "newripepage open error" << endl;
		exit(-1);
	}
	int docnum = 0;
	size_t docbegin = 0;
	size_t doclength = 0;
	for(auto web: _pageLib)
	{
		ofs << web.getDoc() << endl;
		doclength = web.getDoc().size();
		ofset << docnum ++ << "\t" <<  docbegin << "\t" << doclength << endl;
		docbegin += (doclength + 1);
	}
	ofs.close();
	ofset.close();

	//save invertIndex
	ofs.open(_conf.getConfigMap()["invertIndex"]);
	if(!ofs){
		cout << "invertIndex open error" << endl;
		exit(-1);
	}
	for(auto invidx: _invertIndexTable)
	{
		ofs << invidx.first << "\t" ;
		for(auto idx : invidx.second)
		{
			ofs << idx.first << "\t" << idx.second << "\t";
		}
		ofs << endl;
	}
	ofs.close();
}
