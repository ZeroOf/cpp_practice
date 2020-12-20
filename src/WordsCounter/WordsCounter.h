#ifndef __COUNTWORDS_H__
#define __COUNTWORDS_H__

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

struct cmp {
    bool operator()(pair<string, int> left, pair<string, int> right);
};

class WordsCounter {
public:
    WordsCounter(const char *filename);

    ~WordsCounter();

    void read();

    void save(const char *filename);

private:
    ifstream _ifs;
    priority_queue<pair<string, int>, vector<pair<string, int>>, cmp> _count;
};

#endif
