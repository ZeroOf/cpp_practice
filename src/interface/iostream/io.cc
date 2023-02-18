#include <iostream>
#include <string>
#include <limits>

using namespace std;

void printStreamStatus() {
    cout << "cin's badbit = " << cin.bad() << endl;
    cout << "cin's failbit = " << cin.fail() << endl;
    cout << "cin's eofbit = " << cin.eof() << endl;
    cout << "cin's goodbit = " << cin.good() << endl;
}

int test0() {
#if 1
    cout << "sizeof(cin) = " << sizeof(cin) << endl;
    cout << "sizeof(cout) = " << sizeof(cout) << endl;
    printStreamStatus();
    int a;
    while (cin >> a) {
        cout << "a= " << a << endl;
    }
    printStreamStatus();
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << endl;
    printStreamStatus();
#endif

    string s1;
    while (std::getline(cin, s1)) {
        cout << "s1 = " << s1 << endl;
    }
    return 0;
}

void test1() {
    int number, number2;
    while (cin >> number >> number2, !cin.eof()) {
        if (cin.bad()) {
            cout << "cin corrupted!" << endl;
            return;
        } else if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "please input an integer:" << endl;
            continue;
        }
        cout << "number = " << number << " number2 = " << number2<< endl;
    }
}

int main(void) {
    test0();
    test1();
    return 0;
}
