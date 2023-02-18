
#include <iostream>

void test() {
    std::cout << __func__ << std::endl;
}

int main() {
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    ::atexit(test);
    std::cout << __func__ << std::endl;
}