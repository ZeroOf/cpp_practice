
#include "COWString.h"
#include <cstring>

using namespace std;

std::ostream &operator<<(std::ostream &os, const COWString &rhs) {
    os << rhs.pstr_;
    return os;
}

COWString::COWString()
        : pstr_(new char[5]()) {
    cout << "COWString()" << endl;
    pstr_ += 4;
    initRefcount();
}

COWString::COWString(const char *pstr)
        : pstr_(new char[strlen(pstr) + 5]()) {
    cout << "COWString(const char *) " << endl;
    pstr_ += 4;
    initRefcount();
    strcpy(pstr_, pstr);
}

COWString::COWString(const COWString &rhs)
        : pstr_(rhs.pstr_) {
    increaseRefcount();
}

COWString &COWString::operator=(const COWString &rhs) {
    if (this != &rhs) {
        release();//先释放左操作数开辟的空间
        pstr_ = rhs.pstr_;
        increaseRefcount();
    }
    return *this;
}

COWString::~COWString() {
    release();
    cout << "COWStringing()" << endl;
}


COWString::CharProxy COWString::operator[](size_t idx) {
    return CharProxy(idx, *this);
}

char &COWString::CharProxy::operator=(const char &ch) {
    if (self_.refcount() > 1) {
        self_.decreaseRefcount();
        //深拷贝
        char *ptmp = new char[self_.size() + 5]();
        strcpy(ptmp + 4, self_.pstr_);
        self_.pstr_ = ptmp + 4;
        self_.initRefcount();
    }
    self_.pstr_[idx_] = ch;
    return self_.pstr_[idx_];
}

COWString::CharProxy::CharProxy(size_t idx, COWString &self)
        : idx_(idx), self_(self) {}

COWString::CharProxy::operator char() {
    return self_.pstr_[idx_];
}

void COWString::release() {
    decreaseRefcount();
    if (refcount() == 0) {
        delete[] (pstr_ - 4);
        cout << "release data" << endl;
    }
}

void COWString::decreaseRefcount() {
    --(((int *) (pstr_ - 4))[0]);
}

void COWString::increaseRefcount() {
    ++(((int *) (pstr_ - 4))[0]);
}

void COWString::initRefcount() {
    ((int *) (pstr_ - 4))[0] = 1;
}

size_t COWString::size() {
    return strlen(pstr_);
}
