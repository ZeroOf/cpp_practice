#ifndef __DIRSCANNER_H__
#define __DIRSCANNER_H__
#include "Configuration.h"
#include <vector>
#include <string>

class DirScanner
{
public:
	DirScanner(Configuration& conf);
	void operator()();
	std::vector<std::string>  files();
	void traverse(const std::string &dirname);
private:
	std::vector<std::string> _vecFilesDir;
	Configuration & _conf;
};

#endif
