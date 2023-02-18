#include "Point.h"

using namespace std;

Point::Point(int ix, int iy)
        : _ix(ix), _iy(iy) {
    cout << "Point(int,int)" << endl;
}

void Point::display() const {
    cout << "(" << _ix
         << "," << _iy
         << ")" << endl;
}

std::ostream &operator<<(std::ostream &os, const Point &rhs) {
    os << "(" << rhs._ix
       << "," << rhs._iy
       << ")";
    return os;
}

Point::~Point() {
    cout << "~Point()" << endl;
}
