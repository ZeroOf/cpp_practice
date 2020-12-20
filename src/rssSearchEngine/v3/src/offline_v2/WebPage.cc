#include "WebPage.h"
#include <set>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using std::string;
using std::vector;
using std::set;
using std::atoi;
using std::priority_queue;
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;
using std::map;
using std::set_difference;
using std::inserter;
using std::set_intersection;
using std::pair;

string getSubs(string & sor, string lhs, string rhs)
{
	return sor.substr(sor.find(lhs)+lhs.size(),sor.find(rhs)-sor.find(lhs)-lhs.size());
}

WebPage::WebPage(string &doc, Configuration & config, SplitTool &jieba)
: _doc(doc)
{
	processDoc(config,jieba);
	calcTopK();
}

void WebPage::processDoc(Configuration & config,SplitTool & jieba)
{
	_docId = atoi(getSubs(_doc,"<docid>","</docid>").c_str());
	_docTitle = getSubs(_doc,"<title>","</title>");
	_docUrl = getSubs(_doc,"<link>", "</link>");
	cout<<" utl: "<<_docUrl<<endl;
	_docContent = getSubs(_doc,"<content>","</content>");
	
	vector<string> allWords = jieba.cut(_doc);
	vector<string> cutWords ;
	set<string> & stopwords = config.getStopWordList();
	set_difference(allWords.begin(),allWords.end(),stopwords.begin(),stopwords.end(),inserter(cutWords,cutWords.begin()));
	for(auto word: cutWords)
	{
		++_wordsMap[word];
	}
}
struct compare
{
	bool operator()(pair<string,int> lhs, pair<string,int> rhs)
	{
		if(lhs.second < rhs.second)
			return true;
		else
			return false;
	}
};
void WebPage::calcTopK()
{
	priority_queue< pair< string,int> ,vector<pair<string, int> >,compare> fq;
	for(auto word:_wordsMap)
	{
		fq.push(word);
	}

	for(int i = 0; i<TOPK_NUMBER; i++)
	{
		if(!fq.size())	break;
		_topWords.push_back(fq.top().first);
		fq.pop();
	}
}

int WebPage::getDocId()
{
	return _docId;
}

string WebPage::getDoc()
{
	return _doc;
}

map<string,int> & WebPage::getWordsMap()
{
	return _wordsMap;
}

bool operator==(const WebPage & lhs,const WebPage &rhs)
{
	bool ret = false;
	vector<string> intersection;
	set_intersection(lhs._topWords.begin(),lhs._topWords.end(),rhs._topWords.begin(),rhs._topWords.end(),inserter(intersection,intersection.begin()));
	if(intersection.size()>= WebPage::TOPK_NUMBER*0.6|| intersection.size() >= lhs._topWords.size() * 0.6 || intersection.size() >= rhs._topWords.size() * 0.6){
		ret = true;
	}
	return ret;
}

bool operator<(const WebPage & lhs,const WebPage &rhs)
{
	bool ret = false;
	if(lhs._docId<rhs._docId)	ret = true;
	return ret;
}
