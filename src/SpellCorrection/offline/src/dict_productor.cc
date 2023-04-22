#include "DictProductor.h"

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using std::string;
using std::unordered_map;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::cout;
using std::endl;

DictProductor::DictProductor(const string & cndir,const string & endir)
: _cndir(cndir)
, _endir(endir)
{
}

vector<string> DictProductor::getfiles(const string & filedir)
{
	DIR * dir;
	struct dirent * ptr;
	if((dir = opendir(filedir.c_str())) == NULL){
		perror("open dir error!");	
		exit(-1);
	}

	vector<string> _files;
	while((ptr = readdir(dir)) != NULL)
	{
		if((strcmp(ptr->d_name,".") && strcmp(ptr->d_name,"..")) == 0)
			continue;
		else
			_files.push_back(filedir +"/" + ptr->d_name);
	}
	return _files;
}

void DictProductor::build_dict()
{
	vector<string> _files;
	_files = getfiles(_cndir);
	ifstream ifs;
	//中文存入词库
	for(string file : _files)
	{
		cout << file <<endl;
		ifs.open(file);
		stringstream ss;
		ss << ifs.rdbuf();
		string buf = ss.str();
		vector<string> temp = _cut.cut(buf);
		for(auto word : temp)
		{
			++_cndict[word];
		}
		ifs.close();
	}
	//save english words
	_files = getfiles(_endir);
	for(string file : _files)
	{
		ifs.open(file);
		stringstream ss;
		ss << ifs.rdbuf();
		string buf = ss.str();
		Linehandle(buf);
		ss.str("");
		ss << buf;
		string word;
		int i = 0;
		while(ss.good())
		{
			ss.clear();
			ss >> word;
			++_endict[word];
			++i;
		}
	}
}

void DictProductor::store_dict(const string filename)
{
	ofstream ofs(filename);
	for(auto & idx : _endict)
	{
		ofs << idx.first << "\t" << idx.second << endl;
	}
	for(auto & idx : _cndict)
	{
		ofs << idx.first << "\t" << idx.second << endl;
	}
	ofs.close();
}

void DictProductor::Linehandle(string &s)
{
	int i = 0;
	while(s[i])
	{
		if(isalpha(s[i])) ++i;
		else if(s[i] == '\'' && isalpha(s[i-1]) && isalpha(s[i+1]))	 i += 2;
		else s[i++] = ' ';
	}
}


std::unordered_map<std::string,int> & DictProductor::getEndict()
{
	return _endict;
}
std::unordered_map<std::string,int> & DictProductor::getCndict()
{
	return _cndict;
}
