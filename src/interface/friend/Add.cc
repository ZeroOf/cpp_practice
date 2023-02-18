
#include "Add.h"
#include <iostream>

Add::Add()
:i_(3)
,j_(4)
{
    std::cout << "Add()" << std::endl;
}

void print(Add &p) {
    p.i_ = 10;
    p.j_ = 20;
    std::cout << p.i_ << "\t" << p.j_ << std::endl;
}
