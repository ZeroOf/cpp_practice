
#include <iostream>
#include "cast4_io.h"

Cast4IO::operator int() {
  std::cout << __FUNCTION__ << std::endl;
  return iNum_;
}
