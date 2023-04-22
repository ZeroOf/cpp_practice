#include "SplitTool.h"
#include <vector>

using std::vector;
using std::string;

const char* const DICT_PATH = "../../data/jieba.dict.utf8";
const char* const HMM_PATH = "../../data/hmm_model.utf8";
const char* const USER_DICT_PATH = "../../data/user.dict.utf8";
const char* const IDF_PATH = "../../data/idf.utf8";
const char* const STOP_WORD_PATH = "../../data/stop_words.utf8";

SplitTool::SplitTool()
: _jieba(cppjieba::Jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH))
{
}

vector<string> & SplitTool::cut(const string & sentence)
{
	_jieba.Cut(sentence,_words,true);
	return _words;
}

