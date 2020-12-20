
#ifndef CPP_PRACTICE_VARIADIC_H
#define CPP_PRACTICE_VARIADIC_H

#include <iostream>

template<typename... Args>
//Args称为模板参数包
void display(Args... args)//args 称为函数参数包
{
    //获取可变参数的用法
    std::cout << "sizeof(Args) = " << sizeof...(Args) << std::endl;
    std::cout << "sizeof(args) = " << sizeof...(args) << std::endl;
}

void print() {
    std::cout << std::endl;
}

template<typename T, typename... Args>
void print(T t, Args... args) {
    std::cout << t << std::endl;
    print(args...);//函数参数包扩展 print(arg1, arg2, ..., argN)
}

#endif //CPP_PRACTICE_VARIADIC_H
