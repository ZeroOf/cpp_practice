#ifndef __CACHE_H__
#define __CACHE_H__

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Cache
{
public:
	void readFromFile(const std::string & filename);
	void writeToFile(const std::string & filename);
	void update(const Cache &rhs);
	void addElement(const std::string & key, const std::string & value);
	void debug();
	std::string query(const std::string & word);
private:
	std::unordered_map<std::string, std::string> _hashMap;
};

#endif
