#ifndef __OLWEBPAGE_H__
#define __OLWEBPAGE_H__

#include "Configuration.h"
#include "SplitTool.h"

#include <string>
#include <vector>
#include <map>

class OLWebPage
{
const static int TOPK_NUMBER = 20;

friend bool operator==(const OLWebPage & lhs, const OLWebPage & rhs);
friend bool operator<(const OLWebPage & lhs, const OLWebPage & rhs);

public:
	OLWebPage(){}
	OLWebPage(std::string & doc, Configuration & config, SplitTool & jieba);
	int getDocId();
	std::string getDoc();
	std::string getDocUrl();
	std::string getDocTitle();
	std::map<std::string,int> & getWordsMap();
	void processDoc(Configuration &, SplitTool &);
	void calcTopK();
	std::string summary(const std::vector<std::string> & queryword);
private:
	std::string _doc;
	int _docId;
	std::string _docTitle;
	std::string _docUrl;
	std::string _docContent;
	std::string _docSummary;
	std::vector<std::string> _topWords;
	std::map<std::string,int> _wordsMap;
};

bool operator==(const OLWebPage & lhs, const OLWebPage & rhs);
bool operator<(const OLWebPage & lhs, const OLWebPage & rhs);

#endif
