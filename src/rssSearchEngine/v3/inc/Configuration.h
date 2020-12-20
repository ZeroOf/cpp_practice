#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>
#include <map>
#include <set>

class Configuration
{
public:
	static Configuration * CreateConf(const std::string & filepath);
	static Configuration * getConf();
	std::set<std::string>  & getStopWordList();
	std::map<std::string,std::string> & getConfigMap();
private:
	static Configuration * pcreateconf;
	Configuration(const std::string &filepath);
	void addSWL(const std::string&);
private:
	std::string _filepath;
	std::map<std::string,std::string> _configMap;
	std::set<std::string> _stopWordList;
};

#endif
