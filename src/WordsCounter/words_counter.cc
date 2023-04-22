#include "WordsCounter.h"

WordsCounter::WordsCounter(const char *filename) {
    _ifs.open(filename);
    if (!_ifs) {
        cout << "open file error!" << endl;
        exit(-1);
    }
}

WordsCounter::~WordsCounter() {
    _ifs.close();
    cout << "~WordsCounter()" << endl;
}

void WordsCounter::read() {
    map<string, int> count;
    string tmp;
    string word;
    while (getline(_ifs, tmp)) {
        stringstream ss(tmp);
        while (ss >> word) {
            ++count[word];
        }
    }
    for (auto &pr: count) {
        _count.push(pr);
    }
}

void WordsCounter::save(const char *filename) {
    ofstream ofs(filename);
    while (!_count.empty()) {
        ofs << _count.top().first << "\t" << _count.top().second << endl;
        _count.pop();
    }
    ofs.close();
}

bool cmp::operator()(pair<string, int> left, pair<string, int> right) {
    return left.second > right.second;
}
