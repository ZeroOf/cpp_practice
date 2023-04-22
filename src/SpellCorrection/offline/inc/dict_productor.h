#ifndef __DICTPRODUCTOR_H__
#define __DICTPRODUCTOR_H__

#include <string>
#include <vector>
#include <unordered_map>
#include "SplitTool.h"

class DictProductor
{
public:
	DictProductor(const std::string &,const std::string &);
	void build_dict();
	void store_dict(const std::string filename);
	std::unordered_map<std::string,int> & getEndict();
	std::unordered_map<std::string,int> & getCndict();
private:
	std::vector<std::string> getfiles(const std::string &);
	void Linehandle(std::string & s);
	std::string _cndir;
	std::string _endir;
	std::unordered_map<std::string,int> _cndict;
	std::unordered_map<std::string,int> _endict;
	SplitTool _cut;
};
#endif
