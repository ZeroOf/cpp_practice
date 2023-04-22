#ifndef __CFGPROXY_H_
#define __CFGPROXY_H_

#include <string>
#include <map>

class CfgProxy
{
public:
	static CfgProxy & instance();
	bool initialize(std::string filename);
	const std::string getConfig(std::string);
private:
	std::map<std::string, std::string> _configMap;
};

#endif

