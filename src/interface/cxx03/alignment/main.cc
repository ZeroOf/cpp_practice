//
// Created by Will Lee on 2021/9/26.
//

#include <iostream>
#include <stdalign.h>
#include <util.h>


void BitFieldTest() {
  LOG("-------------------------start BitFieldTest-------------------------");
  struct Test {
    int a: 9; // 1st 9bits are a
    int : 7;  // next 7 bits are unused
    int b: 6; // next 6 bits are b
    int : 0;
    int a2: 4;
  };

  LOG_VALUE(sizeof(Test));
  LOG_VALUE(alignof(Test));
  Test test{1, 1};
  test.a = (1 << 17);
  LOG_VALUE(test.a);
  test.a = (1 << 15);
  LOG_VALUE(test.a);

  struct SWith128 {
    __uint128_t i: 8;
    int32_t j: 24;
  };
  LOG_VALUE(sizeof(SWith128));
  LOG_VALUE(alignof(SWith128));
  LOG("---------------- end BitFieldTest----------------");
}


void AlignmentTest() {
  LOG("start AlignmentTest");
  struct S {
    char a;
    char b;
  };
  LOG_VALUE(alignof(S));
  LOG_VALUE(sizeof(S));
  struct X {
    int n;
    char c;
  };
  LOG_VALUE(alignof(X));
  LOG_VALUE(sizeof(X));
  struct D {
    double d;
    char c;
  };

  LOG_VALUE(alignof(D));
  LOG_VALUE(sizeof(D));

  LOG("end AlignmentTest");
}

int main() {
  BitFieldTest();
  AlignmentTest();
  std::cout << "end " << std::endl;
}

