
#include <iostream>
#include "Cast.h"

using namespace std;

Cast::Cast(int iNum) : iNum_(iNum) {}

Cast::Cast(double iNum) : iNum_(iNum) {
    std::cout << "Cast(double)" << std::endl;
}

Cast::operator int() {
    cout << __FUNCTION__ << endl;
    return iNum_;
}

Cast::operator double() {
    cout << __FUNCTION__ << endl;
    return iNum_;
}
