
#ifndef CPP_PRACTICE_ARRAY_H
#define CPP_PRACTICE_ARRAY_H

#include <cstddef>

template<typename T>
class Array {
public:
    explicit Array(size_t size) : size_(size), data_(new T[size_]) {}

    T &operator[](size_t pos);

    virtual ~Array();

private:
    size_t size_;
    T *data_;
};

template<typename T>
T &Array<T>::operator[](size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("out of range");
    }
    return data_[pos];
}

template<typename T>
Array<T>::~Array() {
    if (data_ != nullptr) {
        delete []data_;
    }
    size_ = 0;
}


#endif //CPP_PRACTICE_ARRAY_H
