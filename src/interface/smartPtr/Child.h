
#ifndef CPP_PRACTICE_CHILD_H
#define CPP_PRACTICE_CHILD_H

#include <memory>

class Parent;
class Child {
public:
    Child();

    ~Child();

    std::shared_ptr<Parent> _parentPtr;
};


#endif //CPP_PRACTICE_CHILD_H
