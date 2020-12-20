
#include <iostream>
#include "Complex.h"

using namespace std;

Complex::Complex() : Complex(0, 0) {}

Complex::Complex(double dReal, double dImag) : dReal_(dReal), dImag_(dImag) {}

void Complex::Display() {
    if (dReal_ == 0 && dImag_ != 0) {
        cout << dImag_ << "i" << endl;
    } else {
        cout << dReal_;
        if (dImag_ > 0) {
            cout << "+" << dImag_ << "i" << endl;
        } else if (dImag_ < 0) {
            cout << dImag_ << "i" << endl;
        } else {
            cout << endl;
        }
    }
}

std::istream &operator>>(istream &is, Complex &rhs) {
    is >> rhs.dReal_ >> rhs.dImag_;
    return is;
}

std::ostream &operator<<(ostream &os, const Complex &rhs) {
    if(rhs.dReal_ == 0 && rhs.dImag_ != 0)
        os << rhs.dImag_ << "i";
    else
    {
        os << rhs.dReal_;
        if(rhs.dImag_ > 0)
            os << "+" << rhs.dImag_ << "i";
        else if(rhs.dImag_ < 0)
            os << rhs.dImag_ << "i";
    }
    return os;
}

bool operator<(const Complex &lhs, const Complex &rhs) {
    return lhs.dReal_ < rhs.dReal_;
}

Complex Complex::operator++(int) {
    Complex ret(*this);
    ++dReal_;
    ++dImag_;
    return ret;
}

Complex &Complex::operator++() {
    ++dReal_;
    ++dImag_;
    return *this;
}

Complex &Complex::operator+=(const Complex &rhs) {
    dReal_ += rhs.dReal_;
    dImag_ += rhs.dImag_;
    return *this;
}

Complex operator+(const Complex &lhs, const Complex &rhs) {
    return Complex(lhs.dReal_ + rhs.dReal_,
                   lhs.dReal_ + rhs.dImag_);
}