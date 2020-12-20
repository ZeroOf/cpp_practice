#include <iostream>

using std::cout;
using std::endl;

class Stack {
public:
    Stack(int x = 1, int y = 2)
            : _i(x), _j(y) {
        cout << "Stack()" << endl;
    }

    void print() {
        cout << " _i = " << _i
             << " _j = " << _j << endl;
    }

    ~Stack() {
        cout << "~Stack" << endl;
    }

private:
    void *operator new(size_t sz);

    void operator delete(void *p);

    int _i;
    int _j;
};

int main() {
    Stack test;
    test.print();
    return 0;
}
