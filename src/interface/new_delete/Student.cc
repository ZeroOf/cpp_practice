
#include <iostream>
#include "Student.h"

void *Student::operator new(size_t size) {
    std::cout << "Student::new" << std::endl;
    Student *pSt = static_cast<Student *>(malloc(sizeof(Student)));
    return pSt;
}

Student::Student() {
    std::cout << "Student::Student()" << std::endl;
}

void Student::operator delete(void* pClass) {
    std::cout << __func__ << std::endl;
    free(pClass);
}

Student::~Student() {
    std::cout << __func__ << std::endl;
}
