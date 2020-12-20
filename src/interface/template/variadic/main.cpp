#include "variadic.hpp"
#include <string>

int TestDisplay(void)
{
    std::cout << "test display" << std::endl;
    display(1);
    display(1, 'a');
    display(1, 'a', std::string("hell"));
    display(1, 'a', "hell", 1.1);
    return 0;
}


void TestPrint(void)
{
    std::cout << __func__ << std::endl;
    print(1, 2, 3 ,4);
    print(2, 3, 4);
    print(3, 4);
    print(4);
    print();
}


int main() {
    TestPrint();
    TestDisplay();
}
