//
// Created by Will Lee on 2023/7/30.
//

#ifndef CPP_PRACTICE_SRC_STL_BASE_ALLOCATOR_ALLOCATOR_H_
#define CPP_PRACTICE_SRC_STL_BASE_ALLOCATOR_ALLOCATOR_H_

#include <cstddef>
template<class T>
class Allocator {
 public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using size_type = size_t;

  pointer allocate(size_type n, const void *hint=0) {
    return static_cast<pointer>(::operator new(n * sizeof(T)));
  }

  void deallocate(pointer p, size_type) {
    ::operator delete(p);
  }

  void construct(pointer p, const T& val) {
    new (p) T(val);
  }

  void destroy(pointer p) {
    p->~T();
  }
};

#endif //CPP_PRACTICE_SRC_STL_BASE_ALLOCATOR_ALLOCATOR_H_
