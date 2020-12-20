#include "Cache.h"
#include <iostream>
#include <fstream>

using namespace::std;

void Cache::addElement(const string & key, const string & value)
{
	_hashMap[key] = value;
}

string Cache::query(const string & word)
{
	auto result = _hashMap.find(word);
	if(result != _hashMap.end())
	{
		return result->second;
	}
	else
	{
		return string();
	}
}

void Cache::readFromFile(const string & filename)
{
	ifstream ifs(filename.c_str());
	if(!ifs.good())
	{
		cout << "open cache file error!" << endl;
		return ;
	}

	char buf[1024] = {0};
	string key, value;
	while(ifs >> key)
	{
		ifs.getline(buf, sizeof(buf));
		value = buf;
		_hashMap.insert(std::make_pair(key, value));
	}
}

void Cache::writeToFile(const string &filename)
{
	ofstream ofs(filename.c_str());
	if(!ofs.good())
	{
		cout << "ofstream::write cache file error!" << endl;
	}
	auto iter = _hashMap.begin();
	for(;iter != _hashMap.end(); ++iter)
	{
	ofs << iter->first << "\t" << iter->second << endl;
	}
	ofs.close();
}

void Cache::update(const Cache & rhs)
{
	auto iter = rhs._hashMap.begin();
	for(; iter!= rhs._hashMap.end(); ++iter)
	{
		_hashMap.insert(*iter);
	}
}

void Cache::debug()
{
	cout << "Cache begin:" << endl;
	for(auto & elem: _hashMap)
	{
		cout << elem.first << "\t" << elem.second << endl;
	}
	cout << "Cache end " << endl;
}

