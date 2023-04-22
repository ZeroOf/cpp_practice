#include "DictProductor.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::cout;
using std::endl;

void LineHandle(char *s)
{
	int i = 0;
	while(s[i]){
		if(isalpha(s[i]))	++i;
		else if(s[i]=='\'' && isalpha(s[i-1]) && (s[i+1] && isalpha(s[i+1]))) ++i;
		else s[i++] =' ';
	}
}

DictProductor::DictProductor(const string &dir)
: _dir(dir){}

void DictProductor::build_dict()
{
	ifstream ifs(_dir);
	if(!ifs){
		cout << "DictProductor ifs open error" << endl;
		exit(-1);
	}
	stringstream ss;
	char tmp[4096];
	string buf;
	while(ifs.getline(tmp,sizeof(tmp))){
		LineHandle(tmp);
		ss << tmp;
		while(ss>>buf){
			++_dict[buf];
		}
		ss.clear();
	}
	ifs.close();
}

void DictProductor::store_dict()
{
	ofstream ofs("../../data/index.dat");
	for(auto & i: _dict){
		ofs << i.first << "\t" << i.second << endl;
	}
	ofs.close();
}
