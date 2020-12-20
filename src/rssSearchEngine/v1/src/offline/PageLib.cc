#include "PageLib.h"
#include "RssReader.h"
#include <iostream>

#include <map>

using std::cout;
using std::map;
using std::string;
using std::make_pair;

PageLib::PageLib(Configuration & conf,DirScanner & dirScanner)
: _conf(conf), _dirScanner(dirScanner){
	_dirScanner();
}

void PageLib::create()
{
	RssReader rss;
	rss.parseRss(_dirScanner.files());
	rss.dump(_vecFiles);
}

void PageLib::store()
{
	size_t currentpost = 0, docid = 1;
	for(auto webfile: _vecFiles)
	{
		_offsetLib.insert(make_pair(docid++,make_pair(currentpost,currentpost+webfile.size())));
		currentpost += (webfile.size()+1);
	}

	ofstream of_off(_conf.getConfigMap()["offset"]);
	if(!of_off){
		cout << "offset open error!" << endl;
		exit(-1);
	}
	for(auto offset: _offsetLib)
	{
		of_off << offset.first << "\t" << offset.second.first << "\t" << offset.second.second << endl;
	}
	of_off.close();

	ofstream of_doc(_conf.getConfigMap()["ripepage"]);
	if(!of_doc){
		cout << "ripepage open error!" << endl;
		exit(-1);
	}
	for(auto ripe: _vecFiles)
	{
		of_doc << ripe << endl;
	}
	of_doc.close();
}
