
#include "Sum.h"

Sum::Sum(Add &p) : sum_(p.j_ + p.j_) {
    std::cout << sum_ << std::endl;
}
