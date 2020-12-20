
#ifndef CPP_PRACTICE_SUM_H
#define CPP_PRACTICE_SUM_H


#include <iostream>
#include "Add.h"

class Add;

class Sum {
public:
    Sum(Add &p);

private:
    int sum_;
};



#endif //CPP_PRACTICE_SUM_H
