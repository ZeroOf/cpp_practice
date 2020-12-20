
#ifndef CPP_PRACTICE_PARENT_H
#define CPP_PRACTICE_PARENT_H

#include <memory>

class Child;

class Parent {

public:
    Parent();

    ~Parent();

    std::shared_ptr<Child> _childPtr;
};


#endif //CPP_PRACTICE_PARENT_H
