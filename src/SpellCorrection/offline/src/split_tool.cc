#include "SplitTool.h"
#include <vector>

using std::vector;
using std::string;

const char * const DICT_PATH = "/home/god/Documents/c++/SpellCorrection/SpellCorrection/data/jieba.dict.utf8";
const char * const HMM_PATH = "/home/god/Documents/c++/SpellCorrection/SpellCorrection/data/hmm_model.utf8";
const char* const USER_DICT_PATH = "/home/god/Documents/c++/SpellCorrection/SpellCorrection/data/user.dict.utf8";
const char* const IDF_PATH = "/home/god/Documents/c++/SpellCorrection/SpellCorrection/data/idf.utf8";
const char* const STOP_WORD_PATH = "/home/god/Documents/c++/SpellCorrection/SpellCorrection/data/stop_words.utf8";

SplitTool::SplitTool()
: _Jieba(cppjieba::Jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH))
{}

vector<string> SplitTool::cut(const string & sentence)
{
	vector<string> _words;
	_Jieba.Cut(sentence,_words,true);
	return _words;
}
