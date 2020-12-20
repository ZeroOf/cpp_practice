
#include "Dict.h"
#include <fstream>
#include <sstream>

using std::set;
using std::map;
using std::vector;
using std::make_pair;
using std::ifstream;
using std::string;
using std::pair;

Dict & Dict::instance()
{
	static Dict _instance;
	return _instance;
}

void Dict::init(const char * dicEnPath, const char * dicCnPath)
{
	char buf[1024] = { 0 };
	int count = 0;
	int i = 0;
	if (dicEnPath)
	{
		ifstream ifs(dicEnPath);
		int j = 0;
		while (ifs >> buf, ifs >> count)
		{
			_dict.push_back(make_pair(buf, count));
			j = 0;
			while (buf[j])
			{
				_index_table[string(1, buf[j++])].insert(i);
			}
			++i;
		}
	}
	if (dicCnPath)
	{
		ifstream ifs(dicCnPath);

		while (ifs >> buf, ifs >> count)
		{
			_dict.push_back(make_pair(buf, count));
			string key;
			string word(buf);
			for (std::size_t word_idx = 0; word_idx != word.size(); ++word_idx)
			{
				char ch = word[word_idx];
				if (ch & (1 << 7))
				{
					switch (ch & 0xF0)
					{
						case 0xC0:
						case 0xD0:
							key = word.substr(word_idx, 2);
							++word_idx;
							break;
						case 0xE0:
							key = word.substr(word_idx, 3);
							word_idx += 2;
							break;
					default:
						switch (ch & 0xFF)
						{
						case 0xF8:
						case 0xF9:
						case 0xFA:
						case 0xFB:
							key = word.substr(word_idx, 5);
							word_idx += 4;
							break;
						case 0xFC:
							key = word.substr(word_idx, 6);
							word_idx += 5;
							break;
						default:
							key = word.substr(word_idx, 4);
							word_idx += 3;
							break;
						}
						break;
					}
				}
				else 
				{
					key = word.substr(word_idx, 1);
				}
				_index_table[key].insert(i);
			}
			++i;
		}
	}
}

vector<pair<string, int>> & Dict::getDict()
{
	return _dict;
}

map<string, set<int>> & Dict::getIndexTable()
{
	return _index_table;
}

