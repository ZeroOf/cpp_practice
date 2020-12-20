
#ifndef CPP_PRACTICE_ADD_H
#define CPP_PRACTICE_ADD_H

#include "Reduce.h"
class Sum;

class Add {
    friend Sum;
public:
    Add();

private:
    friend void print(Add &p);

    friend int Reduce::reduce(Add &add);

private:
    int i_;
    int j_;
};

void print(Add &p);

#endif //CPP_PRACTICE_ADD_H
