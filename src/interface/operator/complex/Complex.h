
#ifndef CPP_PRACTICE_COMPLEX_H
#define CPP_PRACTICE_COMPLEX_H

#include <iostream>

class Complex {
public:
    Complex(double dReal, double dImag);

    Complex();

    void Display();

    Complex &operator+=(const Complex &rhs);

    Complex &operator++();

    Complex operator++(int);

    friend Complex operator+(const Complex &lhs, const Complex &rhs);

    friend bool operator<(const Complex &lhs, const Complex &rhs);

    friend std::ostream & operator<<(std::ostream &os, const Complex& rhs);

    friend std::istream&  operator>>(std::istream& is, Complex& rhs);

private:
    double dReal_;
    double dImag_;
};

//Complex operator+(const Complex &lhs, const Complex &rhs);

#endif //CPP_PRACTICE_COMPLEX_H