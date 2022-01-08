#include <iostream>

using namespace std;

void display2(int &&m) {
  cout << "&& " << m << endl;
}

void display(int &&m) {
    cout << "&& " << m << endl;
  display2(std::forward<int>(m));
  display2(std::move(m));
}

void display(const int &m) {
    cout << "& " << m << endl;
}

int main() {
    int a = 1;
    display(2);
    display(a);
    int b = 2;
    int *pflag = &a;

    cout << "&( ++a) " << &(++a) << endl;;

    display(b);
    cout << " pflag" << pflag << endl;
    cout << "&pflag" << &pflag << endl;
    int &&x = 1;
    return 0;

}
