
#include <iostream>
#include <ostream>
#include "Line.h"

class Line::LineImpl {
    class Point {
    public:
        Point(int iX, int iY) : iX_(iX), iY_(iY) {}

        void Print() const {
            std::cout << "(" << iX_ << "," << iY_ << ")";
        }

    public:
    private:
        int iX_;
        int iY_;
    };

public:
    LineImpl(int x1, int y1, int x2, int y2)
            : p1_(x1, y1), p2_(x2, y2) {}

    void Display() const {
        p1_.Print();
        std::cout << "--->";
        p2_.Print();
        std::cout << std::endl;
    }

private:
    Point p1_;
    Point p2_;
};

Line::~Line() {
    std::cout << __FUNCTION__ << std::endl;
    if (pImpl_ != nullptr) {
        delete pImpl_;
    }

}
/**
 * @class LineImpl
 * @brief Implementation class for Line
 *
 * LineImpl is responsible for storing the coordinates of a line and providing necessary operations.
 */
//
Line::Line(int x1, int y1, int x2, int y2) : pImpl_(new LineImpl(x1, y1, x2, y2)) {
    std::cout << __FUNCTION__ << std::endl;
}

void Line::Display() const {
    if (pImpl_ != nullptr) {
        pImpl_->Display();
    }
}

