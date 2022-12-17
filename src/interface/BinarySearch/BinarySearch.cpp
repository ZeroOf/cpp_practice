#include <cstdlib>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main(void) {
    vector<int> numbers;
    srand(time(nullptr));
    for (int i = 0; i < 30; i++) {
        numbers.push_back(rand() % 10);
        //sleep(1);
    }
    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    sort(numbers.begin(), numbers.end());
    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << boolalpha << binary_search(numbers.begin(), numbers.end(), 9) << endl;
    cout << boolalpha << binary_search(numbers.begin(), numbers.end(), 2) << endl;

    auto it1 = lower_bound(numbers.begin(), numbers.end(), 2);
    auto it2 = upper_bound(numbers.begin(), numbers.end(), 2);
    while (it1 != it2) {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;

    auto ret = equal_range(numbers.begin(), numbers.end(), 2);
    cout << ret.second - ret.first << endl;
    while (ret.first != ret.second) {
        cout << *ret.first << " ";
        ++ret.first;
    }
    cout << endl;
    return 0;
}
