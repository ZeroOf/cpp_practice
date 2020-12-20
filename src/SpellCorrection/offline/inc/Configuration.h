#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>
#include <unordered_map>

class Configuration
{
public:
	Configuration(const std::string & filepath);
	std::unordered_map<std::string,std::string> & getConfigMap();
private:
	std::string _filepath;
	std::unordered_map<std::string, std::string> _configMap; 
};

#endif
