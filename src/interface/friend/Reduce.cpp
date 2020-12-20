
#include "Reduce.h"
#include "Add.h"

int Reduce::reduce(Add &add) {
    return add.j_ - add.i_;
}
