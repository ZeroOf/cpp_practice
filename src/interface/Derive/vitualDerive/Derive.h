
#ifndef CPP_PRACTICE_DERIVE_H
#define CPP_PRACTICE_DERIVE_H


#include "DeriveA.h"
#include "DeriveB.h"

class Derive : public DeriveA, public DeriveB {
public:
    Derive();

    virtual ~Derive();
    int a;
};


#endif //CPP_PRACTICE_DERIVE_H
