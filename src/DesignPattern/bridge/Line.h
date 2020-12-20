
#ifndef CPP_PRACTICE_LINE_H
#define CPP_PRACTICE_LINE_H


class Line {
public:
    Line(int x1, int y1, int x2, int y2);

    virtual ~Line();

    void Display() const;;

private:
    class LineImpl;

    LineImpl *pImpl_;
};


#endif //CPP_PRACTICE_LINE_H
