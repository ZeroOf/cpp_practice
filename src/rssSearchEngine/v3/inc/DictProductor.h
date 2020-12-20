#ifndef __DECTPRODUCTOR_H__
#define __DECTPRODUCTOR_H__

#include <string>
#include <vector>
#include <map>

class DictProductor
{
public:
	DictProductor(const std::string &);
	void build_dict();
	void store_dict();
private:
	std::string _dir;
	std::vector<std::string> _files;
	std::map<std::string,int> _dict;
};

#endif
