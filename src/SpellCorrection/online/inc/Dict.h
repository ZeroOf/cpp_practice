
#ifndef __DICT_H__
#define __DICT_H__

#include <map>
#include <vector>
#include <set>
#include <string>

class Dict
{
public:
	static Dict & instance();
	void init(const char * dictEnPath, const char * dicCnPath);
	std::vector<std::pair<std::string, int>> &getDict();
	std::map<std::string, std::set<int>> & getIndexTable();
private:
	std::vector<std::pair<std::string, int>> _dict;
	std::map<std::string, std::set<int>> _index_table;
};

#endif

