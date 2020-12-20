
#ifndef CPP_PRACTICE_STUDENT_H
#define CPP_PRACTICE_STUDENT_H


#include <string>

class Student {
public:
    Student();
    void* operator new(size_t size);

    void operator delete(void* pClass);

    virtual ~Student();

private:
    int id_;
    std::string name_;
};


#endif //CPP_PRACTICE_STUDENT_H
