#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::istream_iterator;
using std::ostream_iterator;

//用容器的观点来看待输入输出流
int main(void) {
    vector<int> numbers;
    //输入流迭代器适配器
    istream_iterator<int> isi(std::cin);
//    std::copy(isi, istream_iterator<int>(), numbers.begin());//插入迭代器
    std::copy(isi, istream_iterator<int>(), std::back_inserter(numbers));//插入迭代器

    std::copy(numbers.begin(), numbers.end(),
              ostream_iterator<int>(cout, ","));
    cout << endl;

    return 0;
}
