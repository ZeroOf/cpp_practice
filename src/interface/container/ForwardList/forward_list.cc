#include <iostream>
#include <forward_list>

using namespace std;

int main() {
    forward_list<int> fl;
    cout << "size " << fl.max_size() << endl;
    fl.push_front(1);
    cout << *fl.begin() << " " << endl;
    return 0;
}
