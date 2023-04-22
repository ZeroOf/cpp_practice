#ifndef __WORDQUERY_H__
#define __WORDQUERY_H__

#include "OLWebPage.h"
#include "Configuration.h"
#include "SplitTool.h"
#include <vector>
#include <set>
#include <map>

using std::unordered_map;
using std::pair;
using std::set;

class wordQuery
{
public:
	wordQuery(Configuration & conf);
	std::string doQuery(const std::string & str);

private:
	Configuration & _conf;
	SplitTool _jieba;
	unordered_map<int,OLWebPage> _pagelib;
	unordered_map<int,pair<int,int> > _offsetlib;
	unordered_map<std::string,set<pair<int,double> > > _invertIndexTable;

private:
	void loadLibrary();
	std::vector<double> getQueryWordsWeightVector(std::vector<std::string > &);
	bool executeQuery(const std::vector<std::string> &,
			std::vector<pair<int,std::vector<double>>>&);
	std::string createJson(std::vector<int> &, const std::vector<std::string> &);
	std::string returnNoAnswer();
};
#endif
