#include "Configuration.h"
#include <fstream>
#include <iostream>
#include <sstream>

using std::stringstream;
using std::ifstream;
using std::string;
using std::unordered_map;
using std::cout;
using std::endl;
using std::getline;

Configuration::Configuration(const string &filepath)
        : _filepath(filepath) {
    ifstream ifs(_filepath);
    if (!ifs) {
        cout << "Configuration open file error!" << endl;
        exit(-1);
    }
    char buf[4096];
    string buf1, buf2;
    stringstream ss;
    ifs.read(buf, sizeof(buf));
    ss << buf;
    while (ss >> buf1, ss >> buf2) {
        _configMap.insert(make_pair(buf1, buf2));
    }
}

unordered_map<string, string> &Configuration::getConfigMap() {
    return _configMap;
}
