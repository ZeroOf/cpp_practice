
#include "CacheManager.h"
#include "CfgProxy.h"
#include <iostream>

using std::cout;
using std::endl;

vector<Cache> CacheManager::_cacheList;

void CacheManager::initCache(size_t sz, const string & filename)
{
	Cache cache;
	cache.readFromFile(filename);
	for(size_t idx = 0; idx <= sz; ++idx)
	{
		_cacheList.push_back(cache);
	}
}

Cache & CacheManager::getCache(const int idx)
{
	return _cacheList[idx];
}

void CacheManager::periodicUpdateCaches()
{
	cout << "> Starting update Caches!" << endl;
	auto base = _cacheList.begin();
	auto current = base + 1;
	for(;current != _cacheList.end(); ++current)
	{
		base->update(*current);
	}

	current = base + 1;
	for(; current != _cacheList.end(); ++current)
	{
		current->update(*base);
	}
	base->writeToFile(CfgProxy::instance().getConfig(cachefile));
}

