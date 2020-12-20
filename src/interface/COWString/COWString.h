
#ifndef CPP_PRACTICE_COWSTRING_H
#define CPP_PRACTICE_COWSTRING_H

#include <cstdlib>
#include <iostream>

class COWString {
    class CharProxy {
    public:
        CharProxy(size_t idx, COWString &self);

        operator char();

        char &operator=(const char &ch);

    private:
        size_t idx_;
        COWString &self_;
    };

public:
    COWString();

    explicit COWString(const char *);

    COWString(const COWString &rhs);

    COWString &operator=(const COWString &rhs);

    ~COWString();

    const char &operator[](size_t idx) const { return pstr_[idx]; }
    //char & operator[](size_t idx);

    CharProxy operator[](size_t idx);

    size_t size();

    const char *c_str() const { return pstr_; }

    size_t refcount() const { return ((int *) (pstr_ - 4))[0]; }

    friend std::ostream &operator<<(std::ostream &os, const COWString &rhs);

private:
    void initRefcount();

    void increaseRefcount();

    void decreaseRefcount();

    void release();

private:
    char *pstr_;
};

#endif //CPP_PRACTICE_COWSTRING_H
