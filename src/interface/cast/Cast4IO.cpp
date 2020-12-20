
#include <iostream>
#include "Cast4IO.h"

Cast4IO::operator int() {
    std::cout << __FUNCTION__ << std::endl;
    return iNum_;
}
