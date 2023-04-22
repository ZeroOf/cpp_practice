#ifndef __SPLITTOOL_H__
#define __SPLITTOOL_H__ 

#include "Jieba.hpp"
#include <string>

class SplitTool
{
public:
	SplitTool();
	std::vector<std::string> cut(const std::string & sentence);
private:
	cppjieba::Jieba _Jieba;
};
#endif
