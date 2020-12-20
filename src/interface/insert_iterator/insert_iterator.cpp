#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <set>

using namespace std;

int main(void) {
    vector<int> numbers1{1, 2, 3};
    list<int> numbers2{4, 5, 6};

    copy(numbers2.begin(), numbers2.end(),
         back_insert_iterator<vector<int>>(numbers1));//调用push_back方法，适用的容器有vector,list,deque
    cout << "vector:";
    copy(numbers1.begin(), numbers1.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

    copy(numbers1.begin(), numbers1.end(),
         front_insert_iterator<list<int>>(numbers2));//调用push_front方法，适用的容器有list,deque
    cout << "list:";
    copy(numbers2.begin(), numbers2.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

    auto it = numbers2.begin();
    ++it;
    ++it;
    ++it;
    copy(numbers1.begin(), numbers1.end(),
         insert_iterator<list<int>>(numbers2, it));//调用insert方法，适用的容器有
    cout << "list:";
    copy(numbers2.begin(), numbers2.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

    set<int> numbers3;
    auto sit = numbers3.begin();
    copy(numbers1.begin(), numbers1.end(),
         insert_iterator<set<int>>(numbers3, sit));//调用insert方法，适用于除std::array/std::forward_list以外的所有容器
    cout << "set:";
    copy(numbers3.begin(), numbers3.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

}
