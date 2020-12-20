#include "Configuration.h"
#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::stringstream;
using std::map;
using std::string;
using std::cout;
using std::endl;
using std::getline;
using std::make_pair;

Configuration * Configuration::pcreateconf = NULL;

Configuration::Configuration(const string & filepath)
:_filepath(filepath)
{
	ifstream ifs(_filepath);	
	if(!ifs){
		cout << "Configuration open file error!" << endl;
		exit(-1);
	}
	char buf[1024];
	string buf1,buf2;
	stringstream ss;
	ifs.read(buf,sizeof(buf));
	ss<<buf;
	while(ss>>buf1,	ss>>buf2){
		_configMap.insert(make_pair(buf1,buf2));
	}
	auto ite = _configMap.find("stop_word_zh");
	if( ite != _configMap.end()){
		addSWL((*ite).second);	
	}
	ite = _configMap.find("stop_word_en");
	if( ite != _configMap.end()){
		addSWL((*ite).second);	
	}
}

Configuration * Configuration::CreateConf(const string & filepath)
{
	if(!pcreateconf){
		pcreateconf = new Configuration(filepath);
	}
	return pcreateconf;
}

Configuration * Configuration::getConf()
{
	return pcreateconf;
}

map<string,string> & Configuration::getConfigMap()
{
	return _configMap;
}

std::set<std::string> & Configuration::getStopWordList()
{
	return _stopWordList;
}

void Configuration::addSWL(const std::string& filepath)
{
	ifstream ifs(filepath);
	if(!ifs){
		cout << filepath << " open error!" << endl;
		return;
	}
	stringstream ss; 
	ss << ifs.rdbuf();
	string tmp;
	while(ss >> tmp)
	{
		_stopWordList.insert(tmp);
	}
}
