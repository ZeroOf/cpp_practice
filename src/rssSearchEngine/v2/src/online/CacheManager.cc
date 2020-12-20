#include "CacheManager.h"
#include "Configuration.h"
#include <iostream>

using std::cout;
using std::endl;

vector<Cache> CacheManager::_cacheList;

void CacheManager::initCache(size_t sz, const string & filename)
{
	Cache cache;
	cache.readFromFile(filename);
	for(size_t idx = 0; idx <= sz; ++idx)
		_cacheList.push_back(cache);
}

Cache & CacheManager::getCache(const int idx)
{
	return _cacheList[idx];
}

void CacheManager::periodicUpdateCaches()
{
	cout << "> Starting update Caches!" << endl;
	auto it1 = _cacheList.begin();
	auto it2 = ++it1;
	for(;it2 != _cacheList.end();++it2){
		it1->update(*it2);
	}

	it1 = _cacheList.begin();
	it2 = ++it1;
	for(;it2 != _cacheList.end();++it2){
		it2->update(*it1);
	}
	it1 ->writeToFile(Configuration::getConf()->getConfigMap()["mycache"]);
}
