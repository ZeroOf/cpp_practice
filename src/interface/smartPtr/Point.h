
#ifndef CPP_PRACTICE_POINT_H
#define CPP_PRACTICE_POINT_H

#include <iostream>

class Point {
public:
    Point(int ix = 0, int iy = 0);

    void display() const;

    ~Point();

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);

private:
    int _ix;
    int _iy;
};

#endif //CPP_PRACTICE_POINT_H
