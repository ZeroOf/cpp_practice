//
// Created by Will Lee on 2021/10/6.
//

#include <coroutine>

lazy<int> GetNext() {
    int a = 1;
    int b = 1;
    int c = a + b;
    co_return c;

}

int main() {

}