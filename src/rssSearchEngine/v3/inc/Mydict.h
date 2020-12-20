#ifndef __MYDICT_H__
#define __MYDICT_H__
#include <vector>
#include <string>
#include <map>
#include <set>

class Mydict
{
public:
	static Mydict * createInstance();
	void init(const char * dicEnPath,const char * dicCnPath);
	std::vector<std::pair<std::string,int>> & getDict();
	std::map<std::string,std::set<int>> & getIndexTable();
private:
	Mydict(){};
private:
	std::vector<std::pair<std::string,int>> _dict;
	std::map<std::string,std::set<int>> _index_table;
	static Mydict * pCreateDic;
};

#endif
