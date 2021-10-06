//
// Created by Will Lee on 2021/10/5.
//

#ifndef CPP_PRACTICE_TURTLE_H
#define CPP_PRACTICE_TURTLE_H

class Turtle {
public:
    virtual ~Turtle() {}

    virtual void PenUp() = 0;

    virtual void PenDown() = 0;

    virtual void Forward(int distance) = 0;

    virtual void Turn(int degrees) = 0;

    virtual void GoTo(int x, int y) = 0;

    virtual int GetX() const = 0;

    virtual int GetY() const = 0;
};

#endif //CPP_PRACTICE_TURTLE_H
