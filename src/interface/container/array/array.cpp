#include <iostream>
#include <list>
#include <array>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    array<int, 3> array1;
    cout << array1.size() << endl;
    cout << array1.max_size() << endl;
    copy(array1.begin(), array1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
