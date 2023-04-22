
#include "WordsSearcher.h"

TextQuery::TextQuery(const char *filename) {
    _ifs.open(filename);
    if (!_ifs) {
        cout << "file open error!" << endl;
        exit(-1);
    }
}

void TextQuery::readFile() {
    string tmp;
    while (getline(_ifs, tmp)) {
        _line.push_back(tmp);
    }
    _ifs.close();
}

void TextQuery::query(const string &word) {
    int count = 0;
    string tmp;
    int flag = 0;
    string ret("\t");
    stringstream ss;
    ostream_iterator<string> il(ss, "\t\t");
    for (size_t i = 0; i < _line.size(); i++) {
        flag = 0;
        stringstream ss(_line[i]);
        while (ss >> tmp) {
            if (tmp == word) {
                ++count;
                flag++;
            }
        }
        if (flag) {
            char wline[50] = {0};
            sprintf(wline, "%s%lu%s", "(line ", i, " )\t");
            ret += wline;
            ret += _line[i];
            ret += "\n\t";
        }
    }
    cout << word << " occurs " << count << " times" << endl;
    cout << ret << endl;;
}
