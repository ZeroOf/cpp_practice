#ifndef __SEARCHWORD_H__
#define __SEARCHWORD_H__

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>

using namespace std;

class TextQuery {
public:
    TextQuery(const char *filename);

    void readFile();

    void query(const string &word);

private:
    ifstream _ifs;
    vector<string> _line;
};

#endif
