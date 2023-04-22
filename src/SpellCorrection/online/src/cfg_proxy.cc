
#include "CfgProxy.h"
#include <fstream>
#include <iostream>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

CfgProxy &CfgProxy::instance()
{
	static CfgProxy _instance;
	return _instance;
}

bool CfgProxy::initialize(string filename)
{
	ifstream ifs_cfg(filename);
	if(!ifs_cfg)
	{
		cout << "config file open failed!" << endl;
		return false;
	}
	string key, value;
	while((ifs_cfg >> key) && (ifs_cfg >> value))
	{
		_configMap[key] = value;
		cout << key << "->" << value << endl;
	}
	ifs_cfg.close();
	return true;
}

const string CfgProxy::getConfig(std::string key)
{
	string ret;
	auto search = _configMap.find(key);
	if(search != _configMap.end())
	{
		ret = search->second;
	}
	return ret;
}

