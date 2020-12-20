#ifndef __PAGELIB_H__
#define __PAGELIB_H__
#include "Configuration.h"
#include "DirScanner.h"
#include <string>
#include <vector>
#include <map>

class PageLib
{
public:
	PageLib(Configuration & conf,DirScanner & dirScanner);
	void create();
	void store();
private:
	Configuration & _conf;
	DirScanner & _dirScanner;
	std::vector<std::string> _vecFiles;
	std::map<int, std::pair<int,int>> _offsetLib;
};

#endif
