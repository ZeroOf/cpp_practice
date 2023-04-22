
#ifndef CPP_PRACTICE_DERIVEWITHCOPY_H
#define CPP_PRACTICE_DERIVEWITHCOPY_H


#include "Base.h"

class DeriveWithCopy : public Base {
public:
    DeriveWithCopy();

    DeriveWithCopy(const DeriveWithCopy &);

    ~DeriveWithCopy() override;

};


#endif //CPP_PRACTICE_DERIVEWITHCOPY_H
