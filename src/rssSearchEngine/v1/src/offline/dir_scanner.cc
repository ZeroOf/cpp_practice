#include "DirScanner.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;


DirScanner::DirScanner(Configuration & conf)
: _conf(conf)
{}

void DirScanner::operator()()
{
	traverse(_conf.getConfigMap()["rssFileDir"]);
}

vector<string> DirScanner::files()
{
	return _vecFilesDir;
}

void DirScanner::traverse(const string &dirname)
{
	DIR *dir;
	struct dirent * ptr;
	if((dir = opendir(dirname.c_str()))==NULL){
		perror("open rss dir error!");			
		exit(-1);
	}
	
	while((ptr = readdir(dir)) != NULL)
	{
		if((strcmp(ptr->d_name,".") && strcmp(ptr->d_name,"..")) ==0)	
				continue;
		else {
			_vecFilesDir.push_back(dirname+"/"+ptr->d_name);
		}
	}
}
