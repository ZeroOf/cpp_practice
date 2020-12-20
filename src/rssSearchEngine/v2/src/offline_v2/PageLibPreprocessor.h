#ifndef __PAGELIBPREPROCESSOR_H__
#define __PAGELIBPREPROCESSOR_H__

#include "Configuration.h"
#include "WebPage.h"
#include <unordered_map>
#include <string>
#include <vector>


class PageLibPreprocessor
{
public:
	PageLibPreprocessor(Configuration& conf);
	void doProcess();
private:
	Configuration & _conf;
	SplitTool _jieba;
	std::vector<WebPage> _pageLib;
	std::unordered_map<int, std::pair<int,int> > _offsetLib;
	std::unordered_map<std::string, std::vector<std::pair<int, double> > > _invertIndexTable;
private:
	void readInfoFromFile();
	void cutRedundantPages();
	void buildInvertIndexTable();
	void storeOnDisk();
};

#endif
