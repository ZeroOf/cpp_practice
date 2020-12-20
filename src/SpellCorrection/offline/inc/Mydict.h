#ifndef __MYDICT_H__
#define __MYDICT_H__ 

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Mydict
{
public:
	Mydict(std::unordered_map<std::string,int> & cndict,std::unordered_map<std::string,int> & endict);
	void getIndexTable();
	void saveIndex(std::string & filename);
private:
	std::unordered_map<std::string,int> & _cndict;
	std::unordered_map<std::string,int> & _endict;
	std::unordered_map<std::string, std::unordered_set<int> > _index_table;
};
#endif
