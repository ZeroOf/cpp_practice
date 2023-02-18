#include "Add.h"
#include "Sum.h"

int main() {
    Add p;
    print(p);
    Sum test(p);
    Reduce reduce;
    std::cout << reduce.reduce(p) << std::endl;
    return 0;
}