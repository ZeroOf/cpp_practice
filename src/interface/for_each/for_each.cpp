#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;


void test(void) {
    cout << "test()" << endl;
}

typedef void(*Function)(void);

int test0(void) {
    Function f1 = test;
    f1();
    return 0;
}

void print(int number) {
    cout << number << " ";
}

void test1(void) {
    int a = 10;
    int b = 100;
    vector<int> numbers{1, 2, 3, 4, 5, 6};
    for_each(numbers.begin(), numbers.end(), print);//可读性不强
    cout << endl;
    for_each(numbers.begin(), numbers.end(), [&](int number) {// lambda表达式代表的是匿名函数
        cout << number << " a = " << a++ << " ,b = " << b++ << endl;
    });
    cout << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

void test2(void) {
    vector<int> numbers{1, 2, 3, 4, 5, 6};
    std::replace(numbers.begin(), numbers.end(), 3, 7);
    std::less<int> lt;
    std::replace_if(numbers.begin(), numbers.end(), std::bind1st(lt, 3), 7);//lt(3, x)  函数适配(绑定)器
    std::replace_if(numbers.begin(), numbers.end(), std::bind2nd(lt, 3), 7);//lt(x, 3)

    for (auto &elem : numbers) {
        cout << elem << " ";
    }
    cout << endl;
    //std::replace_if();
}

int main(void) {
    //test1();
    test2();
    return 0;
}
