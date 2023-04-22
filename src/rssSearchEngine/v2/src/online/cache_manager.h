#ifndef __CACHEMANAGER_H__
#define __CACHEMANAGER_H__

#include "Cache.h"
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class CacheManager
{
public:
	static void initCache(size_t sz, const string & filename);
	static Cache & getCache(const int idx);
	static void periodicUpdateCaches();
private:
	static vector<Cache> _cacheList;
};
#endif
