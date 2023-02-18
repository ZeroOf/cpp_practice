
#include <iostream>
#include <algorithm>

int main() {
    int array[] = {1, 2, 3, 4};
    while (std::next_permutation(array, array + 4)) {
        for (int i = 0; i < 4; ++i) {
            std::cout << array[i] << "\t";
        }
        std::cout << std::endl;
    }
}