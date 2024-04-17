#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

#define FILENAME "test.txt"

//用2个vector 存储 单词 和对应词频 
//每次从文件中读取一行处理
//每次读取一词比较 存在加对应词频 不存在插入单词 插入词频置1
class Dictionary {
 public:
  Dictionary(const char *filename) {
    _ifs = ifstream(filename);
    if (!_ifs) {
      cout << "open error" << endl;
      return;
    }
    cout << "Dictionary()" << endl;
  }

  void read(void);

  void store(void);

 private:
  ifstream _ifs;
  vector<string> _Dic;
  vector<int> _count;
};

//文件特点:单词完整
//
void Dictionary::store() {
  ofstream ofs(FILENAME, std::ios::app);
  size_t i;
  for (i = 0; i < _Dic.size(); i++) {
    if (!isdigit(_Dic[i][0]))
      ofs << _Dic[i] << " " << _count[i] << "\n";
  }
  ofs.close();
}

void Dictionary::read() {
  int words = 0;
  int line = 0;
  size_t i;
  string buf;
  string buf_word;
  while (std::getline(_ifs, buf)) {
    line++;
    stringstream ss(buf);
    while (ss >> buf_word) {
      words++;
      for (i = 0; i < _Dic.size(); i++) {
        if (_Dic[i] == buf_word) {
          _count[i]++;
          break;
        }
      }
      if (i == _Dic.size()) {
        _Dic.push_back(buf_word);
        _count.push_back(1);
      }
    }
    buf_word.clear();
    buf.clear();
  }
  cout << "line :" << line << endl;
  cout << "word :" << words << endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "args error" << endl;
    return -1;
  }
  Dictionary test(argv[1]);
  test.read();
  test.store();
  return 0;
}
