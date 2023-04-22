#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

#include "Configuration.h"
#include "SplitTool.h"

#include <string>
#include <vector>
#include <map>

class WebPage
{
const static int TOPK_NUMBER = 20;

friend bool operator==(const WebPage & lhs, const WebPage & rhs);
friend bool operator<(const WebPage & lhs, const WebPage & rhs);

public:
	WebPage(std::string & doc, Configuration & config, SplitTool & jieba);
	int getDocId();
	std::string getDoc();
	std::map<std::string,int> & getWordsMap();
	void processDoc(Configuration &, SplitTool &);
	void calcTopK();
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

bool operator==(const WebPage & lhs, const WebPage & rhs);
bool operator<(const WebPage & lhs, const WebPage & rhs);

#endif
