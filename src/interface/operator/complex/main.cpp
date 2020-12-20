#include "Complex.h"
#include <iostream>

using namespace std;

int main() {
    std::cout << "hello operator " << std::endl;
    Complex a(-2, -5), b(1, 2);
    a.Display();
    b.Display();
    b += b;
    b.Display();

    Complex c = a + b;
    c.Display();
}
