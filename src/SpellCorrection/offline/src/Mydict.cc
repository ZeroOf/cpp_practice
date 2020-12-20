#include "Mydict.h"
#include <fstream>
#include <sstream>

using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::string;
using std::ofstream;
using std::endl;


Mydict::Mydict(	std::unordered_map<std::string,int> & cndict,	std::unordered_map<std::string,int> & endict)
: _cndict(cndict)
, _endict(endict)
{}

void Mydict::getIndexTable()
{
	int i = 0;
	for(auto words : _endict)
	{
		int j = 0;
		string word = words.first;
		while(word[j])
		{
			_index_table[string(1,word[j++])].insert(i);
		}
		++i;
	}

	for(auto words : _cndict)
	{
		string key;
		string word = words.first;
		for(std::size_t idx = 0; idx  != word.size(); ++idx)
		{
			char ch = word[idx];
			if(ch & (1 << 7))
			{
				if((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)
				{
					key = word.substr(idx,2);
					++idx;
				}
				else if((ch & 0xF0) == 0xE0)
				{
					key = word.substr(idx,3);
					idx += 2;
				}else if((ch & 0xFF) == 0xF0 ||
						 (ch & 0xFF) == 0xF1 ||
						 (ch & 0xFF) == 0xF2 ||
						 (ch & 0xFF) == 0xF3 ||
						 (ch & 0xFF) == 0xF4 ||
						 (ch & 0xFF) == 0xF5 ||
						 (ch & 0xFF) == 0xF6 ||
						 (ch & 0xFF) == 0xF7)
				{
					key = word.substr(idx,4);
					idx += 3;
				}
				else if((ch & 0xFF) == 0xF8 ||
						(ch & 0xFF) == 0xF0 ||
						(ch & 0xFF) == 0xFA ||
						(ch & 0xFF) == 0xFB) 
				{
					key = word.substr(idx,5);
					idx += 4;
				}
				else if((ch & 0xFF) == 0xFC)
				{
					key = word.substr(idx,6);
					idx += 5;
				}
			}
			else
			{
				key = word.substr(idx,1);
			}
			_index_table[key].insert(i);
		}
		++i;
	}
}

void Mydict::saveIndex(string & filename)
{
	ofstream ofs(filename);
	for(auto index : _index_table)
	{
		ofs << index.first << "\t";
		for(auto vector_index : index.second)
		{
			ofs << vector_index << "\t";
		}
		ofs << endl;
	}
	ofs.close();
}
