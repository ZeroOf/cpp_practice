#include "Mydict.h"
#include <fstream>
#include <sstream>

using std::ifstream;
using std::string;
using std::vector;
using std::map;
using std::pair;
using std::set;
using std::make_pair;

Mydict * Mydict::pCreateDic = NULL;

Mydict * Mydict::createInstance()
{
	if(!pCreateDic)
		pCreateDic = new Mydict;
	return pCreateDic;
}

void Mydict::init(const char * dicEnPath,const char * dicCnPath)
{
	char buf[1024] = {'0'};
	int count = 0;
	int i = 0;
	if(dicEnPath){
		ifstream ifs(dicEnPath);
		int  j = 0;
		while(ifs>>buf,ifs>>count){
			_dict.push_back(make_pair(buf,count));		
			j = 0;
			while(buf[j]){
				_index_table[string(1,buf[j++])].insert(i);
			}
			++i;
		}
	}
	if(dicCnPath){
		ifstream ifs(dicCnPath);

		while(ifs>>buf,ifs>>count){
			_dict.push_back(make_pair(buf,count));
			string key ;
			string word(buf);
			for(std::size_t iidx = 0; iidx != word.size(); ++iidx)
			{
				char ch = word[iidx];
				if(ch & (1 << 7))
				{//存储utf-8编码的中文字符
					if((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)
					{
						key = word.substr(iidx, 2);
						++iidx;
					}
					else if((ch & 0xF0) == 0xE0)
					{
						key = word.substr(iidx, 3);
						iidx += 2;
					}
					else if((ch & 0xFF) == 0xF0 || 
							(ch & 0xFF) == 0xF1 || 
							(ch & 0xFF) == 0xF2 || 
							(ch & 0xFF) == 0xF3 || 
							(ch & 0xFF) == 0xF4 || 
							(ch & 0xFF) == 0xF5 || 
							(ch & 0xFF) == 0xF6 || 
							(ch & 0xFF) == 0xF7)
					{
						key = word.substr(iidx, 4);
						iidx += 3;
					}
					else if((ch & 0xFF) == 0xF8 ||
							(ch & 0xFF) == 0xF9 || 
							(ch & 0xFF) == 0xFA || 
							(ch & 0xFF) == 0xFB) 
					{
						key = word.substr(iidx, 5);
						iidx += 4;
					}
					else if((ch & 0xFF) == 0xFC)
					{
						key = word.substr(iidx, 6);
						iidx += 5;
					}
				}
				else
				{
					key = word.substr(iidx, 1);
				}
				_index_table[key].insert(i);
			}
			++i;
		}
	}
}

vector<pair<string,int>> & Mydict::getDict()
{
	return _dict;
}

map<string,set<int>> & Mydict::getIndexTable()
{
	return _index_table;
}
