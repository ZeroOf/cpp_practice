
#ifndef CPP_PRACTICE_SRC_UTIL_UTIL_H_
#define CPP_PRACTICE_SRC_UTIL_UTIL_H_

#include <iostream>

#define LOG(msg) std::cout << __FILE_NAME__ << ":" << __LINE__ << ":" << __func__ << ": " <<  msg << std::endl
#define LOG_VALUE(value) LOG(#value << " : " << value)

#endif //CPP_PRACTICE_SRC_UTIL_UTIL_H_
