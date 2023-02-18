#include <iostream>

using namespace std;

class Base1 {
public:
    Base1() {
        cout << "Base1()" << endl;
    }

    virtual
    void func1() {
        cout << "Base1::func1()" << endl;
    }

    virtual
    void func2() {
        cout << "Base1::func2()" << endl;
    }

    ~Base1() { cout << "~Base1()" << endl; }
};

class Base2
        : public Base1 {
public:
    //在构造函数或析构函数内调用虚函数，采用的是静态联编
    Base2() {
        cout << "Base2()" << endl;
        func1();
    }

#if 1
    virtual
    void func1(){
        cout << "Base2::func1()" << endl;
    }
    virtual
    void func2(){
        cout << "Base2::func2()" << endl;
    }
#endif

    ~Base2() {
        func2();
        cout << "~Base2()" << endl;
    }
};

class Derived
        : public Base2 {
public:
    Derived() {
        cout << "Derived()" << endl;
        func1();
    }

    virtual
    void func1() {
        cout << "Derived::func1()" << endl;
    }

    virtual
    void func2() {
        cout << "Derived::func2()" << endl;
    }

    virtual ~Derived() {
        cout << "~Derived()" << endl;
    }
};

int main(void) {
    Derived d;

    return 0;
}
